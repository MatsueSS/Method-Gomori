#include "gomori.h"

#include <cmath>
#include <iomanip>
#include <algorithm>
#include <limits>

gomori::gomori(std::vector<std::vector<double>>&& matrix, std::vector<double>&& b, std::vector<double>&& f, std::vector<int>&& sign, optimal_func param)
    : sm(std::move(matrix), std::move(b), std::move(f), std::move(sign), param), count_cutting_off(-1), max_index(sm.matrix[0].size()), bad_quest(false)
{
    sm.make_simplex();
}


// bool gomori::has_remnant()
// {
//     for(int i = 0; i < sm.basise.size(); ++i){
//         double frac = get_gomori_fraction(sm.b[i]);
//         if(frac > 1e-10 && frac < 1 - 1e-10)
//             return true;
//     }
//     return false;
// }

bool gomori::has_remnant()
{
    int pivot_row = -1;
    double max_frac = -1;
    for(int i = 0; i < max_index; ++i) {
        auto it = std::find(sm.basise.begin(), sm.basise.end(), i);
        if(it == sm.basise.end())
            continue;
        int pos = std::distance(sm.basise.begin(), it);
        double frac = get_gomori_fraction(sm.b[pos]);
        if(frac > 1e-5 && frac < 1 - 1e-5) {
            return true;
        }
    }
    return false;
}

//Функция, для выбора переменной, которую нужно заносить в базис при методе Гомори
int gomori::index_lead() 
{
    int last_row = sm.matrix.size() - 1;
    int pivot_index = -1;
    double min_ratio = INFINITY;
    
    for(int i = 0; i < sm.f.size() - 2; ++i) {
        if(sm.matrix[last_row][i] < -1e-10) {
            double ratio = std::abs(sm.f[i] / sm.matrix[last_row][i]);
            if(ratio < min_ratio) {
                min_ratio = ratio;
                pivot_index = i;
            }
        }
    }
    
    return pivot_index;
}

double gomori::get_gomori_fraction(double val)
{
    double int_part;
    double frac = std::modf(val, &int_part);
    if(frac < 0) {
        frac = 1.0 + frac;
    }
    
    return frac;
}

void gomori::add_new_restrict()
{
    int pivot_row = -1;
    double max_frac = -1;
    for(int i = 0; i < max_index; ++i) {
        auto it = std::find(sm.basise.begin(), sm.basise.end(), i);
        if(it == sm.basise.end())
            continue;
        int pos = std::distance(sm.basise.begin(), it);
        double frac = get_gomori_fraction(sm.b[pos]);
        if(frac > 1e-5 && frac < 1 - 1e-5) {
            if(frac > max_frac + 1e-10) {
                max_frac = frac;
                pivot_row = pos;
            }
        }
    }
    
    if(pivot_row == -1) {
        std::cerr << "Ошибка: не найдена строка для отсечения\n";
        return;
    }
    
    int old_matrix_rows = sm.matrix.size();
    int old_matrix_cols = sm.matrix[0].size();
    int old_f_size = sm.f.size();
    
    std::vector<double> new_restrict(old_matrix_cols, 0.0);
    for(int j = 0; j < old_matrix_cols; ++j) {
        double frac = get_gomori_fraction(sm.matrix[pivot_row][j]);
        new_restrict[j] = (std::abs(frac) < 1e-10) ? 0.0 : -frac;
    }
    
    double new_b = -get_gomori_fraction(sm.b[pivot_row]);
    
    sm.matrix.push_back(std::move(new_restrict));
    sm.b.push_back(new_b);
    sm.sign.push_back(1);
    
    for(int i = 0; i < sm.matrix.size(); ++i) {
        if(i == sm.matrix.size() - 1) {
            sm.matrix[i].push_back(1.0);
        } else {
            sm.matrix[i].push_back(0.0);
        }
    }
    
    if(old_f_size >= 2) {
        std::vector<double> new_f;
        new_f.reserve(old_f_size + 1);
        
        for(int i = 0; i < old_f_size - 1; ++i) {
            new_f.push_back(sm.f[i]);
        }
        new_f.push_back(0.0);
        new_f.push_back(sm.f[old_f_size - 1]);
        
        sm.f = std::move(new_f);
    } else {
        sm.f.push_back(0.0);
        sm.f.push_back(0.0);
    }
    
    sm.basise.push_back(sm.matrix[0].size() - 1);
}

void gomori::make_good_plan()
{
    bool good_plan = true;
    std::vector<int> indexes;
    for(int i = 0; i < sm.b.size(); ++i){
        if(sm.b[i] < 0){
            good_plan = false;
            indexes.push_back(i);
        }
    }
    if(good_plan)
        return;

    int pivot_row = -1;
    int max_abs_val = 0;
    for(int val : indexes){
        if(std::abs(sm.b[val]) > max_abs_val){
            max_abs_val = std::abs(sm.b[val]);
            pivot_row = val;
        }
    }

    int pivot_index = -1;
    int min_diff = INT32_MAX;
    for(int i = 0; i < sm.matrix[0].size(); ++i){
        if(sm.matrix[pivot_row][i] >= 0)
            continue;
        double diff = sm.f[i]/sm.matrix[pivot_row][i];
        if(diff < min_diff && std::abs(diff) > 1e-10){
            pivot_index = i;
            min_diff = diff;
        }
    }

    if(pivot_index == -1){
        min_diff = INT32_MAX;
        for(int i = 0; i < sm.matrix[0].size(); ++i){
            if(sm.matrix[pivot_row][i] >= 0)
                continue;
            if(min_diff > sm.matrix[pivot_row][i]){
                min_diff = sm.matrix[pivot_row][i];
                pivot_index = i;
            }
        }
    }

    if(pivot_index == -1){
        bad_quest = true;
        std::cerr << "Не удалось найти pivot_index в make_good_plan\n";
        return;
    }

    sm.basise[pivot_row] = pivot_index;

    double pivot_val = sm.matrix[pivot_row][pivot_index];

    for(int i = 0; i < sm.matrix[0].size(); ++i){
        sm.matrix[pivot_row][i] /= pivot_val;
        if(std::abs(sm.matrix[pivot_row][i]) < 1e-10)
            sm.matrix[pivot_row][i] = 0;
    }
    sm.b[pivot_row] /= pivot_val;

    for(int i = 0; i < sm.matrix.size(); ++i){
        if(i == pivot_row)
            continue;
        double pivot_elem = sm.matrix[i][pivot_index];
        for(int j = 0; j < sm.matrix[0].size(); ++j){
            sm.matrix[i][j] -= (sm.matrix[pivot_row][j]*pivot_elem);
        }
        sm.b[i] -= (sm.b[pivot_row]*pivot_elem);
    }

    double f_pivot_val = sm.f[pivot_index];
    for(int i = 0; i < sm.f.size()-1; ++i){
        sm.f[i] -= (f_pivot_val*sm.matrix[pivot_row][i]);
    }
    sm.f[sm.f.size()-1] -= (f_pivot_val*sm.b[pivot_row]);

    return;
}

int gomori::prepare_gomori()
{
    add_new_restrict();

    int pivot_index = index_lead();
    if(pivot_index == -1) {
        return -1;
    }

    sm.basise.back() = pivot_index;
    
    int last_row = sm.matrix.size()-1;
    
    double pivot_val = sm.matrix[last_row][pivot_index];
    if(std::abs(pivot_val) < 1e-10) {
        return -1;
    }

    for(int i = 0; i < sm.matrix[0].size(); ++i){
        sm.matrix[last_row][i] /= pivot_val;
        if(std::abs(sm.matrix[last_row][i]) < 1e-10)
            sm.matrix[last_row][i] = 0;
    }
    sm.b[last_row] /= pivot_val;

    for(int i = 0; i < last_row+1; ++i){
        if(i == last_row)
                continue;
        double temp_pivot_val = sm.matrix[i][pivot_index];
        for(int j = 0; j < sm.matrix[0].size(); ++j){
            sm.matrix[i][j] -= (temp_pivot_val*sm.matrix[last_row][j]);
        }
        sm.b[i] -= (temp_pivot_val*sm.b[last_row]);
    }

    double f_pivot_val = sm.f[pivot_index];
    for(int i = 0; i < sm.f.size()-1; ++i){
        sm.f[i] -= (f_pivot_val*sm.matrix[last_row][i]);
    }
    sm.f[sm.f.size()-1] -= (f_pivot_val*sm.b[last_row]);

    for(int i = 0; i < sm.matrix.size(); ++i){
        for(int j = 0; j < sm.matrix[0].size(); ++j){
            if(std::abs(sm.matrix[i][j]) < 1e-10)
                sm.matrix[i][j] = 0;
        }
        if(std::abs(sm.f[i]) < 1e-10)
            sm.f[i] = 0;
        if(std::abs(sm.b[i]) < 1e-10)
            sm.b[i] = 0;
    }

    make_good_plan();

    return 0;
}

int gomori::method_gomori()
{
    int count = 0;
    const int MAX_ITER = 100;  // Жёсткий лимит!
    
    while(has_remnant() && count < MAX_ITER) {
        
        int err = prepare_gomori();
        if(bad_quest)
            return -1;
        if(err == -1) {
            std::cout << "prepare_gomori не удался на итерации " << count << '\n';
            break;
        }
        
        int simplex_count = 0;
        while(true) {
            int val = find_max(sm.f);
            if(sm.f[val] <= 0) break;
            
            bool result = sm.simplex_step();
            if(!result) return -1;
            
            simplex_count++;
            if(simplex_count > 100) {
                std::cout << "Слишком много итераций симплекса\n";
                return -1;
            }
        }
        
        count++;
    }
    if(count == 0)
        return 0;

    count_cutting_off = count;
        
    return count;
}

double gomori::get_optimum() const
{
    double result = 0;
    for(int i = 0; i < sm.true_f.size()-1; ++i){
        for(int j = 0; j < sm.basise.size(); ++j){
            if(i == sm.basise[j]){
                result += (sm.b[j]*sm.true_f[i]);
            }
        }
    }
    return result;
}

void gomori::print_result() const
{
    std::vector<std::string> result (sm.matrix.size());
    std::cout << std::fixed << std::setprecision(2);
    std::string basise = "Базисные переменные - [";
    for(int i = 0; i < sm.basise.size(); ++i)
        basise += ("x" + std::to_string(int(sm.basise[i])+1) + ", ");
    basise.pop_back();
    basise += "]";

    for(int i = 0; i < sm.matrix.size(); ++i){
        for(int j = 0; j < sm.matrix[0].size(); ++j){
            if(j == 0){
                result[i] += (std::to_string(sm.matrix[i][j]));
            }
            if(sm.matrix[i][j] >= 0){
                result[i] += (" + " + std::to_string(sm.matrix[i][j]));
            } else {
                result[i] += (std::to_string(sm.matrix[i][j]));
            }
        }
    }

    for(int i = 0; i < sm.b.size(); ++i)
        result[i] += (" = " + std::to_string(sm.b[i]));

    std::string func_result = "Целевая функция: f = ";
    for(int i = 0; i < sm.f.size()-1; ++i)
        func_result += (" x" + std::to_string(i+1) + "*" + std::to_string(sm.f[i]) + " +");

    func_result += (" " + std::to_string(sm.f[sm.f.size()-1]));

    std::cout << "=================================\n";

    std::cout << "Матрица:\n";
    for(int i = 0; i < result.size(); ++i)
        std::cout << result[i] << '\n';

    std::cout << '\n' << basise << '\n';

    std::cout << '\n' << func_result << '\n';

    std::cout << '\n' << "Количество отсечений: " << count_cutting_off << '\n';

    std::cout << "=================================\n";
}


// int gomori::method_gomori()
// {
//     int count = 0;
//     const int MAX_ITER = 100;
    
//     while(has_remnant() && count < MAX_ITER) {
//         // 1. Добавляем отсечение (ваша существующая функция)
//         add_new_restrict();  // ← это add_cut()
        
//         // 2. Двойственный симплекс-метод - ПОКА не восстановится допустимость
//         while(has_negative_b()) {
//             bool success = dual_simplex_step();
//             if(!success) {
//                 std::cerr << "Двойственный симплекс не сошёлся на итерации " << count << "\n";
//                 return -1;
//             }
//         }
        
//         // 3. Обычный симплекс для оптимизации (ваш существующий код)
//         while(true) {
//             int val = find_max(sm.f);
//             if(sm.f[val] <= 0) break;
            
//             bool result = sm.simplex_step();
//             if(!result) {
//                 std::cout << "Задача не ограничена на итерации " << count << '\n';
//                 return -1;
//             }
//         }
        
//         count++;
//     }
    
//     count_cutting_off = (count == 0) ? 0 : count;
//     return count;
// }

// // Новая функция для проверки отрицательных B
// bool gomori::has_negative_b() {
//     for(double val : sm.b) {
//         if(val < -1e-8) return true;
//     }
//     return false;
// }

// // Новая функция для двойственного шага
// bool gomori::dual_simplex_step() {
//     // 1. Найти строку с самым отрицательным B
//     int pivot_row = -1;
//     double most_negative = 0;
//     for(int i = 0; i < sm.b.size(); ++i) {
//         if(sm.b[i] < most_negative - 1e-8) {
//             most_negative = sm.b[i];
//             pivot_row = i;
//         }
//     }
    
//     if(pivot_row == -1) return true;  // уже допустимо
    
//     // 2. Найти ведущий столбец по правилу минимального отношения
//     int pivot_col = -1;
//     double min_ratio = std::numeric_limits<double>::max();
    
//     for(int j = 0; j < sm.matrix[0].size(); ++j) {
//         if(sm.matrix[pivot_row][j] >= -1e-10) continue;  // только отрицательные
        
//         double ratio = sm.f[j] / sm.matrix[pivot_row][j];
//         if(ratio < min_ratio - 1e-10) {
//             min_ratio = ratio;
//             pivot_col = j;
//         }
//     }
    
//     // Если не нашли по правилу отношений, пробуем по самому отрицательному элементу
//     if(pivot_col == -1) {
//         double most_negative_elem = 0;
//         for(int j = 0; j < sm.matrix[0].size(); ++j) {
//             if(sm.matrix[pivot_row][j] < most_negative_elem - 1e-10) {
//                 most_negative_elem = sm.matrix[pivot_row][j];
//                 pivot_col = j;
//             }
//         }
//     }
    
//     if(pivot_col == -1) {
//         std::cerr << "В строке " << pivot_row << " нет отрицательных элементов!\n";
//         return false;
//     }
    
//     // 3. Делаем симплекс-шаг (используем существующий метод, но передаём свои pivot)
//     // Для этого нужно либо модифицировать simplex_step, либо написать отдельную функцию
    
//     // Сохраняем текущий базис
//     int old_basis = sm.basise[pivot_row];
    
//     // Нормализуем строку
//     double pivot_val = sm.matrix[pivot_row][pivot_col];
//     for(int j = 0; j < sm.matrix[0].size(); ++j) {
//         sm.matrix[pivot_row][j] /= pivot_val;
//     }
//     sm.b[pivot_row] /= pivot_val;
    
//     // Исключаем из других строк
//     for(int i = 0; i < sm.matrix.size(); ++i) {
//         if(i == pivot_row) continue;
        
//         double factor = sm.matrix[i][pivot_col];
//         if(std::abs(factor) > 1e-10) {
//             for(int j = 0; j < sm.matrix[0].size(); ++j) {
//                 sm.matrix[i][j] -= factor * sm.matrix[pivot_row][j];
//             }
//             sm.b[i] -= factor * sm.b[pivot_row];
//         }
//     }
    
//     // Обновляем целевую функцию
//     double f_factor = sm.f[pivot_col];
//     if(std::abs(f_factor) > 1e-10) {
//         for(int j = 0; j < sm.f.size() - 1; ++j) {
//             sm.f[j] -= f_factor * sm.matrix[pivot_row][j];
//         }
//         sm.f[sm.f.size() - 1] -= f_factor * sm.b[pivot_row];
//     }
    
//     // Обновляем базис
//     sm.basise[pivot_row] = pivot_col;
    
//     return true;
// }