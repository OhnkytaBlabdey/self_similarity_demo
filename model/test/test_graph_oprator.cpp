#include "../graph_operator.h"

int main(int argc, char const *argv[])
{
	newOp("turn -190");
	newOp("draw 30.15");
	newOp("save");
	newOp("load");
	newOp("end");
	return 0;
}
