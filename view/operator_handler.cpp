#include "operator_handler.h"
#include "config.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <stack>
#include <cmath>
using namespace spdlog;
auto handler_logger = stdout_color_mt("operator handler");
OperatorHandler::OperatorHandler(queue<Operator> opq, mpf_class z)
{
	this->zoom = z;
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
	static double pi = 3.1415926535897;
	stack<state> s;
	state now;
	now.x = 0;
	now.y = 0;
	now.facing = 90;
	glColor3f(0.2, 0.8, 0.2);
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
			handler_logger->debug("退栈后余 {}", s.size());
			break;
		case turn:
			now.facing += op.val;
			break;
		case draw:
			glVertex3d(now.x.get_d(), now.y.get_d(), 0);
			now.x += cos(now.facing.get_d() / 180 * pi) * op.val * this->zoom;
			now.y += sin(now.facing.get_d() / 180 * pi) * op.val * this->zoom;
			// now.x += cos(now.facing.get_d()) * op.val * config::width;
			// now.y += sin(now.facing.get_d()) * op.val * config::height;
			glVertex3d(now.x.get_d(), now.y.get_d(), 0);
			if (abs(now.x.get_d()) > 1.1 || abs(now.y.get_d()) > 1.1)
			{
				handler_logger->warn("[{}, {}]", now.x.get_d(), now.y.get_d());
				glEnd();
				return;
			}
			break;

		default:
			handler_logger->warn("invalid operator {}", tostring(op));
			break;
		}
	}

	glColor3f(0.8, 0.2, 0.2);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
}