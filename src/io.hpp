#ifndef IO_HPP
#define IO_HPP

#include <stdio.h>
#include <stdarg.h>

void tee (FILE* fp, const char* format, ...)
{
  va_list args;
  va_start (args, format);
  vprintf (format, args);
  va_end (args);

  va_start (args, format);
  vfprintf (fp, format, args);
  va_end (args);
}

// fill whitespaces
void fill (FILE* fp, uint32_t n)
{
  for (uint32_t i = 0; i < n; ++i)
    tee (fp, " ");
}
  
#endif	// IO_HPP
