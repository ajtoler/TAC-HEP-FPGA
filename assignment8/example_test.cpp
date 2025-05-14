#include "example.h"

int main() {

  din_t A[N][N], B[N][N], C[N][N];

  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      A[i][j] = rand() % 10 ;
      B[i][j] = rand() % 30 ;
    }
  }

  // Call matrix multiplication
  example(A, B, C);


  ofstream FILE;
  FILE.open("result.dat");
  int retval = 0;
  // Create input data
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
    FILE << i <<" "<<A[i][j]<<" "<<B[i][j]<<" "<<C[i][j] << endl;
  }
  }
  // Call the function
  FILE.close();

  // Compare the results file with the golden results
  retval = system("diff --brief -w result.dat result_ref.dat");
  if (retval != 0) {
    printf("Test failed  !!!\n");
    retval = 1;
  } else {
    printf("Test passed !\n");
  }

  // Return 0 if the test passes
  return retval;
}