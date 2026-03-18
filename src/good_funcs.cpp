#include "good_funcs.h"

#include <iostream>

void print_matrix(const std::vector<std::vector<double>>& matrix){
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix[0].size(); ++j){
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void print_vector(const std::vector<double>& f){
    for(int i = 0; i < f.size(); ++i){
        std::cout << f[i] << ' ';
    }
    std::cout << '\n';
}

int find_max(std::vector<double>& f){
    int max_val = INT32_MIN;
    int index = 0;
    for(int i = 0; i < f.size()-1; ++i){
        if(max_val < f[i]){
            max_val = f[i];
            index = i;
        }
    }
    return index;
}

int find_min(std::vector<double>& f){
    double min_val = INT32_MAX;
    int index = 0;
    for(int i = 0; i < f.size(); ++i){
        if(f[i] < min_val){
            index = i;
            min_val = f[i];
        }
    }
    return index;
}