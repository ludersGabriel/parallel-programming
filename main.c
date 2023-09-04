#include <omp.h>
#include <stdio.h>

// gcc -fopenmp main.c -o para

static long num_steps = 1000000000;
double step;

double global_sum = 0.0;
int ths = 4;

int main() {
  step = 1.0 / (double)(num_steps);
#pragma omp parallel num_threads(ths)
  {
    int i;

    double x, pi, sum = 0.0;

    int id = omp_get_thread_num();

    double lim = num_steps / ths;

    for (i = id * lim; i < (id + 1) * lim; i++) {
      x = (i + 0.5) * step;
      sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    printf("Thread %d: %f\n", id, pi);

    global_sum += pi;
  }

  printf("%f\n", global_sum);
}