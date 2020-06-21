#include "calculator.h"

#include "token.h"
#include "tokenstream.h"
#include "defs.h"
#include "function.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

Calculator::Calculator(const std::string &xpr) : Token_stream {xpr}
{
        const char* fname = ".history";

        if (access(fname, F_OK) == -1) {
                int file_descriptor;

                if ((file_descriptor = open(fname , O_RDWR | O_CREAT, 0664)) != -1)
                        close(file_descriptor);
        }
}

double Calculator::primary()
{
        Token t = get();

        switch (t.kind) {
        case '(': {
                double d = expression();
                t = get();

                if (t.kind != ')')
                        throw std::runtime_error("Missing )");
                return d;
        }

        case '{': {
                double d = expression();
                t = get();

                if (t.kind != '}')
                        throw std::runtime_error("Missing }");
                return d;
        }

        case '[': {
                double d = expression();
                t = get();

                if (t.kind != ']')
                        throw std::runtime_error("Missing ]");
                return d;
        }

        case '-':
                return -primary();

        case '+':
                return primary();

        case NUMBER:
                return t.value;

        case FUNCTION: {
                double d = primary();

                return t.func.func(d);
        }

        default:
                throw std::runtime_error("primary expected");
        }
}

double Calculator::term()
{
        double left = primary();

        Token t = get();

        while (true) {
                switch (t.kind) {
                case '!': {
                        if (left == std::floor(left))
                                if (left == 0)
                                        left = 1;
                                else
                                        for (double i = left - 1; i >= 1; --i)
                                                left *= i;
                        else
                                throw std::runtime_error("Can't factorialize a double");
                        t = get();
                        break;
                }

                case '*': {
                        double d = primary();
                        t = get();

                        if (t.kind == '!') {
                                if (d == std::floor(d))
                                        for (int i = (int)d - 1; i >= 1; --i)
                                                d *= i;
                                else
                                        throw std::runtime_error("Can't factorialize a double");
                        } else
                                putback(t);

                        left *= d;
                        t = get();
                        break;
                }

                case '/': {
                        double d = primary();

                        t = get();
                        if (t.kind == '!') {
                                if (d == std::floor(d)) {
                                        if (d == 0)
                                                d = 1;
                                        else
                                                for (int i = (int)d - 1; i >= 1; --i)
                                                        d *= i;
                                } else
                                        throw std::runtime_error("Can't factorialize a double");
                        } else
                                putback(t);

                        if (d == 0)
                                throw std::runtime_error("divide by zero");

                        left /= d;
                        t = get();
                        break;
                }

                case '%': {
                        double d = primary();
                        if (d == 0)
                                throw std::runtime_error("divide by zero");

                        t = get();
                        if (t.kind == '!') {
                                if (d == std::floor(d)) {
                                        if (d == 0)
                                                d = 1;
                                        else
                                                for (int i = (int)d - 1; i >= 1; --i)
                                                        d *= i;
                                } else
                                        throw std::runtime_error("Can't factorialize a double");
                        } else
                                putback(t);

                        left = std::fmod(left, d);
                        t = get();
                        break;
                }

                default:
                        putback(t);
                        return left;
                }
        }
}

double Calculator::expression() {
        double left = term();
        Token t = get();

        while (true) {
                switch (t.kind) {
                case '+':
                        left += term();
                        t = get();
                        break;
                case '-':
                        left -= term();
                        t = get();
                        break;
                default:
                        putback(t);
                        return left;
                }
        }
}

double Calculator::evaluate_expression()
{
        try {
                double val = 0;
                while (input_empty()) {
                        Token t = get();
                        if (t.kind == QUIT)
                                break;
                        if (t.kind == END) {
                                return val;
                        }
                        else
                                putback(t);
                        val = expression();
                }
        } catch (std::exception &e) {
                std::cerr << e.what() << '\n';
                throw;
        } catch (...) {
                std::cerr << "Exception!" << '\n';
                throw;
        }

        return 0;
}
