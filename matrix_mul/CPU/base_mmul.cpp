// Our baseline matrix multiplication
// By: Nick from CoffeeBeforeArch
void base_mmul(const int *a, const int *b, int *c, const int N) {
  // For every row...
  for(int i = 0; i < N; i++) {
    // For every col...
    for(int j = 0; j < N; j++) {
      // For each element in the row-col pair
      for(int k = 0; k < N; k++) {
        // Accumulate the partial results
        c[i * N + j] += a[i * N + k] * b[k * N + j];
      }
    }
  }
}


