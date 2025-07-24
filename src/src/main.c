#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include "rectangle.h"
#include "frame.h"
#include "rotation.h"



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
