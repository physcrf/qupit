#include <iostream>
#include <string>
#include "../../src/string.hpp"
using namespace std;

int main ()
{
  string s = "hello, world";
  cout<<s<<" => "<<endl;
  cout<<trim(s)<<endl;

  s = "  hello, world  ";
  cout<<s<<" => "<<endl;
  cout<<trim(s)<<endl;

  s = "  hello, world  # haha";
  cout<<s<<" => "<<endl;
  cout<<trim(s)<<endl;

  s = "  hello, world  ! hoho";
  cout<<s<<" => "<<endl;
  cout<<trim(s)<<endl;

  return 0;
}
  
