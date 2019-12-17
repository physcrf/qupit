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

const uint32_t indent = 4;

int main ()
{
  // open OUTPUT file
  FILE* OUT = fopen ("OUTPUT", "w");
  if (OUT == NULL)
    {
      fill(OUT, indent);
      tee (OUT, "cannot open output file.\n");
      fill(OUT, indent);
      tee (OUT, "Program Aborted.\n");
      exit(1);
    }

  // launch the program
  tee (OUT, "QUPIT alpha\n\n");

  // time counting
  time_t time1, time2, time3;
  time1 = time(NULL);
  tee (OUT, "excuted at %s", ctime(&time1));

  // number of threads for OPENMP
  tee (OUT, "running on total\t%d threads\n\n", omp_get_max_threads());

  // read parameters from INPUT
  tee (OUT, "reading INPUT:\n");
  vector<pair<string, string>> params = read_parameter_file();
  if (params[0].first == "FAILED")
    {
      fill(OUT, indent);
      tee (OUT, "cannot open INPUT file, use default values\n");
    }
  if (params.empty())  // checking input types
    {
      fill(OUT, indent);
      tee (OUT, "empty INPUT file, use default values\n");
    }
  else
    {
      for (uint32_t i = 0; i < params.size(); ++i)
	if (params[i].first == "UNREGLINE")
	  {
	    fill(OUT, indent);
	    tee (OUT, "found unregonized line:\n");
	    fill(OUT, 2*indent);
	    tee (OUT, "%s\n", params[i].second.c_str());
	    fill(OUT, indent);
	    tee (OUT, "Program Aborted\n");
	    exit(1);
	  }
	else if (params[i].first == "UNREGKEY")
	  {
	    fill(OUT, indent);
	    tee (OUT, "found unregonized parameter: %s\n", params[i].second.c_str());
	    fill(OUT, indent);
	    tee (OUT, "Program Aborted\n");
	    exit(1);
	  }
	else if (params[i].first == "UNREVALUE")
	  {
	    fill(OUT, indent);
	    tee (OUT, "found unregonized value for %s\n", params[i].second.c_str());
	    fill(OUT, indent);
	    tee (OUT, "Program Aborted\n");
	    exit(1);
	  }
    }
}
