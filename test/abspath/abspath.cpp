#include <iostream>
#include "../../src/string.hpp"
using namespace std;

int main ()
{
  string s = "hello";
  cout<<s<<" => "<<abspath(s)<<endl;

  s = "/hello";
  cout<<s<<" => "<<abspath(s)<<endl;

  s = "hello/.///.//";
  cout<<s<<" => "<<abspath(s)<<endl;

  s = "../../";
  cout<<s<<" => "<<abspath(s)<<endl;

  s = "hello/world/..";
  cout<<s<<" => "<<abspath(s)<<endl;
  
  return 0;
}
