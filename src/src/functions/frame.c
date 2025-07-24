#include "frame.h"

void pattern_frame(Rgb **arr, unsigned int W, unsigned int H, struct Configs arg)
{
    int th, wd, width = arg.width;
    Rgb Col, Cof;
    Col = color_set(Col, arg.line);
    Cof = color_set(Cof, arg.fill);

    if (width > 30) {
        th = 10;
        wd = 30;
    }
    else if (width > 14) {
        th = width / 3;
        wd = width;
    }
    else if (width < 15) {
        th = 5;
        wd = 15;
    }
    for (int i = 0; i < th; i++){
        draw_a_line_x(arr, Col, W, H, 0, i, W, i);   // bottom line
        draw_a_line_x(arr, Col, W, H, 2 * wd, 2 * wd - i, W - 2 * wd, 2 * wd - i);  // middle botom line
        draw_a_line_x(arr, Col, W, H, 2 * wd, H - 2 * wd + i, W - 2 * wd, H - 2 * wd + i); // middle upper line
        draw_a_line_x(arr, Col, W, H, 0, H - 1 - i, W, H - 1 - i); // upper line
        draw_a_line_y(arr, Col, W, H, i, 0, i, H);   // left line
        draw_a_line_y(arr, Col, W, H, 2 * wd - i, 2 * wd, 2 * wd - i, H - 2 * wd);  // middle left line
        draw_a_line_y(arr, Col, W, H, W - 2 * wd + i, 2 * wd, W - 2 * wd + i, H - 2 * wd); // middle right line
        draw_a_line_y(arr, Col, W, H, W - 1 - i, 0, W - 1 - i, H);   // right line
    }
    for (int i = 0; i < 2 * wd + 1; i++){
        draw_a_line_x(arr, Col, W, H, 0, i, 2 * wd + 1, i);  // left bottom square
        draw_a_line_x(arr, Col, W, H, 0, H - 2 * wd - 1 + i, 2 * wd + 1, H - 2 * wd - 1 + i ); // left upper square
        draw_a_line_x(arr, Col, W, H, W - 2 * wd, H - 2 * wd - 1 + i, W, H - 2 * wd - 1 + i); // right upper square
        draw_a_line_x(arr, Col, W, H, W - 2 * wd, i, W, i); // right bottom square
    }
    th - 1;
    for (int i = th; i < (2 * wd - th) + 1; i++){
        draw_a_line_y(arr, Cof, W, H, i, 2 * wd + 1, i, H - 2 * wd - 1); // left field
        draw_a_line_y(arr, Cof, W, H, W - (2 * wd) + i, 2 * wd + 1, W - (2 * wd) + i, H - 2 * wd - 1); // right field
        draw_a_line_x(arr, Cof, W, H, 2 * wd + 1, H - (2 * wd) + i, W - (2 * wd), H - (2 * wd) + i); // upper field
        draw_a_line_x(arr, Cof, W, H, 2 * wd + 1, i, W - (2 * wd), i); //bottom field
    }
}


void pattern_1(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, int order, int x1, int y1, int x2, int y2, int i)   // drawing the first pattern
{
    int dif;
    
    if (order > 0)
    {
        draw_a_line_x(arr, Col, W, H, x1, y1, x2, y1);
        draw_a_line_y(arr, Col, W, H, x2, y1, x2, y2);
        
        if (i == 1)
        {
            dif = x2 - x1;
            x1 = x2;
            x2 = x2 + dif;

            draw_a_line_x(arr, Col, W, H, x1, y2, x2 + 1, y2);
            draw_a_line_y(arr, Col, W, H, x2, y1, x2, y2);

            dif = x2 - x1;
            x1 = x2;
            x2 = x2 + dif;
        }
        if (i == -1)
        {    
            dif = y2 - y1;
            y1 = y2;
            y2 = y2 + dif;

            draw_a_line_x(arr, Col, W, H, x1, y1, x2 + 1, y1);
            draw_a_line_y(arr, Col, W, H, x1, y1, x1, y2);

            dif = y2 - y1;
            y1 = y2;
            y2 = y2 + dif;
        }

        pattern_1(arr, Col, W, H, order - 1, x1, y1, x2, y2, i);
    }
}


void pattern_2(Rgb **arr, Rgb Col, unsigned int W, unsigned int H, int order, int x1, int y1, int x2, int y2, int i)  // drawing the second pattern
{
    int dif;

    if (order > 0)
    {
        if (i == 1)
        {
            draw_a_line_x(arr, Col, W, H, x1, y1, x2, y2);
            draw_a_line_x(arr, Col, W, H, x1, y2, x2, y1);
            dif = x2 - x1;
            x1 = x2;
            x2 = x2 + dif;
        }
        if(i == -1)
        {
            draw_a_line_x(arr, Col, W, H, x1, y1, x2, y2);
            draw_a_line_x(arr, Col, W, H, x1, y2, x2, y1);
            dif = y2 - y1;
            y1 = y2;
            y2 = y2 + dif;
        }
        pattern_2(arr, Col, W, H, order - 1, x1, y1, x2, y2, i);
    }
}


void border(Rgb **arr, unsigned int W, unsigned int H, struct Configs arg)
{
   pattern_frame(arr, W, H, arg);
   int order_x, order_y, x1 = arg.start[0], x2 = arg.end[0], y1 = arg.start[1], y2 = arg.end[1], width = arg.width;
   Rgb Col;
   Col = color_set(Col, arg.line);

   if (arg.variant == 1)
   {
        if (width > 30){
            order_x = (W - 60) / 60;
            order_y = (H - 30) / 60;
            x1 = 30;
            x2 = 60;
            y1 = 20;
            y2 = 40;
        }
        else if (width > 14)
        {
            order_x = (W - 2 * width) / (2 * width);
            order_y = (H - width) / (2 * width);
            x1 = width;
            x2 = 2 * width;
            y1 = 2 * x1 / 3;
            y2 = 2 * x2 / 3;
        }
        else if (width < 15)
        {
            order_x = (W - 30) / 30;
            order_y = (H - 15) / 30;
            x1 = 15;
            x2 = 30;
            y1 = 10;
            y2 = 20;
        }

        pattern_1(arr, Col,  W, H, order_x, x1, y1, x2, y2, 1);
        pattern_1(arr, Col,  W, H, order_x, x1, H - y2, x2, H - y1, 1);
        pattern_1(arr, Col,  W, H, order_y, y1, x1, y2, x2, -1);
        pattern_1(arr, Col,  W, H, order_y, W - y2, x1, W - y1, x2, -1);
   }
   if (arg.variant == 2)
   {
       if (width > 30)
       {
           order_x = (W - 80) / 40;
           order_y = (H - 80) / 40;
           x1 = 60;
           x2 = 100;
           y1 = 50;
           y2 = 10;
       }
       else if (width > 14)
       {
           order_x = (W - 2 * width) * 3 / width;
           order_y = (H - 2 * width) * 3 / width;
           y1 = 5 * width / 3;
           y2 = width / 3;
           x1 = 2 * width;
           x2 = x1 + (y1 - y2);
       }
       else if (width < 15)
       {
           order_x = (W - 30) / 15;
           order_y = (H - 30) / 15;
           x1 = 30;
           x2 = 50;
           y1 = 25;
           y2 = 5;
       }
       pattern_2(arr, Col,  W, H, order_x, x1, y1, x2, y2, 1);
       pattern_2(arr, Col,  W, H, order_x, x1, H - y2, x2, H - y1, 1);
       pattern_2(arr, Col,  W, H, order_y, y2, x1, y1 + 1, x2, -1);
       pattern_2(arr, Col,  W, H, order_y, W - y1, x1, W - y2 + 1, x2, -1);
   }
}
