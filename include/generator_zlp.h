#ifndef _GENERATOR_ZLP_H_
#define _GENERATOR_ZLP_H_

#include "good_funcs.h"

#include <random>

class PentagonGenerator {
private:
    std::mt19937 rng;
    
    double random_double(double min, double max) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(rng);
    }
    
    int random_int(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

public:
    PentagonGenerator() : rng(std::random_device{}()) {}
    
    void generate_pentagon_direct(std::vector<std::vector<double>>& matrix, std::vector<double>& b, std::vector<double>& f, std::vector<int>& sign);
    void generate_pentagon_integer(std::vector<std::vector<double>>& matrix, std::vector<double>& b, std::vector<double>& f, std::vector<int>& sign);
    void good_generate(std::vector<std::vector<double>>& matrix, std::vector<double>& b, std::vector<double>& f, std::vector<int>& sign);
};

#endif