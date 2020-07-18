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

TransformRule::TransformRule(string fileName)
{
	//TODO 从文件输入解析转换规则
	/**
	 * 初始串
	 * 比例
	 * 符号表
	 * 产生式
	 */
	ifstream input_file(fileName);
	if (!input_file)
	{
		rule_logger->warn("rule input file not found");
		exit(-1);
	}
	char line[256];
	const int width = 255;
	//初始串
	while (input_file.getline(line, width))
	{
		// 注释符号
		if (line[0] == '#')
			continue;
		this->initial = line;
		rule_logger->info("初始串 [{}]", getInitial());
		break;
	}
	//比例
	while (input_file.getline(line, width))
	{
		// 注释符号
		if (line[0] == '#')
			continue;
		this->shrink = line;
		rule_logger->info("比例 [{}]", this->shrink.get_d());
		break;
	}
	//最小值
	while (input_file.getline(line, width))
	{
		// 注释符号
		if (line[0] == '#')
			continue;
		this->eps = line;
		rule_logger->info("最小值 [{}]", this->eps.get_d());
		break;
	}

	//符号表
	vector<string> v;
	bool has_count = false;
	int token_count;
	while (input_file.getline(line, width))
	{
		// 注释符号
		if (line[0] == '#')
			continue;

		if (!has_count)
		{
			split(v, line, is_any_of(" "));
			if (v.size() == 1)
			{
				has_count = true;
				//TODO 异常处理
				token_count = atoi(line);
			}
		}
		else
		{
			//初始化符号
			Operator op = newOp(line);
			this->tokens.insert(make_pair(op.token, op));
			rule_logger->info("{} 的符号是 {}", tostring(op), op.token);
			//处理符号个数
			token_count--;
			if (token_count == 0)
				break;
		}
	}
	//产生式
	while (input_file.getline(line, width))
	{
		// 注释符号
		if (line[0] == '#')
			continue;
		split(v, line, is_any_of(","));
		if (v[0].size() != 1)
		{
			rule_logger->warn("[{}]中左侧不止有一个字符", line);
			break;
		}
		if (v.size() < 2)
		{
			rule_logger->warn("[{}]缺少产生式", line);
			break;
		}
		vector<string> rule;
		rule.assign(v.begin() + 1, v.end());
		char token = v[0][0];
		this->rule.insert(make_pair(token, rule));
		char expr[255] = {0};
		for (auto e : rule)
		{
			strcat(expr, e.c_str());
		}
		rule_logger->info("添加产生式'{}'->{}", token, expr);
	}
	input_file.close();
}