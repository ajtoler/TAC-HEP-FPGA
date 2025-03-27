#include <ap_int.h>
#include <ap_fixed.h>
#include "assignment5.h"

void assignment5(ap_int<U> ap_arr1[N][N], ap_int<U> ap_arr2[N][N], ap_int<U> ap_arr_mult[N][N]) {

    #pragma HLS INTERFACE s_axilite port=ap_arr1
    #pragma HLS INTERFACE s_axilite port=ap_arr2
    #pragma HLS INTERFACE s_axilite port=ap_arr_mult
    #pragma HLS INTERFACE s_axilite port=return
    #pragma HLS ARRAY_PARTITION variable=ap_arr1 complete dim=1
    #pragma HLS ARRAY_PARTITION variable=ap_arr2 complete dim=1
    #pragma HLS ARRAY_PARTITION variable=ap_arr_mult complete dim=1


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                ap_arr_mult[i][j] += ap_arr1[i][k] * ap_arr2[k][j];
            }
        }
    }
}