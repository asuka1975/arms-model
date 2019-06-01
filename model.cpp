#include <iostream>
#include "model.h"

Model::Model(std::initializer_list<vector> args) :
	rules{vector(AGENT_NUM * 2), vector(AGENT_NUM * 2), vector(AGENT_NUM * 2)},
	agent_num(AGENT_NUM),
	rule_num(RULE_NUM)
{
	std::initializer_list<vector>::iterator iter = args.begin();

	for (int i = 0; i < agent_num; i++) {
		history[i].push_back((*iter)[i]);
	}

	iter++;

	for (int i = 0; iter != args.end(); i++, iter++) {
		rules[i] = *iter;
	}

	std::random_device rnd;
	mt.seed(rnd());
}

const std::vector<int> Model::GetAgentRecord(int idx)
{
	if (0 <= idx && idx < AGENT_NUM) {
		return history[idx];
	}

	return std::vector<int>();
}

vector Model::GetCurrentStep()
{
	vector vec(agent_num);
	for (int i = 0; i < agent_num; i++) vec[i] = history[i].back();

	return vec;
}

void Model::AdvanceStep()
{
	vector next = ApplyRule(DetermineApplyingRule());
	for (int i = 0; i < agent_num; i++) {
		if (next[i] < 0) next[i] = 0;
	}
	PushStep(next);
}

void Model::PushStep(vector& agent_data)
{
	for (int i = 0; i < agent_num; i++) {
		history[i].push_back(agent_data[i]);
	}
}

vector Model::ApplyRule(int idx)
{
	vector next(agent_num);
	if (0 <= idx && idx < rule_num) {
		vector currnt = GetCurrentStep();

		vector prev_rule = rules[idx].slice(0, agent_num);
		vector next_rule = rules[idx].slice(agent_num, agent_num);

		next = currnt - prev_rule + next_rule;
	}

	return next;
}

int Model::DetermineApplyingRule()
{
	vector currnt = GetCurrentStep();
	int sum = summation(currnt);
	
	std::uniform_real_distribution<double> dist;
	double rand = dist(mt);

	int idx = 0;

	for (; idx < agent_num; idx++) {
		if (static_cast<double>(summation(currnt.slice(0, idx))) / sum < rand 
			&& rand <= static_cast<double>(summation(currnt.slice(0, idx + 1))) / sum) {
			break;
		}
	}

	return idx;
}
