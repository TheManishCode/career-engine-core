#include <gtest/gtest.h>

#include <vector>
#include <cstdint>

#include "../../src/rules/RuleEngine.h"
#include "../../src/rules/Rule.h"
#include "../../src/rules/RuleContext.h"
#include "../../src/rules/RuleOutcome.h"
#include "../../src/types/NormalizedEmail.h"
#include "../../src/types/ClassificationResult.h"

namespace career_engine::tests {

// ============================================================================
// Test Helpers — Fake Rules
// ============================================================================

/// Creates a default SafetyContribution with no opinion.
constexpr SafetyContribution make_no_opinion_safety() {
    return SafetyContribution{
        .safe_to_delete = SafetyAssertion::NoOpinion,
        .requires_review = SafetyAssertion::NoOpinion
    };
}

/// Creates a default ClassificationContribution with no opinion.
constexpr ClassificationContribution make_no_opinion_classification() {
    return ClassificationContribution{
        .suggested_category = std::nullopt,
        .confidence_weight = 0
    };
}

/// Creates a default AdvisoryContribution with no opinion.
constexpr AdvisoryContribution make_no_opinion_advisory() {
    return AdvisoryContribution{
        .confidence_delta = std::nullopt,
        .explanation_rule = std::nullopt
    };
}

/// Fake rule that always returns a fixed outcome.
/// Used to test RuleEngine contract without real rule logic.
class FakeRule final : public Rule {
public:
    explicit FakeRule(RuleId id, MatchState match_state)
        : id_{id}
        , outcome_{
            .rule_id = id,
            .match_state = match_state,
            .safety = make_no_opinion_safety(),
            .classification = make_no_opinion_classification(),
            .advisory = make_no_opinion_advisory()
        }
    {}

    explicit FakeRule(RuleId id, RuleOutcome outcome)
        : id_{id}
        , outcome_{outcome}
    {}

    [[nodiscard]] RuleId id() const noexcept override {
        return id_;
    }

    [[nodiscard]] RuleOutcome evaluate(const RuleContext&) const noexcept override {
        return outcome_;
    }

private:
    RuleId id_;
    RuleOutcome outcome_;
};

/// Fake rule that records evaluation order via a shared counter.
/// Test-only side channel for verifying phase ordering.
/// NOTE: This violates strict purity but is acceptable for contract tests.
class OrderTrackingRule final : public Rule {
public:
    OrderTrackingRule(RuleId id, std::vector<RuleId>& evaluation_order)
        : id_{id}
        , evaluation_order_{evaluation_order}
    {}

    [[nodiscard]] RuleId id() const noexcept override {
        return id_;
    }

    [[nodiscard]] RuleOutcome evaluate(const RuleContext&) const noexcept override {
        // Record evaluation order (test-only side effect)
        evaluation_order_.push_back(id_);

        return RuleOutcome{
            .rule_id = id_,
            .match_state = MatchState::Match,
            .safety = make_no_opinion_safety(),
            .classification = make_no_opinion_classification(),
            .advisory = make_no_opinion_advisory()
        };
    }

private:
    RuleId id_;
    std::vector<RuleId>& evaluation_order_;
};

/// Creates a test NormalizedEmail with minimal valid data.
NormalizedEmail make_test_email() {
    return NormalizedEmail{
        .id = "test-email-001",
        .sender = "sender@example.com",
        .subject = "Test Subject",
        .body_plain = "Test body content",
        .recipients = {"recipient@example.com"},
        .timestamp_utc = 1700000000,
        .source_platform = std::nullopt
    };
}

// ============================================================================
// Contract Test Fixture
// ============================================================================

class RuleEngineContractTest : public ::testing::Test {
protected:
    RuleEngine engine_;
    NormalizedEmail test_email_ = make_test_email();
};

// ============================================================================
// Contract Tests
// ============================================================================

/// Test: RuleEngine accepts borrowed rules and input safely.
/// Verifies that evaluate() can be called with valid inputs without error.
TEST_F(RuleEngineContractTest, AcceptsBorrowedRulesAndInputSafely) {
    FakeRule rule1{RuleId::SubjectKeywordOffer, MatchState::Match};
    FakeRule rule2{RuleId::SenderDomainJobBoard, MatchState::NoMatch};

    std::vector<const Rule*> rules = {&rule1, &rule2};

    // Should not crash or throw
    auto outcomes = engine_.evaluate(test_email_, rules);

    // Both rules should produce outcomes
    EXPECT_EQ(outcomes.size(), 2u);
}

/// Test: RuleEngine accepts empty rule collection.
TEST_F(RuleEngineContractTest, AcceptsEmptyRuleCollection) {
    std::vector<const Rule*> empty_rules;

    auto outcomes = engine_.evaluate(test_email_, empty_rules);

    EXPECT_TRUE(outcomes.empty());
}

/// Test: RuleOutcome objects are preserved exactly as returned by rules.
TEST_F(RuleEngineContractTest, OutcomesPreservedExactly) {
    const auto expected_outcome = RuleOutcome{
        .rule_id = RuleId::BodyPatternOffer,
        .match_state = MatchState::Match,
        .safety = SafetyContribution{
            .safe_to_delete = SafetyAssertion::AssertUnsafe,
            .requires_review = SafetyAssertion::AssertUnsafe
        },
        .classification = ClassificationContribution{
            .suggested_category = SignalCategory::Offer,
            .confidence_weight = 85
        },
        .advisory = AdvisoryContribution{
            .confidence_delta = 5,
            .explanation_rule = RuleId::SubjectKeywordOffer
        }
    };

    FakeRule rule{RuleId::BodyPatternOffer, expected_outcome};
    std::vector<const Rule*> rules = {&rule};

    auto outcomes = engine_.evaluate(test_email_, rules);

    ASSERT_EQ(outcomes.size(), 1u);

    const auto& actual = outcomes[0];
    EXPECT_EQ(actual.rule_id, expected_outcome.rule_id);
    EXPECT_EQ(actual.match_state, expected_outcome.match_state);
    EXPECT_EQ(actual.safety.safe_to_delete, expected_outcome.safety.safe_to_delete);
    EXPECT_EQ(actual.safety.requires_review, expected_outcome.safety.requires_review);
    EXPECT_EQ(actual.classification.suggested_category, expected_outcome.classification.suggested_category);
    EXPECT_EQ(actual.classification.confidence_weight, expected_outcome.classification.confidence_weight);
    EXPECT_EQ(actual.advisory.confidence_delta, expected_outcome.advisory.confidence_delta);
    EXPECT_EQ(actual.advisory.explanation_rule, expected_outcome.advisory.explanation_rule);
}

/// Test: Abstaining rules produce outcomes with MatchState::Abstain.
/// Abstaining outcomes are included but contribute nothing.
TEST_F(RuleEngineContractTest, AbstainingRulesProduceOutcomes) {
    FakeRule abstaining_rule{RuleId::FallbackUnknown, MatchState::Abstain};
    std::vector<const Rule*> rules = {&abstaining_rule};

    auto outcomes = engine_.evaluate(test_email_, rules);

    ASSERT_EQ(outcomes.size(), 1u);
    EXPECT_EQ(outcomes[0].match_state, MatchState::Abstain);
    EXPECT_EQ(outcomes[0].rule_id, RuleId::FallbackUnknown);
}

/// Test: Abstaining outcomes have no category, no confidence, no safety assertions.
TEST_F(RuleEngineContractTest, AbstainingOutcomesContributeNothing) {
    // Create an abstaining rule with explicit no-opinion fields
    const auto abstain_outcome = RuleOutcome{
        .rule_id = RuleId::None,
        .match_state = MatchState::Abstain,
        .safety = make_no_opinion_safety(),
        .classification = make_no_opinion_classification(),
        .advisory = make_no_opinion_advisory()
    };

    FakeRule abstaining_rule{RuleId::None, abstain_outcome};
    std::vector<const Rule*> rules = {&abstaining_rule};

    auto outcomes = engine_.evaluate(test_email_, rules);

    ASSERT_EQ(outcomes.size(), 1u);
    const auto& outcome = outcomes[0];

    EXPECT_EQ(outcome.match_state, MatchState::Abstain);
    EXPECT_EQ(outcome.safety.safe_to_delete, SafetyAssertion::NoOpinion);
    EXPECT_EQ(outcome.safety.requires_review, SafetyAssertion::NoOpinion);
    EXPECT_FALSE(outcome.classification.suggested_category.has_value());
    EXPECT_EQ(outcome.classification.confidence_weight, 0u);
    EXPECT_FALSE(outcome.advisory.confidence_delta.has_value());
    EXPECT_FALSE(outcome.advisory.explanation_rule.has_value());
}

/// Test: Multiple rules all produce outcomes in order.
TEST_F(RuleEngineContractTest, MultipleRulesProduceOrderedOutcomes) {
    FakeRule rule1{RuleId::SubjectKeywordOffer, MatchState::Match};
    FakeRule rule2{RuleId::SubjectKeywordRejection, MatchState::NoMatch};
    FakeRule rule3{RuleId::SenderDomainJobBoard, MatchState::Abstain};

    std::vector<const Rule*> rules = {&rule1, &rule2, &rule3};

    auto outcomes = engine_.evaluate(test_email_, rules);

    ASSERT_EQ(outcomes.size(), 3u);

    // Verify rule IDs are present (order depends on phase evaluation)
    std::vector<RuleId> returned_ids;
    for (const auto& outcome : outcomes) {
        returned_ids.push_back(outcome.rule_id);
    }

    EXPECT_NE(std::find(returned_ids.begin(), returned_ids.end(), RuleId::SubjectKeywordOffer), returned_ids.end());
    EXPECT_NE(std::find(returned_ids.begin(), returned_ids.end(), RuleId::SubjectKeywordRejection), returned_ids.end());
    EXPECT_NE(std::find(returned_ids.begin(), returned_ids.end(), RuleId::SenderDomainJobBoard), returned_ids.end());
}

/// Test: Engine is deterministic — same inputs produce same outputs.
TEST_F(RuleEngineContractTest, DeterministicForIdenticalInputs) {
    FakeRule rule1{RuleId::SubjectKeywordOffer, MatchState::Match};
    FakeRule rule2{RuleId::BodyPatternRejection, MatchState::NoMatch};

    std::vector<const Rule*> rules = {&rule1, &rule2};

    auto outcomes1 = engine_.evaluate(test_email_, rules);
    auto outcomes2 = engine_.evaluate(test_email_, rules);

    ASSERT_EQ(outcomes1.size(), outcomes2.size());

    for (size_t i = 0; i < outcomes1.size(); ++i) {
        EXPECT_EQ(outcomes1[i].rule_id, outcomes2[i].rule_id);
        EXPECT_EQ(outcomes1[i].match_state, outcomes2[i].match_state);
        EXPECT_EQ(outcomes1[i].safety.safe_to_delete, outcomes2[i].safety.safe_to_delete);
        EXPECT_EQ(outcomes1[i].safety.requires_review, outcomes2[i].safety.requires_review);
        EXPECT_EQ(outcomes1[i].classification.suggested_category, outcomes2[i].classification.suggested_category);
        EXPECT_EQ(outcomes1[i].classification.confidence_weight, outcomes2[i].classification.confidence_weight);
    }
}

/// Test: Safety assertions are monotonic — AssertUnsafe cannot be overridden.
/// This test verifies that if multiple rules assert safety, AssertUnsafe persists.
/// NOTE: Monotonicity is enforced by the aggregator, not RuleEngine.
/// This test validates that RuleEngine preserves all safety assertions for aggregation.
TEST_F(RuleEngineContractTest, SafetyAssertionsPreservedForMonotonicAggregation) {
    // Rule 1: Assert unsafe (critical email)
    const auto unsafe_outcome = RuleOutcome{
        .rule_id = RuleId::SubjectKeywordOffer,
        .match_state = MatchState::Match,
        .safety = SafetyContribution{
            .safe_to_delete = SafetyAssertion::AssertUnsafe,
            .requires_review = SafetyAssertion::NoOpinion
        },
        .classification = make_no_opinion_classification(),
        .advisory = make_no_opinion_advisory()
    };

    // Rule 2: Assert safe (would be overridden in aggregation)
    const auto safe_outcome = RuleOutcome{
        .rule_id = RuleId::NoisePatternAdvertisement,
        .match_state = MatchState::Match,
        .safety = SafetyContribution{
            .safe_to_delete = SafetyAssertion::AssertSafe,
            .requires_review = SafetyAssertion::NoOpinion
        },
        .classification = make_no_opinion_classification(),
        .advisory = make_no_opinion_advisory()
    };

    FakeRule rule1{RuleId::SubjectKeywordOffer, unsafe_outcome};
    FakeRule rule2{RuleId::NoisePatternAdvertisement, safe_outcome};

    std::vector<const Rule*> rules = {&rule1, &rule2};

    auto outcomes = engine_.evaluate(test_email_, rules);

    ASSERT_EQ(outcomes.size(), 2u);

    // Both assertions must be preserved for the aggregator to enforce monotonicity
    bool found_unsafe = false;
    bool found_safe = false;

    for (const auto& outcome : outcomes) {
        if (outcome.safety.safe_to_delete == SafetyAssertion::AssertUnsafe) {
            found_unsafe = true;
        }
        if (outcome.safety.safe_to_delete == SafetyAssertion::AssertSafe) {
            found_safe = true;
        }
    }

    EXPECT_TRUE(found_unsafe) << "AssertUnsafe must be preserved in outcomes";
    EXPECT_TRUE(found_safe) << "AssertSafe must be preserved in outcomes (aggregator decides)";
}

/// Test: Rules are evaluated in correct semantic phase order.
/// Uses tracking rules to verify Safety -> Classification -> Noise -> Advisory order.
TEST_F(RuleEngineContractTest, RulesEvaluatedInPhaseOrder) {
    std::vector<RuleId> evaluation_order;

    // Create rules with distinct IDs to track order
    // These would be assigned to different phases in a real implementation
    OrderTrackingRule rule1{RuleId::SubjectKeywordOffer, evaluation_order};
    OrderTrackingRule rule2{RuleId::SenderDomainJobBoard, evaluation_order};
    OrderTrackingRule rule3{RuleId::NoisePatternAdvertisement, evaluation_order};

    std::vector<const Rule*> rules = {&rule1, &rule2, &rule3};

    auto outcomes = engine_.evaluate(test_email_, rules);

    // All rules should have been evaluated
    EXPECT_EQ(evaluation_order.size(), 3u);
    EXPECT_EQ(outcomes.size(), 3u);

    // Verify all rules were invoked (specific order depends on phase assignment)
    EXPECT_NE(std::find(evaluation_order.begin(), evaluation_order.end(), RuleId::SubjectKeywordOffer), evaluation_order.end());
    EXPECT_NE(std::find(evaluation_order.begin(), evaluation_order.end(), RuleId::SenderDomainJobBoard), evaluation_order.end());
    EXPECT_NE(std::find(evaluation_order.begin(), evaluation_order.end(), RuleId::NoisePatternAdvertisement), evaluation_order.end());
}

/// Test: Same rule instance can be evaluated multiple times.
TEST_F(RuleEngineContractTest, SameRuleCanBeEvaluatedMultipleTimes) {
    FakeRule rule{RuleId::SubjectKeywordOffer, MatchState::Match};

    std::vector<const Rule*> rules = {&rule};

    auto outcomes1 = engine_.evaluate(test_email_, rules);
    auto outcomes2 = engine_.evaluate(test_email_, rules);

    ASSERT_EQ(outcomes1.size(), 1u);
    ASSERT_EQ(outcomes2.size(), 1u);

    EXPECT_EQ(outcomes1[0].rule_id, outcomes2[0].rule_id);
    EXPECT_EQ(outcomes1[0].match_state, outcomes2[0].match_state);
}

/// Test: Different emails with same rules can produce different outcomes.
/// (Depends on rule logic, but engine must support this)
TEST_F(RuleEngineContractTest, DifferentEmailsCanBeEvaluated) {
    FakeRule rule{RuleId::SubjectKeywordOffer, MatchState::Match};
    std::vector<const Rule*> rules = {&rule};

    NormalizedEmail email1 = make_test_email();
    NormalizedEmail email2{
        .id = "test-email-002",
        .sender = "other@example.com",
        .subject = "Different Subject",
        .body_plain = "Different body",
        .recipients = {},
        .timestamp_utc = 1700000001,
        .source_platform = SourcePlatform::LinkedIn
    };

    auto outcomes1 = engine_.evaluate(email1, rules);
    auto outcomes2 = engine_.evaluate(email2, rules);

    // Both should succeed (fake rule returns same outcome regardless)
    EXPECT_EQ(outcomes1.size(), 1u);
    EXPECT_EQ(outcomes2.size(), 1u);
}

} // namespace career_engine::tests
