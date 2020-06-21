#include "function.h"

#include <string>

function::function()
{

}

function::function(const std::string n, double (*f)(double))
{
        name = n;
        func = f;
}
