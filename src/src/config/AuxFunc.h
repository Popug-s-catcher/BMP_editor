#include "configs.h"

#ifndef AuxFunc_h
#define AuxFunc_h

int check_coordinate(unsigned int W, unsigned int H, int left, int right, int top, int bottom);


void pixel_fill(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, unsigned int i, unsigned int j);


void draw_a_line_x(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, int x0, int y0, int x1, int y1);


void draw_a_line_y(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, int x0, int y0, int x1, int y1);

#endif