#pragma once
#include "graph_operator.h"
#include "transform_rule.h"
#include <queue>
class PatternHandler
{
private:
	std::queue<Operator> opQueue;
	TransformTule *prule = nullptr;

public:
	PatternHandler() {}
	~PatternHandler() {}
	void replace();
};