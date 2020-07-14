#pragma once
#include<iostream>
#include<gmpxx.h>

enum OperatorType {
	save,
	load,
	trun,
	draw,
	end
};

typedef struct {
	OperatorType type;
	mpf_class val;
} Operator;