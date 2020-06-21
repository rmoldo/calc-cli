#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

struct function {
        function();
        function(const std::string n, double (*f)(double));

        std::string name;
        double (*func)(double);
};

#endif
