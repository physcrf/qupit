#include <stdio.h>
#include <math.h>
#include "../../src/field.hpp"
using namespace std;

int main ()
{
  FILE* fp = fopen("dat", "w");
  for (int i = 0; i < 10; ++i)
    fprintf (fp, "%f\t%f\t%f\t%f\n", i*0.1, sin(i*0.1), cos(i*0.1), 1.0);
  fclose(fp);

  field F;
  F.read("dat");
  for (int i = 0; i < 19; ++i)
    printf ("%f\t%f\t%f\t%f\n", i*0.05, F.x(i*0.05), F.y(i*0.05), F.z(i*0.05));

  return 0;
}
