#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "string.hpp"
#include "parameter.hpp"
#include "io.hpp"
using namespace std;

int main ()
{
  // open OUTPUT file
  OUT = fopen ("OUTPUT", "w");
  if (OUT == NULL)
    {
      fill(indent); tee ("cannot open output file.\n");
      qupit_abort();
    }

  // launch the program
  tee ("QUPIT alpha\n\n");

  // time counting
  time_t time1, time2, time3;
  time1 = time(NULL);
  tee ("excuted at %s", ctime(&time1));

  // number of threads for OPENMP
  tee ("running on total %d threads\n", omp_get_max_threads());

  // read parameters from INPUT
  read_input ();

  // checking parameters
  check_parameters ();
  
  // parameters list
  parameter_list ();

  // external field
  field ext;
  read_extfl(ext);
}
