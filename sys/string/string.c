#include "string.h"

char
tolower (char s1)
{
  if (s1 >= 65 && s1 <= 90)
    s1 += 32;

  return s1;
}

int
strlen (const char *str)
{
  int i = 0;
  while (*str != 0)
    {
      i++;
      str += 1;
    }

  return i;
}

int
strnlen (const char *str, int max)
{
  int i = 0;
  for (int i = 0; i < max; i++)
    {
      if (str[i] == 0)
        break;
    }

  return i;
}
