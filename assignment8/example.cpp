#include <ap_int.h>
#include <hls_stream.h>
#include "example.h"

void example(din4_t A[N][N], din5_t B[N][N], din15_t C[N][N]) {
    #pragma HLS INLINE
    // #pragma HLS FUNCTION_INSTANTIATE
    #pragma HLS STABLE variable=A
    #pragma HLS STABLE variable=B

    #pragma HLS ARRAY_PARTITION variable=A complete dim=2
    #pragma HLS ARRAY_PARTITION variable=B complete dim=1
    #pragma HLS ARRAY_PARTITION variable=C complete dim=0
    
    #pragma HLS INTERFACE s_axilite port=return
    #pragma HLS INTERFACE ap_memory port=A
    #pragma HLS INTERFACE ap_memory port=B
    #pragma HLS INTERFACE ap_vld port=C

    #pragma HLS DATAFLOW

    // #pragma HLS LOOP_FLATTEN
    LOOP_1: for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            #pragma HLS PIPELINE II=2
            // #pragma HLS LOOP_TRIPCOUNT min=64 max=64
            din15_t temp = 0;
            LOOP_2: for (size_t k = 0; k < N; ++k) {
                #pragma HLS UNROLL //factor=8
                // #pragma HLS LOOP_TRIPCOUNT min=64 max=64
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
    }
}