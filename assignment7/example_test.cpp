#include "example.h"
#include <cstdlib> // for rand

int main() {
    din7_t rand_i, rand_j;
    din8_t A[N][N];
    din13_t B[N];
    din26_t C[N];
    

    // Initialize A and B
    for (size_t i = 0; i < N; i++) {
        rand_i = (rand() % N) + 1; 
        // Max 63 + 1 = 64, 7 bits = 
        // Average 32, 5 bits = 32
        for (size_t j = 0; j < N; j++) {
            rand_j = (rand() % N) + 1; 
            // Max 63 + 1 = 64, 6 bits = 64
            // Average 32, 5 bits = 32
            A[i][j] = rand_i + rand_j + 1; //i + j + 1; 
            // Max 64 + 64 + 1 = 129, 8 bits = 256
            // Average 65, 7 bits = 128
        }
        B[i] = rand_i * (rand_j + 1); //(i) * (j+1); 
        // Max 64 * (64 + 1) = 4160, 13 bits = 8192
        // Average 1056, 11 bits = 2048
    }

    // Call matrix multiplication
    example(A, B, C);
    // Max A[i][j] * B[j] * N = (129 * 4160) * 64 = 34344960, 26 bits = 67108864
    // Average = 4392960, 23 bits = 8388608

    // Prdin_t result
    cout << "Initial Matrix A:" << endl;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Initial Matrix B:" << endl;
    for (size_t i = 0; i < N; i++) {
        cout << B[i] << " ";
    }

    cout << "Result Matrix C:" << endl;
    for (size_t i = 0; i < N; i++) {
        cout << C[i] << " "<<endl; 
    }

    return 0;
}