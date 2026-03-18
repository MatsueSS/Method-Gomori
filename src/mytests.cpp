#include "good_funcs.h"
#include "prepare_simplex.h"
#include "generator_zlp.h"
#include "gomori.h"

double test1(){
    std::vector<std::vector<double>> matrix = {{2,1}, {1,2}};
    std::vector<double> b = {8,7};
    std::vector<double> f = {3,2,0};
    std::vector<int> s = {1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    double r = m.make_simplex(); //13 +
    return r;
}

double test2(){
    std::vector<std::vector<double>> matrix = {{1,1}, {1,0}, {0,1}};
    std::vector<double> b = {5,3,4};
    std::vector<double> f = {2,3,0};
    std::vector<int> s = {1,1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    return m.make_simplex(); //14 +
}

double test3(){
    std::vector<std::vector<double>> matrix = {{1,1,1}, {2,-1,0}};
    std::vector<double> b = {10,5};
    std::vector<double> f = {4,-2,1,0};
    std::vector<int> s = {1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    return m.make_simplex(); //17.5 +
}

double test4(){
    std::vector<std::vector<double>> matrix = {{1,1}, {1,0}, {0,1}};
    std::vector<double> b = {6,4,4};
    std::vector<double> f = {3,2,0};
    std::vector<int> s = {1,1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    return m.make_simplex(); //16 +
}

double test5(){
    std::vector<std::vector<double>> matrix = {{2,1,1,1}, {1,2,1,0}, {1,1,0,2}};
    std::vector<double> b = {20,15,12};
    std::vector<double> f = {5,4,3,2,0};
    std::vector<int> s = {1,1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    double r = m.make_simplex(); //55 +
    return r;
}

double test6(){
    std::vector<std::vector<double>> matrix = {{1,2}, {1,1}};
    std::vector<double> b = {5,4};
    std::vector<double> f = {2,4,0};
    std::vector<int> s = {1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    return m.make_simplex(); //10 +
}

double test7(){
    std::vector<std::vector<double>> matrix = {{0.5,0.75}, {1.2,0.8}};
    std::vector<double> b = {6,8};
    std::vector<double> f = {1.5,2.5,0};
    std::vector<int> s = {1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    return m.make_simplex(); //20 +
}

double test8(){
    std::vector<std::vector<double>> matrix = {{10,5}, {5,10}};
    std::vector<double> b = {100,80};
    std::vector<double> f = {100,50,0};
    std::vector<int> s = {1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    return m.make_simplex(); //1000 +
}

double test9(){
    std::vector<std::vector<double>> matrix = {{3,4}, {1,5}, {2,1}};
    std::vector<double> b = {10,30,30};
    std::vector<double> f = {1,2,0};    
    std::vector<int> s = {1,1,1};
    simplex_method m(std::move(matrix), std::move(b), std::move(f), std::move(s), max_func);
    double r = m.make_simplex();
    r = m.get_optimum();
    return r;
}