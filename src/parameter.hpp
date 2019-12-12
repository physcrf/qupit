#ifndef PARAMETER_HPP
#define PARAMETER_HPP

// control parameters
string		RMODE	= "DYNAMICS";		// DYNAMICS, running the full dynamics, or FUNCTIONAL, compute the influential functional
int32_t 	RDFUN	= 0;			// read functional from file
int32_t		WRFUN	= 0;			// write functional to file
string		IFUNF	= "IFUN";		// file to store functional
string		EXTFL	= "EXT";		// file to store external field
string		SPNFL	= "SPIN";		// file to store spin dynamics
string		RDMFL	= "RDM";		// file to store rho dynamics

// common phyiscal parameters
double		TMINV 	= 0.25;			// delta t
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
double		LPOTL	= +0.5;			// chemical potential for left lead
double		RPOTL	= -0.5;			// chemical potential for right lead
double		LTEMP	= 0;			// temperature for left lead
double		RTEMP	= 0;			// temperature for right lead

#endif	// PARAMETER_HPP
