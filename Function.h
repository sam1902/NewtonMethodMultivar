//
// Created by Samuel Prevost on 2019-12-19.
//

#ifndef NEWTONMULTIVAR_FUNCTION_H
#define NEWTONMULTIVAR_FUNCTION_H

#include <math.h>
#include "Vector.h"
#include "Matrix.h"

typedef double (*DoubleToDouble)(double);
typedef double (*DoubleDoubleToDouble)(double, double);
typedef Vector* (*VectorToVector)(const Vector*);

// If f is a Function, derivatives is a list of Function* which are
// df/dx1, df/dx2, df/dx2, etc with x1, x2, ... its input vector's component.
// to get d2f/dx1dx2 or some other crazy stuff, call partial_derivative(f, [0, 1], 2)
// to be able to do that, you should define f->derivative = [f1] and f1->derivative = [smthg, d2f/dx1dx2]
// where d2f/dx1dx2 is a Function pointing to the appropriate VectorToVector function.
typedef struct Function {
    Vector* (*functionPtr)(const Vector*);
    Vector* x_min;
    Vector* x_max;
    struct Function** derivatives;
    int derivatives_length;
} Function;

Vector* map(DoubleToDouble f, const Vector *x);
Vector* map2d(DoubleDoubleToDouble f, const Vector* x1, const Vector* x2);
Function* partial_derivative(const Function *f, const int *vars, int length);
Function* nth_derivative(const Function *f, int n);

Function* copy_array_to_heap(const Function *function_array, int length);
Function* copy_to_heap(const Function *function);

double tail_rec(const Vector *x, DoubleDoubleToDouble f, double acc);

static inline double addition(double x1, double x2);
static inline double subtract(double x1, double x2);
static inline double multiply(double x1, double x2);
static inline double   divide_(double x1, double x2);

double sum(const Vector *x);
Vector* mul(const Vector *x, double factor);
double prod(const Vector *x);
double dot(const Vector *x1, const Vector *x2);

Vector* add(const Vector *x1, const Vector *x2);
Vector* sub(const Vector *x1, const Vector *x2);
Vector* divide(const Vector *x1, const Vector *x2);
Vector* hadamar(const Vector *x1, const Vector *x2);
Vector* absolute(const Vector *x);

Vector* vec_mat_mul(const Vector* x, const Matrix* mat);

bool all(const Vector *x);
bool any(const Vector *x);

#endif //NEWTONMULTIVAR_FUNCTION_H
