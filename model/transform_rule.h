#pragma once
#include "graph_operator.h"
#include <map>
#include <vector>
#include <string>

class TransformTule
{
private:
	std::map<char, std::vector<std::string>> rule;
	std::map<char, Operator> tokens;
	std::string initial;
	mpf_class shrink;
	mpf_class eps;

public:
	TransformTule(std::string);
	~TransformTule() {}
	const std::map<char, std::vector<std::string>> &getRule()
	{
		return rule;
	}
	const std::map<char, Operator> &getTokens()
	{
		return tokens;
	}
	const std::string &getInitial()
	{
		return initial;
	}
	const mpf_class &getShrink()
	{
		return shrink;
	}
	const mpf_class &getEps()
	{
		return eps;
	}
};