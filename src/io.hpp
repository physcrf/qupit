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

#endif	// IO_HPP
