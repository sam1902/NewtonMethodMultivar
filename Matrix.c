//
// Created by Samuel Prevost on 20/12/2019.
//

#include <stdio.h>
#include <assert.h>
#include "Matrix.h"

Matrix* mat(int rows, int cols, const double arr[rows][cols]){
    Matrix* tail = NULL;
    Matrix* head = NULL;
    for (int i = 0; i < cols; ++i) {
        Matrix* new_tail = malloc(sizeof(Matrix));
        if(head == NULL){
            head = new_tail;
        }
        if(tail != NULL){
            tail->next = new_tail;
        }
        tail = new_tail;
        tail->row = array_to_vect(rows, arr[i]);
    }
    return head;
}

Matrix* tr(const Matrix* mat){
    Matrix* tail = copy_mat(mat);
    Matrix* head = tail;
    int* shape = shape_mat(mat);
    for (int j = 0; j < shape[1]; ++j) {
        tail->row = get_col(mat, j);
        tail = tail->next;
    }
    return head;
}

double get_val(const Matrix* mat, int i, int j){
    if (i == 0){
        return get(mat->row, j);
    }
    if (mat->next != NULL){
        return get_val(mat->next, i-1, j);
    } else {
        fprintf(stderr, "Index error !\n");
        exit(1);
    }
}

Matrix* copy_mat(const Matrix* mat){
    Matrix* tail = NULL;
    Matrix* head = NULL;
    while (mat != NULL) {
        Matrix* new_tail = malloc(sizeof(Matrix));
        if(head == NULL){
            head = new_tail;
        }
        if(tail != NULL){
            tail->next = new_tail;
        }
        tail = new_tail;
        tail->row = copy_vect(mat->row);
        mat = mat->next;
    }
    return head;
}
int* shape_mat(const Matrix *mat){
    int* shape_array = malloc(sizeof(int)*2);
    shape_array[0] = 0;
    shape_array[1] = len(mat->row);
    while (mat != NULL) {
        mat = mat->next;
        shape_array[0]++;
    }
    return shape_array;
}

void print_mat(const Matrix *mat){
    while (mat != NULL) {
        Vector* row = mat->row;
        while (row != NULL) {
            printf("%9.5f, ", row->val);
            row = row->next;
        }
        printf("\n");
        mat = mat->next;
    }
}

Vector* get_row(const Matrix* mat, int i){
    while (mat != NULL && i--) {
        mat = mat->next;
    }
    if (mat == NULL){
        fprintf(stderr, "Index error !\n");
        exit(1);
    }
    return mat->row;
}

Vector* get_col(const Matrix* mat, int j){
    Vector* tail = NULL;
    Vector* head = NULL;
    while (mat != NULL) {
        Vector* new_tail = malloc(sizeof(Vector));
        if (head == NULL){
            head = new_tail;
        }
        if (tail != NULL){
            tail->next = new_tail;
        }
        tail = new_tail;
        tail->val = get(mat->row, j);
        mat = mat->next;
    }
    return head;
}

void set_inplace(Matrix* mat, double val, int i, int j){
    while (mat != NULL && i--) {
        mat = mat->next;
    }
    if (mat == NULL){
        fprintf(stderr, "Index error !\n");
        exit(1);
    }
    Vector* row = mat->row;
    while (row != NULL && j--) {
        row = row->next;
    }
    if (row == NULL){
        fprintf(stderr, "Index error !\n");
        exit(1);
    }
    row->val = val;
}

Matrix* set(const Matrix* mat, double val, int i, int j){
    Matrix* res = copy_mat(mat);
    set_inplace(res, val, i, j);
    return res;
}

Matrix* invert2d(const Matrix* mat){
    int* shape = shape_mat(mat);
    assert(shape[0] == 2);
    assert(shape[1] == 2);
    Matrix* res = copy_mat(mat);
    double det_val = det2d(mat);
    if(fabs(det_val) < NULL_EPS){
        fprintf(stderr, "Not invertible !\n");
        exit(1);
    }
    Vector* row0 = mat->row;
    Vector* row1 = mat->next->row;
    set_inplace(res, get(row1, 1)/det_val, 0, 0);
    set_inplace(res, get(row0, 0)/det_val, 1, 1);

    set_inplace(res, -get(row0, 1)/det_val, 0, 1);
    set_inplace(res, -get(row1, 0)/det_val, 1, 0);
    return res;
}

double det2d(const Matrix* mat){
    int* shape = shape_mat(mat);
    assert(shape[0] == 2);
    assert(shape[1] == 2);
    Vector* row0 = mat->row;
    double a = get(row0, 0), b = get(row0, 1);
    Vector* row1 = mat->next->row;
    double c = get(row1, 0), d = get(row1, 1);
    return a*d - b*c;
}