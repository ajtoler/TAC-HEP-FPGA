#include <ap_int.h>
#include <ap_fixed.h>
#ifndef ASSIGNMENT4_H_
#define ASSIGNMENT4_H_
#define N	15
#define U 20

void assignment4_c (
  int arr1[N],
  int arr2[N],
  int arr_add[N],
  int arr_sub[N],
  int arr_mul[N],
  float arr_div[N],
  int arr_mod[N]
);

void assignment4_ap (
  ap_int<U> arr1[N],
  ap_int<U> arr2[N],
  ap_int<U> arr_add[N],
  ap_int<U> arr_sub[N],
  ap_int<U> arr_mul[N],
  ap_fixed<U, U/2> arr_div[N],
  ap_int<U> arr_mod[N]
);

#endif
