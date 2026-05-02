#include <stdio.h>
#include <stdlib.h>

struct Node_1{
    double val;
    long long mask, unmask;
    int last_pos;
    double last_fraction;
    double fixed_v, fixed_l;
};

struct Node_3{
    double val;
    long long mask, unmask;
    int last_pos;
    double last_fraction;
    double fixed_v, fixed_l1, fixed_l2, fixed_l3;
};

struct TempDancig{
    double val;
    int pos;
};

//Priority queue for node_1

void swap_node_1(struct Node_1* a, struct Node_1* b){
    struct Node_1 temp = *a;
    *a = *b;
    *b = temp;
}

void push_node_1(struct Node_1** arr, int* size, int* capacity, struct Node_1 val){
    if(*size == *capacity){
        int new_capacity = *capacity == 0 ? 24 : *capacity + *capacity/8;
        struct Node_1* new_arr = (struct Node_1*)realloc(*arr, sizeof(struct Node_1)*new_capacity);
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
        swap_node_1(&(*arr)[parent], &(*arr)[child]);
        child = parent;
        parent = (child-1)/2;
    }

    (*size)++;
}

void pop_node_1(struct Node_1* arr, int* size){
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

        swap_node_1(&arr[parent], &arr[smallest]);

        parent = smallest;
    }
}

struct Node_1 top_node_1(struct Node_1* arr, int* size){
    if(*size == 0) return (struct Node_1){-1.0, -1};

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

//Priority queue for Node_3

void swap_node_3(struct Node_3* a, struct Node_3* b){
    struct Node_3 temp = *a;
    *a = *b;
    *b = temp;
}

void push_node_3(struct Node_3** arr, int* size, int* capacity, struct Node_3 val){
    if(*size == *capacity){
        int new_capacity = *capacity == 0 ? 24 : *capacity + *capacity/8;
        struct Node_3* new_arr = (struct Node_3*)realloc(*arr, sizeof(struct Node_3)*new_capacity);
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
        swap_node_3(&(*arr)[parent], &(*arr)[child]);
        child = parent;
        parent = (child-1)/2;
    }

    (*size)++;
}

void pop_node_3(struct Node_3* arr, int* size){
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

        swap_node_3(&arr[parent], &arr[smallest]);

        parent = smallest;
    }
}

struct Node_3 top_node_3(struct Node_3* arr, int* size){
    if(*size == 0) return (struct Node_3){-1.0, -1};

    return arr[0];
}

struct ResultDancig{
    double cur_v;
    long long mask;
    double last_fraction;
    int last_pos;
};

struct BoundResult{
    double val;
    long long mask;
};

struct ResultDancig dancig(double* values, double* limit, int* size, int l, double* cur_v, int* cur_l, long long* mask, long long* unmask){
    long long m = *mask;
    double* temp = (double*)malloc(sizeof(double)*(*size));
    struct TempDancig* queue = (struct TempDancig*)malloc(sizeof(struct TempDancig)*(*size));
    int que_size = 0, capacity = *size;
    for(int i = 0; i < *size; ++i){
        if(((*mask) & ((long long)1 << i)) || ((*unmask) & ((long long)1 << i))) continue;
        temp[i] = values[i]/limit[i];
        push_double(&queue, &que_size, &capacity, (struct TempDancig){temp[i], i});
    }
    double variadic = 0;
    int pos_last = -1;
    while(que_size != 0 && *cur_l <= l){
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
        m |= ((long long)1 << temp.pos);
    }

    free(queue);
    free(temp);

    return (struct ResultDancig){*cur_v, m, variadic, pos_last};
}

struct BoundResult lower_bound_triple_dimensional(double* values, double* limit1, int l1, double* limit2, int l2, double* limit3, int l3, int* size){
    struct TempDancig* queue = (struct TempDancig*)malloc(sizeof(struct TempDancig)*(*size));
    int q_size = 0, q_capacity = *size;
    for(int i = 0; i < *size; ++i){
        push_double(&queue, &q_size, &q_capacity, (struct TempDancig){values[i], i});
    }

    long long m = 0;
    int t_l1 = 0, t_l2 = 0, t_l3 = 0;
    double res = 0;
    for (int idx = 0; idx < *size; idx++) {
        int i = top_double(queue, &q_size).pos;
        pop_double(queue, &q_size);
        if (t_l1 + limit1[i] <= l1 && 
            t_l2 + limit2[i] <= l2 && 
            t_l3 + limit3[i] <= l3) {
            m |= ((long long)1 << i);
            res += values[i];
            t_l1 += limit1[i];
            t_l2 += limit2[i];
            t_l3 += limit3[i];
        }
    }
    
    free(queue);
    return (struct BoundResult){res, m};
}

struct ResultDancig* get_min_triple_dimensional(struct ResultDancig* rd1, struct ResultDancig* rd2, struct ResultDancig* rd3){
    if(rd1->cur_v <= rd2->cur_v && rd1->cur_v <= rd3->cur_v) return rd1;
    if(rd2->cur_v < rd1->cur_v && rd2->cur_v <= rd3->cur_v) return rd2;
    if(rd3->cur_v < rd1->cur_v && rd3->cur_v < rd2->cur_v) return rd3;
    return NULL;
}

struct BoundResult triple_dimensional_knapsack(double* values, double* limit1, double* limit2, double* limit3, int* size, int l1, int l2, int l3){
    double cur_v = 0;
    int cur_l = 0;
    long long mask = 0, unmask = 0;
    struct ResultDancig res1 = dancig(values, limit1, size, l1, &cur_v, &cur_l, &mask, &unmask);
    cur_v = 0; cur_l = 0;
    struct ResultDancig res2 = dancig(values, limit2, size, l2, &cur_v, &cur_l, &mask, &unmask);
    cur_v = 0; cur_l = 0;
    struct ResultDancig res3 = dancig(values, limit3, size, l3, &cur_v, &cur_l, &mask, &unmask);

    struct Node_3* queue = NULL;
    int q_size = 0, q_capacity = 0;

    struct ResultDancig * rd = get_min_triple_dimensional(&res1, &res2, &res3);
    if(rd == NULL){
        printf("error in dancig\n");
        exit(1);
    }

    push_node_3(&queue, &q_size, &q_capacity, (struct Node_3){rd->cur_v, 0, 0, rd->last_pos, rd->last_fraction, 0, 0, 0, 0});

    struct BoundResult lb = lower_bound_triple_dimensional(values, limit1, l1, limit2, l2, limit3, l3, size);

    printf("%d <= f <= %d\n", (int)lb.val, (int)top_node_3(queue, &q_size).val);

    double result = lb.val;
    long long result_mask = lb.mask;

    while(q_size != 0){
        struct Node_3 temp = top_node_3(queue, &q_size);
        pop_node_3(queue, &q_size);

        int pos = temp.last_pos;

        long long left_mask = temp.mask, left_unmask = temp.unmask;
        double left_v_cur = temp.fixed_v;
        left_unmask |= ((long long)1 << pos);
        int left_l1_cur = temp.fixed_l1, left_l2_cur = temp.fixed_l2, left_l3_cur = temp.fixed_l3;

        long long right_mask = temp.mask, right_unmask = temp.unmask;
        double right_v_cur = temp.fixed_v;
        int right_l1_cur = temp.fixed_l1, right_l2_cur = temp.fixed_l2, right_l3_cur = temp.fixed_l3;

        int valid = 0;

        if(right_l1_cur + limit1[pos] <= l1 && right_l2_cur + limit2[pos] <= l2 && right_l3_cur + limit3[pos] <= l3){
            right_mask |= ((long long)1 << pos);
            right_v_cur += values[pos];
            right_l1_cur += limit1[pos];
            right_l2_cur += limit2[pos];
            right_l3_cur += limit3[pos];
            valid = 1;
        } else {
            valid = 0;
        }

        double t_left_v_cur = left_v_cur, t_right_v_cur = right_v_cur;
        struct ResultDancig left1 = dancig(values, limit1, size, l1, &t_left_v_cur, &left_l1_cur, &left_mask, &left_unmask);
        t_left_v_cur = left_v_cur;
        struct ResultDancig left2 = dancig(values, limit2, size, l2, &t_left_v_cur, &left_l2_cur, &left_mask, &left_unmask);
        t_left_v_cur = left_v_cur;
        struct ResultDancig left3 = dancig(values, limit3, size, l3, &t_left_v_cur, &left_l3_cur, &left_mask, &left_unmask);

        struct ResultDancig right1, right2, right3;

        double flr1 = right_l1_cur, flr2 = right_l2_cur, flr3 = right_l3_cur;

        if(valid){
            right1 = dancig(values, limit1, size, l1, &t_right_v_cur, &right_l1_cur, &right_mask, &right_unmask);
            t_right_v_cur = right_v_cur;
            right2 = dancig(values, limit2, size, l2, &t_right_v_cur, &right_l2_cur, &right_mask, &right_unmask);
            t_right_v_cur = right_v_cur;
            right3 = dancig(values, limit3, size, l3, &t_right_v_cur, &right_l3_cur, &right_mask, &right_unmask);
        }

        struct ResultDancig * rd_left = get_min_triple_dimensional(&left1, &left2, &left3);
        struct ResultDancig * rd_right;
        if(valid){
            rd_right = get_min_triple_dimensional(&right1, &right2, &right3);
        }

        if(rd_left->cur_v >= result){
            if(rd_left->last_pos == -1){
                int weight1 = 0, weight2 = 0, weight3 = 0;
                for(int i = 0; i < *size; i++) {
                    if((rd_left->mask & ((long long)1 << i))) {
                        weight1 += limit1[i];
                        weight2 += limit2[i];
                        weight3 += limit3[i];
                    }
                }
                if(weight1 <= l1 && weight2 <= l2 && weight3 <= l3) {
                    if(rd_left->cur_v > result) {
                        result = rd_left->cur_v;
                        result_mask = rd_left->mask;
                    }
                }
                continue;
            }
            push_node_3(&queue, &q_size, &q_capacity, (struct Node_3){rd_left->cur_v, left_mask, left_unmask, rd_left->last_pos, rd_left->last_fraction, left_v_cur, temp.fixed_l1, temp.fixed_l2, temp.fixed_l3});
        }

        if(valid == 1 && rd_right->cur_v >= result){
            if(rd_right->last_pos == -1){
                int weight1 = 0, weight2 = 0, weight3 = 0;
                for(int i = 0; i < *size; i++) {
                    if((rd_right->mask & ((long long)1 << i))) {
                        weight1 += limit1[i];
                        weight2 += limit2[i];
                        weight3 += limit3[i];
                    }
                }
                if(weight1 <= l1 && weight2 <= l2 && weight3 <= l3) {
                    if(rd_right->cur_v > result) {
                        result = rd_right->cur_v;
                        result_mask = rd_right->mask;
                    }
                }
                continue;
            }
            push_node_3(&queue, &q_size, &q_capacity, (struct Node_3){rd_right->cur_v, right_mask, right_unmask, rd_right->last_pos, rd_right->last_fraction, right_v_cur, flr1, flr2, flr3});
        }
        int d = 0;
    }

    free(queue);
    return (struct BoundResult){result, result_mask};
}

void quest2(){
    int size = 10, capacity = 10;
    double* values = (double*)malloc(sizeof(double)*size);
    double* limit1 = (double*)malloc(sizeof(double)*size);
    double* limit2 = (double*)malloc(sizeof(double)*size);
    double* limit3 = (double*)malloc(sizeof(double)*size);

    values[0] = 6; values[1] = 5; values[2] = 2; values[3] = 3; values[4] = 4;
    values[5] = 5; values[6] = 4; values[7] = 8; values[8] = 7; values[9] = 3;

    limit1[0] = 2; limit1[1] = 2; limit1[2] = 2; limit1[3] = 1; limit1[4] = 2;
    limit1[5] = 2; limit1[6] = 2; limit1[7] = 3; limit1[8] = 3; limit1[9] = 1;
    int l1 = 10;

    limit2[0] = 1; limit2[1] = 3; limit2[2] = 3; limit2[3] = 2; limit2[4] = 2;
    limit2[5] = 2; limit2[6] = 1; limit2[7] = 4; limit2[8] = 2; limit2[9] = 2;
    int l2 = 7;

    limit3[0] = 4; limit3[1] = 1; limit3[2] = 2; limit3[3] = 2; limit3[4] = 2;
    limit3[5] = 3; limit3[6] = 3; limit3[7] = 3; limit3[8] = 2; limit3[9] = 1;
    int l3 = 8;

    struct BoundResult res = triple_dimensional_knapsack(values, limit1, limit2, limit3, &size, l1, l2, l3);

    printf("%.1f\n", res.val);

    for(int i = 0; i < size; ++i){
        if((res.mask & ((long long)1 << i))) printf("1 ");
        else printf("0 ");
    }
    printf("\n");

    free(values);
    free(limit1);
    free(limit2);
    free(limit3);
}

void generate_quest(double** values, double** limit1, double** limit2, double** limit3, int* size, int* l1, int* l2, int* l3){
    (*values) = (double*)malloc(sizeof(double)*(*size));
    (*limit1) = (double*)malloc(sizeof(double)*(*size));
    (*limit2) = (double*)malloc(sizeof(double)*(*size));
    (*limit3) = (double*)malloc(sizeof(double)*(*size));
    int s1 = 0, s2 = 0, s3 = 0;
    for(int i = 0; i < *size; ++i){
        (*values)[i] = rand()%25+1;
        (*limit1)[i] = rand()%15+1;
        (*limit2)[i] = rand()%20+1;
        (*limit3)[i] = rand()%25+1;
        s1 += (*limit1)[i];
        s2 += (*limit2)[i];
        s3 += (*limit3)[i];
    }
    *l1 = s1*(0.3 + rand()%30/100);
    *l2 = s2*(0.3 + rand()%40/100);
    *l3 = s3*(0.3 + rand()%50/100);
}