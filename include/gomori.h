#ifndef _GOMORI_H_
#define _GOMORI_H_

#include "simplex_method.h"

class gomori{
private:
    simplex_method sm;
    int count_cutting_off;
    int max_index;
    bool bad_quest;

    bool has_remnant();
    int index_lead();
    double get_gomori_fraction(double val);

public:
    gomori(std::vector<std::vector<double>>&& matrix, std::vector<double>&& b, std::vector<double>&& f, std::vector<int>&& sign, optimal_func param);

    void add_new_restrict();
    int prepare_gomori();
    int method_gomori();
    void make_good_plan();

    bool has_negative_b();
    bool dual_simplex_step();

    double get_optimum() const;

    //Отладка
    void print_result() const;
};

#endif