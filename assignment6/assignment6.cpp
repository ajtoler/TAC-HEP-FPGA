#include "assignment6.h"


void read_data(din9_t in_r[N], din9_t out_r[N]) {
    // #pragma HLS PIPELINE II=2
    // #pragma HLS ARRAY_PARTITION variable=out_r cyclic factor=2

    for (size_t  i = 0; i < N; i++) {
        // #pragma HLS UNROLL
        out_r[i] = in_r[i];  // Simple pass-through
    }
}

void compute_blur(din9_t in_c[N], din9_t out_c[N]) {
    #pragma HLS PIPELINE II=2
    // #pragma HLS LATENCY min=2 max=4
    // #pragma HLS ALLOCATION instances=mul limit=1 function
    #pragma HLS ALLOCATION instances=mul limit=0 operation
    // #pragma HLS ARRAY_PARTITION variable=in_c cyclic factor=2
    // #pragma HLS ARRAY_PARTITION variable=out_c cyclic factor=2
    #pragma HLS INLINE

    for (size_t i = 1; i < N - 1; i++) {
        // #pragma HLS UNROLL
        out_c[i] = din9_t(in_c[i - 1] + in_c[i] + in_c[i + 1]) / 3;  // Box blur operation
        // din9_t sum = in_c[i - 1] + in_c[i] + in_c[i + 1];
        // out_c[i] = sum / 3; // integer division (should use LUTs)

    }
}

void write_data(din9_t in_w[N], din9_t out_w[N]) {
    // #pragma HLS PIPELINE II=2
    // #pragma HLS ARRAY_PARTITION variable=in_w cyclic factor=2

    for (size_t i = 0; i < N; i++) {
        // #pragma HLS UNROLL
        out_w[i] = in_w[i];  // Simple pass-through
    }
}

void example(din9_t A[N], din9_t B[N]) {
    // #pragma HLS DATAFLOW
    din9_t temp1[N], temp2[N];

    for (size_t i = 0; i < N; i++) 
      temp2[i]=0;

    read_data(A, temp1);
    compute_blur(temp1, temp2);
    write_data(temp2, B);
}