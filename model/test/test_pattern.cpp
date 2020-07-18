#include "../replace_pattern.h"
int main(int argc, char const *argv[])
{
	PatternHandler pattern("test/rule.txt");
	pattern.replace();
	//TODO 为什么栈里的东西那么少
	std::queue<Operator> q = pattern.getOps();
	while (!q.empty())
	{
		// std::cout << tostring(q.front());
		std::cout << q.front().token;
		q.pop();
	}
	return 0;
}
