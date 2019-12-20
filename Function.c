//
// Created by Samuel Prevost on 2019-12-19.
//

#include <stdio.h>
#include <stdlib.h>
#include <libc.h>
#include "Function.h"

Vector* map(const DoubleToDouble f, const Vector* x){
    Vector* tail = malloc(sizeof(Vector));
    Vector* head = tail;

    while (x != NULL) {
        tail->val = f(x->val);
        x = x->next;
        if (x != NULL) {
            tail->next = malloc(sizeof(Vector));
            tail = tail->next;
        }
    }

    return head;
}

Vector* map2d(const DoubleDoubleToDouble f, const Vector* x1, const Vector* x2){
    Vector* tail = malloc(sizeof(Vector));
    Vector* head = tail;

    while (x1 != NULL && x2 != NULL) {
        tail->val = f(x1->val, x2->val);
        x1 = x1->next;
        x2 = x2->next;
        if (x1 != NULL && x2 != NULL) {
            tail->next = malloc(sizeof(Vector));
            tail = tail->next;
        }
    }

    if (x1 != NULL || x2 != NULL){
        fprintf(stderr, "Vectors of different length !\n");
        exit(1);
    }

    return head;
}

/***
 * Returns the `length` order partial derivative w.r.t. vars[0], then vars[1], then vars[2] etc. in that order !
 *
 * TL;DR above
 * If f is a Function, derivatives is a list of Function* which are
 * df/dx1, df/dx2, df/dx2, etc with x1, x2, ... its input vector's component.
 * to get d2f/dx1dx2 or some other crazy stuff, call partial_derivative(f, [0, 1], 2)
 * to be able to do that, you should define f->derivative = [f1] and f1->derivative = [smthg, d2f/dx1dx2]
 * where d2f/dx1dx2 is a Function pointing to the appropriate VectorToVector function.
 * @param f
 * @param vars
 * @param length
 * @return
 */
Function* partial_derivative(const Function* f, const int* vars, int length){
    if (length == 0){
        return (Function*)f;
    }
    return partial_derivative(f->derivatives[*vars], vars+1, length-1);
}


/***
 * Returns the Function that is the nth derivative of the given Function, i.e. w.r.t. the first variable.
 * Equivalent to partial_derivative(f, [0,0,.. n zeros ..,0,0], n)
 * @param f
 * @param n
 * @return
 */
Function* nth_derivative(const Function *f, int n){
    int* vars = malloc(sizeof(int)*n);
    memset(vars, 0, n);  // Creates a zero array of size n
    Function* res = partial_derivative(f, vars, n);
    free(vars);
    return res;
}

/***
 * Copies an array of Function to the heap.
 * @param function_array
 * @param length
 * @return a pointer to the copied array of structs
 */
Function* copy_array_to_heap(const Function *function_array, int length){
    Function* function_array_on_heap = malloc(sizeof(Function)*length);
    for (int i = 0; i < length; ++i) {
        function_array_on_heap[i] = *copy_to_heap(function_array + i);
    }
    return function_array_on_heap;
}

/***
 * Copies a Function to the heap, as well as its sub-structures, recursively.
 * @param function
 * @return a pointer to the copied struct's head
 */
Function* copy_to_heap(const Function *function){
    if (function == NULL){
        return NULL;
    }
    Function* heap_fun = malloc(sizeof(Function));
    heap_fun->functionPtr = function->functionPtr;
    heap_fun->x_min = copy_vect(function->x_min);
    heap_fun->x_max = copy_vect(function->x_max);
    Function** derivatives_on_heap = malloc(sizeof(Function)*function->derivatives_length);
    for (int i = 0; i < function->derivatives_length; ++i) {
        derivatives_on_heap[i] = copy_to_heap(function->derivatives[i]);
    }
    heap_fun->derivatives = derivatives_on_heap;
    return heap_fun;
}

double tail_rec(const Vector *x, DoubleDoubleToDouble f, double acc){
    if (x->next == NULL){
        return f(acc, x->val);
    }
    return tail_rec(x->next, f, f(acc, x->val));
}

static inline double addition(double x1, double x2){ return x1 + x2; }
static inline double subtract(double x1, double x2){ return x1 - x2; }
static inline double multiply(double x1, double x2){ return x1 * x2; }
static inline double  divide_(double x1, double x2){ return x1 / x2; }

double sum(const Vector *x){
    return tail_rec(x, &addition, 0);
}

double prod(const Vector *x){
    return tail_rec(x, &multiply, 1);;
}

Vector* mul(const Vector *x, double factor){
    // TODO: Improve implementation speed
    Vector* factor_vect = full(len(x), factor);
    Vector* res = hadamar(factor_vect, x);
    free(factor_vect);
    return res;
}

double dot(const Vector *x1, const Vector *x2){
    return sum(hadamar(x1, x2));
}

Vector* add(const Vector *x1, const Vector *x2){
    return map2d(&addition, x1, x2);
}
Vector* sub(const Vector *x1, const Vector *x2){
    return map2d(&subtract, x1, x2);
}
Vector* divide(const Vector *x1, const Vector *x2){
    return map2d(&divide_, x1, x2);
}
Vector* hadamar(const Vector *x1, const Vector *x2){
    return map2d(&multiply, x1, x2);
}
Vector* absolute(const Vector *x){
    return map(fabs, x);
}

bool all(const Vector *x){
    if (x == NULL){
        return true;
    }
    return (fabs(x->val) > 0) && all(x->next);
}

bool any(const Vector *x){
    if (x == NULL){
        return false;
    }
    return (fabs(x->val) > 0) || any(x->next);
}

Vector* vec_mat_mul(const Vector* x, const Matrix* mat){
    Vector* tail = NULL;
    Vector* head = NULL;
    while (mat != NULL){
        Vector* new_tail = malloc(sizeof(Vector));
        if(head == NULL){
            head = new_tail;
        }
        if(tail != NULL){
            tail->next = new_tail;
        }
        tail = new_tail;
        tail->val = dot(x, mat->row);
        mat = mat->next;
    }
    return head;
}