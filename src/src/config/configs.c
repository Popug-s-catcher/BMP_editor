#include "configs.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>

void print_help()
{
    printf("\n\tThe program supports BMP files V3 version.\n");
    printf("\n\tKeys:\n");
    printf("\n-h or --help - to call the help list of commands\n");
    printf("-i or --info - to print info about file\n");
    printf("-n or --name - name of file to open\n");
    printf("-s or --save - name of file to save\n");
    printf("\n\tMain functions:\n");
    printf("\n-r or --rectangle - then coordinates, thickness of line, color of line, filling or not entering the parameter to draw without it\n");
    printf("-b or --border - then the variant, color of line, color of filling, width of frame\n");
    printf("-R or --rotation - then coordinates, then the angle of rotation\n");
    printf("\n\tAuxiliary functions:\n");
    printf("\n-S or --start - entering the left and top coordinates\n");
    printf("-e or --end - entering the right and bottom coordinates\n");
    printf("-t or --thickness - the thicknenss of line\n");
    printf("-l or --line - the color of line - write the name of color\n");
    printf("-f or --fill - the color of filling of area - write the name of color\n");
    printf("-w or --width - width of border\n");
    printf("-v or --variant - the variant of border (1 or 2)\n");
    printf("-a or --angle - the angle of rotation (90 - 180 - 270)\n");
    printf("\n\tHelp info:\n");
    printf("\nSuggested colors are: black, white, grey, red, green, blue, brown, yellow, purple, aquamarine, olive, khaki, indigo.\n");
    printf("If the function requires to enter the coordinates, then correct will be the left(x) top(y) and the right(x) bottom(y) points.\n");
    printf("\n\tThe example of correct entering:\n");
    printf("\n./a.out --rectangle --start 200,400 --end 500,200 --thickness 7 --line green --fill brown image.bmp\n\n");
}


void printFileHeader(BitmapFileHeader header){
	printf("signature:\t%x (%hu)\n", header.signature, header.signature);
	printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
	printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
	printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
	printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}


void printInfoHeader(BitmapInfoHeader header){
	printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
	printf("width:     \t%x (%u)\n", header.width, header.width);
	printf("height:    \t%x (%u)\n", header.height, header.height);
	printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
	printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
	printf("compression:\t%x (%u)\n", header.compression, header.compression);
	printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
	printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
	printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
	printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
	printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}


void opts_pr(struct Configs *config, int mark)
{
    switch(mark)
    {
        case 'h':
            config -> help_f = 1;
            break;
        case 'i':
            config -> info_f = 1;
            break;
        case 'n':
            sscanf(optarg, "%s", config -> in_name);
            break;
        case 's':
            sscanf(optarg, "%s", config -> out_name);
            break;
        case 'r':
            config -> rectangle_f = 1;
            break;
        case 'b':
            config -> border_f = 1;
            break;
        case 'R':
            config -> rotation_f = 1;
            break;
        case 'S':
            sscanf(optarg, "%d,%d", &(config -> start[0]), &(config -> start[1]));
            break;
        case 'e':
            sscanf(optarg, "%d,%d", &(config -> end[0]), &(config -> end[1]));
            break;
        case 't':
            sscanf(optarg, "%d", &(config -> thickness));
            if (config -> thickness < 0) config -> config_err_f = 1;
            break;
        case 'l':
            sscanf(optarg, "%s", config -> line);
            break;
        case 'f':
            config -> fill_f = 1;
            sscanf(optarg, "%s", config -> fill);
            break;
        case 'w':
            sscanf(optarg, "%d", &(config -> width));
            if (config -> width < 0) config -> config_err_f = 1;
            break;
        case 'v':
            sscanf(optarg, "%d", &(config -> variant));
            if (config -> variant < 0) config -> config_err_f = 1;
            break;
        case 'a':
            sscanf(optarg, "%d", &(config -> angle));
            if (config -> angle < 0) config -> config_err_f = 1;
            break;
        case '?':
            printf("The commands or arguments are not correct\n");
            print_help();
            break;
    }
}

Rgb color_set(Rgb pix, char *color)
{
    if (!strcmp(color, "red")){
        pix.r = 139;
        pix.g = 0;
        pix.b = 0;
    }
    else if (!strcmp(color, "black")){
        pix.r = 0;
        pix.g = 0;
        pix.b = 0;
    }
    else if (!strcmp(color, "white")){
        pix.r = 255;
        pix.g = 250;
        pix.b = 250;
    }
    else if (!strcmp(color, "grey")){
        pix.r = 105;
        pix.g = 105;
        pix.b = 105;
    }
    else if (!strcmp(color, "green")){
        pix.r = 0;
        pix.g = 100;
        pix.b = 0;
    }
    else if (!strcmp(color, "blue")){
        pix.r = 0;
        pix.g = 0;
        pix.b = 150;
    }
    else if (!strcmp(color, "brown")){
        pix.r = 165;
        pix.g = 42;
        pix.b = 42;
    }
    else if (!strcmp(color, "yellow")){
        pix.r = 215;
        pix.g = 215;
        pix.b = 0;
    }
    else if (!strcmp(color, "purple")){
        pix.r = 128;
        pix.g = 0;
        pix.b = 128;
    }
    else if (!strcmp(color, "aquamarine")){
        pix.r = 127;
        pix.g = 255;
        pix.b = 212;
    }
    else if (!strcmp(color, "olive")){
        pix.r = 128;
        pix.g = 128;
        pix.b = 0;
    }
    else if (!strcmp(color, "khaki")){
        pix.r = 240;
        pix.g = 230;
        pix.b = 140;
    }
    else if (!strcmp(color, "indigo")){
        pix.r = 75;
        pix.g = 0;
        pix.b = 130;
    }
    return pix;
}