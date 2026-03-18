#include "generator_zlp.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <ctime>

void PentagonGenerator::generate_pentagon_direct(std::vector<std::vector<double>>& matrix, std::vector<double>& b, std::vector<double>& f, std::vector<int>& sign)
{
    matrix.clear();
    b.clear();
    f.clear();
    sign.clear();
    
    double xB, xC, yC, xD, yD, yE;
    
    do {
        xB = random_double(2.0, 6.0);
        xC = random_double(xB + 0.5, xB + 2.5);
        yC = random_double(1.5, 4.0);
        xD = random_double(0.5, xC - 0.5);
        yD = random_double(yC + 0.5, yC + 2.5);
        yE = random_double(yD + 0.5, yD + 3.0);
    } while (xD >= xC - 0.1 || yD <= yC + 0.1 || yE <= yD + 0.1);
    
    // B - C
    double a1 = yC;
    double b1 = xB - xC;
    double c1 = xB * yC;
    
    // C - D
    double a2 = yD - yC;
    double b2 = xC - xD;
    double c2 = xC * yD - xD * yC;
    
    // D - E
    double a3 = yE - yD;
    double b3 = xD;
    double c3 = xD * yE;
    
    auto fix_inequality = [&](double& a, double& b, double& c) {
        if (c < 0) {
            a = -a;
            b = -b;
            c = -c;
        }
    };
    
    fix_inequality(a1, b1, c1);
    fix_inequality(a2, b2, c2);
    fix_inequality(a3, b3, c3);
    
    matrix.push_back({a1, b1}); b.push_back(c1); sign.push_back(1);
    matrix.push_back({a2, b2}); b.push_back(c2); sign.push_back(1);
    matrix.push_back({a3, b3}); b.push_back(c3); sign.push_back(1);
    
    double f1 = random_double(1.0, 8.0);
    double f2 = random_double(1.0, 8.0);
    f = {f1, f2, 0.0};
}

void PentagonGenerator::generate_pentagon_integer(std::vector<std::vector<double>>& matrix, 
                                                   std::vector<double>& b, 
                                                   std::vector<double>& f, 
                                                   std::vector<int>& sign) 
{
    matrix.clear();
    b.clear();
    f.clear();
    sign.clear();
    
    int xB, xC, yC, xD, yD, yE;
    
    do {
        xB = random_int(2, 5);
        xC = random_int(xB + 1, xB + 3);
        yC = random_int(2, 4);
        xD = random_int(1, xC - 1);
        yD = random_int(yC + 1, yC + 3);
        yE = random_int(yD + 1, yD + 3);
    } while (xD >= xC || yD <= yC || yE <= yD); // невыпуклости
    
    //A(0,0) B(xB,0) C(xC,yC) D(xD,yD) E(0,yE)
    
    //B - C
    int a1 = yC - 0;
    int b1 = xB - xC;
    int c1 = xB * yC - xC * 0;
    
    //C - D
    int a2 = yD - yC;
    int b2 = xC - xD;
    int c2 = xC * yD - xD * yC;
    
    //D - E
    int a3 = yE - yD;
    int b3 = xD - 0;
    int c3 = xD * yE - 0 * yD;
    
    auto fix_inequality = [&](int& a, int& b, int& c) {
        if (c < 0) {
            a = -a;
            b = -b;
            c = -c;
        }
    };
    
    fix_inequality(a1, b1, c1);
    fix_inequality(a2, b2, c2);
    fix_inequality(a3, b3, c3);
    
    matrix.push_back({(double)a1, (double)b1}); b.push_back((double)c1); sign.push_back(1);
    matrix.push_back({(double)a2, (double)b2}); b.push_back((double)c2); sign.push_back(1);
    matrix.push_back({(double)a3, (double)b3}); b.push_back((double)c3); sign.push_back(1);
    
    int f1 = random_int(1, 5);
    int f2 = random_int(1, 5);
    f = {(double)f1, (double)f2, 0.0};
    std::cout << "Ограничения:\n";
    std::cout << a1 << "x + " << b1 << "y ≤ " << c1 << "\n";
    std::cout << a2 << "x + " << b2 << "y ≤ " << c2 << "\n";
    std::cout << a3 << "x + " << b3 << "y ≤ " << c3 << "\n";
}

void PentagonGenerator::good_generate(std::vector<std::vector<double>>& matrix, std::vector<double>& b, std::vector<double>& f, std::vector<int>& sign)
{
    matrix.clear();
    b.clear();
    f.clear();
    sign.clear();

    int xB, xC, yC, xD, yD, yE;

    time(nullptr);

    xC = rand()%7 + 14;
    yC = rand()%7 + 1;

    xD = rand()%7 + 1;
    yD = rand()%7 + 14;

    double val_k = (double)(yD-yC)/(xD-xC);
    double val_b = (double)yC - ((double)xC/(xD-xC))*(yD-yC);

    int i_k = static_cast<int>(val_k+1);
    int i_b = static_cast<int>(val_b+1);

    xB = rand()%(xC-xD-1) + (xD+1);
    yE = rand()%(yD-i_k*xB-i_b-1) + (i_k*xB+i_b+1);

    //B - C
    int a1 = yC - 0;
    int b1 = xB - xC;
    int c1 = xB * yC - xC * 0;
    
    //C - D
    int a2 = yD - yC;
    int b2 = xC - xD;
    int c2 = xC * yD - xD * yC;
    
    //D - E
    int a3 = yE - yD;
    int b3 = xD - 0;
    int c3 = xD * yE - 0 * yD;
    
    auto fix_inequality = [&](int& a, int& b, int& c) {
        if (c < 0) {
            a = -a;
            b = -b;
            c = -c;
        }
    };
    
    fix_inequality(a1, b1, c1);
    fix_inequality(a2, b2, c2);
    fix_inequality(a3, b3, c3);
    
    matrix.push_back({(double)a1, (double)b1}); b.push_back((double)c1); sign.push_back(1);
    matrix.push_back({(double)a2, (double)b2}); b.push_back((double)c2); sign.push_back(1);
    matrix.push_back({(double)a3, (double)b3}); b.push_back((double)c3); sign.push_back(1);
    
    int f1 = random_int(1, 5);
    int f2 = random_int(1, 5);
    f = {(double)f1, (double)f2, 0.0};
}