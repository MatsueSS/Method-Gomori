#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

#include "gomori.h"
#include "mvag.c"

int main(void)
{
    //result ->

    // std::vector<int> remnants;
    // PentagonGenerator pg;
    // int count = 0;
    // for(int i = 0; i < 1000000; ++i) {
    //     {
    //         count++;
    //         auto matrix = std::vector<std::vector<double>>();
    //         auto b = std::vector<double>();
    //         auto f = std::vector<double>();
    //         auto sign = std::vector<int>();

    //         // pg.generate_pentagon_integer(matrix, b, f, sign);
    //         //pg.generate_pentagon_direct(matrix, b, f, sign);
    //         pg.good_generate(matrix, b, f, sign);
            
    //         gomori sm(std::move(matrix), std::move(b), 
    //                         std::move(f), std::move(sign), max_func);
            
    //         int result = sm.method_gomori();
            
    //         if(result != -1 && result != 0)
    //             remnants.push_back(result);
    //         else
    //             --i;
    //     }

    // }

    // int sum = 0;
    // int min_val = remnants[0], max_val = remnants[0];
    // for(int i : remnants){
    //     sum += i;
    //     min_val = std::min(min_val, i);
    //     max_val = std::max(max_val, i);
    // }

    // double k = sum/(double)remnants.size();

    // double n_sum = 0;
    // for(int i : remnants){
    //     n_sum += (i - k)*(i - k);
    // }

    // double disper = n_sum/(double)remnants.size();

    // std::cout << count << '\n';
    // std::cout << k << '\n';
    // std::cout << disper << '\n';
    // std::cout << min_val << ' ' << max_val<< '\n';
    
    // option_1();
    // option_2();
    // option_4();
    // option_5();
    // option_6();
    // option_7();
    // option_9();
    // option_10();
    // option_11();
    // option_12();
    // option_13();
    // option_14();
    // option_15();
    // option_16();
    // option_18();
    // option_19();
    // option_20();

    // std::vector<std::vector<double>> matrix = {{3.16005, -0.651156}, {1.11032, 0.770733}, {1.45603, 5.34204}};
    // std::vector<double> b = {17.259, 9.22272, 30.5907}, f = {4.22069, 5.59835, 0};
    // std::vector<int> sign = {1,1,1};

    // gomori g(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    // g.method_gomori();
    // g.print_result();

    // PentagonGenerator pg;
    // auto matrix = std::vector<std::vector<double>>();
    // auto b = std::vector<double>();
    // auto f = std::vector<double>();
    // auto sign = std::vector<int>();

    // pg.good_generate(matrix, b, f, sign);

//knapsack

    // std::vector<std::vector<double>> matrix = {{2,2,2,1,2,2,2,3,3,1}, 
    //                                             {1,3,3,2,2,2,1,4,2,2},
    //                                             {4,1,2,2,2,3,3,3,2,1},
    //                                             {1,0,0,0,0,0,0,0,0,0},
    //                                             {0,1,0,0,0,0,0,0,0,0},
    //                                             {0,0,1,0,0,0,0,0,0,0},
    //                                             {0,0,0,1,0,0,0,0,0,0},
    //                                             {0,0,0,0,1,0,0,0,0,0},
    //                                             {0,0,0,0,0,1,0,0,0,0},
    //                                             {0,0,0,0,0,0,1,0,0,0},
    //                                             {0,0,0,0,0,0,0,1,0,0},
    //                                             {0,0,0,0,0,0,0,0,1,0},
    //                                             {0,0,0,0,0,0,0,0,0,1},
    //                                             {-1,0,0,0,0,0,0,0,0,0},
    //                                             {0,-1,0,0,0,0,0,0,0,0},
    //                                             {0,0,-1,0,0,0,0,0,0,0},
    //                                             {0,0,0,-1,0,0,0,0,0,0},
    //                                             {0,0,0,0,-1,0,0,0,0,0},
    //                                             {0,0,0,0,0,-1,0,0,0,0},
    //                                             {0,0,0,0,0,0,-1,0,0,0},
    //                                             {0,0,0,0,0,0,0,-1,0,0},
    //                                             {0,0,0,0,0,0,0,0,-1,0},
    //                                             {0,0,0,0,0,0,0,0,0,-1}
    //                                         };
    // std::vector<double> f = {6,5,2,3,4,5,4,8,7,3,0};
    // std::vector<double> b = {10,7,8,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
    // std::vector<int> sign = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    // auto start = std::chrono::high_resolution_clock::now();
    // gomori sm(std::move(matrix), std::move(b), std::move(f), std::move(sign), max_func);
    // sm.method_gomori();
    // auto end = std::chrono::high_resolution_clock::now();

    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // auto duration_sec = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    
    // // Выводим время
    // std::cout << "\n=================================\n";
    // std::cout << "Время выполнения:\n";
    // std::cout << "  - " << duration_sec.count() << " секунд\n";
    // std::cout << "  - " << duration.count() << " миллисекунд\n";
    // std::cout << "  - " << duration_micro.count() << " микросекунд\n";
    // std::cout << "=================================\n";

    srand(time(nullptr));
    int i = 1000, nc = 0;
    while(i != 0){
        double* values = NULL, *limit = NULL;
        int l, size;

        generate_quest(&values, &limit, &size, &l);

        std::vector<std::vector<double>> matrix (size + 1 + size, std::vector<double>(size, 0));
        std::vector<double> f(values, values+size);
        f.push_back(0);
        matrix[0] = std::vector<double>(limit, limit+size);
        std::vector<double> b (size+1+size, 1);
        b[0] = l;
        for(int i = size+1; i < size+size+1; ++i) b[i] = 0;

        std::vector<int> sign (size+1+size, 1);

        for(int i = 1; i < size+1; ++i){
            for(int j = 0; j < size; ++j){
                if(i-1 == j) matrix[i][j] = 1;
                else matrix[i][j] = 0;
            }
        }
        for(int i = size+1; i < size+size+1; ++i){
            for(int j = 0; j < size; ++j){
                if(i-size-1 == j) matrix[i][j] = -1;
                else matrix[i][j] = 0;
            }
        }

        auto n_matrix = matrix;
        auto n_f = f;
        auto n_b = b;

        gomori sm(std::move(matrix), std::move(b), std::move(f), std::move(sign), optimal_func::max_func);
        int c = sm.method_gomori();
        double res_g = sm.get_optimum();

        if(c == -1) continue;

        TempDancig res = one_dimensional_knapsack(values, limit, size, l);
        if(std::abs(std::abs(res.val) - std::abs(res_g)) > 1e-10){
            nc++;
            std::cout << "===\n";
            std::cout << "Методы не сошлись\n";
            std::cout << res.val << ' ' << res_g << '\n';

            print_matrix(n_matrix);
            print_vector(n_f);
            print_vector(n_b);

            for(int i = 0; i < size; ++i){
                if(res.pos & (1 << i)){
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            }

            std::cout << "\n===\n";
        }
        i--;
        free(values);
        free(limit);
    }
    std::cout << nc << '\n';

    return 0;
}