#include "../replace_pattern.h"
int main(int argc, char const *argv[])
{
	PatternHandler pattern("model/test/test_rule.txt");
	pattern.replace();
	return 0;
}
