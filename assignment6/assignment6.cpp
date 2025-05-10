#include "assignment6.h"

void read_data(din9_t in_r[N], din9_t out_r[N]) { 
    for (size_t  i = 0; i < N; i++) {
        out_r[i] = in_r[i];  // Simple pass-through
    }
}

void compute_blur(din9_t in_c[N], din9_t out_c[N]) {
    #pragma HLS PIPELINE II=2
    #pragma HLS LATENCY min=1 max=2
    #pragma HLS ALLOCATION instances=mul limit=0 operation
    #pragma HLS ALLOCATION instances=fdiv limit=0 operation
    #pragma HLS ARRAY_PARTITION variable=in_c cyclic factor=3
    #pragma HLS ARRAY_PARTITION variable=out_c cyclic factor=3
    #pragma HLS INLINE

    for (size_t i = 1; i < N - 1; i++) {
        // #pragma HLS UNROLL
        out_c[i] = din11_t(in_c[i - 1] + in_c[i] + in_c[i + 1]) / din2_t(3);  // Box blur operation
    }
    
}

void write_data(din9_t in_w[N], din9_t out_w[N]) {
    for (size_t i = 0; i < N; i++) {
        out_w[i] = in_w[i];  // Simple pass-through
    }
}

void example(din9_t A[N], din9_t B[N]) {
    #pragma HLS DATAFLOW
    din9_t temp1[N], temp2[N];

    for (size_t i = 0; i < N; i++) 
      temp2[i]=0;

    read_data(A, temp1);
    compute_blur(temp1, temp2);
    write_data(temp2, B);
}