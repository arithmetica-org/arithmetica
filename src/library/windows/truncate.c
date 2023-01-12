#include <stddef.h>
#include <string.h>

// Truncates [n] to [accuracy] decimals.
void
truncate (char *n, size_t accuracy)
{
  char *find = strchr (n, '.');
  if (find == NULL)
    return;

  size_t location = find - n;
  size_t cutoff = location + accuracy + 1;
  if (cutoff < strlen (n))
    n[cutoff] = 0;

  return;
}