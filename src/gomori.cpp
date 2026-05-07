#include "gomori.h"
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <iostream>
#include <map>

gomori::gomori(std::vector<std::vector<double>>&& matrix, std::vector<double>&& b, 
               std::vector<double>&& f, std::vector<int>&& sign, optimal_func param)
    : sm(std::move(matrix), std::move(b), std::move(f), std::move(sign), param), 
      count_cutting_off(-1), max_index(sm.matrix[0].size()), bad_quest(false)
{
    sm.make_simplex();
}

bool gomori::has_remnant()
{
    for(int i = 0; i < sm.basise.size(); ++i) {
        double frac = get_gomori_fraction(sm.b[i]);
        if(frac > 1e-6 && frac < 1 - 1e-6) {
            return true;
        }
    }
    return false;
}

std::vector<double> gomori::get_basise(){
    return sm.basise;
}
bool gomori::has_negative_b() {
    for(double val : sm.b) {
        if(val < -1e-8) return true;
    }
    return false;
}

double gomori::get_gomori_fraction(double a)
{
    double int_part;
    double frac = std::modf(a, &int_part);

    if (a >= 0) return frac;

    if (std::abs(frac) < 1e-10) return 0.0;
    return 1.0 + frac;
}

void gomori::add_new_restrict()
{
    int pivot_row = -1;
    double max_frac = -1;
    
    for(int i = 0; i < sm.basise.size(); ++i) {
        double frac = get_gomori_fraction(sm.b[i]);
        if(frac > 1e-6 && frac < 1 - 1e-6) {
            if(frac > max_frac + 1e-10) {
                max_frac = frac;
                pivot_row = i;
            }
        }
    }
    
    if(pivot_row == -1) {
        //std::cerr << "Ошибка: не найдена строка для отсечения\n";
        return;
    }
    
    int old_matrix_cols = sm.matrix[0].size();
    std::vector<double> new_restrict(old_matrix_cols, 0.0);
    for(int j = 0; j < old_matrix_cols; ++j) {
        double frac = get_gomori_fraction(sm.matrix[pivot_row][j]);
        new_restrict[j] = -frac;
        if(std::abs(new_restrict[j]) < 1e-10) new_restrict[j] = 0.0;
    }
    
    double new_b = -get_gomori_fraction(sm.b[pivot_row]);

    sm.matrix.push_back(new_restrict);
    sm.b.push_back(new_b);
    sm.sign.push_back(1);

    for(int i = 0; i < sm.matrix.size(); ++i) {
        if(i == sm.matrix.size() - 1) {
            sm.matrix[i].push_back(1.0);
        } else {
            sm.matrix[i].push_back(0.0);
        }
    }
    
    sm.f.insert(sm.f.end() - 1, 0.0);
    
    sm.basise.push_back(sm.matrix[0].size() - 1);
}

bool gomori::dual_simplex_step() {
    int pivot_row = -1;
    double most_negative = 0;
    for(int i = 0; i < sm.b.size(); ++i) {
        if(sm.b[i] < most_negative - 1e-8) {
            most_negative = sm.b[i];
            pivot_row = i;
        }
    }
    
    if(pivot_row == -1) return true;
    
    int pivot_col = -1;
    double min_ratio = std::numeric_limits<double>::max();
    
    for(int j = 0; j < sm.matrix[0].size(); ++j) {
        if(sm.matrix[pivot_row][j] >= -1e-10) continue;
        
        double ratio = std::abs(sm.f[j] / sm.matrix[pivot_row][j]);
        
        if(ratio < min_ratio - 1e-10) {
            min_ratio = ratio;
            pivot_col = j;
        }
    }
    
    if(pivot_col == -1) {
        // std::cerr << "Нет допустимого столбца для двойственного шага\n";
        // std::cerr << "Строка " << pivot_row << " имеет b = " << sm.b[pivot_row] << "\n";
        // std::cerr << "Коэффициенты строки: ";
        // for(int j = 0; j < sm.matrix[0].size(); ++j) {
        //     std::cerr << sm.matrix[pivot_row][j] << " ";
        // }
        // std::cerr << "\n";
        
        //std::cerr << "Пробуем прямой симплекс для восстановления допустимости\n";
        
        int artificial_col = sm.matrix[0].size();
        for(int i = 0; i < sm.matrix.size(); ++i) {
            sm.matrix[i].push_back(0.0);
        }
        sm.matrix[pivot_row][artificial_col] = 1.0;
        sm.f.insert(sm.f.end() - 1, 1000.0);
        
        sm.basise[pivot_row] = artificial_col;
        
        sm.b[pivot_row] = -sm.b[pivot_row];
        for(int j = 0; j < sm.matrix[0].size(); ++j) {
            sm.matrix[pivot_row][j] = -sm.matrix[pivot_row][j];
        }
        
        return true;
    }
    
    double pivot_val = sm.matrix[pivot_row][pivot_col];

    for(int j = 0; j < sm.matrix[0].size(); ++j) {
        sm.matrix[pivot_row][j] /= pivot_val;
    }
    sm.b[pivot_row] /= pivot_val;

    for(int i = 0; i < sm.matrix.size(); ++i) {
        if(i == pivot_row) continue;
        
        double factor = sm.matrix[i][pivot_col];
        if(std::abs(factor) > 1e-10) {
            for(int j = 0; j < sm.matrix[0].size(); ++j) {
                sm.matrix[i][j] -= factor * sm.matrix[pivot_row][j];
            }
            sm.b[i] -= factor * sm.b[pivot_row];
        }
    }

    double f_factor = sm.f[pivot_col];
    if(std::abs(f_factor) > 1e-10) {
        for(int j = 0; j < sm.f.size() - 1; ++j) {
            sm.f[j] -= f_factor * sm.matrix[pivot_row][j];
        }
        sm.f[sm.f.size() - 1] -= f_factor * sm.b[pivot_row];
    }
    
    sm.basise[pivot_row] = pivot_col;
    
    return true;
}

bool gomori::primal_simplex_step() {
    int pivot_col = -1;
    
    for(int j = 0; j < sm.f.size() - 1; ++j) {
        if(sm.f[j] > 1e-8) {
            pivot_col = j;
            break;
        }
    }
    
    if(pivot_col == -1) return true;

    int pivot_row = -1;
    double min_ratio = std::numeric_limits<double>::max();
    
    for(int i = 0; i < sm.matrix.size(); ++i) {
        if(sm.matrix[i][pivot_col] > 1e-10) {
            double ratio = sm.b[i] / sm.matrix[i][pivot_col];
            if(ratio < min_ratio - 1e-10 && ratio >= 0) {
                min_ratio = ratio;
                pivot_row = i;
            }
        }
    }
    
    if(pivot_row == -1) {
        // std::cerr << "Задача не ограничена\n";
        return false;
    }

    double pivot_val = sm.matrix[pivot_row][pivot_col];

    for(int j = 0; j < sm.matrix[0].size(); ++j) {
        sm.matrix[pivot_row][j] /= pivot_val;
    }
    sm.b[pivot_row] /= pivot_val;

    for(int i = 0; i < sm.matrix.size(); ++i) {
        if(i == pivot_row) continue;
        
        double factor = sm.matrix[i][pivot_col];
        if(std::abs(factor) > 1e-10) {
            for(int j = 0; j < sm.matrix[0].size(); ++j) {
                sm.matrix[i][j] -= factor * sm.matrix[pivot_row][j];
            }
            sm.b[i] -= factor * sm.b[pivot_row];
        }
    }

    double f_factor = sm.f[pivot_col];
    if(std::abs(f_factor) > 1e-10) {
        for(int j = 0; j < sm.f.size() - 1; ++j) {
            sm.f[j] -= f_factor * sm.matrix[pivot_row][j];
        }
        sm.f[sm.f.size() - 1] -= f_factor * sm.b[pivot_row];
    }

    sm.basise[pivot_row] = pivot_col;
    
    return true;
}

int gomori::method_gomori()
{
    int count = 0;
    const int MAX_ITER = 100;
    
    // std::cout << "Начальное решение симплекс-метода: " << sm.f[sm.f.size()-1] << '\n';
    
    while(has_remnant() && count < MAX_ITER) {
        // std::cout << "\n--- Итерация Гомори " << count + 1 << " ---\n";
        
        add_new_restrict();
        // std::cout << "Добавлено новое ограничение\n";
        
        int dual_iter = 0;
        while(has_negative_b() && dual_iter < 50) {
            bool success = dual_simplex_step();
            if(!success) {
                // std::cerr << "Двойственный симплекс не сошёлся на итерации " << count << "\n";
                return -1;
            }
            dual_iter++;
        }
        
        if(has_negative_b()) {
            // std::cerr << "Не удалось восстановить допустимость после " << dual_iter << " итераций\n";
            return -1;
        }
        
        // std::cout << "Допустимость восстановлена. Значение функции: " << sm.f[sm.f.size()-1] << '\n';
        
        int primal_iter = 0;
        while(primal_iter < 50) {
            bool optimal = true;
            for(int j = 0; j < sm.f.size() - 1; ++j) {
                if(sm.f[j] > 1e-8) {
                    optimal = false;
                    break;
                }
            }
            
            if(optimal) break;
            
            bool success = primal_simplex_step();
            if(!success) {
                // std::cerr << "Прямой симплекс не сошёлся\n";
                return -1;
            }
            primal_iter++;
        }
        
        // std::cout << "Оптимизация завершена. Значение функции: " << sm.f[sm.f.size()-1] << '\n';
        
        // std::cout << "Текущее решение:\n";
        // for(int i = 0; i < sm.basise.size(); ++i) {
        //     if(sm.basise[i] < max_index) {
        //         std::cout << "x" << sm.basise[i] + 1 << " = " << sm.b[i] << "\n";
        //     }
        // }
        count++;
    }
    
    if(count == 0) {
        // std::cout << "Решение уже целочисленное\n";
    } else if(count >= MAX_ITER) {
        // std::cout << "Достигнут максимум итераций\n";
        return -1;
    }
    
    count_cutting_off = count;
    
    std::cout << "\n=================================\n";
    std::cout << "Оптимальное целочисленное решение: " << sm.f[sm.f.size()-1] << '\n';
    std::cout << "Количество отсечений: " << count_cutting_off << '\n';
    std::cout << "=================================\n";
    
    return count;
}

double gomori::get_optimum() const
{
    return sm.f[sm.f.size()-1];
}