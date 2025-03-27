#include "problem2.h"

void foo(int in[3], char a, char b, char c, int out[3]){
    int x, y;
    for(int i = 0; i < 3; i++){
        x = in[i];
        y = a*x + b + c;
        out[i] = y;
    }
}