#include "AuxFunc.h"

int check_coordinate(unsigned int W, unsigned int H, int left, int right, int top, int bottom)
{
    if (left < 0 || right > W || top > H || bottom < 0 || left > right || bottom > top)
    {
        printf("Wrong entering of arguments! Please, try again.\n");
        print_help();
        return 1;
    }
    return 0;
}


void pixel_fill(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, unsigned int i, unsigned int j)
{
    if (i < 0 || i >= H || j < 0 || j >= W) return;

    arr[i][j].r = Col.r;
    arr[i][j].g = Col.g;
    arr[i][j].b = Col.b;
}


void draw_a_line_x(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, int x0, int y0, int x1, int y1)
{
    int delta_x = abs(x1 - x0);
    int delta_y = abs(y1 - y0);
    int err = 0;
    int delta_err = (delta_y + 1);
    int y = y0;
    int dir_y = (y1 - y0);
    if (dir_y > 0) dir_y = 1;
    if (dir_y < 0) dir_y = -1;
    for (int x = x0; x < x1; x++){
        pixel_fill(arr, Col, W, H, y, x);
        err = err + delta_err;
        if (err >= (delta_x + 1)){
            y = y + dir_y;
            err = err - (delta_x + 1);
        }
    }
}


void draw_a_line_y(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, int x0, int y0, int x1, int y1)
{
    int delta_x = abs(x1 - x0);
    int delta_y = abs(y1 - y0);
    int err = 0;
    int delta_err = (delta_x + 1);
    int x = x0;
    int dir_x = (x1 - x0);
    if (dir_x > 0) dir_x = 1;
    if (dir_x < 0) dir_x = -1;
    for (int y = y0; y < y1; y++){
        pixel_fill(arr, Col, W, H, y, x);
        err = err + delta_err;
        if (err >= (delta_y + 1)){
            x = x + dir_x;
            err = err - (delta_y + 1);
        }
    }
}