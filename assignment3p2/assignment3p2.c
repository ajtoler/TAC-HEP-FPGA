#include "assignment3p2.h"

void assignment3p2 (int in[3], char a, char b, char c, int out[3]) {

    int x;
    int y;
    int i;

Loop:
    for (i = 0; i < 3; i++)
    {
        x = in[i];
        y = a*x + b + c;
        out[i] = y;
    }
}
