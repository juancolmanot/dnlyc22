#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "../../../cursos/modulosc/linear_algebra.h"
#include "../../../cursos/modulosc/dnlycsystems.h"

int main(void) {

    FILE *bifurcation = fopen("datafiles/bifurcation_sys1_driver.dat", "w");

    /* Seed */
    unsigned long int seed = (unsigned long int)time(NULL);

    /* Array of mu values*/
    int N_mu = 200;
    double mu_0, mu_N;
    mu_0 = - 6.0;
    mu_N = 0.1;
    gsl_vector *mu_values = gsl_linspace(mu_0, mu_N, N_mu);

    /* System */
    gsl_odeiv2_system sys = {sys1, jac1, 1, NULL};

    /* Integration parameters */
    unsigned int transient_t = 4.5;
    double rel_err = 1e-8, abs_err = 1e-6;
    double h = 1e-6;
    const gsl_odeiv2_step_type *integrator = gsl_odeiv2_step_rkf45;
    
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(rng, seed);

    for (unsigned int i = 0; i < N_mu; i++) {
        
        double mu = gsl_vector_get(mu_values, i);
        printf("i: %d  mu: %5.15f\n", i, mu);
        sys.params = &mu;
        gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&sys, integrator, h, abs_err, rel_err);

        double t0 = 0.0, t1 = 5.0, ti = t0;
        double x[1] = {(double)gsl_ran_flat(rng, -5.0, 0.0)};

        while (ti < t1) {
            ti += h;
            int status = gsl_odeiv2_driver_apply(driver, &t0, ti, x);

            if (status != GSL_SUCCESS) {
                printf("error, return value=%d\n", status);
                break;
            }
            if (ti > transient_t) {
                fprintf(bifurcation, "%5.15f  %5.15f  %5.15f\n", mu, x[0], h);
            }
        }
        gsl_odeiv2_driver_free(driver);
    }
    gsl_vector_free(mu_values);
    gsl_rng_free(rng);
    fclose(bifurcation);
    return 0;
}
