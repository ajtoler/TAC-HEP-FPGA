#include <stdio.h>
#include <math.h>
#include "problem2.h"

int main()
{
    FILE *oFile;

    int in[3] = {1, 2, 3};
    char a = '2';
    char b = '3';
    char c = '4';
    int out[3] = {0, 0, 0};

    oFile = fopen("problem2.dat", "w");
    // Execute the function with latest input
    foo(in, a, b, c, out);

    // Save the results.
    fprintf(oFile, "in: %i %i %i\n", in[0], in[1], in[2]);
    fprintf(oFile, "char a: %c, b: %c, c: %c\n", a, b, c);
    fprintf(oFile, "int a: %i, b: %i, c: %i\n", a, b, c);
    fprintf(oFile, "out: %i %i %i\n", out[0], out[1], out[2]);

    fclose(oFile);
    return 0;
}
