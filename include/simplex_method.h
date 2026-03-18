#ifndef _SIMPLEX_METHOD_H_
#define _SIMPLEX_METHOD_H_

#include "good_funcs.h"

#include <iostream>

class gomori;

class simplex_method{
private:
    std::vector<std::vector<double>> matrix;
    std::vector<double> b, f, basise;
    std::vector<int> sign;
    std::vector<double> true_f;
    optimal_func param;

    int count_nonpositive(std::vector<double>& f);

    friend class gomori;

public:
    simplex_method(std::vector<std::vector<double>>&& matrix, std::vector<double>&& b, std::vector<double>&& f, std::vector<int>&& sign, optimal_func param = max_func);

    bool simplex_step();
    double make_simplex();

    double get_optimum();
    
    std::vector<double> get_basise() const;
};

#endif