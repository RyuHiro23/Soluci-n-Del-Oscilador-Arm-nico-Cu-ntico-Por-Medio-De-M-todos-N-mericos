#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_eigen.h>

#define HBAR 1.0
#define MASS 1.0
#define OMEGA 1.0

void build_hamiltonian(double *H, double x_min, double x_max, int N) {
    double dx = (x_max - x_min) / (N - 1);
    double alpha = 1.0 / (dx * dx);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                double x = x_min + i * dx;
                H[i * N + j] = HBAR * HBAR * alpha / (2.0 * MASS) + 0.5 * MASS * OMEGA * OMEGA * x * x;
            } else if (abs(i - j) == 1) {
                H[i * N + j] = -HBAR * HBAR * alpha / (2.0 * MASS);
            } else {
                H[i * N + j] = 0.0;
            }
        }
    }
}

void normalize(double *psi, int N, double dx) {
    double norm = 0.0;
    for (int i = 0; i < N; i++) {
        norm += psi[i] * psi[i] * dx;
    }
    norm = sqrt(norm);
    for (int i = 0; i < N; i++) {
        psi[i] /= norm;
    }
}

void write_to_csv(const char *filename, double *x, double *psi, int N) {
    FILE *file = fopen(filename, "w");
    fprintf(file, "x,psi\n");
    for (int i = 0; i < N; i++) {
        fprintf(file, "%lf,%lf\n", x[i], psi[i]);
    }
    fclose(file);
}

int main() {
    int N = 1000;
    double x_min = -4.0, x_max = 4.0;
    double dx = (x_max - x_min) / (N - 1);
    double *x = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        x[i] = x_min + i * dx;
    }

    double *H = malloc(N * N * sizeof(double));
    build_hamiltonian(H, x_min, x_max, N);

    gsl_matrix_view m = gsl_matrix_view_array(H, N, N);
    gsl_vector *eval = gsl_vector_alloc(N);
    gsl_matrix *evec = gsl_matrix_alloc(N, N);
    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(N);
    gsl_eigen_symmv(&m.matrix, eval, evec, w);
    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_ASC);

    printf("Seleccione una opción:\n");
    printf("1. Ver las funciones de onda (ψ_n(x))\n");
    printf("2. Ver las densidades de probabilidad (ψ_n^2(x))\n");
    int opcion;
    scanf("%d", &opcion);

    printf("Seleccione el nivel de energía n (0-3): ");
    int n;
    scanf("%d", &n);

    if (n < 0 || n > 3) {
        printf("Nivel no válido.\n");
        return 1;
    }

    double *psi = malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        psi[i] = gsl_matrix_get(evec, i, n);
    }

    normalize(psi, N, dx);

    if (opcion == 2) {
        for (int i = 0; i < N; i++) {
            psi[i] = psi[i] * psi[i];
        }
    }

    write_to_csv("results.csv", x, psi, N);

    free(x);
    free(H);
    free(psi);
    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    gsl_eigen_symmv_free(w);

    printf("Resultados guardados en results.csv. Use Python para graficar los datos.\n");

    return 0;
}
