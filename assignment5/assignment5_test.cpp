#include <stdio.h>
#include <math.h>
#include <ap_int.h>
#include <ap_fixed.h>
#include "assignment5.h"

int main()
{
    FILE *oFile;

    ap_int<U> ap_arr1[N][N];
    ap_int<U> ap_arr2[N][N];
    ap_int<U> ap_arr_mult[N][N];

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            ap_arr1[i][j] = i + j;
            ap_arr2[i][j] = i - j;
        }
    }


    oFile = fopen("assignment5_out.dat", "w");
    assignment5(ap_arr1, ap_arr2, ap_arr_mult);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            fprintf(oFile, "%i ", ap_arr1[i][j].to_int());
        }
        fprintf(oFile, "\t");
        for (int j = 0; j < N; j++){
            fprintf(oFile, "%i ", ap_arr2[i][j].to_int());
        }
        fprintf(oFile, "\t");
        for (int j = 0; j < N; j++){
            fprintf(oFile, "%i ", ap_arr_mult[i][j].to_int());
        }
        fprintf(oFile, "\n");
    }

    fclose(oFile);
    return 0;
}
