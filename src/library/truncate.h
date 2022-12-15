#ifndef _truncate_h_
#define _truncate_h_

#include <stddef.h>
#include <string.h>

// Truncates [n] to [accuracy] decimals.
void truncate(char *n, size_t accuracy) {
  char *find = strstr(n, ".");
  if (find == NULL)
    return;

  size_t location = find - n;
  size_t cutoff = location + accuracy + 1;
  if (cutoff < strlen(n))
    n[cutoff] = 0;

  return;
}

#endif