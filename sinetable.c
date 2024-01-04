#include "sinetable.h"

#include <stdio.h>
#include <math.h>

int16_t SIN_DIV_256[256] = {0};
int16_t SIN_DIV_65536[256] = {0};
int16_t COS_DIV_256[256] = {0};
int16_t COS_DIV_65536[256] = {0};

void SineTable_Generate()
{
  double div_256 = 2.0 * M_PI / 256.0;
  double div_65536 = 2.0 * M_PI / 65536.0;
  for (int i = 0; i < 256; i++)
  {
    SIN_DIV_256[i] = sin(div_256 * i) * INT16_MAX;
    SIN_DIV_65536[i] = sin(div_65536 * i) * INT16_MAX;
    COS_DIV_256[i] = cos(div_256 * i) * INT16_MAX;
    COS_DIV_65536[i] = cos(div_65536 * i) * INT16_MAX;
  }
}

int16_t SineTable_Sin(uint16_t index)
{
  uint8_t div_256 = index >> 8;
  uint8_t div_65536 = index & 0xFF;
  return (SIN_DIV_256[div_256] * COS_DIV_65536[div_65536] + COS_DIV_256[div_256] * SIN_DIV_65536[div_65536]) / INT16_MAX;
}

bool SineTable_WriteBin(const char *const path)
{
  bool ret = false;
  FILE *file = NULL;
  size_t size = 0;

  // Write bin
  file = fopen(path, "wb");
  if (!file)
  {
    goto err;
  }

  // sin_div_256
  size = sizeof(SIN_DIV_256);
  if (fwrite(SIN_DIV_256, 1, size, file) != size)
  {
    goto err;
  }

  // sin_div_65536
  size = sizeof(SIN_DIV_65536);
  if (fwrite(SIN_DIV_65536, 1, size, file) != size)
  {
    goto err;
  }

  // cos_div_256
  size = sizeof(COS_DIV_256);
  if (fwrite(COS_DIV_256, 1, size, file) != size)
  {
    goto err;
  }

  // cos_div_65536
  size = sizeof(COS_DIV_65536);
  if (fwrite(COS_DIV_65536, 1, size, file) != size)
  {
    goto err;
  }

  ret = true;

err:
  fclose(file);

  return ret;
}

bool SineTable_LoadBin(const char *const path)
{
  bool ret = false;
  FILE *file = NULL;
  size_t size = 0;

  // Load bin
  file = fopen(path, "rb");
  if (!file)
  {
    goto err;
  }

  // sin_div_256
  size = sizeof(SIN_DIV_256);
  if (fread(SIN_DIV_256, 1, size, file) != size)
  {
    goto err;
  }

  // sin_div_65536
  size = sizeof(SIN_DIV_65536);
  if (fread(SIN_DIV_65536, 1, size, file) != size)
  {
    goto err;
  }

  // cos_div_256
  size = sizeof(COS_DIV_256);
  if (fread(COS_DIV_256, 1, size, file) != size)
  {
    goto err;
  }

  // cos_div_65536
  size = sizeof(COS_DIV_65536);
  if (fread(COS_DIV_65536, 1, size, file) != size)
  {
    goto err;
  }

  ret = true;

err:
  fclose(file);

  return ret;
}
