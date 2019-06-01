#include <iostream>
#include "model.h"

Model::Model(std::initializer_list<vector> args) :
	rules{vector(AGENT_NUM * 2), vector(AGENT_NUM * 2), vector(AGENT_NUM * 2)},
	k(RULE_NUM),
	agent_num(AGENT_NUM),
	rule_num(RULE_NUM)
{
	std::initializer_list<vector>::iterator iter = args.begin();

	for (int i = 0; i < agent_num; i++) {
		history[i].push_back((*iter)[i]);
	}

	iter++;

	for (int i = 0; i < agent_num; i++) {
		k[i] = (*iter)[i];
	}

	iter++;

	for (int i = 0; iter != args.end(); i++, iter++) {
		rules[i] = *iter;
	}

	std::random_device rnd;
	mt.seed(rnd());
}

const std::vector<double> Model::GetAgentRecord(int idx)
{
	if (0 <= idx && idx < agent_num) {
		return history[idx];
	}

	return std::vector<double>();
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
	next = map([](double a) {return a < 0 ? 0 : a; }, next);

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
	double sum = currnt * k;
	
	std::uniform_real_distribution<double> dist;
	double rand = dist(mt);

	int idx = 0;

	for (; idx < rule_num; idx++) {
		if (AgentSummation(idx) / AgentSummation(rule_num) < rand 
			&& rand <= AgentSummation(idx + 1) / AgentSummation(rule_num)) {
			break;
		}
	}

	return idx;
}

double Model::AgentSummation(int end)
{
	double sum = 0.0;

	for (int i = 0; i < end; i++) {
		sum += RuleWeight(i);
	}

	return sum;
}

double Model::RuleWeight(int idx)
{
	vector currnt = GetCurrentStep();

	vector pro = map2([](auto a, auto b) {return pow(a, b); }, currnt, rules[idx]);

	return k[idx] * foldr([](auto a, auto b) {return a * b; }, 1.0, pro);
}


