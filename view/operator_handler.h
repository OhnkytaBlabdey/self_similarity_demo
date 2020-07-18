#include "../model/replace_pattern.h"
#include <GLFW/glfw3.h>
#include <list>
#include <iostream>
using namespace std;
class OperatorHandler
{
private:
	list<Operator> ops;
	mpf_class zoom;

public:
	OperatorHandler(queue<Operator>, mpf_class);
	~OperatorHandler();
	void Draw();
};