#include "good_funcs.h"
#include "prepare_simplex.h"
#include "generator_zlp.h"
#include "gomori.h"

#include <iostream>

void option_1(){
    std::vector<std::vector<double>> matrix = {{6,4,3}, {5,3,2}};
    std::vector<double> b = {25,15}, f = {1,2,3,0};
    std::vector<int> sign = {1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 1 =====\n";
    g.print_result(); // (0,0,7) - 21 | 1 отсечение - excel +
}

void option_2(){
    std::vector<std::vector<double>> matrix = {{3,4}, {2,1}, {0,1}};
    std::vector<double> b = {10,8,5}, f = {110,90,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 2 =====\n";
    g.print_result(); // (3,0) - 330 | 1 отсечение - excel +
}

void option_4(){
    std::vector<std::vector<double>> matrix = {{1,1,0},{1,0,2},{3,1,1}};
    std::vector<double> b = {2,3,4}, f = {1,2,1,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 4 =====\n";
    g.print_result(); // (0,2,1) - 5 | 1 отсечения - excel +
}

void option_5(){
    std::vector<std::vector<double>> matrix = {{1,2,-2}, {1,3,1}};
    std::vector<double> b = {1,4}, f = {-1,3,-1,0};
    std::vector<int> sign = {1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 5 =====\n";
    g.print_result(); // (0,1,1) - 2 | 1 отсечений - excel +
}

void option_6(){
    std::vector<std::vector<double>> matrix = {{3,4,-1}, {1,2,0}, {2,-1,3}};
    std::vector<double> b = {7,3,5}, f = {1,2,1,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 6 =====\n";
    g.print_result(); // (1,1,1) - 4 | 2 отсечения - excel +
}

void option_7(){
    std::vector<std::vector<double>> matrix = {{1,3,0,1}, {2,1,0,0}, {0,1,4,1}};
    std::vector<double> b = {4,3,4}, f = {2,4,1,1,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 7 =====\n";
    g.print_result(); // (1,1,0,0) - 6 | 1 отсечение - excel +
}

void option_9(){
    std::vector<std::vector<double>> matrix = {{1,3,1}, {2,1,0},{0,1,4}};
    std::vector<double> b = {2,1,2}, f = {2,1,1,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 9 =====\n";
    g.print_result(); // (0,0,0) - 0 | 3 отсечения - excel +
}

void option_10(){
    std::vector<std::vector<double>> matrix = {{1,1,0}, {1,0,2}, {1,1,1}};
    std::vector<double> b = {2,3,4}, f = {1,1,1,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 10 =====\n";
    g.print_result(); // (1,1,1) - 3 | 1 отсечение - excel +
}

void option_11(){
    std::vector<std::vector<double>> matrix = {{2,2,1}, {1,4,-1}};
    std::vector<double> b = {9,10}, f = {3,1,0,0};
    std::vector<int> sign = {1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 11 =====\n";
    g.print_result(); // (4,0,1) - 12 | 1 отсечение - excel +
}

void option_12(){
    std::vector<std::vector<double>> matrix = {{2,2,0}, {2,4,0}, {3,3,1}};
    std::vector<double> b = {1,4,6}, f = {4,1,0,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 12 =====\n";
    g.print_result(); // (0,0,0) - 0 | 1 отсечение - excel +
}

void option_13(){
    std::vector<std::vector<double>> matrix = {{3,1,0}, {3,2,1}};
    std::vector<double> b = {6,5}, f = {1,1,0,0};
    std::vector<int> sign = {1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 13 =====\n";
    g.print_result(); // (1,1,0) - 2 | 1 отсечение - excel +
}

void option_14(){
    std::vector<std::vector<double>> matrix = {{-1,-1,-2}, {2,-3,1}, {2,-5,6}};
    std::vector<double> b = {5,3,5}, f = {1,-3,-2,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 14 =====\n";
    g.print_result(); // (1,0,0) - 1 | 1 отсечение - excel +
}

void option_15(){
    std::vector<std::vector<double>> matrix = {{1,1,0}, {1,0,2}, {3,1,0}};
    std::vector<double> b = {2,3,4}, f = {2,2,2,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 15 =====\n";
    g.print_result(); // (1,1,1) - 6 | 1 отсечение - excel +
}

void option_16(){
    std::vector<std::vector<double>> matrix = {{1,3,1}, {2,1,0}, {0,1,4}};
    std::vector<double> b = {4,1,3}, f = {2,4,1,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 16 =====\n";
    g.print_result(); // (0,1,0) - 4 | 2 отсечения - excel +
}

void option_18(){
    std::vector<std::vector<double>> matrix = {{2,1,2}, {1,1,-1}, {4,1,0}};
    std::vector<double> b = {10,5,7}, f = {-8,5,1,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 18 =====\n";
    g.print_result(); // (0,6,2) - 32 | 1 отсечение
}

void option_19(){
    std::vector<std::vector<double>> matrix = {{3,1,-2}, {1,0,1}, {1,2,-1}};
    std::vector<double> b = {1,2,4}, f = {1,1,-1,0};
    std::vector<int> sign = {1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 19 =====\n";
    g.print_result(); // (0,3,2) - 1 | 2 отсечения - excel +
}

void option_20(){
    std::vector<std::vector<double>> matrix = {{1,3,0,1}, {2,1,0,0}, {0,1,4,-1}};
    std::vector<double> b = {4,3,3}, f = {2,4,1,1,0};
    std::vector<int> sign = {1,1,1,1};

    gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    int count = g.method_gomori();
    std::cout << "\n===== Вариант 20 =====\n";
    g.print_result(); // (1,0,1,3) - 6 | 2 отсечения
}