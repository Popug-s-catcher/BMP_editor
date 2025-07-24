#include "rotation.h"

Rgb** rotate_90(Rgb **arr, Rgb **tmp, unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
{
    int y = top - bottom, x = right - left;
    
    for (int i = 0; i < y; i++){
        for (int j = 0; j < x; j++) tmp[j][y - i - 1] = arr[bottom + i][left + j]; 
    }

    return tmp;
}

Rgb** rotate_180(Rgb **arr, Rgb **tmp, unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
{
    int y = top - bottom, x = right - left;
    
    for (int i = 0; i < y; i++){
        for (int j = 0; j < x; j++) tmp[y - i - 1][x - j - 1] = arr[bottom + i][left + j];
    }

    return tmp;
}

Rgb** rotate_270(Rgb **arr, Rgb **tmp, unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
{
    int y = top - bottom, x = right - left;
    
    for (int i = 0; i < y; i++){
        for (int j = 0; j < x; j++) tmp[x - j - 1][i] = arr[bottom + i][left + j]; 
    }

    return tmp;
}


void rotation(Rgb **arr, unsigned int W, unsigned int H, struct Configs arg)
{
    unsigned int left = arg.start[0], top = arg.start[1];
    unsigned int right = arg.end[0], bottom = arg.end[1];
    unsigned int x, y, alignment, angle = (unsigned int)arg.angle;

    if (check_coordinate(W, H, left, right, top, bottom)) return;

    if (angle == 90 || angle == 270)
    {
        x = top - bottom;
        y = right - left;
    }

    else if (angle == 180)
    {
        x = right - left;
        y = top - bottom;
    }else{
        printf("Wrong entering of angle! Please try again.\n");
        printf("%d\n", angle);
        print_help();
        return;
    }

    alignment = 4 - (x * 3) % 4;
    if (((x * 3) % 4) == 0) alignment = 0;

    Rgb **tmp = malloc(y * sizeof(Rgb*));
    for (int i = 0; i < y; i++){
        tmp[i] = calloc(x * sizeof(Rgb) + alignment, sizeof(char));
    }


    if (angle == 90)
    {
        tmp = rotate_90(arr, tmp, left, top, right, bottom);
    }
    if (angle == 180)
    {   
        tmp = rotate_180(arr, tmp, left, top, right, bottom);
    }
    if(angle == 270)
    {   
        tmp = rotate_270(arr, tmp, left, top, right, bottom);
    }

    for (int i = bottom; i < (bottom + y) && i < H; i++){
        for (int j = left; j < (left + x) && j < W; j++) arr[i][j] = tmp[i - bottom][j - left];
    }

    for (int i = 0; i < y; i++) free(tmp[i]);
    free(tmp);
}