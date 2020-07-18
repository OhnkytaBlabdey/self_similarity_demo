#pragma once
#include "graph_operator.h"
#include "transform_rule.h"
#include <queue>
#include <string>
class PatternHandler
{
private:
	std::queue<Operator> opQueue;
	TransformTule *prule = nullptr;

public:
	PatternHandler(std::string);
	~PatternHandler() {}
	void replace();
	std::queue<Operator> getOps()
	{
		return opQueue;
	}
};