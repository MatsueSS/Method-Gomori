#include <iostream>
#include <vector>
#include <cmath>

#include "lab1.cpp"

int main(void)
{
    //result ->

    std::vector<int> remnants;
    PentagonGenerator pg;
    for(int i = 0; i < 10; ++i) {
        {
            auto matrix = std::vector<std::vector<double>>();
            auto b = std::vector<double>();
            auto f = std::vector<double>();
            auto sign = std::vector<int>();

            // pg.generate_pentagon_integer(matrix, b, f, sign);
            //pg.generate_pentagon_direct(matrix, b, f, sign);
            pg.good_generate(matrix, b, f, sign);

            std::cout << "\n=====\n";

            print_matrix(matrix);
            print_vector(b);
            print_vector(f);

            std::cout << "\n=====\n";

            continue;
            
            gomori sm(std::move(matrix), std::move(b), 
                            std::move(f), std::move(sign), max_func);

            sm.print_result();
            
            int result = sm.method_gomori();
            
            if(result != -1 && result != 0)
                remnants.push_back(result);
            else
                --i;
        }

    }

    int sum = 0;
    for(int i : remnants)
        sum += i;

    std::cout << sum/(double)remnants.size() << '\n';
    
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

    return 0;
}