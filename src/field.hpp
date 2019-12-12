#ifndef FIELD_HPP
#define FIELD_HPP

#include <math.h>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "math.hpp"
#include "string.hpp"
using namespace std;

struct field
{
  vector<double> _t;
  vector<double> _x;
  vector<double> _y;
  vector<double> _z;

  int32_t read (const char* filename);
  double tmin ();
  double tmax ();
  double x (double t);
  double y (double t);
  double z (double t);
  double abs (double t);
};

int32_t field::read (const char* filename)
{
  ifstream fin (filename);
  if (!fin.is_open())
    return 1;

  string line;
  while (getline(fin,line))
    {
      trim(line);
      if (blankp(line))
	continue;

      istringstream strin(line);
      double t, x, y, z;
      strin>>t>>x>>y>>z;
      _t.push_back(t);
      _x.push_back(x);
      _y.push_back(y);
      _z.push_back(z);
    }

  for (int i = 1; i < _t.size(); ++i)
    if (_t[i-1] >= _t[i])
      return 2;

  return 0;
}

double field::tmin()
{
  return _t.front();
}

double field::tmax()
{
  return _t.back();
}

double lininter (double t, vector<double>& _t, vector<double>& _x)
{
  uint32_t i;
  for (i = 0; i < _t.size()-1; ++i)
    if (_t[i] <= t and t <= _t[i+1]) break;

  return (t-_t[i])/(_t[i+1]-_t[i])*(_x[i+1]-_x[i])+_x[i];
}

double field::x (double t)
{
  return lininter (t, _t, _x);
}

double field::y (double t)
{
  return lininter (t, _t, _y);
}

double field::z (double t)
{
  return lininter (t, _t, _z);
}

double field::abs (double t)
{
  return sqrt (square(x(t)) + square(y(t)) + square(z(t)));
}

#endif	// FIELD_HPP
