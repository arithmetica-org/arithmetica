#ifndef _clear_string_h
#define _clear_string_h

#include <stddef.h>

void
clear_string (char *s)
{
  while (*s != 0)
    *s++ = 0;
}

void
clear_string_s (char *s, size_t n)
{
  while (n--)
    *s++ = 0;
}

#endif