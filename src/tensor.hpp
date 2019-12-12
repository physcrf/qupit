#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <complex>
#include <fstream>
#include <omp.h>
#include <Eigen/Dense>
#include "bits.hpp"
#include "math.hpp"
using namespace std;
using namespace Eigen;

struct tensor
{
  VectorXcd _elements;
  uint32_t _length;

  tensor (uint32_t n);
  uint32_t size();	// the total size
  uint32_t length();	// the rank
  complex<double>& operator[] (uint32_t n);
  complex<double>& operator[] (bits& b);
  Matrix2cd reduce ();
  void write (const char* filename);
  void read (const char* filename);
};

tensor::tensor (uint32_t n)
{
  _length = n;
  _elements.resize (pow2(n));
}

uint32_t tensor::size()
{
  return _elements.size();
}

uint32_t tensor::length()
{
  return _length;
}

complex<double>& tensor::operator[] (uint32_t n)
{
  return _elements[n];
}

complex<double>& tensor::operator[] (bits& b)
{
  return _elements[b.value()];
}

Matrix2cd tensor::reduce ()
{
  Matrix2cd R = Matrix2cd::Zero();
  for (uint32_t i = 0; i < size(); ++i)
    {
      bits b(length(), i);
      R(b[b.size()-1], b[b.size()-2]) += _elements[i];
    }

  return R;
}

void convolute (tensor& C, tensor& A, tensor& B)
{
#pragma omp parallel for
  for (uint32_t i = 0; i < C.size(); ++i)
    {
      bits m (A.length(), i);
      bits n (B.length(), i);
      m <<= 2; n <<= 2;

      // 0 0
      C[i] = A[m]*B[n];
      // 0 1
      m.set(0); n.set(0);
      C[i] += A[m]*B[n];
      // 1 1
      m.set(1); n.set(1);
      C[i] += A[m]*B[n];
      // 1 0
      m.reset(0); n.reset(0);
      C[i] += A[m]*B[n];
    }
}
      
ostream& operator<< (ostream& out, tensor& A)
{
  out<<"length: "<<A.length()<<". size: "<<A.size()<<endl;
  for (uint32_t i = 0; i < A.size(); ++i)
    {
      bits b (A.length(), i);
      out<<i<<'\t'<<b<<'\t'<<A[i]<<endl;
    }
  return out;
}

void tensor::write (const char* filename)
{
  ofstream fout (filename, ios::binary);
  uint32_t m = length();
  uint32_t n = size();
  fout.write ((char*)&m, sizeof(uint32_t));
  fout.write ((char*)&n, sizeof(uint32_t));
  fout.write ((char*)_elements.data(), n*sizeof(complex<double>));
  fout.close ();
}

#endif	// TENSOR_HPP
