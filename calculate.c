#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "sinetable.h"

#define NAME "sintable.bin"

int main(void) {
  // Load binary
  assert(SineTable_LoadBin(NAME) == true);

  for (int i = 0; i < UINT16_MAX; i++)
  {
    printf("%d ", SineTable_Sin(i));
  }
  puts("");

  return 0;
}
