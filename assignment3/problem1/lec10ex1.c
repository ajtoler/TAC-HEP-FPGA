#include "lec10ex1.h"

void lec10ex1 (int *y, int c[N],  int x) {

   static int arr[N];
   int sum;
   int data;
   int i;

   sum=0;
Loop:
   for (i = N - 1; i >= 0; i--)
   {
      if (i == 0)
      {
         arr[0] = x;
         data = x;
      }
      else
      {
         arr[i] = arr[i - 1];
         data = arr[i];
      }
      sum += data * c[i];
      ;
   }
   *y = sum;
}