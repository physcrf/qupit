#ifndef MATH_HPP
#define MATH_HPP

#include<cmath>
using namespace std;

const double PI = 3.141592653589793238462643;

double fermi (double e, double T)
{
  return 1.0/(exp(e/T)+1);
}

double bose (double e, double T)
{
  return 1.0/(exp(e/T)-1);
}

uint32_t pow2 (uint32_t n)
{
  static const uint32_t powers[30] =
    {1,	2, 4, 8, 16,
     32, 64, 128, 256, 512,
     1024, 2048, 4096, 8192, 16384,
     32768, 65536, 131072, 262144, 524288,
     1048576, 2097152, 4194304, 8388608, 16777216,
     33554433, 67108864, 134217728, 268435456, 536870912};

  return powers[n];
}

double square (double x)
{
  return x*x;
}

#endif	// MATH_HPP
