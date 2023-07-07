#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "../../../cursos/modulosc/dnlycsystems.h"

int main(void) {

    FILE *evolution = fopen("datafiles/evolution_sys5_driver.dat", "w");

    /* Seed */
    unsigned long int seed = (unsigned long int)time(NULL);

    /* System parameters */    
    double mu = -0.2;

    /* System */
    gsl_odeiv2_system sys = {sys5, jac5, 1, &mu};

    /* Integration parameters */
    unsigned int N = 1000;
    double rel_err = 1e-8, abs_err = 1e-6;
    double h = 1e-6;
    const gsl_odeiv2_step_type *integrator = gsl_odeiv2_step_rkf45;
    

    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&sys, integrator, h, abs_err, rel_err);

    double t = 0.0, t1 = 1.0;
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(rng, seed);
    double x[1] = {(double)gsl_ran_flat(rng, 0.0, 1.0)};
    
    for (unsigned int i = 0; i < N; i++) {
        double ti = (double) i * t1 / N;
        int status = gsl_odeiv2_driver_apply(driver, &t, ti, x);

        if (status != GSL_SUCCESS) {
            printf("error, return value=%d\n", status);
            break;
        }
        // printf("%5.15f  %5.15f\n", t, x[0]);
        fprintf(evolution, "%5.15f  %5.15f  %5.15f\n", t, x[0], h);
    }

    gsl_odeiv2_driver_free(driver);
    gsl_rng_free(rng);
    fclose(evolution);
    return 0;
}
