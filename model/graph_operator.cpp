#include "graph_operator.h"
#include <boost/algorithm/string.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
using namespace std;
using namespace boost;
using namespace spdlog;

auto op_logger = stdout_color_mt("graph operator");
bool operator<(const struct _op &a, const struct _op &b)
{
	return (a.type < b.type) || (a.type == b.type && a.val < b.val) || (a.type == b.type && a.val == b.val && a.token < b.token);
}
std::string tostring(Operator op)
{
	static char buffer[255] = {0};
	switch (op.type)
	{
	case draw:
		sprintf(buffer, "\n{\n\ttype:draw,\n\tval:%lf,\n\ttoken:%c\n}", op.val.get_d(), op.token);
		break;
	case turn:
		sprintf(buffer, "\n{\n\ttype:turn,\n\tval:%lf,\n\ttoken:%c\n}", op.val.get_d(), op.token);
		break;
	case save:
		sprintf(buffer, "\n{\n\ttype:save,\n\ttoken:%c\n}", op.token);
		break;
	case load:
		sprintf(buffer, "\n{\n\ttype:load,\n\ttoken:%c\n}", op.token);
		break;
	default:
		break;
	}

	return buffer;
}
Operator newOp(std::string s)
{
	/**
	 * example :
	 * draw 15.5 f
	 * turn -30 +
	 * save [
	 * load ]
	 */
	vector<string> v;
	split(v, s, is_any_of(" "));
	Operator res = Operator{OperatorType(4), 0, 0};
	if (v.size() == 3)
	{
		/*
		`If the string is not a valid integer, 
		an std::invalid_argument exception is thrown.
		The same applies to operator=.` -- GMP-6.2.0 manual
		*/
		if (v.front() == "draw")
		{
			res.type = draw;
			try
			{
				res.val = mpf_class(v[1]);
			}
			catch (const std::invalid_argument &e)
			{
				op_logger->warn("[{}] caused err in \"{}\"", s, e.what());
				return res;
			}
			res.token = v[2][0];
		}
		else if (v.front() == "turn")
		{
			res.type = turn;
			try
			{
				res.val = mpf_class(v[1]);
			}
			catch (const std::invalid_argument &e)
			{
				op_logger->warn("[{}] caused err in \"{}\"", s, e.what());
				return res;
			}
			res.token = v[2][0];
		}
		else
		{
			op_logger->warn("invalid operator type :[{}]", s);
			return res;
		}
	}
	else if (v.size() == 2)
	{
		if (v[0] == "save")
		{
			res.type = save;
			res.token = v[1][0];
		}
		else if (v[0] == "load")
		{
			res.type = load;
			res.token = v[1][0];
		}
		else
		{
			op_logger->warn("invalid operator type :[{}]", s);
			return res;
		}
	}
	else
	{
		op_logger->warn("invalid operator syntax :[{}]", s);
		return res;
	}
	op_logger->info("[{}] initialized as :{}", s, tostring(res));
	return res;
}
