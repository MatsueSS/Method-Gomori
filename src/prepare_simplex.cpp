#include "prepare_simplex.h"

void prepare_simplex::make_prepare(std::vector<std::vector<double>>& matrix, std::vector<double>& b, std::vector<double>& f, std::vector<int>& sign, std::vector<double>& basise, optimal_func param)
{
    int count_restriction = matrix.size();
    int count_params = matrix[0].size();

    int last_val = f[count_params];
    f.pop_back();

    for(int i = 0; i < count_restriction; ++i){
        for(int j = 0; j < count_restriction; ++j){
            matrix[i].push_back(j == i ? sign[i]*1.0 : 0.0);
        }
        basise.push_back(i+count_params);
        f.push_back(0);
    }
    f.push_back(last_val);
}