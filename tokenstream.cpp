#include "tokenstream.h"

#include "token.h"
#include "defs.h"
#include "function.h"
#include "constant.h"

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>

Token_stream::Token_stream(const std::string& str_input)
{
        input = new std::istringstream {str_input};
}

Token_stream::~Token_stream()
{
        delete input;
}

void Token_stream::putback(Token t)
{
        if (full)
                throw std::runtime_error("putback() into a full buffer");

        buffer = t;
        full = true;
}

bool Token_stream::input_empty()
{
        return *input ? 1 : 0;
}

Token Token_stream::get()
{
        if (full) {
                full = false;
                return buffer;
        }

        char ch;
        *input >> ch;

        switch (ch) {
        case ';':  case 'q': case '(': case ')':
        case '+': case '-': case '*': case '/':
        case '{': case '}': case '!': case '%':
                return Token {ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
                input->putback(ch);
                double val;
                *input >> val;

                return Token {'8', val};
        }

        case 'h': case 'H': {
                int val;

                *input >> std::hex >> val;

                return Token {'8', (double)val};
        }

        case 'b': case 'B': {
                auto valid_binary =
                        [](const std::string& nb) {
                                for (int i = 0; i < nb.size(); ++i)
                                        if (nb[i] != '1' && nb[i] != '0')
                                                return 0;
                                return 1;};

                std::string binary_value;
                while (input->get(ch) && std::isdigit(ch))
                        binary_value += ch;

                input->putback(ch);

                if (!valid_binary(binary_value))
                        throw std::runtime_error("Number is not binary!\n");

                int val = 0;

                for (int i = 0; i < binary_value.size(); ++i)
                        val = (val << 1) + (binary_value[i] - 0x30);

                return Token {'8', (double)val};
        }

        default: {
                if (isalnum(ch)) {
                        std::string name {ch};

                        while (input->get(ch) && isalnum(ch))
                                name += ch;
                        input->putback(ch);

                        auto func_it = std::find_if(func_vector.begin(),
                                               func_vector.end(),
                                               [&name] (const function& f) {
                                                       return f.name == name;
                                               });

                        auto const_it = std::find_if(constant_vector.begin(),
                                                constant_vector.end(),
                                                [&name](const constant& c) {
                                                        return c.name == name;
                                                });

                        if (const_it != constant_vector.end())
                                return Token {'8', const_it->value};

                        if (func_it == func_vector.end())
                                throw std::runtime_error("Illegal function call");

                        return Token {'9', {name, func_it->func}};
                }

                throw std::runtime_error("Bad token!");
        }
        }
}
