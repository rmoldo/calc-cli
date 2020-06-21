#include "token.h"

#include "defs.h"
#include "function.h"

#include <iostream>
#include <string>

Token::Token()
{

}

Token::Token(char ch) : kind {ch}
{

}

Token::Token(char ch, double val) : kind {ch}, value {val}
{

}

Token::Token(char ch, const function &fname) : kind {ch}, func {fname}
{

}

