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

typedef ap_int<32>  din_t;

void example(din_t A[N][N], din_t B[N], din_t C[N]);

void bubble_sort(din_t arr[SORT_N]);


#endif