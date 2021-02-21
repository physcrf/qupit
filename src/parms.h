#ifndef PARMS_H
#define PARMS_H

#include <stdint.h>
#include <libconfig.h>

// control parameters
char*		MODE	= "dynamics";		// dynamics, running the full dynamics, or functional, compute the influential functional
int	 	RDIF	= 0;		// read functional from file
int		WRIF	= 0;		// write functional to file
char*		IFUNC	= "IFUNC";		// file to store functional
char*		IN	= "";		// file to store external field
char*		SPNFL	= "SPIN";		// file to store spin dynamics
char*		RDMFL	= "RHO";		// file to store rho dynamics

// common phyiscal parameters
double		TMITV 	= 0.25;			// delta t
uint32_t	NSTEP 	= 4000;			// run time steps, N
uint32_t	TSTEP 	= 3;			// truncated time steps, Ns
double		INRHO[8] = {1,0,0,0,0,0,0,0};	// initial rho

// spin-boson parameters
double		CUTFQ	= 1;			// cutoff frequency
double		ALPHA	= 1;			// system-bath coupling strength, \alpha
double		OHMIS	= 1;			// ohmic exponential, s
double		BTEMP	= 1;			// temperature

// configuration file reading

void parms_init ()
{
  config_t config;
  char* path = "INPUT";
  
  config_init (&config);
  config_read_file (&config, "INPUT");

  // control parameters
  //config_lookup_string (config, path, &RUNMD);
   config_lookup_int (&config, "RDFUN", &RDFUN); 
  /* config_lookup_int (config, path, &WRFUN); */
  /* config_lookup_string (config, path, &FUNFL); */
  /* config_lookup_string (config, path, &EXTFL); */
  /* config_lookup_string (config, path, &SPNFL); */
  /* config_lookup_string (config, path, &RDMFL); */

  /* // common physical parameters */
  /* config_lookup_float (config, path, &TMITV); */
  /* config_lookup_int (config, path, &NSTEP); */
}

void show_parms ()
{
  printf ("RUNMD = %s\n", RUNMD);
  printf ("RDFUN = %d\n", RDFUN);
  printf ("WRFUN = %d\n", WRFUN);
  printf ("FUNFL = %s\n", FUNFL);
  printf ("EXTFL = %s\n", EXTFL);
  printf ("SPNFL = %s\n", SPNFL);
  printf ("RDMFL = %s\n", RDMFL);
  printf ("TMITV = %f\n", TMITV);
  printf ("NSTEP = %d\n", NSTEP);
}
  
  

#endif	// PARMS_H
