#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct Node{
    double val;
    int mask, unmask;
    int last_pos;
    double last_fraction;
};

struct ResultDancig{
    double cur_v;
    int mask;
    double last_fraction;
    int last_pos;
};

struct TempDancig{
    double val;
    int pos;
};

//Priority queue for node

void swap_node(struct Node* a, struct Node* b){
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

void push_node(struct Node** arr, int* size, int* capacity, struct Node val){
    if(*size == *capacity){
        int new_capacity = *capacity == 0 ? 24 : *capacity + *capacity/8;
        struct Node* new_arr = (struct Node*)realloc(*arr, sizeof(struct Node)*new_capacity);
        if(new_arr == NULL){
            printf("Error in realloc\n");
            exit(1);
        }
        *arr = new_arr;
        *capacity = new_capacity;
    }

    (*arr)[*size] = val;
    int parent = (*size-1)/2, child = *size;
    while(parent >= 0 && (*arr)[child].val > (*arr)[parent].val){
        swap_node(&(*arr)[parent], &(*arr)[child]);
        child = parent;
        parent = (child-1)/2;
    }

    (*size)++;
}

void pop_node(struct Node* arr, int* size){
    if(*size == 0) return;

    arr[0] = arr[*size-1];
    (*size)--;

    int parent = 0;

    while(1){
        int left = 2*parent+1;
        int right = 2*parent+2;
        int smallest = parent;

        if(left < *size && arr[smallest].val < arr[left].val) smallest = left;
        if(right < *size && arr[smallest].val < arr[right].val) smallest = right;

        if(smallest == parent) break;

        swap_node(&arr[parent], &arr[smallest]);

        parent = smallest;
    }
}

struct Node top_node(struct Node* arr, int* size){
    if(*size == 0) return (struct Node){-1.0, -1};

    return arr[0];
}

//Priority queue for double

void swap_double(struct TempDancig* a, struct TempDancig* b){
    struct TempDancig temp = *a;
    *a = *b;
    *b = temp;
}

void push_double(struct TempDancig** arr, int* size, int* capacity, struct TempDancig val){
    if(*size == *capacity){
        int new_capacity = *capacity == 0 ? 24 : *capacity + *capacity/8;
        struct TempDancig* new_arr = (struct TempDancig*)realloc(*arr, sizeof(struct TempDancig)*new_capacity);
        if(new_arr == NULL){
            printf("Error in realloc\n");
            exit(1);
        }
        *arr = new_arr;
        *capacity = new_capacity;
    }

    (*arr)[*size] = val;
    int parent = (*size-1)/2, child = *size;
    while(parent >= 0 && (*arr)[child].val > (*arr)[parent].val){
        swap_double(&(*arr)[parent], &(*arr)[child]);
        child = parent;
        parent = (child-1)/2;
    }

    (*size)++;
}

void pop_double(struct TempDancig* arr, int* size){
    if(*size == 0) return;

    arr[0] = arr[*size-1];
    (*size)--;

    int parent = 0;

    while(1){
        int left = 2*parent+1;
        int right = 2*parent+2;
        int smallest = parent;

        if(left < *size && arr[smallest].val < arr[left].val) smallest = left;
        if(right < *size && arr[smallest].val < arr[right].val) smallest = right;

        if(smallest == parent) break;

        swap_double(&arr[parent], &arr[smallest]);

        parent = smallest;
    }
}

struct TempDancig top_double(struct TempDancig* arr, int* size){
    if(*size == 0) return (struct TempDancig){-1.0, -1};

    return arr[0];
}

//method Dancig

struct ResultDancig dancig(double* values, double* limit, int* size, int l, double* cur_v, int* cur_l, int* mask, int* unmask){
    int m = *mask;
    double* temp = (double*)malloc(sizeof(double)*(*size));
    struct TempDancig* queue = (struct TempDancig*)malloc(sizeof(struct TempDancig)*(*size));
    int que_size = 0, capacity = *size;
    for(int i = 0; i < *size; ++i){
        if(((*mask) & (1 << i)) || ((*unmask) & (1 << i))) continue;
        temp[i] = values[i]/limit[i];
        push_double(&queue, &que_size, &capacity, (struct TempDancig){temp[i], i});
    }
    double variadic = 0;
    int pos_last = -1;
    while(que_size != 0 && *cur_l < l){
        struct TempDancig temp = top_double(queue, &que_size);
        pop_double(queue, &que_size);
        if(*cur_l + limit[temp.pos] > l){
            variadic = (l-*cur_l)/limit[temp.pos];
            pos_last = temp.pos;
            (*cur_v) += variadic*values[temp.pos];
            break;
        }
        (*cur_l) += limit[temp.pos];
        (*cur_v) += values[temp.pos];
        m |= (1 << temp.pos);
    }

    free(queue);
    free(temp);

    return (struct ResultDancig){*cur_v, m, variadic, pos_last};
}

//method high values

struct TempDancig lower_bound_one_dimensional(double* values, double* limit, int* size, int l){
    struct TempDancig* queue = (struct TempDancig*)malloc(sizeof(struct TempDancig)*(*size));
    int que_size = 0, capacity = *size;
    for(int i = 0; i < *size; ++i){
        push_double(&queue, &que_size, &capacity, (struct TempDancig){values[i], i});
    }

    int m = 0;
    int t_l1 = 0;
    double res = 0;
    for (int idx = 0; idx < *size; idx++) {
        int i = top_double(queue, &que_size).pos;
        pop_double(queue, &que_size);
        if (t_l1 + limit[i] <= l) {
            m |= (1 << i);
            res += values[i];
            t_l1 += limit[i];
        }
    }
    free(queue);
    return (struct TempDancig){res, m};
}

struct TempDancig one_dimensional_knapsack(double* values, double* limit, int size, int l){
    int mask = 0, unmask = 0, cur_l = 0;
    double cur_v = 0;

    struct ResultDancig res = dancig(values, limit, &size, l, &cur_v, &cur_l, &mask, &unmask);
    if(res.last_pos == -1){
        printf("%.1f\n", res.cur_v);
        return (struct TempDancig){res.cur_v, res.mask};
    }
    struct TempDancig lb = lower_bound_one_dimensional(values, limit, &size, l);

    struct Node* queue = NULL;
    int q_size = 0, q_capacity = 0;

    push_node(&queue, &q_size, &q_capacity, (struct Node){res.cur_v, mask, unmask, res.last_pos, res.last_fraction});

    double result = lb.val;
    int result_mask = lb.pos;

    while(q_size != 0){
        struct Node temp = top_node(queue, &q_size);
        pop_node(queue, &q_size);

        int pos = temp.last_pos;

        // Левая ветка (НЕ берем предмет)
        int left_mask = temp.mask;
        int left_unmask = temp.unmask | (1 << pos);
        double left_v_cur = 0;
        int left_l_cur = 0;
        for(int i = 0; i < size; ++i) {
            if((left_mask & (1 << i))) { 
                left_v_cur += values[i]; 
                left_l_cur += limit[i]; 
            }
        }

        // Правая ветка (берем предмет)
        int right_mask = temp.mask;
        int right_unmask = temp.unmask;
        double right_v_cur = 0;
        int right_l_cur = 0;
        
        // Сначала добавляем предметы из temp.mask
        for(int i = 0; i < size; ++i) {
            if((temp.mask & (1 << i))) { 
                right_v_cur += values[i]; 
                right_l_cur += limit[i]; 
            }
        }
        
        // Проверяем, можем ли добавить новый предмет
        if(right_l_cur + limit[pos] <= l){
            right_mask |= (1 << pos);
            right_l_cur += limit[pos];
            right_v_cur += values[pos];
        } else {
            // Не можем взять - обрабатываем только левую ветку
            struct ResultDancig left = dancig(values, limit, &size, l, &left_v_cur, &left_l_cur, &left_mask, &left_unmask);
            if(left.cur_v > result){
                if(left.last_pos == -1){
                    if(left.cur_v > result){
                        result = left.cur_v;
                        result_mask = left.mask;
                    }
                } else {
                    push_node(&queue, &q_size, &q_capacity, (struct Node){left.cur_v, left_mask, left_unmask, left.last_pos, left.last_fraction});
                }
            }
            continue;
        }

        struct ResultDancig left = dancig(values, limit, &size, l, &left_v_cur, &left_l_cur, &left_mask, &left_unmask);
        struct ResultDancig right = dancig(values, limit, &size, l, &right_v_cur, &right_l_cur, &right_mask, &right_unmask);

        if(left.cur_v > result){
            if(left.last_pos == -1){
                result = left.cur_v;
                result_mask = left.mask;
            } else {
                push_node(&queue, &q_size, &q_capacity, (struct Node){left.cur_v, left_mask, left_unmask, left.last_pos, left.last_fraction});
            }
        }

        if(right.cur_v > result){
            if(right.last_pos == -1){
                result = right.cur_v;
                result_mask = right.mask;
            } else {
                push_node(&queue, &q_size, &q_capacity, (struct Node){right.cur_v, right_mask, right_unmask, right.last_pos, right.last_fraction});
            }
        }
    }
    free(queue);
    return (struct TempDancig){result, result_mask};
}

void generate_quest(double** values, double** limit, int* size, int* l){
    *size = rand()%22+10;
    (*values) = (double*)malloc(sizeof(double)*(*size));
    (*limit) = (double*)malloc(sizeof(double)*(*size));
    int s = 0;
    for(int i = 0; i < *size; ++i){
        (*values)[i] = rand()%25 + 1;
        (*limit)[i] = rand()%15 + 1;
        s += (*limit)[i];
    }
    *l = s*(0.3 + rand()%30/100);
}