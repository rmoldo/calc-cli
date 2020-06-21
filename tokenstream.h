#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "token.h"

#include <istream>
#include <string>

class Token_stream {
public:
        Token_stream(const std::string& str_input);

        ~Token_stream();


        bool input_empty();

        Token get();
        void putback(Token t);

private:
        bool full {false};
        Token buffer;
        std::istream* input;
};

#endif
