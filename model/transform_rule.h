#pragma once
#include "graph_operator.h"
#include <map>
#include <list>
#include <string>

class TransformTule
{
private:
	std::map<char, std::list<std::string>> rule;
	std::map<char, Operator> tokens;

public:
	TransformTule(std::string);
	~TransformTule() {}
	const std::map<char, std::list<std::string>> &getRule()
	{
		return rule;
	}
};