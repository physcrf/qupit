#ifndef BITS_HPP
#define BITS_HPP

#include <bitset>
#include <cstdint>
#include <iostream>
using namespace std;

struct bits
{
  bitset<32> _bset;
  uint32_t _size;

  bits (uint32_t n, uint32_t val);
  bits (uint32_t n);
  uint32_t size();
  bool operator[] (uint32_t n);
  void set (uint32_t n);
  void reset (uint32_t n);
  void flip (uint32_t n);
  uint32_t value ();
};

bits::bits (uint32_t n, uint32_t val)
{
  _size = n;
  _bset = bitset<32>(val);
}

bits::bits (uint32_t n)
{
  bits(n,0);
}

uint32_t bits::size ()
{
  return _size;
}

bool bits::operator[] (uint32_t n)
{
  return _bset[n];
}

void bits::set (uint32_t n)
{
  _bset.set(n);
}

void bits::reset (uint32_t n)
{
  _bset.reset(n);
}

void bits::flip (uint32_t n)
{
  _bset.flip(n);
}

uint32_t bits::value ()
{
  return _bset.to_ulong();
}

bits& operator<<= (bits& b, uint32_t n)
{
  b._bset <<= n;
  for (uint32_t i = 0; i < n; ++i)
    b._bset.reset(i+b._size);

  return b;
}

bits& operator>>= (bits& b, uint32_t n)
{
  b._bset >>= n;

  return b;
}

ostream& operator<< (ostream& out, bits& b)
{
  for (int32_t i = b._size-1; i >= 0; --i)
    out<<b[i];

  return out;
}

#endif	// BITS_HPP

