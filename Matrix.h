//
// Created by Samuel Prevost on 20/12/2019.
//

#ifndef NEWTONMULTIVAR_MATRIX_H
#define NEWTONMULTIVAR_MATRIX_H

// To compare if something is null
#define NULL_EPS 0.00000001

#include <stdlib.h>
#include <math.h>
#include "Vector.h"

typedef struct Matrix {
    Vector* row;
    struct Matrix* next;
} Matrix;

double get_val(const Matrix* mat, int i, int j);
Vector* get_row(const Matrix* mat, int i);
Vector* get_col(const Matrix* mat, int j);
Matrix* tr(const Matrix* mat);
Matrix* mat(int rows, int cols, const double arr[rows][cols]);
Matrix* copy_mat(const Matrix* mat);
int* shape_mat(const Matrix *mat);
void print_mat(const Matrix *mat);
Matrix* invert2d(const Matrix* mat);
double det2d(const Matrix* mat);
Matrix* set(const Matrix* mat, double val, int i, int j);
void set_inplace(Matrix* mat, double val, int i, int j);

#endif //NEWTONMULTIVAR_MATRIX_H
