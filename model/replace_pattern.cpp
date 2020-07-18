#include "replace_pattern.h"
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <random>
auto patt_logger = spdlog::stdout_color_mt("replace pattern");

void PatternHandler::replace()
{
	std::random_device rd;
	std::mt19937 gen(rd());
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
			patt_logger->info("为替换 {}", op.token);
			//多个产生式，随机选一个
			auto exprs = prule->getRule().at(op.token);
			//TODO 从vector中随机选一个
			std::uniform_int_distribution<int> uni(0, exprs.size() - 1);
			int i = uni(gen);
			patt_logger->debug("chose {} among {}", i, exprs.size());
			std::string expr = exprs[i];
			for (char token : expr)
			{
				//没找到
				if (prule->getTokens().find(token) == prule->getTokens().end())
				{
					patt_logger->warn("没有找到{}", token);
					continue;
				}
				Operator image = prule->getTokens().at(token);
				patt_logger->debug("pushed {}", image.token);
				if (image.type == draw)
				{
					Operator t = Operator{draw, prule->getShrink() * op.val, image.token};
					if (t.val < 0.1)
						converge = true;
					res.push(t);
				}
				else
				{
					res.push(image);
				}
			}
		}
		patt_logger->info("当前队列中有{}个元素", res.size());
		std::swap(opQueue, res);
	}
	patt_logger->info("替换结束");
}

PatternHandler::PatternHandler(std::string rule_file)
{
	//初始化rule数据
	this->prule = new TransformTule(rule_file);
	//初始化初始串
	patt_logger->info("初始串{}", prule->getInitial());
	for (auto c : prule->getInitial())
	{
		// 查不到的情况
		if (prule->getTokens().find(c) == prule->getTokens().end())
		{
			continue;
		}
		Operator op = prule->getTokens().at(c);
		this->opQueue.push(op);
		patt_logger->info("插入了{}", tostring(op));
	}
}