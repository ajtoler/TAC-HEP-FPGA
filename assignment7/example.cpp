#include <ap_int.h>
#include <hls_stream.h>
#include "example.h"

// void matrix_multiplication(din8_t A[N][N], din13_t B[N], din26_t C[N]) {
//     #pragma HLS ARRAY_PARTITION variable=A complete dim=2
//     #pragma HLS ARRAY_PARTITION variable=B complete dim=1
//     #pragma HLS ARRAY_PARTITION variable=C complete dim=1
//     #pragma HLS INLINE
//     #pragma HLS STABLE variable=A
//     #pragma HLS STABLE variable=B

//     // Matrix multiplication
//     for (size_t i = 0; i < N; i++) {
//         #pragma HLS PIPELINE II=1
//         din26_t prod = 0;
//         for (size_t j = 0; j < N; j++) {
//             #pragma HLS UNROLL
//             prod += A[i][j] * B[j];
//         }
//         C[i] = prod;
//     }
// }

void bubble_sort(din26_t arr[SORT_N]) {
    #pragma HLS ARRAY_PARTITION variable=arr complete dim=1
    #pragma HLS INLINE
    for (int i = 0; i < SORT_N - 1; i++) {
        for (int j = 0; j < SORT_N - i - 1; j++) {
            #pragma HLS PIPELINE II=1
            if (arr[j] > arr[j + 1]) {
                din26_t  temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Top-level function for HLS
void example(din8_t A[N][N], din13_t B[N], din26_t C[N]) {
    #pragma HLS INTERFACE ap_memory port=A
    #pragma HLS INTERFACE ap_memory port=B
    #pragma HLS INTERFACE ap_memory port=C
    #pragma HLS INTERFACE ap_ctrl_hs port=return
    #pragma HLS ARRAY_PARTITION variable=A complete dim=2
    #pragma HLS ARRAY_PARTITION variable=B complete dim=1
    #pragma HLS ARRAY_PARTITION variable=C complete dim=1
    #pragma HLS STABLE variable=A
    #pragma HLS STABLE variable=B
    #pragma HLS INLINE
    // Matrix multiplication
    for (size_t i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        din26_t prod = 0;
        for (size_t j = 0; j < N; j++) {
            #pragma HLS UNROLL 
            prod += A[i][j] * B[j];
        }
        C[i] = prod;
    }
    bubble_sort(C);

    // # pragma HLS DATAFLOW
    // din26_t prod[N];
    // matrix_multiplication(A, B, prod);
    // bubble_sort(prod);
    // for (size_t i = 0; i < N; i++) {
    //     #pragma HLS PIPELINE II=1
    //     C[i] = prod[i];
    // }
}