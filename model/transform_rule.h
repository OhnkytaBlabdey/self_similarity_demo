#pragma once
#include "graph_operator.h"
#include <map>
#include <list>
#include <string>

class TransformTule
{
private:
	std::map<Operator, std::list<Operator>> rule;

public:
	TransformTule(std::string);
	~TransformTule() {}
	const std::map<Operator, std::list<Operator>>& getRule()
	{
		return rule;
	}
};