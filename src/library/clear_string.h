#ifndef _clear_string_h
#define _clear_string_h

void clear_string(char *s) {
  while (*s != 0)
    *s++ = 0;
}

#endif