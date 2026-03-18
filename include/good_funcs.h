#ifndef _GOOD_FUNCS_H_
#define _GOOD_FUNCS_H_

#include <vector>

enum optimal_func { min_func, max_func };

void print_matrix(const std::vector<std::vector<double>>& matrix);

void print_vector(const std::vector<double>& f);

int find_max(std::vector<double>& f);

int find_min(std::vector<double>& f);

#endif