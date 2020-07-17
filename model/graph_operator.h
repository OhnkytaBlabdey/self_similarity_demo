#pragma once
#include <iostream>
#include <gmpxx.h>
#include <string>

enum OperatorType
{
	save,
	load,
	turn,
	draw,
	end
};

typedef struct _op
{
	OperatorType type;
	mpf_class val;
	char token;
} Operator;
bool operator<(const struct _op &a, const struct _op &b);
Operator newOp(std::string);
std::string tostring(Operator);