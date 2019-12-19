#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <stdint.h>
#include <vector>
#include <Eigen/Dense>
#include "field.hpp"
using namespace std;
using namespace Eigen;

struct spropagator  // system propagator
{
  Matrix2cd sx;
  Matrix2cd sy;
  Matrix2cd sz;
  vector<Matrix2cd> Kp; // K plus
  vector<Matrix2cd> Km; // k minus

  spropagator(uint32_t n);
};

spropagator::spropagator (uint32_t n)
{
  Kp.resize (n);
  Km.resize (n);
  sx << 0.0, 1.0, 1.0, 0.0;
  sy << 0.0, complex<double>(0,-1), complex<double>(0,1), 0.0;
  sz << 1.0, 0.0, 0.0, -1.0;
}

#endif // SYSTEM_HPP
