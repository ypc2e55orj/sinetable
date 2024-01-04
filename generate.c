#include <assert.h>
#include <stdbool.h>

#include "sinetable.h"

#define NAME "sintable.bin"

int main(void) {
  // Generate sine wave
  SineTable_Generate();

  // Write binary
  assert(SineTable_WriteBin(NAME) == true);

  return 0;
}
