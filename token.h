#ifndef TOKEN_H
#define TOKEN_H

#include "function.h"

#include <string>

struct Token {
	Token();
	Token(char ch);
	Token(char ch, double val);
	Token(char ch, const function &fname);

	char kind;
	double value;
	function func;
};

#endif
