#include "mem.h"

void *
memset (void *ptr, int c, u32 size)
{
  char *c_ptr = (char *)ptr;

  for (u32 i = 0; i < size; i++)
    {
      c_ptr[i] = (char)c;
    }

  return ptr;
}
