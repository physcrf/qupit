#ifndef IO_HPP
#define IO_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include "parameter.hpp"
#include "string.hpp"
#include "field.hpp"

FILE* OUT = NULL;
FILE* FUNC = NULL;
FILE* EXT = NULL;
FILE* SPIN = NULL;
FILE* RDM = NULL;
const int32_t indent = 4;
const int32_t tab1st = 30;

uint32_t tee (const char* format, ...)
{
  uint32_t n;
  va_list args;
  va_start (args, format);
  n = vprintf (format, args);
  va_end (args);

  va_start (args, format);
  vfprintf (OUT, format, args);
  va_end (args);

  return n;
}

// fill whitespaces
int32_t fill (int32_t n)
{
  for (int32_t i = 0; i < n; ++i)
    tee (" ");
  return n;
}

void qupit_abort()
{
  tee ("\nProgram Aborted.\n");
  exit(1);
}

void read_input ()
{
  tee ("\nreading INPUT:\n");
  vector<pair<string, string>> params = read_parameter_file();
  if (params[0].first == "FAILED")
    {
      fill(indent); tee ("cannot open INPUT file, use default values\n");
    }
  else if (params.empty())  // checking input types
    {
      fill(indent); tee ("empty INPUT file, use default values\n");
    }
  else
    {
      for (uint32_t i = 0; i < params.size(); ++i)
	if (params[i].first == "UNREGLINE")
	  {
	    fill(indent); tee ("found unregonized line:\n");
	    fill(2*indent); tee ("%s\n", params[i].second.c_str());
	    qupit_abort();
	  }
	else if (params[i].first == "UNREGKEY")
	  {
	    fill(indent);
	    tee ("found unregonized parameter: %s\n", params[i].second.c_str());
	    qupit_abort();
	  }
	else if (params[i].first == "UNREGVALUE")
	  {
	    fill(indent);
	    tee ("found unregonized value for %s\n", params[i].second.c_str());
	    qupit_abort();
	  }
	else
	  {
	    fill(indent);
	    tee ("found %s = %s\n", params[i].first.c_str(), params[i].second.c_str());
	  }
    }
}

void check_parameters ()
{
  tee ("\nchecking parameters:\n");
  if (RUNMD == "Functional")
    {
      fill(indent);
      RDFUN = false; WRFUN = true;
      tee ("RUNMD = Functional, forcedly set RDFUN = false and WRFUN = true\n");
    }
  if (RDFUN and WRFUN)
    {
      fill(indent);
      tee ("confliction that RDFUN and WRFUN both be true, please check\n");
      qupit_abort();
    }

  if (TMITV <= 0)
    {
      fill(indent);
      tee ("TMITV must be positive, please check\n");
      qupit_abort();
    }
  else if (TMITV < 0.1)
    {
      fill(indent);
      tee ("TMITV is smaller than 0.1, please be careful\n");
    }
  else if (TMITV > 1.0)
    {
      fill(indent);
      tee ("TMITV is larger than 1.0, please be careful\n");
    }

  if (NSTEP <= TSTEP)
    {
      fill(indent);
      tee ("NSTEP should be larger than TSTEP, please check\n");
      qupit_abort();
    }
	
  if (TSTEP > 10)
    {
      fill(indent);
      tee ("TSTEP is larger than 10, may be very time consuming, please be careful\n");
    }

  if (INRHO[1] != -INRHO[1] or INRHO[3] != -INRHO[5] or INRHO[7] != -INRHO[7])
    {
      fill(indent);
      tee ("initial system density matrix is not Hermite, please check\n");
      qupit_abort();
    }

  if (INRHO[0]+INRHO[6] != 1)
    {
      fill(indent);
      tee ("trace of initial system matrix is not one, please check\n");
      qupit_abort();
    }

  fill(indent);
  tee ("common parameters checked\n");
  
  if (SYSTM == "SpinBoson")
    {
      if (CUTFQ <= 0)
	{
	  fill(indent);
	  tee ("CUTFQ must be positive, please check\n");
	  qupit_abort();
	}
  
      if (ALPHA <= 0)
	{
	  fill(indent);
	  tee ("ALPHA must be positive, please check\n");
	  qupit_abort();
	}

      if (BTEMP <= 0)
	{
	  fill(indent);
	  tee ("BTEMP must be positive, please check\n");
	  qupit_abort();
	}

      fill(indent);
      tee ("parameters for spin-boson model checked\n");
    }

  if (SYSTM == "SpinFermion")
    {
      if (BDWID <= 0)
	{
	  fill(indent);
	  tee ("BDWID must be positive, please check\n");
	  qupit_abort();
	}

      if (LPOTE <= -BDWID/2 or LPOTE >= BDWID/2)
	{
	  fill(indent);
	  tee ("chemical potential of left lead is out of range, please check\n");
	  qupit_abort();
	}

      if (RPOTE <= -BDWID/2 or RPOTE >= BDWID/2)
	{
	  fill(indent);
	  tee ("chemical potential of right lead is out of range, please check\n");
	  qupit_abort();
	}

      if (LTEMP < 0)
	{
	  fill(indent);
	  tee ("LTEMP must be nonnegative, please check\n");
	  qupit_abort();
	}

      if (RTEMP < 0)
	{
	  fill(indent);
	  tee ("RTEMP must be nonnegative, please check\n");
	  qupit_abort();
	}

      fill(indent);
      tee ("parameters for spin-fermion model checked\n");
    }
}

void parameter_list ()
{
  uint32_t n;
  tee ("\nparameter list:\n");

  // control parameters
  fill(indent);  // RUNMD
  n = tee ("RUNMD = %s,", RUNMD.c_str());
  fill (tab1st-indent-n);
  tee("run %s mode\n", RUNMD.c_str());
  fill(indent);  // SYSTM
  n = tee ("SYSTM = %s,", SYSTM.c_str());
  fill (tab1st-indent-n);
  tee("run %s system\n", SYSTM.c_str());
  fill(indent);  // RDFUN
  n = tee ("RDFUN = %s,", RDFUN ? "true" : "false");
  fill (tab1st-indent-n);
  if (!RDFUN)
    tee ("do not ");
  tee ("read functional influential from file\n");
  fill(indent);  // WRFUN
  n = tee ("WRFUN = %s,", WRFUN ? "true" : "false");
  fill (tab1st-indent-n);
  if (!WRFUN)
    tee ("do not ");
  tee ("write functional influential to file\n");
  if (RDFUN or WRFUN)
    {
      fill(indent);  // FUNCL
      tee ("FUNFL = %s\n", abspath(FUNFL).c_str());
      fill (tab1st); tee ("file to store influential functional\n");
    }
  fill(indent);  // EXTFL
  tee ("EXTFL = %s,\n", abspath(EXTFL).c_str());
  fill(tab1st); tee ("file to store external field\n");
  fill(indent);  // SPNFL
  tee ("SPNFL = %s,\n", abspath(SPNFL).c_str());
  fill(tab1st); tee ("file to store spin dynamics\n");
  fill(indent);  // RDMFL
  tee ("RDMFL = %s,\n", abspath(RDMFL).c_str());
  fill(tab1st); tee ("file to store system density matrix dynamics\n");
  
  // common physical parameters
  fill(indent);  // TMITV
  n = tee ("TMITV = %.4f,", TMITV);
  fill(tab1st-indent-n);
  tee ("Trotter-Suzuki time interval, \\delta t\n", TMITV);
  fill(indent);  // NSTEP
  n = tee ("NSTEP = %d,", NSTEP);
  fill(tab1st-indent-n);
  tee("total run steps, N\n");
  fill(indent);  // TSTEP
  n = tee ("TSTEP = %d,", TSTEP);
  fill(tab1st-indent-n);
  tee("truncated steps, N_s\n", TSTEP);
  fill(indent);  // INRHO
  tee ("INRHO = %.4f %.4f %.4f %.4f %.4f %.4f %.4f %.4f,\n",
       INRHO[0], INRHO[1], INRHO[2], INRHO[3],
       INRHO[4], INRHO[5], INRHO[6], INRHO[7]);
  fill(tab1st); tee ("initial system density matrix shall be set as\n");
  fill(tab1st);
  tee ("[%+.4f%+.4fi, %+.4f%+.4fi]\n", INRHO[0], INRHO[1], INRHO[2], INRHO[3]);
  fill(tab1st);
  tee ("[%+.4f%+.4fi, %+.4f%+.4fi]\n", INRHO[4], INRHO[5], INRHO[6], INRHO[7]);
  fill(indent);  // THETA
  n = tee ("THETA = %.4f,", THETA);
  fill(tab1st-indent-n);
  tee ("coupling angle \\theta\n");
  fill(indent);  // VRPHI
  n = tee ("VRPHI = %.4f,", VRPHI);
  fill(tab1st-indent-n);
  tee ("coupling angle \\phi\n");

  // spin-boson parameters
  if (SYSTM == "SpinBoson")
    {
      fill(indent);  // CUTFQ
      n = tee ("CUTFQ = %.4f,", CUTFQ);
      fill(tab1st-indent-n);
      tee ("phonon cutoff frequency \\omega_c\n");
      fill(indent);  // ALPHA
      n = tee ("ALPHA = %.4f,", ALPHA);
      fill(tab1st-indent-n);
      tee ("system-bath coupling strength, \\alpha\n");
      fill(indent);  // MDNUM
      n = tee ("MDNUM = %d,", MDNUM);
      fill(tab1st-indent-n);
      tee ("number of phonon modes\n");
      fill(indent);  // OHMIS
      n = tee ("OHMIS = %.4f,", OHMIS);
      fill(tab1st-indent-n);
      tee ("ohmic exponential factor, s\n");
      fill(indent);  // BTEMP
      n = tee ("BTEMP = %.4f,", BTEMP);
      fill(tab1st-indent-n);
      tee ("phonon bath temperature\n");
    }
  
  // spin-fermion parameters
  if (SYSTM == "SpinFermion")
  {
    fill(indent);  // BDWID
    n = tee ("BDWID = %.4f,", BDWID);
    fill(tab1st-indent-n);
    tee ("band width of lead\n");
    fill(indent);  // LVNUM
    n = tee ("LVNUM = %d,", LVNUM);
    fill(tab1st-indent-n);
    tee ("number of energy levels\n");
    fill(indent);  // LAMBD
    n = tee ("LAMBD = %.4f,", LAMBD);
    fill(tab1st-indent-n);
    tee ("system-bath coupling strength, \\lambda\n");
    fill(indent);  // LPOTE
    n = tee ("LPOTE = %+.4f,", LPOTE);
    fill(tab1st-indent-n);
    tee ("chemical potential of left lead\n");
    fill(indent);  // RPOTE
    n = tee ("RPOTE = %+.4f,", RPOTE);
    fill(tab1st-indent-n);
    tee ("chemical potential of right lead\n");
    fill(indent);  // LTEMP
    n = tee ("LTEMP = %.4f,", LTEMP);
    fill(tab1st-indent-n);
    tee ("temperature of left lead\n");
    fill(indent);  // RTEMP
    n = tee ("RTEMP = %.4f,", RTEMP);
    fill(tab1st-indent-n);
    tee ("temperature of right lead\n");
  }
}

void read_extfl (field& ext)
{
  int32_t cols = 15;
  uint32_t n;

  tee ("\nreading external field:\n");
  fill(indent);
  tee ("reading from %s\n", abspath(EXTFL).c_str());

  int32_t flag = ext.read(abspath(EXTFL).c_str());
  if (flag == 1)
    {
      fill(indent);
      tee ("cannot open the file, please check\n");
      qupit_abort();
    }
  else if (flag == 2)
    {
      fill(indent);
      tee ("empty file, please check\n");
      qupit_abort();
    }
  else if (flag == 3)
    {
      fill(indent);
      tee ("time must be in ascending order, please check\n");
      qupit_abort();
    }
  
  // check range
  if (ext.tmin() > 0 or ext.tmax() < NSTEP*TMITV)
    {
      fill(indent);
      tee ("time range in file does not satisfy the running condition, please check\n");
      qupit_abort();
    }
  
  fill(indent);
  tee ("external field read:\n");
  fill(indent); n = tee ("#");
  fill(7); n = tee ("time");
  fill(cols-n); n = tee ("x");
  fill(cols-n); n = tee ("y");
  fill(cols-n); n = tee ("z\n");

  for (uint32_t i = 0; i <= NSTEP; ++i)
    {
      double t = i*TMITV;
      fill(indent); n = tee ("%12.4f", t);
      fill(cols-n); n = tee ("%12.4f", ext.x(t));
      fill(cols-n); n = tee ("%12.4f", ext.y(t));
      fill(cols-n); n = tee ("%12.4f\n", ext.z(t));
    }
}

void init_boson_bath ()
{
  tee ("\ninitializing phonon bath:\n");
  fill(indent);
}


#endif	// IO_HPP
