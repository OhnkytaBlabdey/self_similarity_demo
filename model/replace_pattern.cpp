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
			if (op.type != draw)
				continue;
			if (prule->getRule().find(op) == prule->getRule().end())
			{
				//没有替换规则
				continue;
			}
			for (auto image : prule->getRule().find(op)->second)
			{
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