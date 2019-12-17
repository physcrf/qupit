#include <iostream>
#include "../../src/parameter.hpp"
using namespace std;

int main ()
{
  vector<pair<string, string>> parms = read_parameter_file();
  cout<<"read:"<<endl;
  for (uint32_t i = 0; i < parms.size(); ++i)
    cout<<parms[i].first<<"\t=\t"<<parms[i].second<<endl;

  cout<<"values:"<<endl;
  
  cout<<"RUNMD"<<"\t=\t"<<RUNMD<<endl;
  cout<<"SYSTM"<<"\t=\t"<<SYSTM<<endl;
  cout<<"RDFUN"<<"\t=\t"<<RDFUN<<endl;
  cout<<"WRFUN"<<"\t=\t"<<WRFUN<<endl;
  cout<<"FUNFL"<<"\t=\t"<<FUNFL<<endl;
  cout<<"EXTFL"<<"\t=\t"<<EXTFL<<endl;
  cout<<"SPNFL"<<"\t=\t"<<SPNFL<<endl;
  cout<<"RDMFL"<<"\t=\t"<<RDMFL<<endl;

  cout<<"TMITV"<<"\t=\t"<<TMITV<<endl;
  cout<<"NSTEP"<<"\t=\t"<<NSTEP<<endl;
  cout<<"TSTEP"<<"\t=\t"<<TSTEP<<endl;
  cout<<"INRHO"<<"\t=\t";
  for (uint32_t i = 0; i < 8; ++i)
    cout<<INRHO[i]<<" ";
  cout<<endl;
  cout<<"THETA"<<"\t=\t"<<THETA<<endl;
  cout<<"VRPHI"<<"\t=\t"<<VRPHI<<endl;

  cout<<"CUTFQ"<<"\t=\t"<<CUTFQ<<endl;
  cout<<"ALPHA"<<"\t=\t"<<ALPHA<<endl;
  cout<<"OHMIS"<<"\t=\t"<<OHMIS<<endl;
  cout<<"BTEMP"<<"\t=\t"<<BTEMP<<endl;

  cout<<"BDWID"<<"\t=\t"<<BDWID<<endl;
  cout<<"LPOTE"<<"\t=\t"<<LPOTE<<endl;
  cout<<"RPOTE"<<"\t=\t"<<RPOTE<<endl;
  cout<<"LTEMP"<<"\t=\t"<<LTEMP<<endl;
  cout<<"RTEMP"<<"\t=\t"<<RTEMP<<endl;

  return 0;
}
