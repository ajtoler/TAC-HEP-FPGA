#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ap_int.h"

using namespace std;

#define N 64

typedef ap_uint<4>   din4_t;
typedef ap_uint<5>   din5_t;
typedef ap_uint<15>  din15_t;

void example(din4_t A[N][N], din5_t B[N][N], din15_t C[N][N]);

#endif