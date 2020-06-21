#ifndef PARSER_H
#define PARSER_H

#include "tokenstream.h"

class Calculator : public Token_stream {
public:
        Calculator(const std::string &xpr);

        double evaluate_expression();

private:
        std::string expr;

        double expression();
        double primary();
        double term();
};

#endif
