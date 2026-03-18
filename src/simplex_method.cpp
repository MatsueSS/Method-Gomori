#include "simplex_method.h"
#include "prepare_simplex.h"

#include <cmath>

int simplex_method::count_nonpositive(std::vector<double>& f){
    int count = 0;
    for(int i = 0; i < f.size()-1; ++i){
        if(f[i] <= 0)
            count++;
    }
    return count;
}

simplex_method::simplex_method(std::vector<std::vector<double>>&& matrix, std::vector<double>&& b, std::vector<double>&& f, std::vector<int>&& sign, optimal_func param)
{
    this->matrix = std::move(matrix);
    this->b = std::move(b);
    this->f = std::move(f);
    this->param = param;
    this->sign = std::move(sign);
    this->true_f = this->f;
}

double simplex_method::make_simplex(){
    int count_params_orig = matrix[0].size();
    int count_nonpos = count_nonpositive(f);

    if(param == min_func){
        for(int i = 0; i < f.size(); ++i){
            f[i] = -f[i];
        }
    }

    prepare_simplex::make_prepare(matrix, b, f, sign, basise, param);

    int count_params_total = matrix[0].size();

    while(true){
        int val = find_max(f);
        if(f[val] <= 0)
            break;

        bool result = simplex_step();
        if(!result) {
            std::cout << "Задача не ограничена!" << std::endl;
            return -1;
        }
        
        count_params_total = matrix[0].size();
    }

    return f[f.size()-1];
}

bool simplex_method::simplex_step(){
    int count_restriction = b.size();
    int count_params = matrix[0].size();

    int pivot_col = find_max(f);
    if(f[pivot_col] <= 0)
        return 1;

    std::vector<double> temp_colision (count_restriction, INFINITY);
    for(int i = 0; i < count_restriction; ++i){
        if(matrix[i][pivot_col] > 0)
            temp_colision[i] = b[i]/matrix[i][pivot_col];
    }

    int pivot_row = find_min(temp_colision);
    if(temp_colision[pivot_row] == INFINITY){
        return 0;
    }

    double val = matrix[pivot_row][pivot_col];
    for(int i = 0; i < count_params; ++i){
        matrix[pivot_row][i] /= val;
    }
    b[pivot_row] /= val;

    for(int i = 0; i < count_restriction; ++i){
        if(i == pivot_row)
            continue;
        double coef = matrix[i][pivot_col];
        if(coef != 0){
            b[i] -= coef*b[pivot_row];

            for(int j = 0; j < count_params; ++j){
                matrix[i][j] -= (matrix[pivot_row][j]*coef);
            }
        }
    }
    basise[pivot_row] = pivot_col;
    
    double f_val = f[pivot_col];
    if(f_val != 0){
        for(int j = 0; j < count_params; ++j){
            f[j] -= (f_val*matrix[pivot_row][j]);
        }
        f[count_params] -= (f_val*b[pivot_row]);
    }

    return 1;
}

std::vector<double> simplex_method::get_basise() const
{
    int result_size = f.size() - 1 - basise.size();
    if(result_size <= 0) {
        std::cerr << "get_basise: result_size = " << result_size << " (некорректный)\n";
        return {};
    }
    
    std::vector<double> result(result_size, 0);
    for(int i = 0; i < b.size() && i < basise.size(); ++i) {
        if(basise[i] >= 0 && basise[i] < result_size) {
            result[basise[i]] = b[i];
        }
    }
    return result;
}

double simplex_method::get_optimum()
{
    return f[f.size()-1];
}