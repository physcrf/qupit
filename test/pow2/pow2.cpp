#include <iostream>
#include "../../src/math.hpp"
using namespace std;

int main ()
{
  int s = 1;
  for (int i = 0; i < 30; ++i)
    {
      cout<<"p = "<<i<<",\t"<<s<<" == "<<pow2(i)<<",\t"<<(s==pow2(i))<<endl;
      s *= 2;
    }
  return 0;
}
