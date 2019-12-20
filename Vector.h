//
// Created by Samuel Prevost on 2019-12-18.
//

#ifndef NEWTONMULTIVAR_VECTOR_H
#define NEWTONMULTIVAR_VECTOR_H
#include <stdbool.h>

typedef struct Vector {
    double val;
    struct Vector* next;
} Vector;

Vector* vect(int len, ...);
Vector* array_to_vect(int len, const double* arr);
Vector* full(int len, double val);
double get(const Vector *v, int i);
double v2d(const Vector *v);
Vector* copy_vect(const Vector* x);
Vector* cat(const Vector* x1, const Vector* x2);
int len(const Vector *v);

// TODO: to implem someday, c.f. numpy.mesh
Vector** mesh(const Vector* x_min, const Vector* x_max, const Vector* EPS);

void print_vect(const Vector *v);

Vector* gt(const Vector *x1, const Vector *x2);
Vector* ge(const Vector *x1, const Vector *x2);
Vector* lt(const Vector *x1, const Vector *x2);
Vector* le(const Vector *x1, const Vector *x2);

#endif //NEWTONMULTIVAR_VECTOR_H
