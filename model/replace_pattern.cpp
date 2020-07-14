#include "replace_pattern.h"
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
			if(prule->getRule().find(op)==prule->getRule().end()){
				//TODO 错误处理
				exit(-1);
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