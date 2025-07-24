#ifndef configs_h  
#define configs_h


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


void print_help();


void opts_pr(struct Configs *config, int mark);


void printFileHeader(BitmapFileHeader header);


void printInfoHeader(BitmapInfoHeader header);


Rgb color_set(Rgb pix, char *color);

#endif