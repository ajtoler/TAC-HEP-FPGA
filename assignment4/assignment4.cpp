#include "assignment4.h"
#include <ap_int.h>
#include <ap_fixed.h>

void assignment4_c(int arr1[N], int arr2[N], int arr_add[N], int arr_sub[N], int arr_mul[N], float arr_div[N], int arr_mod[N]) {

    for (int i = 0; i < N; i++)
    {
        arr_add[i] = arr1[i] + arr2[i];
        arr_sub[i] = arr1[i] - arr2[i];
        arr_mul[i] = arr1[i] * arr2[i];
        arr_div[i] = float(arr1[i]) / float(arr2[i]);
        arr_mod[i] = arr1[i] % arr2[i];
    }
}

void assignment4_ap(ap_int<U> ap_arr1[N], ap_int<U> ap_arr2[N], ap_int<U> ap_arr_add[N], ap_int<U> ap_arr_sub[N], ap_int<U> ap_arr_mul[N], ap_fixed<U, U/2> ap_arr_div[N], ap_int<U> ap_arr_mod[N]) {

Loop:
    for (int i = 0; i < N; i++)
    {
        ap_arr_add[i] = ap_arr1[i] + ap_arr2[i];
        ap_arr_sub[i] = ap_arr1[i] - ap_arr2[i];
        ap_arr_mul[i] = ap_arr1[i] * ap_arr2[i];
        ap_arr_div[i] = ap_fixed<U, U/2>(ap_arr1[i]) / ap_fixed<U, U/2>(ap_arr2[i]);
        ap_arr_mod[i] = ap_arr1[i] % ap_arr2[i];
    }
}