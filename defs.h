#ifndef DEFS_H
#define DEFS_H

#include <vector>
#include <cmath>

#include "constant.h"
#include "function.h"

#define NUMBER '8'
#define FUNCTION '9'
#define QUIT 'q'
#define END ';'

static std::vector<function> func_vector {{"sin", std::sin},
                                          {"cos", std::cos},
                                          {"tan", std::tan},
                                          {"abs", std::fabs},
                                          {"sqrt", std::sqrt},
                                          {"ceil", std::ceil},
                                          {"floor", std::floor},
                                          {"exp", std::exp},
                                          {"cosh", std::cosh},
                                          {"sinh", std::sinh},
                                          {"log10", std::log10},
                                          {"log", std::log},
                                          {"log2", std::log2},
                                          {"tanh", std::tanh},
                                          {"atan", std::atan}};


static std::vector<constant> constant_vector {{3.14159265359, "PI"},
                                              {3.14159265359, "pi"},
                                              {0.5772156649, "e"},
                                              {0.5772156649, "E"},
                                              {1.4142135623, "root2"}};

#endif
