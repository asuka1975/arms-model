#pragma once

#include <array>
#include <vector>
#include <random>
#include "vector.h"

#define AGENT_NUM 3
#define RULE_NUM 3

class Model {
public:
	Model(std::initializer_list<vector> args);
	const std::vector<double> GetAgentRecord(int idx);
	vector GetCurrentStep();
	void AdvanceStep();
private:
	vector rules[RULE_NUM];
	std::vector<double> history[AGENT_NUM];
	vector k;
	int agent_num;
	int rule_num;
	std::mt19937 mt;
private:
	void PushStep(vector& agent_data);
	vector ApplyRule(int idx);
	int DetermineApplyingRule();
	double AgentSummation(int end);
	double RuleWeight(int idx);
};

