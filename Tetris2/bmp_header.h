/* Tells the compiler not to add padding for these structs. This may
   be useful when reading/writing to binary files.
   http://stackoverflow.com/questions/3318410/pragma-pack-effect
*/
#pragma pack(1)

struct bmp_fileheader
{
    unsigned char  fileMarker1; /* 'B' */
    unsigned char  fileMarker2; /* 'M' */
    unsigned int   bfSize; /* File's size */
    unsigned short unused1; //0
    unsigned short unused2; //0
    unsigned int   imageDataOffset; //54 Offset to the start of image data
};

struct bmp_infoheader
{
    unsigned int   biSize; /*40 Size of the info header - 40 bytes */
    signed int     width; /* Width of the image */
    signed int     height; /* Height of the image */
    unsigned short planes; //1 
    unsigned short bitPix; //24
    unsigned int   biCompression; //0
    unsigned int   biSizeImage; /* Size of the image data */
    int            biXPelsPerMeter; //0
    int            biYPelsPerMeter; //0
    unsigned int   biClrUsed; //0
    unsigned int   biClrImportant; //0
};

#pragma pack()
