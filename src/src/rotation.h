#include "configs.h"
#include "AuxFunc.h"

Rgb** rotate_90(Rgb **arr, Rgb **tmp, unsigned int left, unsigned int top, unsigned int right, unsigned int bottom);

Rgb** rotate_180(Rgb **arr, Rgb **tmp, unsigned int left, unsigned int top, unsigned int right, unsigned int bottom);

Rgb** rotate_270(Rgb **arr, Rgb **tmp, unsigned int left, unsigned int top, unsigned int right, unsigned int bottom);


void rotation(Rgb **arr, unsigned int W, unsigned int H, struct Configs arg);