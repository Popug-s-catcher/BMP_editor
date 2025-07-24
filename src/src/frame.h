#include "configs.h"
#include "AuxFunc.h"

void pattern_frame(Rgb **arr, unsigned int W, unsigned int H, struct Configs arg);


void pattern_1(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, int order, int x1, int y1, int x2, int y2, int i);


void pattern_2(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, int order, int x1, int y1, int x2, int y2, int i);


void border(Rgb **arr, unsigned int W, unsigned int H, struct Configs arg);
