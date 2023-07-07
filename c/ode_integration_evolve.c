#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "../../../cursos/modulosc/dnlycsystems.h"

int main(void) {

    FILE *evolution = fopen("datafiles/evolution_sys5_evolve.dat", "w");

    /* Seed */
    unsigned long int seed = (unsigned long int)time(NULL);

    /* System parameters */
    double mu = 2;

    /* Integration parameters */
    double rel_err = 1e-8, abs_err = 1e-6;
    double h = 1e-6;
    const gsl_odeiv_step_type *integrator = gsl_odeiv_step_rk8pd;
    gsl_odeiv_step *s = gsl_odeiv_step_alloc(integrator, 1);
    gsl_odeiv_control *c = gsl_odeiv_control_y_new(abs_err, rel_err);
    gsl_odeiv_evolve *e = gsl_odeiv_evolve_alloc(1);
    
    gsl_odeiv_system sys = {sys5, jac5, 1, &mu};
    
    double t = 0.0, t1 = 10.0;
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(rng, seed);
    double x[1] = {(double)gsl_ran_flat(rng, 0.4, 0.6)};
    
    while(t < t1){
        int status = gsl_odeiv_evolve_apply(e, c, s, &sys, &t, t1, &h, x);

        if (status != GSL_SUCCESS)
            printf("error, return value=%d\n", status);
            break;
    
        fprintf(evolution, "%5.15f  %5.15f  %5.15f\n", t, x[0], h);
    }
    
    gsl_odeiv_evolve_free(e);
    gsl_odeiv_control_free(c);
    gsl_odeiv_step_free(s);
    gsl_rng_free(rng);
    fclose(evolution);
    return 0;
}
