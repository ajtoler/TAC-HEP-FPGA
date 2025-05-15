#include "example.h"

int main() {

    din4_t A[N][N];
    din5_t B[N][N];
    din15_t C[N][N];

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            A[i][j] = rand() % 10 ; // Max 10 -> 4 bits
            B[i][j] = rand() % 30 ; // Max 30 -> 5 bits
        }
    }

    // Call matrix multiplication
    example(A, B, C);
    // Max 10*30*64 = 19200 -> 15 bits

    ofstream FILE;
    FILE.open("result.dat");
    int retval = 0;
    // Create input data
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            FILE << i <<" "<<A[i][j]<<" "<<B[i][j]<<" "<<C[i][j] << endl;
        }
    }
    // Call the function
    FILE.close();

    // Compare the results file with the golden results
    retval = system("diff --brief -w result.dat result_ref.dat");
    if (retval != 0) {
        printf("Test failed  !!!\n");
        retval = 1;
    } else {
        printf("Test passed !\n");
    }

    // Return 0 if the test passes
    return retval;
}