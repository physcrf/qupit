#include <stdio.h>
#include "../../src/io.hpp"

int main ()
{
  FILE* fp = fopen("test", "w");
  tee (fp, "hello world\n");
  tee (fp, "%+.8f\n", 1.0);
  tee (fp, "%+.8f\n", -1.0);
}
