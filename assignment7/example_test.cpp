#include "example.h"
#include <cstdlib> // for rand

int main() {
    din_t A[N][N], B[N], C[N];
    din_t rand_i, rand_j;

    // Initialize A and B
    for (size_t i = 0; i < N; i++) {
        rand_i = (rand() % N) + 1;
        for (size_t j = 0; j < N; j++) {
            rand_j = (rand() % N) + 1;
            A[i][j] = rand_i + rand_j + 1; //i + j + 1;
        }
        B[i] = rand_i * (rand_j + 1); //(i) * (j+1);
    }

    // Call matrix multiplication
    example(A, B, C);

    // Prdin_t result
    cout << "Result Matrix C:" << endl;
    for (size_t i = 0; i < N; i++) {
        cout << C[i] << " "<<endl;
    }

    return 0;
}