#include "../model/replace_pattern.h"
#include <GLFW/glfw3.h>
#include <list>
#include <iostream>
using namespace std;
class OperatorHandler
{
private:
	list<Operator> ops;

public:
	OperatorHandler(queue<Operator>);
	~OperatorHandler();
	void Draw();
};