#include <string>
#include <iostream>
#include <cstdlib>
#include "../../src/string.hpp"
using namespace std;

int main ()
{
  string s;
  cout<<"test numberp:"<<endl;
  s = "123";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;
  
  s = "123.321";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "+123.321";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;
  
  s = "-123.321";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;
  
  s = "++123.321";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "--123.321";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "123.321e2";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "123.321e-2";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "123.321e+2";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "123.e2";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "123.321ed2";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "1d3.e2";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  s = "hello";
  cout<<s<<",\t"<<numberp(s)<<endl;
  cout<<"atof("<<s<<") => "<<atof(s.c_str())<<endl;

  return 0;
}
