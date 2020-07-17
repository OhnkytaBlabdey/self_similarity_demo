#include "transform_rule.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vector>
using namespace std;
using namespace boost;
using namespace spdlog;

auto rule_logger = stdout_color_mt("transform rule");

TransformTule::TransformTule(string fileName)
{
	//TODO 从文件输入解析转换规则
	/**
	 * sample :
	 * draw 1:draw 0.5,save,turn -30,draw 0.5,load,draw 0.25,save,turn 30,draw 0.25,load,draw 0.25
	 * 
	 * 
	 */
	ifstream input_file(fileName);
	if (!input_file)
	{
		rule_logger->warn("rule input file not found");
		exit(-1);
	}
	char line[256];
	const int width = 255;
	vector<string> v;
	while (input_file.getline(line, width))
	{
		split(v, line, is_any_of(":"));
		assert(v.size() == 2);
		Operator op = newOp(v[0]);
		vector<string> images;
		split(images, v[1], is_any_of(","));
		list<Operator> ops;
		for (auto image : images)
		{
			ops.push_back(newOp(image));
		}
		this->rule.insert(make_pair(op, ops));
	}
	input_file.close();
}