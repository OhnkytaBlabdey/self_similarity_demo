#include "../graph_operator.h"

int main(int argc, char const *argv[])
{
	newOp("turn -190 -");
	newOp("turn -190");
	newOp("draw 30.15 f");
	newOp("draw 30.15");
	newOp("save {");
	newOp("save [");
	newOp("save");
	newOp("load )");
	newOp("load ]");
	newOp("load");
	newOp("end");
	newOp("blabla");
	newOp("blabla bla");
	newOp("blabla bla bla");
	newOp("turn bla");
	newOp("turn bla bla");
	return 0;
}
