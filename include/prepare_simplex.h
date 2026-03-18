#ifndef _PREPARE_SIMPLEX_H_
#define _PREPARE_SIMPLEX_H_

#include "good_funcs.h"

class prepare_simplex{
public:
    static void make_prepare(std::vector<std::vector<double>>& matrix, std::vector<double>& b, std::vector<double>& f, std::vector<int>& sign, std::vector<double>& basise, optimal_func param);
};

#endif