//
// Created by Samuel Prevost on 19/12/2019.
//

#ifndef NEWTONMULTIVAR_FUNCTIONSINIT_H
#define NEWTONMULTIVAR_FUNCTIONSINIT_H

#include <stdlib.h>
#include <math.h>
#include "Vector.h"
#include "Function.h"

#define FUNCOUNT 2

Function* getAllFunctions();

Vector* f1(const Vector* v);
Vector* f1_dx(const Vector* v);
Vector* f1_dy(const Vector* v);
Vector* f1_dxdx(const Vector* v);
Vector* f1_dydy(const Vector* v);
Vector* f1_dxdy(const Vector* v);
Vector* f1_dydx(const Vector* v);

Vector* f2(const Vector* v);
Vector* f2_dx(const Vector* v);
Vector* f2_dy(const Vector* v);
Vector* f2_dxdx(const Vector* v);
Vector* f2_dydy(const Vector* v);
Vector* f2_dxdy(const Vector* v);
Vector* f2_dydx(const Vector* v);

#endif //NEWTONMULTIVAR_FUNCTIONSINIT_H
