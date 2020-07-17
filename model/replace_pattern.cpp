#include "replace_pattern.h"
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
auto patt_logger = spdlog::stderr_color_mt("replace pattern");

void PatternHandler::replace()
{
	std::queue<Operator> res;
	bool converge = false;
	while (!converge)
	{
		while (!this->opQueue.empty())
		{
			Operator op = opQueue.front();
			opQueue.pop();
			//一般只有画线的操作才能作为产生式左侧符号
			if (op.type != draw)
				continue;
			if (prule->getRule().find(op.token) == prule->getRule().end())
			{
				//没有替换规则
				continue;
			}
			//多个产生式，随机选一个
			auto exprs = prule->getRule().find(op.token)->second;
			//TODO 从vector中随机选一个
			std::string expr = exprs[0];
			for (char token : expr)
			{
				Operator image = prule->getTokens().find(token)->second;
				if (image.type == draw)
				{
					Operator t = Operator{draw, image.val * op.val};
					if (t.val < 0.5)
						converge = true;
					res.push(t);
				}
				else
				{
					res.push(image);
				}
			}
		}
		std::swap(opQueue, res);
	}
}

PatternHandler::PatternHandler(std::string rule_file)
{
	//初始化rule数据
	this->prule = new TransformTule(rule_file);
	//初始化初始串
	for (const char &c : prule->getInitial())
	{
		//TODO 查不到的情况
		this->opQueue.push(prule->getTokens().find(c)->second);
	}
}