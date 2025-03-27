#include <stdio.h>
#include <math.h>
#include <ap_int.h>
#include <ap_fixed.h>
#include "assignment4.h"

int main()
{
  FILE *oFile;

  int arr1[N] = {-5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int arr2[N] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5};
  int arr_add[N];
  int arr_sub[N];
  int arr_mul[N];
  float arr_div[N];
  int arr_mod[N];

  ap_int<U> ap_arr1[N] = {-5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ap_int<U> ap_arr2[N] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5};
  ap_int<U> ap_arr_add[N];
  ap_int<U> ap_arr_sub[N];
  ap_int<U> ap_arr_mul[N];
  ap_fixed<U, U/2> ap_arr_div[N];
  ap_int<U> ap_arr_mod[N];


  oFile = fopen("assignment4_out.dat", "w");
  assignment4_c(arr1, arr2, arr_add, arr_sub, arr_mul, arr_div, arr_mod);
  assignment4_ap(ap_arr1, ap_arr2, ap_arr_add, ap_arr_sub, ap_arr_mul, ap_arr_div, ap_arr_mod);

  for (int i = 0; i < N; i++) {
    fprintf(oFile, "arr1: %i, arr2: %i, add: %i, sub: %i, mul: %i, div: %f, mol: %i\n", arr1[i], arr2[i], arr_add[i], arr_sub[i], arr_mul[i], arr_div[i], arr_mod[i]);
  }

  for (int i = 0; i < N; i++) {
    fprintf(oFile, "arr1: %i, arr2: %i, add: %i, sub: %i, mul: %i, div: %f, mol: %i\n", ap_arr1[i].to_int(), ap_arr2[i].to_int(), ap_arr_add[i].to_int(), ap_arr_sub[i].to_int(), ap_arr_mul[i].to_int(), ap_arr_div[i].to_float(), ap_arr_mod[i].to_int());
  }

  fclose(oFile);
  return 0;
}
