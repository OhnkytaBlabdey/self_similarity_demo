#pragma once
#include "graph_operator.h"
#include <map>
#include <vector>
#include <string>

class TransformRule
{
private:
	std::map<char, std::vector<std::string>> rule;
	std::map<char, Operator> tokens;
	std::string initial;
	mpf_class shrink;
	mpf_class eps;

public:
	TransformRule(std::string);
	~TransformRule() {}
	const std::map<char, std::vector<std::string>> &getRule() const
	{
		return rule;
	}
	const std::map<char, Operator> &getTokens() const
	{
		return tokens;
	}
	const std::string &getInitial() const
	{
		return initial;
	}
	const mpf_class &getShrink() const
	{
		return shrink;
	}
	const mpf_class &getEps() const
	{
		return eps;
	}
};