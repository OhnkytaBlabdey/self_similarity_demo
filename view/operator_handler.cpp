#include "operator_handler.h"
#include "config.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <stack>
#include <cmath>
using namespace spdlog;
auto handler_logger = stdout_color_mt("operator handler");
OperatorHandler::OperatorHandler(queue<Operator> opq)
{
	while (!opq.empty())
	{
		this->ops.push_back(opq.front());
		opq.pop();
	}
}

OperatorHandler::~OperatorHandler()
{
	ops.clear();
}

typedef struct
{
	mpf_class x, y, facing;
} state;
void OperatorHandler::Draw()
{
	stack<state> s;
	state now;
	now.x = 0;
	now.y = 0;
	now.facing = 90;
	glBegin(GL_LINES);
	for (auto op : ops)
	{
		switch (op.type)
		{
		case save:
			s.push(now);
			break;
		case load:
			now = s.top();
			s.pop();
			break;
		case turn:
			now.facing += op.val;
			break;
		case draw:
			glVertex3d(now.x.get_d(), now.y.get_d(), 0);
			now.x += cos(now.facing.get_d()) * op.val;
			now.y += sin(now.facing.get_d()) * op.val;
			// now.x += cos(now.facing.get_d()) * op.val * config::width;
			// now.y += sin(now.facing.get_d()) * op.val * config::height;
			glVertex3d(now.x.get_d(), now.y.get_d(), 0);
			break;

		default:
			handler_logger->warn("invalid operator {}", tostring(op));
			break;
		}
	}
	glEnd();
}