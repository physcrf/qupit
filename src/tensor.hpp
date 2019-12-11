#ifndef TENSOR_HPP
#define TENSOR_HPP 1

#include <Eigen/Dense>
#include <omp.h>
#include <fstream>
#include "bits.hpp"
using namespace std;

struct tensor
{
  VectorXcd _elements;
  uint32_t _length;

  tensor ();
  tensor (uint32_t n);
  uint32_t size();
  uint32_t length();
  
