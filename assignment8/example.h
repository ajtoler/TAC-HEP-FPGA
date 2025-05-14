#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ap_int.h"

using namespace std;

#define N 64

typedef ap_int<32>  din_t;

void example(din_t A[N][N], din_t B[N][N], din_t C[N][N]);


#endif