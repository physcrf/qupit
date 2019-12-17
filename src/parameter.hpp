#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include <algorithm>
#include <fstream>
#include <utility>
#include <stdint.h>
#include "string.hpp"
using namespace std;

// control parameters
string		RUNMD	= "Dynamics";		// DYNAMICS, running the full dynamics, or FUNCTIONAL, compute the influential functional
string		SYSTM	= "SpinBoson";		// specify the system 
bool	 	RDFUN	= 0;			// read functional from file
bool		WRFUN	= 0;			// write functional to file
string		FUNFL	= "FUNC";		// file to store functional
string		EXTFL	= "EXT";		// file to store external field
string		SPNFL	= "SPIN";		// file to store spin dynamics
string		RDMFL	= "RDM";		// file to store rho dynamics

// common phyiscal parameters
double		TMITV 	= 0.25;			// delta t
uint32_t	NSTEP 	= 4000;			// run time steps, N
uint32_t	TSTEP 	= 3;			// truncated time steps, Ns
double		INRHO[8] = {1,0,0,0,0,0,0,0};	// initial rho
double		THETA	= 0;			// coupling angle theta
double		VRPHI	= 0;			// coupling angle phi

// spin-boson parameters
double		CUTFQ	= 1;			// cutoff frequency
double		ALPHA	= 1;			// system-bath coupling strength
double		OHMIS	= 1;			// expotenial of ohmic form, s
double		BTEMP	= 1;			// temperature

// spin-fermion parameters
double		BDWID	= 3;			// band width
double		LPOTE	= +0.5;			// chemical potential for left lead
double		RPOTE	= -0.5;			// chemical potential for right lead
double		LTEMP	= 0;			// temperature for left lead
double		RTEMP	= 0;			// temperature for right lead

/*-----------------------------------------------------------*/
bool keyp (string& s)
{
  // control parameters
  if (s == "RUNMD") return true;
  if (s == "SYSTM") return true;
  if (s == "RDFUN") return true;
  if (s == "WRFUN") return true;
  if (s == "FUNFL") return true;
  if (s == "EXTFL") return true;
  if (s == "SPNFL") return true;
  if (s == "RDMFL") return true;

  // common physical parameters
  if (s == "TMITV") return true;
  if (s == "NSTEP") return true;
  if (s == "TSTEP") return true;
  if (s == "INRHO") return true;
  if (s == "THETA") return true;
  if (s == "VRPHI") return true;

  // spin-boson parameters
  if (s == "CUTFQ") return true;
  if (s == "ALPHA") return true;
  if (s == "OHMIS") return true;
  if (s == "BTEMP") return true;

  // spin-fermion parameters
  if (s == "BDWID") return true;
  if (s == "LPOTE") return true;
  if (s == "RPOTE") return true;
  if (s == "RPOTE") return true;
  if (s == "LTEMP") return true;
  if (s == "RTEMP") return true;

  return false;
}

vector<pair<string, string>> read_parameter_file ()
{
  vector<pair<string, string>> vp;
  
  ifstream INPUT("INPUT");
  if (not INPUT)
    vp.push_back(pair<string, string>("FAILED", "OPEN"));
  else
    {
      string line;
      vector<string> kv;
      while (getline(INPUT, line))
	{
	  trim(line);
	  if (blankp(line)) continue;
	  
	  kv = split (line, "\\s*=\\s*");
	  if (kv.size() != 2)
	    vp.push_back(pair<string, string>("UNREGLINE", line));
	  else if (not keyp(kv[0]))
	    vp.push_back(pair<string, string>("UNREGKEY", kv[0]));

	  // control parameters
	  if (kv[0] == "RUNMD")
	    {
	      if (kv[0] != "Dynamics" and kv[1] != "Functional")
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      RUNMD = kv[1];
	    }

	  if (kv[0] == "SYSTM")
	    {
	      if (kv[0] != "SpinBoson" and kv[0] != "SpinFermion")
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      SYSTM = kv[1];
	    }

	  if (kv[0] == "RDFUN")
	    {
	      if (not boolp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      RDFUN = truep(kv[1]);
	    }

	  if (kv[0] == "WRFUN")
	    {
	      if (not boolp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      WRFUN = truep(kv[1]);
	    }

	  if (kv[0] == "FUNCL")
	    {
	      vp.push_back(pair<string, string>(kv[0], kv[1]));

	      FUNFL = kv[1];
	    }

	  if (kv[0] == "EXTFL")
	    {
	      vp.push_back(pair<string, string>(kv[0], kv[1]));

	      EXTFL = kv[1];
	    }

	  if (kv[0] == "SPNFL")
	    {
	      vp.push_back(pair<string, string>(kv[0], kv[1]));

	      SPNFL = kv[1];
	    }

	  if (kv[0] == "RDMFL")
	    {
	      vp.push_back(pair<string, string>(kv[0], kv[1]));

	      RDMFL = kv[1];
	    }

	  // common physical parameters
	  if (kv[0] == "TMITV")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      TMITV = stof(kv[1]);
	    }
	  
	  if (kv[0] == "NSTEP")
	    {
	      if (not integerp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));
	      
	      NSTEP = stoi(kv[1]);
	    }
	  
	  if (kv[0] == "TSTEP")
	    {
	      if (not integerp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      TSTEP = stoi(kv[1]);
	    }

	  if (kv[0] == "INRHO")
	    {
	      vector<string> ss = split(kv[1], "\\s+");
	      bool flag = false;
	      if (not all_of(ss.begin(), ss.end(), numberp))
		flag = true;
		
	      if (flag)
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      for (uint32_t i = 0; i < ss.size() and i < 8; ++i)
		INRHO[i] = stof(ss[i]);
	    }

	  if (kv[0] == "THETA")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      THETA = stof(kv[1]);
	    }

	  if (kv[0] == "VRPHI")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      VRPHI = stof(kv[1]);
	    }

	  // spin-boson parameters
	  if (kv[0] == "CUTFQ")
	    {
	       if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	       CUTFQ = stof(kv[1]);
	    }

	  if (kv[0] == "ALPHA")
	    {
	       if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	       ALPHA = stof(kv[1]);
	    }

	  if (kv[0] == "OHMIS")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      OHMIS = stof(kv[1]);
	    }

	  if (kv[0] == "BTEMP")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      BTEMP = stof(kv[1]);
	    }

	  // spin-fermion parameters
	  if (kv[0] == "BDWID")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      BDWID = stof(kv[1]);
	    }

	  if (kv[0] == "LPOTE")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      LPOTE = stof(kv[1]);
	    }

	  if (kv[0] == "RPOTE")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      RPOTE = stof(kv[1]);
	    }

	  if (kv[0] == "LTEMP")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      LTEMP = stof(kv[1]);
	    }

	  if (kv[0] == "RTEMP")
	    {
	      if (not numberp(kv[1]))
		vp.push_back(pair<string, string>("UNREGVALUE", kv[0]));
	      else
		vp.push_back(pair<string, string>(kv[0], kv[1]));

	      RTEMP = stof(kv[1]);
	    }
	}
    }	 
  return vp;
}	 

#endif	// PARAMETER_HPP
