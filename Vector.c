//
// Created by Samuel Prevost on 2019-12-18.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "Vector.h"

void print_vect(const Vector *v){
    printf("%.5f", v->val);
    if (v->next != NULL){
        printf(",\n");
        print_vect(v->next);
    } else {
        printf("\n");
    }
}

/***
 * ALWAYS. EXPLICITLY. TYPECAST !!!!!
 * @param len
 * @param ...
 * @return
 */
Vector* vect(int len, ...) {
    va_list valist;
    va_start(valist, len);

    Vector* v = malloc(sizeof(Vector));
    Vector* head = v;

    for (int i = 0; i < len; i++) {
        v->val = va_arg(valist, double);
        if (i != len-1) {
            v->next = malloc(sizeof(Vector));
            v = v->next;
        } else {
            v->next = NULL;
        }
    }

    va_end(valist);

    return head;
}

Vector* array_to_vect(int len, const double* arr){
    Vector* v = malloc(sizeof(Vector));
    Vector* head = v;

    for (int i = 0; i < len; i++) {
        v->val = arr[i];
        if (i != len-1) {
            v->next = malloc(sizeof(Vector));
            v = v->next;
        } else {
            v->next = NULL;
        }
    }
    return head;
}

Vector* full(int len, double val){
    Vector* v = malloc(sizeof(Vector));
    Vector* head = v;

    for (int i = 0; i < len; i++) {
        v->val = val;
        if (i != len-1) {
            v->next = malloc(sizeof(Vector));
            v = v->next;
        } else {
            v->next = NULL;
        }
    }
    return head;
}

double get(const Vector *v, int i){
    if (i == 0){
        return v->val;
    }
    if (v->next != NULL){
        return get(v->next, i-1);
    } else {
        fprintf(stderr, "Index error !\n");
        exit(1);
    }
}

double v2d(const Vector *v){
    return get(v, 0);
}

Vector* copy_vect(const Vector* x){
    Vector* tail = malloc(sizeof(Vector));
    Vector* head = tail;
    while (x != NULL){
        tail->val = x->val;
        if(x->next != NULL){
            tail->next = malloc(sizeof(Vector));
            tail = tail->next;
        }
        x = x->next;
    }
    return head;
}

Vector* cat(const Vector* x1, const Vector* x2){
    Vector* x1_copy = copy_vect(x1);
    Vector* x2_copy = copy_vect(x2);
    Vector* head = x1_copy;
    while(x1_copy->next != NULL){ x1_copy = x1_copy->next; }
    x1_copy->next = x2_copy;
    return head;
}

int len(const Vector *v){
    int l = 0;
    while (v != NULL){
        ++l;
        v = v->next;
    }
    return l;
}



Vector* gt(const Vector *x1, const Vector *x2){
    if (x1 == NULL || x2 == NULL){
        fprintf(stderr, "Index error !\n");
        exit(1);
    }
    Vector* res = NULL;
    Vector* head = NULL;
    do {
        Vector* next = malloc(sizeof(Vector));
        if(res != NULL) {
            res->next = next;
        } else {
            head = next;
        }
        res = next;
        res->val = (double)(x1->val > x2->val);
        x1 = x1->next;
        x2 = x2->next;
    } while(x1 != NULL && x2 != NULL);

    return head;
}
Vector* ge(const Vector *x1, const Vector *x2){
    if (x1 == NULL || x2 == NULL){
        fprintf(stderr, "Index error !\n");
        exit(1);
    }
    Vector* res = NULL;
    Vector* head = NULL;
    do {
        Vector* next = malloc(sizeof(Vector));
        if(res != NULL) {
            res->next = next;
        } else {
            head = next;
        }
        res = next;
        res->val = (double)(x1->val >= x2->val);
        x1 = x1->next;
        x2 = x2->next;
    } while(x1 != NULL && x2 != NULL);

    return head;
}

Vector* lt(const Vector *x1, const Vector *x2){
    return gt(x2, x1);
}
Vector* le(const Vector *x1, const Vector *x2){
    return ge(x2, x1);
}