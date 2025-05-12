#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ap_int.h"

using namespace std;

#define N 64
#define SORT_N 32

typedef ap_uint<7> din7_t; // for rand_i, rand_j
typedef ap_uint<8> din8_t; // for A[N][N]
typedef ap_uint<13> din13_t; // for B[N]
typedef ap_uint<26> din26_t; // for C[N], prod, arr[SORT_N], temp
typedef ap_uint<32> din32_t;

void example(din8_t A[N][N], din13_t B[N], din26_t C[N]);
// void matrix_multiplication(din8_t A[N][N], din13_t B[N], din26_t C[N]);
void bubble_sort(din26_t arr[SORT_N]);


#endif