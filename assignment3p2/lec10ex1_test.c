#include <stdio.h>
#include <math.h>
#include "lec10ex1.h"

int main()
{
  const int samples = 600;
  FILE *oFile;

  int inp, output;
  int coef[N] = { 0, -10, -9, 23, 56, 63, 56, 23, -9, -10, 0};

  int i, rmp;
  inp = 0;
  rmp = 1;

  oFile = fopen("lec10ex1_out.dat", "w");
  for (i = 0; i <= samples; i++)
  {
    if (rmp == 1)
      inp = inp + 1;
    else
      inp = inp - 1;

    // Execute the function with latest input
    lec10ex1(&output, coef, inp);

    if ((rmp == 1) && (inp >= 75))
      rmp = 0;
    else if ((rmp == 0) && (inp <= -75))
      rmp = 1;

    // Save the results.
    fprintf(oFile, "%i %d %d\n", i, inp, output);
  }
  fclose(oFile);

  printf("Comparing against output data \n");
  if (system("diff -w lec10ex1_out.dat lec10ex1_out_ref.dat"))
  {

    fprintf(stdout, "*******************************************\n");
    fprintf(stdout, "FAIL: Output DOES NOT match the reference output\n");
    fprintf(stdout, "*******************************************\n");
    return 1;
  }
  else
  {
    fprintf(stdout, "*******************************************\n");
    fprintf(stdout, "PASS: The output matches the reference output!\n");
    fprintf(stdout, "*******************************************\n");
    return 0;
  }
}
