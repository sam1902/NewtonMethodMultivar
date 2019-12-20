//
// Created by Samuel Prevost on 19/12/2019.
//

#include "FunctionsInit.h"

Function* getAllFunctions(){
    /* Function 1 */
    Vector* f1_x_min = vect(2, (double)0, (double)0);
    Vector* f1_x_max = vect(2, (double)1, (double)1);
    Function func1_dxdx = {.functionPtr = &f1_dxdx, .derivatives = NULL, .derivatives_length = 0, .x_min = f1_x_min, .x_max = f1_x_max};
    Function func1_dxdy = {.functionPtr = &f1_dxdy, .derivatives = NULL, .derivatives_length = 0, .x_min = f1_x_min, .x_max = f1_x_max};
    Function func1_dydx = {.functionPtr = &f1_dydx, .derivatives = NULL, .derivatives_length = 0, .x_min = f1_x_min, .x_max = f1_x_max};
    Function func1_dydy = {.functionPtr = &f1_dydy, .derivatives = NULL, .derivatives_length = 0, .x_min = f1_x_min, .x_max = f1_x_max};

    Function* func1_dx_d[2] = {&func1_dxdx, &func1_dxdy};
    Function* func1_dy_d[2] = {&func1_dydx, &func1_dydy};
    Function func1_dx = {.functionPtr = &f1_dx, .derivatives = func1_dx_d, .derivatives_length = 2, .x_min = f1_x_min, .x_max = f1_x_max};
    Function func1_dy = {.functionPtr = &f1_dy, .derivatives = func1_dy_d, .derivatives_length = 2, .x_min = f1_x_min, .x_max = f1_x_max};

    Function* func1_d[2] = {&func1_dx, &func1_dy};
    Function func1 = {.functionPtr = &f1, .derivatives = func1_d, .derivatives_length = 2, .x_min = f1_x_min, .x_max = f1_x_max};

    /* Function 2 */
    // On retrouve l'exemple du cours en 3 itérations
    // Cours: (-0.2970, -0.2199) it=2 ?
    // Nous : (-0.29727, -0.21693) it=3
    Vector* f2_x_min = vect(2, (double)-17, (double)-30);
    Vector* f2_x_max = vect(2, (double)17, (double)12);
    Function func2_dxdx = {.functionPtr = &f2_dxdx, .derivatives = NULL, .derivatives_length = 0, .x_min = f2_x_min, .x_max = f2_x_max};
    Function func2_dxdy = {.functionPtr = &f2_dxdy, .derivatives = NULL, .derivatives_length = 0, .x_min = f2_x_min, .x_max = f2_x_max};
    Function func2_dydx = {.functionPtr = &f2_dydx, .derivatives = NULL, .derivatives_length = 0, .x_min = f2_x_min, .x_max = f2_x_max};
    Function func2_dydy = {.functionPtr = &f2_dydy, .derivatives = NULL, .derivatives_length = 0, .x_min = f2_x_min, .x_max = f2_x_max};

    Function* func2_dx_d[2] = {&func2_dxdx, &func2_dxdy};
    Function* func2_dy_d[2] = {&func2_dydx, &func2_dydy};
    Function func2_dx = {.functionPtr = &f2_dx, .derivatives = func2_dx_d, .derivatives_length = 2, .x_min = f2_x_min, .x_max = f2_x_max};
    Function func2_dy = {.functionPtr = &f2_dy, .derivatives = func2_dy_d, .derivatives_length = 2, .x_min = f2_x_min, .x_max = f2_x_max};

    Function* func2_d[2] = {&func2_dx, &func2_dy};
    Function func2 = {.functionPtr = &f2, .derivatives = func2_d, .derivatives_length = 2, .x_min = f2_x_min, .x_max = f2_x_max};

    Function funcs[FUNCOUNT] = {func1, func2};
    return copy_array_to_heap(funcs, FUNCOUNT);
}
/* Function 1 */
Vector* f1(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(2*x*y + 2*y - pow(x, 2) - 2*pow(y, 2)));
}
Vector* f1_dx(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(2*y - 2*x));
}
Vector* f1_dy(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(2*x +2 - 4*y));
}
Vector* f1_dxdx(const Vector* v){
    return vect(1, (double)(-2));
}
Vector* f1_dydy(const Vector* v){
    return vect(1, (double)(-4));
}
Vector* f1_dxdy(const Vector* v){
    return vect(1, (double)(2));
}
Vector* f1_dydx(const Vector* v){
    return vect(1, (double)(2));
}

/* Function 2 */

Vector* f2(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(exp(x+y) + pow(x, 2) + 2*pow(y, 2)));
}
Vector* f2_dx(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(exp(x+y) + 2*x));
}
Vector* f2_dy(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(exp(x+y) + 4*y));
}
Vector* f2_dxdx(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(exp(x+y) + 2));
}
Vector* f2_dydy(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(exp(x+y) + 2));
}
Vector* f2_dxdy(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(exp(x+y)));
}
Vector* f2_dydx(const Vector* v){
    double x = get(v, 0), y = get(v, 1);
    return vect(1, (double)(exp(x+y)));
}