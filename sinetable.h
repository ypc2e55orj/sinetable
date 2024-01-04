#ifndef SINETABLE_H
#define SINETABLE_H

#include <stdint.h>
#include <stdbool.h>

void SineTable_Generate();
int16_t SineTable_Sin(uint16_t index);
bool SineTable_WriteBin(const char *const path);
bool SineTable_LoadBin(const char *const path);

#endif // SINETABLE_H
