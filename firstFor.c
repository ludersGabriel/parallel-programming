#include <omp.h>
#include <stdio.h>

// gcc -fopenmp main.c -o para

static long num_steps = 1000000000;

double step;

int main() {
  double sum = 0.0;

  step = 1.0 / (double)num_steps;

#pragma omp parallel
  {
    double localSum = 0.0;
    double x;

#pragma omp for
    for (int i = 0; i < num_steps; i++) {
      x = (i + 0.5) * step;
      localSum = localSum + 4.0 / (1.0 + x * x);
    }

    double partial = step * localSum;

#pragma omp atomic
    sum += partial;
  }

  printf("%f\n", sum);
}