#include "rectangle.h"

void rectanlge(Rgb **arr, unsigned int W, unsigned int H, struct Configs arg)
{
    unsigned int left = arg.start[0], top = arg.start[1];
    unsigned int right = arg.end[0], bottom = arg.end[1];
    Rgb Col, Cof;
    Col = color_set(Col, arg.line);
    Cof = color_set(Cof, arg.fill);

    if (check_coordinate(W, H, left, right, top, bottom)) return;


    while ((top != (arg.start[1] - arg.thickness)) && (bottom != (arg.end[1] + arg.thickness)))  // painting horizontal
    {
        draw_a_line_x(arr, Col, W, H, left, top, right + 1, top);
        draw_a_line_x(arr, Col, W, H, left, bottom, right + 1, bottom);
        top--;
        bottom++;
    }
    while ((left != (arg.start[0] + arg.thickness)) && (right != (arg.end[0] - arg.thickness))) // painting vertical
    {
        draw_a_line_y(arr, Col, W, H, left, bottom, left, top + 1);
        draw_a_line_y(arr, Col, W, H, right, bottom, right, top + 1);
        left++;
        right--;
    }

    if (arg.fill_f)
    {
        for (int i = bottom; i < top + 1; i++) draw_a_line_x(arr, Cof, W, H, left, i, right + 1, i);    // rectangle fill
    }
}