#include <ap_int.h>
#include <hls_stream.h>

#include "example.h"

void example(din_t A[N][N], din_t B[N][N], din_t C[N][N]) {

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {


      C[i][j]=0;
      for (size_t k = 0; k < N; ++k) {
	C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}