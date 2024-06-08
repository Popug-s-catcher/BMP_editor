#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>


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


struct Configs{
    int config_err_f;
    int help_f;
    int info_f;
    int rectangle_f;
    int border_f;
    int rotation_f;
    int fill_f;
    char in_name[40];
    char out_name[40];
    int start[2];
    int end[2];
    int thickness;
    char line[11];
    char fill[11];
    int width;
    int variant;
    int angle;
};


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


#pragma pack (push, 1)
typedef struct
{
	unsigned short signature;
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
	unsigned int headerSize;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bitsPerPixel;
	unsigned int compression;
	unsigned int imageSize;
	unsigned int xPixelsPerMeter;
	unsigned int yPixelsPerMeter;
	unsigned int colorsInColorTable;
	unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} Rgb;

#pragma pack(pop)


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


int main(int argc, char* argv[]){
    struct Configs arguments = {0, 0, 0, 0, 0, 0, 0, "", "out.bmp", 0, 0, 0, 0, 0, "", "", 1, 0, 0};
    char *short_opt = "hin:s:rbRS:e:t:l:f:w:v:a:";
    struct option long_opt[] ={
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 'i'},
        {"name", required_argument, NULL, 'n'},
        {"save", required_argument, NULL, 's'},
        {"rectangle", no_argument, NULL, 'r'},
        {"border", no_argument, NULL, 'b'},
        {"rotation", no_argument, NULL, 'R'},
        {"start", required_argument, NULL, 'S'},
        {"end", required_argument, NULL, 'e'},
        {"thickness", required_argument, NULL, 't'},
        {"line", required_argument, NULL, 'l'},
        {"fill", required_argument, NULL, 'f'},
        {"width", required_argument, NULL, 'w'},
        {"variant", required_argument, NULL, 'v'},
        {"angle", required_argument, NULL, 'a'},
        {NULL, 0, NULL, 0}
    };

    int mark, long_index;
    
    mark = getopt_long(argc, argv, short_opt, long_opt, &long_index);

    while(mark != -1)
    {
        opts_pr(&arguments, mark);
        mark = getopt_long(argc, argv, short_opt, long_opt, &long_index);
    }
    if (!strlen(arguments.in_name)) sscanf(argv[argc - 1], "%s", arguments.in_name);

    if (argc == 1){
        print_help();
        return 0;
    }

    if (arguments.help_f == 1)
    {
        print_help();
        return 0;
    }

    if (!strcmp(arguments.in_name, "")){
        puts("Input file is missing!\nPlease, checkout the example.");
        print_help();
        return 0;
    }

    if (strstr(arguments.in_name, ".bmp") == NULL){
        puts("Invalid file format!\nProgram supports only BMP files.");
        return 0;
    }

    if (arguments.config_err_f == 1){
        puts("Invalid entering of arguments!\nPlease check out the example");
        print_help();
        return 0;
    }



	FILE *f = fopen(arguments.in_name, "rb");  // opening the files
	FILE *ff = fopen(arguments.out_name, "wb");

	if ((f == NULL) || (ff == NULL)){
        puts("Error! File cannot be opened!");
        return 0;
    }
    
    BitmapFileHeader bmfh;
	BitmapInfoHeader bmif;

	fread(&bmfh,1,sizeof(BitmapFileHeader),f);
	fread(&bmif,1,sizeof(BitmapInfoHeader),f);

	unsigned int H = bmif.height;
	unsigned int W = bmif.width;

    int alignment = 4 - (W * 3) % 4;
    if (((W * 3) % 4) == 0) alignment = 0;

	Rgb **arr = malloc(H * sizeof(Rgb*));
	for(int i = 0; i < H; i++){
		arr[i] = malloc(W * sizeof(Rgb) + alignment);
		fread(arr[i], 1,W * sizeof(Rgb) + alignment, f);
    }


    if (arguments.info_f == 1)
    {
        printFileHeader(bmfh);
        printInfoHeader(bmif);
    }

    if (arguments.rectangle_f == 1)
    {
        rectanlge(arr, W, H, arguments);
    }

    if (arguments.border_f == 1)
    {
        border(arr, W, H, arguments);
    }

    if (arguments.rotation_f == 1)
    {
        rotation(arr, W, H, arguments);
    }

    fwrite(&bmfh, 1, sizeof(BitmapFileHeader),ff);  // recording and closing the files
	fwrite(&bmif, 1, sizeof(BitmapInfoHeader),ff);
	unsigned int w = W * sizeof(Rgb) + alignment;
	for(int i = 0; i < H; i++){
		fwrite(arr[i], 1, w, ff);
	}

    for (int i = 0; i < H; i++) free(arr[i]);
    free(arr);

	fclose(ff);
	fclose(f);

    return 0;
}
