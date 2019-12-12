#include <iostream>
#include "../../src/tensor.hpp"
using namespace std;

int main ()
{
  tensor I(4);
  cout<<I<<endl;

  for (int i = 0; i < I.size(); ++i)
    I[i] = complex<double>(sin(i),sin(i));
  cout<<I<<endl;

  for (int i = 0; i < I.size(); ++i)
    {
      bits b(I.length(), i);
      I[b] = complex<double>(sin(i),sin(i));
    }
  cout<<I<<endl;

  I.write("dat");
  
  tensor J(4);
  cout<<J<<endl;
  
  J.read("dat");
  cout<<J<<endl;
  return 0;
}
