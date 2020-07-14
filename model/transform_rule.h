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
	// TransformTule()
	// {
	// rule.insert(
	// 	std::pair<Operator, std::list<Operator>>(
	// 		Operator(end, 0),

	// 	)
	// );
	// }
	TransformTule(std::string);
	~TransformTule() {}
	const std::map<Operator, std::list<Operator>>& getRule()
	{
		return rule;
	}
};