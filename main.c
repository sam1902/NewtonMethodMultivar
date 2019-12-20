#include <stdio.h>
#include <math.h>
#include "Vector.h"
#include "Matrix.h"
#include "Function.h"
#include "FunctionsInit.h"

#define STEP_EPS_X 1.0
#define STEP_EPS_Y 1.0

#define CONV_EPS_X 0.000001
#define CONV_EPS_Y 0.000001

int main() {
    const Vector* CONV_EPS = vect(2, CONV_EPS_X, CONV_EPS_Y);
    Function* funcs = getAllFunctions();

    for (int i = 0; i < FUNCOUNT; ++i) {
        printf("##################  ");
        printf("Function f%d", i+1);
        printf("  ##################\n");
        printf("x0\t\t\t\t\t\tconverges to\t\t\t#it\t\n");
        Function* func = funcs + i;
        int dx[1] = {0};
        VectorToVector f_dx = partial_derivative(func, dx, 1)->functionPtr;
        int dy[1] = {1};
        VectorToVector f_dy = partial_derivative(func, dy, 1)->functionPtr;
        int dxdx[2] = {0,0};
        VectorToVector f_dxdx = partial_derivative(func, dxdx, 2)->functionPtr;
        int dydx[2] = {1,0};
        VectorToVector f_dydx = partial_derivative(func, dydx, 2)->functionPtr;
        int dxdy[2] = {0,1};
        VectorToVector f_dxdy = partial_derivative(func, dxdy, 2)->functionPtr;
        int dydy[2] = {1,1};
        VectorToVector f_dydy = partial_derivative(func, dydy, 2)->functionPtr;
        Vector* x_min = func->x_min;
        Vector* x_max = func->x_max;

        // This double for loop should be replaced with a "mesh" function which generates all of them.
        for (double x_comp = get(x_min, 0); x_comp < get(x_max, 0); x_comp += STEP_EPS_X) {
            for (double y_comp = get(x_min, 1); y_comp < get(x_max, 1); y_comp += STEP_EPS_Y) {
                Vector* x0 = vect(2, x_comp, y_comp);

                int it_count = 0;
                while (fabs(v2d(f_dx(x0))) > get(CONV_EPS, 0)
                    || fabs(v2d(f_dy(x0))) > get(CONV_EPS, 1)){
                    // Résouds HX = b avec X = P^k+1, H la hessienne de f en x0, et b = (P^k).A - grad_f(P^k)
                    // en inversant la hessienne pour établir X = A_inv . b = H_inv.(P^k).H - grad_f(P^k)
                    // Ici, x0 est P^0 et est graduellement amélioré vers l'optimum.
                    /* Calc de la Hessienne */
                    const double _H[2][2] = {{v2d(f_dxdx(x0)), v2d(f_dxdy(x0))},
                                             {v2d(f_dydx(x0)), v2d(f_dydy(x0))}};
                    Matrix* H = mat(2, 2, _H);
                    /* Calc de b */
                    Vector* grad = vect(2, v2d(f_dx(x0)), v2d(f_dy(x0)));
                    Vector* b = sub(vec_mat_mul(x0, H), grad);

                    /* Calc inverse H */
                    Matrix* H_inv = invert2d(H);

                    /* Calc solution du system par H_inv.b */
                    x0 = vec_mat_mul(b, H_inv);
                    it_count++;
                }
                printf("(%9.5f, %9.5f)\t(%9.5f, %9.5f)\t%02d\n",
                        x_comp, y_comp, get(x0, 0), get(x0, 1), it_count);
            }
        }


    }
    return 0;
}
