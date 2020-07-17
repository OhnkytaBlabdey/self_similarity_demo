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
};