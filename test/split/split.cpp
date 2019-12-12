#include <iostream>
#include "../../src/string.hpp"
using namespace std;

int main ()
{
  string s = "1 2	3   4";
  vector<string> v = split(s);
  cout<<s<<endl;
  for (int i = 0; i < v.size(); ++i)
   cout<<v[i]<<endl;

  s = "  1 2 3	 4";
  v = split(s);
  cout<<s<<endl;
  for (int i = 0; i < v.size(); ++i)
   cout<<v[i]<<endl;

  s = "  1 2 3	 4   ";
  v = split(s);
  cout<<s<<endl;
  for (int i = 0; i < v.size(); ++i)
   cout<<v[i]<<endl;

  s = "1, 2,   3,	 4";
  v = split(s, "\\s*,\\s*");
  cout<<s<<endl;
  for (int i = 0; i < v.size(); ++i)
   cout<<v[i]<<endl;

  s = "  1, 2,   3,	 4   ";
  v = split(s, "\\s*,\\s*");
  cout<<s<<endl;
  for (int i = 0; i < v.size(); ++i)
   cout<<v[i]<<endl;

  return 0;
}
  
