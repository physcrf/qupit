#include <iostream>
#include "../../src/bits.hpp"
using namespace std;

int main ()
{
  bits I(10,4);
  cout<<I<<'\t'<<I.value()<<endl;
  
  for (int i = 0; i < I.size(); ++i)
    cout<<I[i];
  cout<<'\t'<<I.value()<<endl;

  I.set(0);
  cout<<I<<'\t'<<I.value()<<endl;

  I.reset(2);
  cout<<I<<'\t'<<I.value()<<endl;

  I.flip(2);
  cout<<I<<'\t'<<I.value()<<endl;

  return 0;
}
