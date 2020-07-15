#include "graph_operator.h"
#include <boost/algorithm/string.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
using namespace std;
using namespace boost;
using namespace spdlog;

auto op_logger = stdout_color_mt("graph operator");
bool operator<(const struct _op &a, const struct _op &b)
{
	return (a.type < b.type) || (a.type == b.type && a.val < b.val);
}
Operator newOp(std::string s)
{
	/**
	 * sample :
	 * draw 15.5
	 * turn -30
	 * save
	 * load
	 * end
	 */
	vector<string> v;
	split(v, s, is_any_of(" "));
	Operator res = Operator{OperatorType(4), 0};
	if (v.size() == 2)
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
				op_logger->warn(e.what());
				op_logger->warn(s);
				return res;
			}
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
				op_logger->warn(e.what());
				op_logger->warn(s);
				return res;
			}
		}
		else
		{
			op_logger->warn("invalid operator type");
			op_logger->warn(s);
			return res;
		}
	}
	else
	{
		if (s == "save")
		{
			res.type = save;
		}
		else if (s == "load")
		{
			res.type = load;
		}
		else if (s == "end")
		{
		}
		else
		{
			op_logger->warn("invalid operator type");
			op_logger->warn(s);
			return res;
		}
	}
	op_logger->info(res.type);
	op_logger->info(res.val.get_d());
	return res;
}