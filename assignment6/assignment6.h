#ifndef _ASSIGNMENT6_H_
#define _ASSIGNMENT6_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ap_int.h"

using namespace std;

#define N 30

typedef ap_uint<5>   din5_t;
typedef ap_uint<6>   din6_t;
typedef ap_uint<8>   din8_t;
typedef ap_uint<9>   din9_t;
typedef ap_uint<10>  din10_t;

void read_data(din9_t *in_r, din9_t *out_r);
void compute_blur(din9_t *in_c, din9_t *out_c);
void write_data(din9_t *in_w, din9_t *out_w);
void example(din9_t *A, din9_t *B);

#endif