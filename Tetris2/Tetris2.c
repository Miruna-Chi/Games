//Chiricu Miruna - Catalina
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"

void createBoard (long int **Board, int H, int Le) {
	struct bmp_fileheader O1;
	struct bmp_infoheader O2;

	int i, j, Osize;

	if (Le % 4 != 0) {
		Osize = (Le * 3 + 2) * (H + 40);
		
	}
	else Osize = (H + 40) * 3 * Le;

	O1.fileMarker1 = 'B';
	O1.fileMarker2 = 'M';
	O1.bfSize = Osize + 54;
	O1.unused1 = 0;
	O1.unused2 = 0;
	O1.imageDataOffset = 54;

	O2. biSize = 40;
	O2.width = Le;
	O2.height = H + 40;
	O2.planes = 1;
	O2.bitPix = 24;
	O2.biCompression = 0;
	O2.biSizeImage = Osize;
	O2.biXPelsPerMeter = 0;
	O2.biYPelsPerMeter = 0;
	O2.biClrUsed = 0;
	O2.biClrImportant = 0;

	FILE *outO = fopen("Board.bmp", "wb");

	fwrite(&O1.fileMarker1, 1, 1, outO);
	fwrite(&O1.fileMarker2, 1, 1, outO);
	fwrite(&O1.bfSize, 4, 1, outO);
	fwrite(&O1.unused1, 2, 1, outO);
	fwrite(&O1.unused2, 2, 1, outO);
	fwrite(&O1.imageDataOffset, 4, 1, outO);

	fwrite(&O2.biSize, 4, 1, outO);
	fwrite(&O2.width, 4, 1, outO);
	fwrite(&O2.height, 4, 1, outO);
	fwrite(&O2.planes, 2, 1, outO);
	fwrite(&O2.bitPix, 2, 1, outO);
	fwrite(&O2.biCompression, 4, 1, outO);
	fwrite(&O2.biSizeImage, 4, 1, outO);
	fwrite(&O2.biXPelsPerMeter, 4, 1, outO);
	fwrite(&O2.biYPelsPerMeter, 4, 1, outO);
	fwrite(&O2.biClrUsed, 4, 1, outO);
	fwrite(&O2.biClrImportant, 4, 1, outO);

	for (i = 0; i < H; i++) 
		for (j = 0; j < Le; j++) {
			Board[i][j] = 0;
			//equivalent of the color black
		}
	for (i = H; i < H + 40; i++)
		for (j = 0; j < Le; j++)
			Board[i][j] = 16777215;
		//equivalent of the color white
	for (i = 0; i < H + 40; i++) 
		for (j = 0; j < Le; j++) {
			fwrite(&Board[i][j], 3, 1, outO);
			if (j == Le - 1 && (Le % 4 != 0))
				
				fwrite(&O1.unused1, 2, 1, outO);

		}

	fclose (outO);

}

int readBoard (long int **Board, int *H, int *Le) {
	struct bmp_fileheader O1;
	struct bmp_infoheader O2;
	int i, j;
	


	FILE *in = fopen("cerinta4.bmp", "rb");
	if (in == NULL) {
        printf("ERROR: Can't open file\n");
        return 0;
    }

	fread(&O1.fileMarker1, 1, 1, in);
	fread(&O1.fileMarker2, 1, 1, in);
	fread(&O1.bfSize, 4, 1, in);
	fread(&O1.unused1, 2, 1, in);
	fread(&O1.unused2, 2, 1, in);
	fread(&O1.imageDataOffset, 4, 1, in);

	fread(&O2.biSize, 4, 1, in);
	fread(&O2.width, 4, 1, in);
	fread(&O2.height, 4, 1, in);
	fread(&O2.planes, 2, 1, in);
	fread(&O2.bitPix, 2, 1, in);
	fread(&O2.biCompression, 4, 1, in);
	fread(&O2.biSizeImage, 4, 1, in);
	fread(&O2.biXPelsPerMeter, 4, 1, in);
	fread(&O2.biYPelsPerMeter, 4, 1, in);
	fread(&O2.biClrUsed, 4, 1, in);
	fread(&O2.biClrImportant, 4, 1, in);

	*Le = O2.width;
	*H = O2.height - 40; 

	
	unsigned char a, b, c;
		
	for (i = 0; i < *H + 40; i++) 
		for (j = 0; j < *Le; j++) {
			
			a = fgetc(in);
			b = fgetc(in);
			c = fgetc(in);
			int value = (c << 16) + (b << 8) + a;
			Board[i][j] = value;
			if (j == *Le - 1 && (*Le % 4 != 0)) {
				a = fgetc(in);
				a = fgetc(in);
			}
				

		}

	fclose (in);
	return 1;

}

void createFullBoard (long int **Board, int H, int Le, char d) {
	struct bmp_fileheader O1;
	struct bmp_infoheader O2;

	int i, j, Osize;

	if (Le % 4 != 0) 
		Osize = (Le * 3 + 2) * (H + 40); 
	else Osize = (H + 40) * 3 * Le;

	O1.fileMarker1 = 'B';
	O1.fileMarker2 = 'M';
	O1.bfSize = Osize + 54;
	O1.unused1 = 0;
	O1.unused2 = 0;
	O1.imageDataOffset = 54;

	O2. biSize = 40;
	O2.width = Le;
	O2.height = H + 40;
	O2.planes = 1;
	O2.bitPix = 24;
	O2.biCompression = 0;
	O2.biSizeImage = Osize;
	O2.biXPelsPerMeter = 0;
	O2.biYPelsPerMeter = 0;
	O2.biClrUsed = 0;
	O2.biClrImportant = 0;

	FILE *outO;
	if (d == '3')
		outO = fopen("task3.bmp", "wb");
	else if (d == '4')
		outO = fopen("task4.bmp", "wb");
	if (outO == NULL) {
		printf ("ERROR: Can't open file.\n");
		return;
	}


	fwrite(&O1.fileMarker1, 1, 1, outO);
	fwrite(&O1.fileMarker2, 1, 1, outO);
	fwrite(&O1.bfSize, 4, 1, outO);
	fwrite(&O1.unused1, 2, 1, outO);
	fwrite(&O1.unused2, 2, 1, outO);
	fwrite(&O1.imageDataOffset, 4, 1, outO);

	fwrite(&O2.biSize, 4, 1, outO);
	fwrite(&O2.width, 4, 1, outO);
	fwrite(&O2.height, 4, 1, outO);
	fwrite(&O2.planes, 2, 1, outO);
	fwrite(&O2.bitPix, 2, 1, outO);
	fwrite(&O2.biCompression, 4, 1, outO);
	fwrite(&O2.biSizeImage, 4, 1, outO);
	fwrite(&O2.biXPelsPerMeter, 4, 1, outO);
	fwrite(&O2.biYPelsPerMeter, 4, 1, outO);
	fwrite(&O2.biClrUsed, 4, 1, outO);
	fwrite(&O2.biClrImportant, 4, 1, outO);

	for (i = 0; i < H + 40; i++) 
		for (j = 0; j < Le; j++) {
			fwrite(&Board[i][j], 3, 1, outO);
			if (j == Le - 1 && (Le % 4 != 0))
				
				fwrite(&O1.unused1, 2, 1, outO);

		}

	fclose (outO);

}

void createPiece_O (long int **O, int Ow, int Oh, int Osize) {
	struct bmp_fileheader O1;
	struct bmp_infoheader O2;

	int i, j;

	O1.fileMarker1 = 'B';
	O1.fileMarker2 = 'M';
	O1.bfSize = Osize + 54;
	O1.unused1 = 0;
	O1.unused2 = 0;
	O1.imageDataOffset = 54;

	O2. biSize = 40;
	O2.width = Ow;
	O2.height = Oh;
	O2.planes = 1;
	O2.bitPix = 24;
	O2.biCompression = 0;
	O2.biSizeImage = Osize;
	O2.biXPelsPerMeter = 0;
	O2.biYPelsPerMeter = 0;
	O2.biClrUsed = 0;
	O2.biClrImportant = 0;

	FILE *outO = fopen("piesa_O.bmp", "wb");

	fwrite(&O1.fileMarker1, 1, 1, outO);
	fwrite(&O1.fileMarker2, 1, 1, outO);
	fwrite(&O1.bfSize, 4, 1, outO);
	fwrite(&O1.unused1, 2, 1, outO);
	fwrite(&O1.unused2, 2, 1, outO);
	fwrite(&O1.imageDataOffset, 4, 1, outO);

	fwrite(&O2.biSize, 4, 1, outO);
	fwrite(&O2.width, 4, 1, outO);
	fwrite(&O2.height, 4, 1, outO);
	fwrite(&O2.planes, 2, 1, outO);
	fwrite(&O2.bitPix, 2, 1, outO);
	fwrite(&O2.biCompression, 4, 1, outO);
	fwrite(&O2.biSizeImage, 4, 1, outO);
	fwrite(&O2.biXPelsPerMeter, 4, 1, outO);
	fwrite(&O2.biYPelsPerMeter, 4, 1, outO);
	fwrite(&O2.biClrUsed, 4, 1, outO);
	fwrite(&O2.biClrImportant, 4, 1, outO);

/* white = (255, 255, 255), which means FF FF FF in hex, 
but FF FF FF as an integer is 16777215.*/ 
	for (i = 0; i < Oh; i++) 
		for (j = 0; j < Ow; j++) {
			O[i][j] = 16777215;
		}
	for (i = 10; i < Oh - 10; i++)
		for (j = 10; j < Ow - 10; j++)
			O[i][j] = 16776960;
		//yellow (255, 255, 0), FF FF 00
	for (i = 0; i < Oh; i++) 
		for (j = 0; j < Ow; j++) {
			fwrite(&O[i][j], 3, 1, outO);
		}

	fclose (outO);
}

void pieceRotations_O (long int **O, int Ow, int Oh, int Osize) {
	struct bmp_fileheader O1;
	struct bmp_infoheader O2;

	int i, j;

	O1.fileMarker1 = 'B';
	O1.fileMarker2 = 'M';
	O1.bfSize = Osize + 54;
	O1.unused1 = 0;
	O1.unused2 = 0;
	O1.imageDataOffset = 54;

	O2. biSize = 40;
	O2.width = Oh; 
	O2.height = Ow; 
	O2.planes = 1;
	O2.bitPix = 24;
	O2.biCompression = 0;
	O2.biSizeImage = Osize;
	O2.biXPelsPerMeter = 0;
	O2.biYPelsPerMeter = 0;
	O2.biClrUsed = 0;
	O2.biClrImportant = 0;

	FILE *out1 = fopen("piesa_O_90.bmp", "wb");

	fwrite(&O1.fileMarker1, 1, 1, out1);
	fwrite(&O1.fileMarker2, 1, 1, out1);
	fwrite(&O1.bfSize, 4, 1, out1);
	fwrite(&O1.unused1, 2, 1, out1);
	fwrite(&O1.unused2, 2, 1, out1);
	fwrite(&O1.imageDataOffset, 4, 1, out1);

	fwrite(&O2.biSize, 4, 1, out1);
	fwrite(&O2.width, 4, 1, out1);
	fwrite(&O2.height, 4, 1, out1);
	fwrite(&O2.planes, 2, 1, out1);
	fwrite(&O2.bitPix, 2, 1, out1);
	fwrite(&O2.biCompression, 4, 1, out1);
	fwrite(&O2.biSizeImage, 4, 1, out1);
	fwrite(&O2.biXPelsPerMeter, 4, 1, out1);
	fwrite(&O2.biYPelsPerMeter, 4, 1, out1);
	fwrite(&O2.biClrUsed, 4, 1, out1);
	fwrite(&O2.biClrImportant, 4, 1, out1);

	 
	for (i = 0; i < Oh; i++) 
		for (j = 0; j < Ow; j++) {
			fwrite(&O[i][j], 3, 1, out1);
		}

	fclose (out1);

	FILE *out2 = fopen("piesa_O_180.bmp", "wb");

	fwrite(&O1.fileMarker1, 1, 1, out2);
	fwrite(&O1.fileMarker2, 1, 1, out2);
	fwrite(&O1.bfSize, 4, 1, out2);
	fwrite(&O1.unused1, 2, 1, out2);
	fwrite(&O1.unused2, 2, 1, out2);
	fwrite(&O1.imageDataOffset, 4, 1, out2);

	fwrite(&O2.biSize, 4, 1, out2);
	fwrite(&O2.width, 4, 1, out2);
	fwrite(&O2.height, 4, 1, out2);
	fwrite(&O2.planes, 2, 1, out2);
	fwrite(&O2.bitPix, 2, 1, out2);
	fwrite(&O2.biCompression, 4, 1, out2);
	fwrite(&O2.biSizeImage, 4, 1, out2);
	fwrite(&O2.biXPelsPerMeter, 4, 1, out2);
	fwrite(&O2.biYPelsPerMeter, 4, 1, out2);
	fwrite(&O2.biClrUsed, 4, 1, out2);
	fwrite(&O2.biClrImportant, 4, 1, out2);

	 
	for (i = 0; i < Oh; i++) 
		for (j = 0; j < Ow; j++) {
			fwrite(&O[i][j], 3, 1, out2);
		}

	fclose (out2);

	FILE *out3 = fopen("piesa_O_270.bmp", "wb");

	fwrite(&O1.fileMarker1, 1, 1, out3);
	fwrite(&O1.fileMarker2, 1, 1, out3);
	fwrite(&O1.bfSize, 4, 1, out3);
	fwrite(&O1.unused1, 2, 1, out3);
	fwrite(&O1.unused2, 2, 1, out3);
	fwrite(&O1.imageDataOffset, 4, 1, out3);

	fwrite(&O2.biSize, 4, 1, out3);
	fwrite(&O2.width, 4, 1, out3);
	fwrite(&O2.height, 4, 1, out3);
	fwrite(&O2.planes, 2, 1, out3);
	fwrite(&O2.bitPix, 2, 1, out3);
	fwrite(&O2.biCompression, 4, 1, out3);
	fwrite(&O2.biSizeImage, 4, 1, out3);
	fwrite(&O2.biXPelsPerMeter, 4, 1, out3);
	fwrite(&O2.biYPelsPerMeter, 4, 1, out3);
	fwrite(&O2.biClrUsed, 4, 1, out3);
	fwrite(&O2.biClrImportant, 4, 1, out3);

	 
	for (i = 0; i < Oh; i++) 
		for (j = 0; j < Ow; j++) {
			fwrite(&O[i][j], 3, 1, out3);
		}

	fclose (out3);
}

void createPiece_I (long int **I, int Iw, int Ih, int Isize) {
	struct bmp_fileheader I1;
	struct bmp_infoheader I2;

	int i, j;

	I1.fileMarker1 = 'B';
	I1.fileMarker2 = 'M';
	I1.bfSize = Isize + 54;
	I1.unused1 = 0;
	I1.unused2 = 0;
	I1.imageDataOffset = 54;

	I2. biSize = 40;
	I2.width = Iw;
	I2.height = Ih;
	I2.planes = 1;
	I2.bitPix = 24;
	I2.biCompression = 0;
	I2.biSizeImage = Isize;
	I2.biXPelsPerMeter = 0;
	I2.biYPelsPerMeter = 0;
	I2.biClrUsed = 0;
	I2.biClrImportant = 0;

	FILE *outI = fopen("piesa_I.bmp", "wb");

	fwrite(&I1.fileMarker1, 1, 1, outI);
	fwrite(&I1.fileMarker2, 1, 1, outI);
	fwrite(&I1.bfSize, 4, 1, outI);
	fwrite(&I1.unused1, 2, 1, outI);
	fwrite(&I1.unused2, 2, 1, outI);
	fwrite(&I1.imageDataOffset, 4, 1, outI);

	fwrite(&I2.biSize, 4, 1, outI);
	fwrite(&I2.width, 4, 1, outI);
	fwrite(&I2.height, 4, 1, outI);
	fwrite(&I2.planes, 2, 1, outI);
	fwrite(&I2.bitPix, 2, 1, outI);
	fwrite(&I2.biCompression, 4, 1, outI);
	fwrite(&I2.biSizeImage, 4, 1, outI);
	fwrite(&I2.biXPelsPerMeter, 4, 1, outI);
	fwrite(&I2.biYPelsPerMeter, 4, 1, outI);
	fwrite(&I2.biClrUsed, 4, 1, outI);
	fwrite(&I2.biClrImportant, 4, 1, outI);

	for (i = 0; i < Ih; i++) 
		for (j = 0; j < Iw; j++) {
			I[i][j] = 16777215;
		}
	for (i = 10; i < Ih - 10; i++)
		for (j = 10; j < Iw - 10; j++)
			I[i][j] = 255;
		//blue(0, 0, 255), 00 00 FF
	for (i = 0; i < Ih; i++) 
		for (j = 0; j < Iw; j++) {
			fwrite(&I[i][j], 3, 1, outI);
			if (j == Iw - 1)
				fwrite(&I1.unused1, 2, 1, outI);
				//add padding because Iw is not a multiple of 4
		}

	fclose (outI);
}

void pieceRotations_I (long int **I, int Iw, int Ih, int Isize) {
	struct bmp_fileheader I1;
	struct bmp_infoheader I2;

	int i, j;
	//180 degree rotation
	I1.fileMarker1 = 'B';
	I1.fileMarker2 = 'M';
	I1.bfSize = Isize + 54;
	I1.unused1 = 0;
	I1.unused2 = 0;
	I1.imageDataOffset = 54;

	I2. biSize = 40;
	I2.width = Iw;
	I2.height = Ih;
	I2.planes = 1;
	I2.bitPix = 24;
	I2.biCompression = 0;
	I2.biSizeImage = Isize;
	I2.biXPelsPerMeter = 0;
	I2.biYPelsPerMeter = 0;
	I2.biClrUsed = 0;
	I2.biClrImportant = 0;

	FILE *outI = fopen("piesa_I_180.bmp", "wb");

	fwrite(&I1.fileMarker1, 1, 1, outI);
	fwrite(&I1.fileMarker2, 1, 1, outI);
	fwrite(&I1.bfSize, 4, 1, outI);
	fwrite(&I1.unused1, 2, 1, outI);
	fwrite(&I1.unused2, 2, 1, outI);
	fwrite(&I1.imageDataOffset, 4, 1, outI);

	fwrite(&I2.biSize, 4, 1, outI);
	fwrite(&I2.width, 4, 1, outI);
	fwrite(&I2.height, 4, 1, outI);
	fwrite(&I2.planes, 2, 1, outI);
	fwrite(&I2.bitPix, 2, 1, outI);
	fwrite(&I2.biCompression, 4, 1, outI);
	fwrite(&I2.biSizeImage, 4, 1, outI);
	fwrite(&I2.biXPelsPerMeter, 4, 1, outI);
	fwrite(&I2.biYPelsPerMeter, 4, 1, outI);
	fwrite(&I2.biClrUsed, 4, 1, outI);
	fwrite(&I2.biClrImportant, 4, 1, outI);
	 
	for (i = 0; i < Ih; i++) 
		for (j = 0; j < Iw; j++) {
			fwrite(&I[i][j], 3, 1, outI);
			if (j == Iw - 1)
				fwrite(&I1.unused1, 2, 1, outI);

		}

	fclose (outI);

	// 90 degree rotation
	Isize = Iw * Ih * 3;
	I1.bfSize = Isize + 54;
	I2.biSizeImage = Isize;
	I2.width = Ih;
	I2.height = Iw;

	FILE *out1 = fopen("piesa_I_90.bmp", "wb");

	fwrite(&I1.fileMarker1, 1, 1, out1);
	fwrite(&I1.fileMarker2, 1, 1, out1);
	fwrite(&I1.bfSize, 4, 1, out1);
	fwrite(&I1.unused1, 2, 1, out1);
	fwrite(&I1.unused2, 2, 1, out1);
	fwrite(&I1.imageDataOffset, 4, 1, out1);

	fwrite(&I2.biSize, 4, 1, out1);
	fwrite(&I2.width, 4, 1, out1);
	fwrite(&I2.height, 4, 1, out1);
	fwrite(&I2.planes, 2, 1, out1);
	fwrite(&I2.bitPix, 2, 1, out1);
	fwrite(&I2.biCompression, 4, 1, out1);
	fwrite(&I2.biSizeImage, 4, 1, out1);
	fwrite(&I2.biXPelsPerMeter, 4, 1, out1);
	fwrite(&I2.biYPelsPerMeter, 4, 1, out1);
	fwrite(&I2.biClrUsed, 4, 1, out1);
	fwrite(&I2.biClrImportant, 4, 1, out1);
	 
	for (j = 0; j < Iw; j++) 
		for (i = Ih - 1; i >= 0; i--) {
			fwrite(&I[i][j], 3, 1, out1);
		}

	fclose (out1);

	/* 270 degree rotation
	identical with the 90 degree rotation (symmetrical piece)*/

	FILE *out2 = fopen("piesa_I_270.bmp", "wb");

	fwrite(&I1.fileMarker1, 1, 1, out2);
	fwrite(&I1.fileMarker2, 1, 1, out2);
	fwrite(&I1.bfSize, 4, 1, out2);
	fwrite(&I1.unused1, 2, 1, out2);
	fwrite(&I1.unused2, 2, 1, out2);
	fwrite(&I1.imageDataOffset, 4, 1, out2);

	fwrite(&I2.biSize, 4, 1, out2);
	fwrite(&I2.width, 4, 1, out2);
	fwrite(&I2.height, 4, 1, out2);
	fwrite(&I2.planes, 2, 1, out2);
	fwrite(&I2.bitPix, 2, 1, out2);
	fwrite(&I2.biCompression, 4, 1, out2);
	fwrite(&I2.biSizeImage, 4, 1, out2);
	fwrite(&I2.biXPelsPerMeter, 4, 1, out2);
	fwrite(&I2.biYPelsPerMeter, 4, 1, out2);
	fwrite(&I2.biClrUsed, 4, 1, out2);
	fwrite(&I2.biClrImportant, 4, 1, out2);
	 
	for (j = 0; j < Iw; j++) 
		for (i = Ih - 1; i >= 0; i--) {
			fwrite(&I[i][j], 3, 1, out2);
		}

	fclose (out2);
}

void createPiece_S (long int **S, int Sw, int Sh, int Ssize) {
	struct bmp_fileheader S1;
	struct bmp_infoheader S2;

	int i, j;

	S1.fileMarker1 = 'B';
	S1.fileMarker2 = 'M';
	S1.bfSize = Ssize + 54;
	S1.unused1 = 0;
	S1.unused2 = 0;
	S1.imageDataOffset = 54;

	S2. biSize = 40;
	S2.width = Sw;
	S2.height = Sh;
	S2.planes = 1;
	S2.bitPix = 24;
	S2.biCompression = 0;
	S2.biSizeImage = Ssize;
	S2.biXPelsPerMeter = 0;
	S2.biYPelsPerMeter = 0;
	S2.biClrUsed = 0;
	S2.biClrImportant = 0;

	FILE *outS = fopen("piesa_S.bmp", "wb");

	fwrite(&S1.fileMarker1, 1, 1, outS);
	fwrite(&S1.fileMarker2, 1, 1, outS);
	fwrite(&S1.bfSize, 4, 1, outS);
	fwrite(&S1.unused1, 2, 1, outS);
	fwrite(&S1.unused2, 2, 1, outS);
	fwrite(&S1.imageDataOffset, 4, 1, outS);

	fwrite(&S2.biSize, 4, 1, outS);
	fwrite(&S2.width, 4, 1, outS);
	fwrite(&S2.height, 4, 1, outS);
	fwrite(&S2.planes, 2, 1, outS);
	fwrite(&S2.bitPix, 2, 1, outS);
	fwrite(&S2.biCompression, 4, 1, outS);
	fwrite(&S2.biSizeImage, 4, 1, outS);
	fwrite(&S2.biXPelsPerMeter, 4, 1, outS);
	fwrite(&S2.biYPelsPerMeter, 4, 1, outS);
	fwrite(&S2.biClrUsed, 4, 1, outS);
	fwrite(&S2.biClrImportant, 4, 1, outS);

	for (i = 0; i < Sh; i++) 
		for (j = 0; j < Sw; j++)
			S[i][j] = 16777215;

	for (i = 20; i < Sh - 10; i++)
		for (j = 20; j < Sw - 10; j++)
			S[i][j] = 16711680;
		//red (255, 0, 0), FF 00 00
	for (i = 10; i < Sh - 20; i++)
		for (j = 10; j < Sw - 20; j++)
			S[i][j] = 16711680;
	

	for (i = 0; i < Sh; i++) 
		for (j = 0; j < Sw; j++) {
			fwrite(&S[i][j], 3, 1, outS);
			if (j == Sw - 1)
				fwrite(&S1.unused1, 2, 1, outS);
				
		}

	fclose (outS);
}

void pieceRotations_S (long int **S, int Sw, int Sh, int Ssize) {
	struct bmp_fileheader S1;
	struct bmp_infoheader S2;

	int i, j;

	S1.fileMarker1 = 'B';
	S1.fileMarker2 = 'M';
	S1.bfSize = Ssize + 54;
	S1.unused1 = 0;
	S1.unused2 = 0;
	S1.imageDataOffset = 54;

	S2. biSize = 40;
	S2.width = Sw;
	S2.height = Sh;
	S2.planes = 1;
	S2.bitPix = 24;
	S2.biCompression = 0;
	S2.biSizeImage = Ssize;
	S2.biXPelsPerMeter = 0;
	S2.biYPelsPerMeter = 0;
	S2.biClrUsed = 0;
	S2.biClrImportant = 0;

	FILE *out1 = fopen("piesa_S_180.bmp", "wb");

	fwrite(&S1.fileMarker1, 1, 1, out1);
	fwrite(&S1.fileMarker2, 1, 1, out1);
	fwrite(&S1.bfSize, 4, 1, out1);
	fwrite(&S1.unused1, 2, 1, out1);
	fwrite(&S1.unused2, 2, 1, out1);
	fwrite(&S1.imageDataOffset, 4, 1, out1);

	fwrite(&S2.biSize, 4, 1, out1);
	fwrite(&S2.width, 4, 1, out1);
	fwrite(&S2.height, 4, 1, out1);
	fwrite(&S2.planes, 2, 1, out1);
	fwrite(&S2.bitPix, 2, 1, out1);
	fwrite(&S2.biCompression, 4, 1, out1);
	fwrite(&S2.biSizeImage, 4, 1, out1);
	fwrite(&S2.biXPelsPerMeter, 4, 1, out1);
	fwrite(&S2.biYPelsPerMeter, 4, 1, out1);
	fwrite(&S2.biClrUsed, 4, 1, out1);
	fwrite(&S2.biClrImportant, 4, 1, out1);
	 
	for (i = Sh - 1; i >= 0; i--) 
		for (j = Sw - 1; j >= 0; j--) {
			fwrite(&S[i][j], 3, 1, out1);
			if (j == 0)
				fwrite(&S1.unused1, 2, 1, out1);
		}

	fclose (out1);

	// symmetrical piece
	Ssize = Sw * Sh * 3;
	S1.bfSize = Ssize + 54;
	S2.biSizeImage = Ssize;
	S2.width = Sh;
	S2.height = Sw;


	FILE *out2 = fopen("piesa_S_90.bmp", "wb");

	fwrite(&S1.fileMarker1, 1, 1, out2);
	fwrite(&S1.fileMarker2, 1, 1, out2);
	fwrite(&S1.bfSize, 4, 1, out2);
	fwrite(&S1.unused1, 2, 1, out2);
	fwrite(&S1.unused2, 2, 1, out2);
	fwrite(&S1.imageDataOffset, 4, 1, out2);

	fwrite(&S2.biSize, 4, 1, out2);
	fwrite(&S2.width, 4, 1, out2);
	fwrite(&S2.height, 4, 1, out2);
	fwrite(&S2.planes, 2, 1, out2);
	fwrite(&S2.bitPix, 2, 1, out2);
	fwrite(&S2.biCompression, 4, 1, out2);
	fwrite(&S2.biSizeImage, 4, 1, out2);
	fwrite(&S2.biXPelsPerMeter, 4, 1, out2);
	fwrite(&S2.biYPelsPerMeter, 4, 1, out2);
	fwrite(&S2.biClrUsed, 4, 1, out2);
	fwrite(&S2.biClrImportant, 4, 1, out2);
	 
	for (j = 0; j < Sw; j++) 
		for (i = Sh - 1; i >= 0; i--) {
			fwrite(&S[i][j], 3, 1, out2);
			

		}

	fclose (out2);

	FILE *out3 = fopen("piesa_S_270.bmp", "wb");

	fwrite(&S1.fileMarker1, 1, 1, out3);
	fwrite(&S1.fileMarker2, 1, 1, out3);
	fwrite(&S1.bfSize, 4, 1, out3);
	fwrite(&S1.unused1, 2, 1, out3);
	fwrite(&S1.unused2, 2, 1, out3);
	fwrite(&S1.imageDataOffset, 4, 1, out3);

	fwrite(&S2.biSize, 4, 1, out3);
	fwrite(&S2.width, 4, 1, out3);
	fwrite(&S2.height, 4, 1, out3);
	fwrite(&S2.planes, 2, 1, out3);
	fwrite(&S2.bitPix, 2, 1, out3);
	fwrite(&S2.biCompression, 4, 1, out3);
	fwrite(&S2.biSizeImage, 4, 1, out3);
	fwrite(&S2.biXPelsPerMeter, 4, 1, out3);
	fwrite(&S2.biYPelsPerMeter, 4, 1, out3);
	fwrite(&S2.biClrUsed, 4, 1, out3);
	fwrite(&S2.biClrImportant, 4, 1, out3);
	 
	for (j = 0; j < Sw; j++) 
		for (i = Sh - 1; i >= 0; i--) {
			fwrite(&S[i][j], 3, 1, out3);
		}

	fclose (out3);
}

void createPiece_Z (long int **Z, int Zw, int Zh, int Zsize) {
	struct bmp_fileheader Z1;
	struct bmp_infoheader Z2;

	int i, j;

	Z1.fileMarker1 = 'B';
	Z1.fileMarker2 = 'M';
	Z1.bfSize = Zsize + 54;
	Z1.unused1 = 0;
	Z1.unused2 = 0;
	Z1.imageDataOffset = 54;

	Z2. biSize = 40;
	Z2.width = Zw;
	Z2.height = Zh;
	Z2.planes = 1;
	Z2.bitPix = 24;
	Z2.biCompression = 0;
	Z2.biSizeImage = Zsize;
	Z2.biXPelsPerMeter = 0;
	Z2.biYPelsPerMeter = 0;
	Z2.biClrUsed = 0;
	Z2.biClrImportant = 0;

	FILE *outZ = fopen("piesa_Z.bmp", "wb");

	fwrite(&Z1.fileMarker1, 1, 1, outZ);
	fwrite(&Z1.fileMarker2, 1, 1, outZ);
	fwrite(&Z1.bfSize, 4, 1, outZ);
	fwrite(&Z1.unused1, 2, 1, outZ);
	fwrite(&Z1.unused2, 2, 1, outZ);
	fwrite(&Z1.imageDataOffset, 4, 1, outZ);

	fwrite(&Z2.biSize, 4, 1, outZ);
	fwrite(&Z2.width, 4, 1, outZ);
	fwrite(&Z2.height, 4, 1, outZ);
	fwrite(&Z2.planes, 2, 1, outZ);
	fwrite(&Z2.bitPix, 2, 1, outZ);
	fwrite(&Z2.biCompression, 4, 1, outZ);
	fwrite(&Z2.biSizeImage, 4, 1, outZ);
	fwrite(&Z2.biXPelsPerMeter, 4, 1, outZ);
	fwrite(&Z2.biYPelsPerMeter, 4, 1, outZ);
	fwrite(&Z2.biClrUsed, 4, 1, outZ);
	fwrite(&Z2.biClrImportant, 4, 1, outZ);

	for (i = 0; i < Zh; i++) 
		for (j = 0; j < Zw; j++)
			Z[i][j] = 16777215;

	for (i = 10; i < Zh - 20; i++)
		for (j = 20; j < Zw - 10; j++)
			Z[i][j] = 65280;
		//green(0, 255, 0) = 00 FF 00
	for (i = 20; i < Zh - 10; i++)
		for (j = 10; j < Zw - 20; j++)
			Z[i][j] = 65280;
	

	for (i = 0; i < Zh; i++) 
		for (j = 0; j < Zw; j++) {
			fwrite(&Z[i][j], 3, 1, outZ);
			if (j == Zw - 1)
				fwrite(&Z1.unused1, 2, 1, outZ);
				
		}

	fclose (outZ);
}

void pieceRotations_Z (long int **Z, int Zw, int Zh, int Zsize) {
	struct bmp_fileheader Z1;
	struct bmp_infoheader Z2;

	int i, j;

	Z1.fileMarker1 = 'B';
	Z1.fileMarker2 = 'M';
	Z1.bfSize = Zsize + 54;
	Z1.unused1 = 0;
	Z1.unused2 = 0;
	Z1.imageDataOffset = 54;

	Z2. biSize = 40;
	Z2.width = Zw;
	Z2.height = Zh;
	Z2.planes = 1;
	Z2.bitPix = 24;
	Z2.biCompression = 0;
	Z2.biSizeImage = Zsize;
	Z2.biXPelsPerMeter = 0;
	Z2.biYPelsPerMeter = 0;
	Z2.biClrUsed = 0;
	Z2.biClrImportant = 0;

	FILE *out1 = fopen("piesa_Z_180.bmp", "wb");

	fwrite(&Z1.fileMarker1, 1, 1, out1);
	fwrite(&Z1.fileMarker2, 1, 1, out1);
	fwrite(&Z1.bfSize, 4, 1, out1);
	fwrite(&Z1.unused1, 2, 1, out1);
	fwrite(&Z1.unused2, 2, 1, out1);
	fwrite(&Z1.imageDataOffset, 4, 1, out1);

	fwrite(&Z2.biSize, 4, 1, out1);
	fwrite(&Z2.width, 4, 1, out1);
	fwrite(&Z2.height, 4, 1, out1);
	fwrite(&Z2.planes, 2, 1, out1);
	fwrite(&Z2.bitPix, 2, 1, out1);
	fwrite(&Z2.biCompression, 4, 1, out1);
	fwrite(&Z2.biSizeImage, 4, 1, out1);
	fwrite(&Z2.biXPelsPerMeter, 4, 1, out1);
	fwrite(&Z2.biYPelsPerMeter, 4, 1, out1);
	fwrite(&Z2.biClrUsed, 4, 1, out1);
	fwrite(&Z2.biClrImportant, 4, 1, out1);
	 
	for (i = Zh - 1; i >= 0; i--) 
		for (j = Zw - 1; j >= 0; j--) {
			fwrite(&Z[i][j], 3, 1, out1);
			if (j == 0)
				fwrite(&Z1.unused1, 2, 1, out1);
		}

	fclose (out1);

	//symmetrical piece
	Zsize = Zw * Zh * 3;
	Z1.bfSize = Zsize + 54;
	Z2.biSizeImage = Zsize;
	Z2.width = Zh;
	Z2.height = Zw;


	FILE *out2 = fopen("piesa_Z_90.bmp", "wb");

	fwrite(&Z1.fileMarker1, 1, 1, out2);
	fwrite(&Z1.fileMarker2, 1, 1, out2);
	fwrite(&Z1.bfSize, 4, 1, out2);
	fwrite(&Z1.unused1, 2, 1, out2);
	fwrite(&Z1.unused2, 2, 1, out2);
	fwrite(&Z1.imageDataOffset, 4, 1, out2);

	fwrite(&Z2.biSize, 4, 1, out2);
	fwrite(&Z2.width, 4, 1, out2);
	fwrite(&Z2.height, 4, 1, out2);
	fwrite(&Z2.planes, 2, 1, out2);
	fwrite(&Z2.bitPix, 2, 1, out2);
	fwrite(&Z2.biCompression, 4, 1, out2);
	fwrite(&Z2.biSizeImage, 4, 1, out2);
	fwrite(&Z2.biXPelsPerMeter, 4, 1, out2);
	fwrite(&Z2.biYPelsPerMeter, 4, 1, out2);
	fwrite(&Z2.biClrUsed, 4, 1, out2);
	fwrite(&Z2.biClrImportant, 4, 1, out2);
	 
	for (j = 0; j < Zw; j++) 
		for (i = Zh - 1; i >= 0; i--) {
			fwrite(&Z[i][j], 3, 1, out2);
			

		}

	fclose (out2);

	FILE *out3 = fopen("piesa_Z_270.bmp", "wb");

	fwrite(&Z1.fileMarker1, 1, 1, out3);
	fwrite(&Z1.fileMarker2, 1, 1, out3);
	fwrite(&Z1.bfSize, 4, 1, out3);
	fwrite(&Z1.unused1, 2, 1, out3);
	fwrite(&Z1.unused2, 2, 1, out3);
	fwrite(&Z1.imageDataOffset, 4, 1, out3);

	fwrite(&Z2.biSize, 4, 1, out3);
	fwrite(&Z2.width, 4, 1, out3);
	fwrite(&Z2.height, 4, 1, out3);
	fwrite(&Z2.planes, 2, 1, out3);
	fwrite(&Z2.bitPix, 2, 1, out3);
	fwrite(&Z2.biCompression, 4, 1, out3);
	fwrite(&Z2.biSizeImage, 4, 1, out3);
	fwrite(&Z2.biXPelsPerMeter, 4, 1, out3);
	fwrite(&Z2.biYPelsPerMeter, 4, 1, out3);
	fwrite(&Z2.biClrUsed, 4, 1, out3);
	fwrite(&Z2.biClrImportant, 4, 1, out3);
	 
	for (j = 0; j < Zw; j++) 
		for (i = Zh - 1; i >= 0; i--) {
			fwrite(&Z[i][j], 3, 1, out3);
		}

	fclose (out3);
}

void createPiece_L (long int **L, int Lw, int Lh, int Lsize) {
	struct bmp_fileheader L1;
	struct bmp_infoheader L2;

	int i, j;

	L1.fileMarker1 = 'B';
	L1.fileMarker2 = 'M';
	L1.bfSize = Lsize + 54;
	L1.unused1 = 0;
	L1.unused2 = 0;
	L1.imageDataOffset = 54;

	L2. biSize = 40;
	L2.width = Lw;
	L2.height = Lh;
	L2.planes = 1;
	L2.bitPix = 24;
	L2.biCompression = 0;
	L2.biSizeImage = Lsize;
	L2.biXPelsPerMeter = 0;
	L2.biYPelsPerMeter = 0;
	L2.biClrUsed = 0;
	L2.biClrImportant = 0;

	FILE *outL = fopen("piesa_L.bmp", "wb");

	fwrite(&L1.fileMarker1, 1, 1, outL);
	fwrite(&L1.fileMarker2, 1, 1, outL);
	fwrite(&L1.bfSize, 4, 1, outL);
	fwrite(&L1.unused1, 2, 1, outL);
	fwrite(&L1.unused2, 2, 1, outL);
	fwrite(&L1.imageDataOffset, 4, 1, outL);

	fwrite(&L2.biSize, 4, 1, outL);
	fwrite(&L2.width, 4, 1, outL);
	fwrite(&L2.height, 4, 1, outL);
	fwrite(&L2.planes, 2, 1, outL);
	fwrite(&L2.bitPix, 2, 1, outL);
	fwrite(&L2.biCompression, 4, 1, outL);
	fwrite(&L2.biSizeImage, 4, 1, outL);
	fwrite(&L2.biXPelsPerMeter, 4, 1, outL);
	fwrite(&L2.biYPelsPerMeter, 4, 1, outL);
	fwrite(&L2.biClrUsed, 4, 1, outL);
	fwrite(&L2.biClrImportant, 4, 1, outL);

	for (i = 0; i < Lh; i++) 
		for (j = 0; j < Lw; j++)
			L[i][j] = 16777215;

	for (i = 10; i < Lh - 30; i++)
		for (j = 10; j < Lw - 10; j++)
			L[i][j] = 16747520;
		//orange (255, 140, 0) = FF 8C 00
	for (i = 10; i < Lh - 10; i++)
		for (j = 10; j < Lw - 20; j++)
			L[i][j] = 16747520;
	

	for (i = 0; i < Lh; i++) 
		for (j = 0; j < Lw; j++) {
			fwrite(&L[i][j], 3, 1, outL);
			}

	fclose (outL);
}

void pieceRotations_L (long int **L, int Lw, int Lh, int Lsize) {
	
	struct bmp_fileheader L1;
	struct bmp_infoheader L2;

	int i, j;

	L1.fileMarker1 = 'B';
	L1.fileMarker2 = 'M';
	L1.bfSize = Lsize + 54;
	L1.unused1 = 0;
	L1.unused2 = 0;
	L1.imageDataOffset = 54;

	L2. biSize = 40;
	L2.width = Lw;
	L2.height = Lh;
	L2.planes = 1;
	L2.bitPix = 24;
	L2.biCompression = 0;
	L2.biSizeImage = Lsize;
	L2.biXPelsPerMeter = 0;
	L2.biYPelsPerMeter = 0;
	L2.biClrUsed = 0;
	L2.biClrImportant = 0;

	FILE *out1 = fopen("piesa_L_180.bmp", "wb");

	fwrite(&L1.fileMarker1, 1, 1, out1);
	fwrite(&L1.fileMarker2, 1, 1, out1);
	fwrite(&L1.bfSize, 4, 1, out1);
	fwrite(&L1.unused1, 2, 1, out1);
	fwrite(&L1.unused2, 2, 1, out1);
	fwrite(&L1.imageDataOffset, 4, 1, out1);

	fwrite(&L2.biSize, 4, 1, out1);
	fwrite(&L2.width, 4, 1, out1);
	fwrite(&L2.height, 4, 1, out1);
	fwrite(&L2.planes, 2, 1, out1);
	fwrite(&L2.bitPix, 2, 1, out1);
	fwrite(&L2.biCompression, 4, 1, out1);
	fwrite(&L2.biSizeImage, 4, 1, out1);
	fwrite(&L2.biXPelsPerMeter, 4, 1, out1);
	fwrite(&L2.biYPelsPerMeter, 4, 1, out1);
	fwrite(&L2.biClrUsed, 4, 1, out1);
	fwrite(&L2.biClrImportant, 4, 1, out1);
	 
	for (i = Lh - 1; i >= 0; i--) 
		for (j = Lw - 1; j >= 0; j--) {
			fwrite(&L[i][j], 3, 1, out1);
		}

	fclose (out1);

	//270 degree rotation

	Lsize = (Lh * 3 + 2) * Lw;
	L1.bfSize = Lsize + 54;
	L2.biSizeImage = Lsize;
	L2.width = Lh;
	L2.height = Lw;


	FILE *out2 = fopen("piesa_L_270.bmp", "wb");

	fwrite(&L1.fileMarker1, 1, 1, out2);
	fwrite(&L1.fileMarker2, 1, 1, out2);
	fwrite(&L1.bfSize, 4, 1, out2);
	fwrite(&L1.unused1, 2, 1, out2);
	fwrite(&L1.unused2, 2, 1, out2);
	fwrite(&L1.imageDataOffset, 4, 1, out2);

	fwrite(&L2.biSize, 4, 1, out2);
	fwrite(&L2.width, 4, 1, out2);
	fwrite(&L2.height, 4, 1, out2);
	fwrite(&L2.planes, 2, 1, out2);
	fwrite(&L2.bitPix, 2, 1, out2);
	fwrite(&L2.biCompression, 4, 1, out2);
	fwrite(&L2.biSizeImage, 4, 1, out2);
	fwrite(&L2.biXPelsPerMeter, 4, 1, out2);
	fwrite(&L2.biYPelsPerMeter, 4, 1, out2);
	fwrite(&L2.biClrUsed, 4, 1, out2);
	fwrite(&L2.biClrImportant, 4, 1, out2);
	 
	for (j = 0; j < Lw; j++) 
		for (i = Lh - 1; i >= 0; i--) {
			fwrite(&L[i][j], 3, 1, out2);
			if (i == 0)
				fwrite(&L1.unused1, 2, 1, out1);
			

		}

	fclose (out2);

	//90 degree rotation
	FILE *out3 = fopen("piesa_L_90.bmp", "wb");

	fwrite(&L1.fileMarker1, 1, 1, out3);
	fwrite(&L1.fileMarker2, 1, 1, out3);
	fwrite(&L1.bfSize, 4, 1, out3);
	fwrite(&L1.unused1, 2, 1, out3);
	fwrite(&L1.unused2, 2, 1, out3);
	fwrite(&L1.imageDataOffset, 4, 1, out3);

	fwrite(&L2.biSize, 4, 1, out3);
	fwrite(&L2.width, 4, 1, out3);
	fwrite(&L2.height, 4, 1, out3);
	fwrite(&L2.planes, 2, 1, out3);
	fwrite(&L2.bitPix, 2, 1, out3);
	fwrite(&L2.biCompression, 4, 1, out3);
	fwrite(&L2.biSizeImage, 4, 1, out3);
	fwrite(&L2.biXPelsPerMeter, 4, 1, out3);
	fwrite(&L2.biYPelsPerMeter, 4, 1, out3);
	fwrite(&L2.biClrUsed, 4, 1, out3);
	fwrite(&L2.biClrImportant, 4, 1, out3);
	 
	for (i = Lw - 1; i >= 0; i--) 
		for (j = 0; j <= Lh - 1; j++) {
			fwrite(&L[j][i], 3, 1, out3);
			if (j == Lh - 1)
				fwrite(&L1.unused1, 2, 1, out1);
		}

	fclose (out3);
}

void createPiece_J (long int **J, int Jw, int Jh, int Jsize) {
	struct bmp_fileheader J1;
	struct bmp_infoheader J2;

	int i, j;

	J1.fileMarker1 = 'B';
	J1.fileMarker2 = 'M';
	J1.bfSize = Jsize + 54;
	J1.unused1 = 0;
	J1.unused2 = 0;
	J1.imageDataOffset = 54;

	J2. biSize = 40;
	J2.width = Jw;
	J2.height = Jh;
	J2.planes = 1;
	J2.bitPix = 24;
	J2.biCompression = 0;
	J2.biSizeImage = Jsize;
	J2.biXPelsPerMeter = 0;
	J2.biYPelsPerMeter = 0;
	J2.biClrUsed = 0;
	J2.biClrImportant = 0;

	FILE *outJ = fopen("piesa_J.bmp", "wb");

	fwrite(&J1.fileMarker1, 1, 1, outJ);
	fwrite(&J1.fileMarker2, 1, 1, outJ);
	fwrite(&J1.bfSize, 4, 1, outJ);
	fwrite(&J1.unused1, 2, 1, outJ);
	fwrite(&J1.unused2, 2, 1, outJ);
	fwrite(&J1.imageDataOffset, 4, 1, outJ);

	fwrite(&J2.biSize, 4, 1, outJ);
	fwrite(&J2.width, 4, 1, outJ);
	fwrite(&J2.height, 4, 1, outJ);
	fwrite(&J2.planes, 2, 1, outJ);
	fwrite(&J2.bitPix, 2, 1, outJ);
	fwrite(&J2.biCompression, 4, 1, outJ);
	fwrite(&J2.biSizeImage, 4, 1, outJ);
	fwrite(&J2.biXPelsPerMeter, 4, 1, outJ);
	fwrite(&J2.biYPelsPerMeter, 4, 1, outJ);
	fwrite(&J2.biClrUsed, 4, 1, outJ);
	fwrite(&J2.biClrImportant, 4, 1, outJ);

	for (i = 0; i < Jh; i++) 
		for (j = 0; j < Jw; j++)
			J[i][j] = 16777215;

	for (i = 10; i < Jh - 30; i++)
		for (j = 10; j < Jw - 10; j++)
			J[i][j] = 16711935;
		//pink (255, 0, 255) = FF 00 FF
	for (i = 20; i < Jh - 10; i++)
		for (j = 20; j < Jw - 10; j++)
			J[i][j] = 16711935;
	

	for (i = 0; i < Jh; i++) 
		for (j = 0; j < Jw; j++) {
			fwrite(&J[i][j], 3, 1, outJ);
			}

	fclose (outJ);
}

void pieceRotations_J (long int **J, int Jw, int Jh, int Jsize) {
	
	struct bmp_fileheader J1;
	struct bmp_infoheader J2;

	int i, j;

	J1.fileMarker1 = 'B';
	J1.fileMarker2 = 'M';
	J1.bfSize = Jsize + 54;
	J1.unused1 = 0;
	J1.unused2 = 0;
	J1.imageDataOffset = 54;

	J2. biSize = 40;
	J2.width = Jw;
	J2.height = Jh;
	J2.planes = 1;
	J2.bitPix = 24;
	J2.biCompression = 0;
	J2.biSizeImage = Jsize;
	J2.biXPelsPerMeter = 0;
	J2.biYPelsPerMeter = 0;
	J2.biClrUsed = 0;
	J2.biClrImportant = 0;

	FILE *out1 = fopen("piesa_J_180.bmp", "wb");

	fwrite(&J1.fileMarker1, 1, 1, out1);
	fwrite(&J1.fileMarker2, 1, 1, out1);
	fwrite(&J1.bfSize, 4, 1, out1);
	fwrite(&J1.unused1, 2, 1, out1);
	fwrite(&J1.unused2, 2, 1, out1);
	fwrite(&J1.imageDataOffset, 4, 1, out1);

	fwrite(&J2.biSize, 4, 1, out1);
	fwrite(&J2.width, 4, 1, out1);
	fwrite(&J2.height, 4, 1, out1);
	fwrite(&J2.planes, 2, 1, out1);
	fwrite(&J2.bitPix, 2, 1, out1);
	fwrite(&J2.biCompression, 4, 1, out1);
	fwrite(&J2.biSizeImage, 4, 1, out1);
	fwrite(&J2.biXPelsPerMeter, 4, 1, out1);
	fwrite(&J2.biYPelsPerMeter, 4, 1, out1);
	fwrite(&J2.biClrUsed, 4, 1, out1);
	fwrite(&J2.biClrImportant, 4, 1, out1);

	for (i = Jh - 1; i >= 0; i--) 
		for (j = Jw - 1; j >= 0; j--) {
			fwrite(&J[i][j], 3, 1, out1);
		}

	fclose (out1);

	// 270 degree rotation

	Jsize = (Jh * 3 + 2) * Jw;
	J1.bfSize = Jsize + 54;
	J2.biSizeImage = Jsize;
	J2.width = Jh;
	J2.height = Jw;


	FILE *out2 = fopen("piesa_J_270.bmp", "wb");

	fwrite(&J1.fileMarker1, 1, 1, out2);
	fwrite(&J1.fileMarker2, 1, 1, out2);
	fwrite(&J1.bfSize, 4, 1, out2);
	fwrite(&J1.unused1, 2, 1, out2);
	fwrite(&J1.unused2, 2, 1, out2);
	fwrite(&J1.imageDataOffset, 4, 1, out2);

	fwrite(&J2.biSize, 4, 1, out2);
	fwrite(&J2.width, 4, 1, out2);
	fwrite(&J2.height, 4, 1, out2);
	fwrite(&J2.planes, 2, 1, out2);
	fwrite(&J2.bitPix, 2, 1, out2);
	fwrite(&J2.biCompression, 4, 1, out2);
	fwrite(&J2.biSizeImage, 4, 1, out2);
	fwrite(&J2.biXPelsPerMeter, 4, 1, out2);
	fwrite(&J2.biYPelsPerMeter, 4, 1, out2);
	fwrite(&J2.biClrUsed, 4, 1, out2);
	fwrite(&J2.biClrImportant, 4, 1, out2);
	
	for (j = 0; j < Jw; j++) 
		for (i = Jh - 1; i >= 0; i--) {
			fwrite(&J[i][j], 3, 1, out2);
			if (i == 0)
				fwrite(&J1.unused1, 2, 1, out1);
			

		}

	fclose (out2);

	//90 degree rotation
	FILE *out3 = fopen("piesa_J_90.bmp", "wb");

	fwrite(&J1.fileMarker1, 1, 1, out3);
	fwrite(&J1.fileMarker2, 1, 1, out3);
	fwrite(&J1.bfSize, 4, 1, out3);
	fwrite(&J1.unused1, 2, 1, out3);
	fwrite(&J1.unused2, 2, 1, out3);
	fwrite(&J1.imageDataOffset, 4, 1, out3);

	fwrite(&J2.biSize, 4, 1, out3);
	fwrite(&J2.width, 4, 1, out3);
	fwrite(&J2.height, 4, 1, out3);
	fwrite(&J2.planes, 2, 1, out3);
	fwrite(&J2.bitPix, 2, 1, out3);
	fwrite(&J2.biCompression, 4, 1, out3);
	fwrite(&J2.biSizeImage, 4, 1, out3);
	fwrite(&J2.biXPelsPerMeter, 4, 1, out3);
	fwrite(&J2.biYPelsPerMeter, 4, 1, out3);
	fwrite(&J2.biClrUsed, 4, 1, out3);
	fwrite(&J2.biClrImportant, 4, 1, out3);
	
	for (i = Jw - 1; i >= 0; i--) 
		for (j = 0; j < Jh; j++) {
			fwrite(&J[j][i], 3, 1, out3);
			if (j == Jh - 1)
				fwrite(&J1.unused1, 2, 1, out1);
		}

	fclose (out3);
}

void createPiece_T (long int **T, int Tw, int Th, int Tsize) {
	struct bmp_fileheader T1;
	struct bmp_infoheader T2;

	int i, j;

	T1.fileMarker1 = 'B';
	T1.fileMarker2 = 'M';
	T1.bfSize = Tsize + 54;
	T1.unused1 = 0;
	T1.unused2 = 0;
	T1.imageDataOffset = 54;

	T2. biSize = 40;
	T2.width = Tw;
	T2.height = Th;
	T2.planes = 1;
	T2.bitPix = 24;
	T2.biCompression = 0;
	T2.biSizeImage = Tsize;
	T2.biXPelsPerMeter = 0;
	T2.biYPelsPerMeter = 0;
	T2.biClrUsed = 0;
	T2.biClrImportant = 0;

	FILE *outT = fopen("piesa_T.bmp", "wb");

	fwrite(&T1.fileMarker1, 1, 1, outT);
	fwrite(&T1.fileMarker2, 1, 1, outT);
	fwrite(&T1.bfSize, 4, 1, outT);
	fwrite(&T1.unused1, 2, 1, outT);
	fwrite(&T1.unused2, 2, 1, outT);
	fwrite(&T1.imageDataOffset, 4, 1, outT);

	fwrite(&T2.biSize, 4, 1, outT);
	fwrite(&T2.width, 4, 1, outT);
	fwrite(&T2.height, 4, 1, outT);
	fwrite(&T2.planes, 2, 1, outT);
	fwrite(&T2.bitPix, 2, 1, outT);
	fwrite(&T2.biCompression, 4, 1, outT);
	fwrite(&T2.biSizeImage, 4, 1, outT);
	fwrite(&T2.biXPelsPerMeter, 4, 1, outT);
	fwrite(&T2.biYPelsPerMeter, 4, 1, outT);
	fwrite(&T2.biClrUsed, 4, 1, outT);
	fwrite(&T2.biClrImportant, 4, 1, outT);

	for (i = 0; i < Th; i++) 
		for (j = 0; j < Tw; j++)
			T[i][j] = 16777215;

	for (i = 20; i < Th - 10; i++)
		for (j = 10; j < Tw - 10; j++)
			T[i][j] = 8519935;
		//purple rgb(130, 0, 255) = 82 00 FF
	for (i = 10; i < Th - 20; i++)
		for (j = 20; j < Tw - 20; j++)
			T[i][j] = 8519935;
	

	for (i = 0; i < Th; i++) 
		for (j = 0; j < Tw; j++) {
			fwrite(&T[i][j], 3, 1, outT);
			if (j == Tw - 1)
				fwrite(&T1.unused1, 2, 1, outT);
			}

	fclose (outT);
}

void pieceRotations_T (long int **T, int Tw, int Th, int Tsize) {
	
	struct bmp_fileheader T1;
	struct bmp_infoheader T2;

	int i, j;

	T1.fileMarker1 = 'B';
	T1.fileMarker2 = 'M';
	T1.bfSize = Tsize + 54;
	T1.unused1 = 0;
	T1.unused2 = 0;
	T1.imageDataOffset = 54;

	T2. biSize = 40;
	T2.width = Tw;
	T2.height = Th;
	T2.planes = 1;
	T2.bitPix = 24;
	T2.biCompression = 0;
	T2.biSizeImage = Tsize;
	T2.biXPelsPerMeter = 0;
	T2.biYPelsPerMeter = 0;
	T2.biClrUsed = 0;
	T2.biClrImportant = 0;

	FILE *out1 = fopen("piesa_T_180.bmp", "wb");

	fwrite(&T1.fileMarker1, 1, 1, out1);
	fwrite(&T1.fileMarker2, 1, 1, out1);
	fwrite(&T1.bfSize, 4, 1, out1);
	fwrite(&T1.unused1, 2, 1, out1);
	fwrite(&T1.unused2, 2, 1, out1);
	fwrite(&T1.imageDataOffset, 4, 1, out1);

	fwrite(&T2.biSize, 4, 1, out1);
	fwrite(&T2.width, 4, 1, out1);
	fwrite(&T2.height, 4, 1, out1);
	fwrite(&T2.planes, 2, 1, out1);
	fwrite(&T2.bitPix, 2, 1, out1);
	fwrite(&T2.biCompression, 4, 1, out1);
	fwrite(&T2.biSizeImage, 4, 1, out1);
	fwrite(&T2.biXPelsPerMeter, 4, 1, out1);
	fwrite(&T2.biYPelsPerMeter, 4, 1, out1);
	fwrite(&T2.biClrUsed, 4, 1, out1);
	fwrite(&T2.biClrImportant, 4, 1, out1);
	 
	for (i = Th - 1; i >= 0; i--) 
		for (j = Tw - 1; j >= 0; j--) {
			fwrite(&T[i][j], 3, 1, out1);
			if (j == 0)
				fwrite(&T1.unused1, 2, 1, out1);

		}

	fclose (out1);

	// 270 degree rotation

	Tsize = Th * 3 * Tw;
	T1.bfSize = Tsize + 54;
	T2.biSizeImage = Tsize;
	T2.width = Th;
	T2.height = Tw;


	FILE *out2 = fopen("piesa_T_270.bmp", "wb");

	fwrite(&T1.fileMarker1, 1, 1, out2);
	fwrite(&T1.fileMarker2, 1, 1, out2);
	fwrite(&T1.bfSize, 4, 1, out2);
	fwrite(&T1.unused1, 2, 1, out2);
	fwrite(&T1.unused2, 2, 1, out2);
	fwrite(&T1.imageDataOffset, 4, 1, out2);

	fwrite(&T2.biSize, 4, 1, out2);
	fwrite(&T2.width, 4, 1, out2);
	fwrite(&T2.height, 4, 1, out2);
	fwrite(&T2.planes, 2, 1, out2);
	fwrite(&T2.bitPix, 2, 1, out2);
	fwrite(&T2.biCompression, 4, 1, out2);
	fwrite(&T2.biSizeImage, 4, 1, out2);
	fwrite(&T2.biXPelsPerMeter, 4, 1, out2);
	fwrite(&T2.biYPelsPerMeter, 4, 1, out2);
	fwrite(&T2.biClrUsed, 4, 1, out2);
	fwrite(&T2.biClrImportant, 4, 1, out2);
	 
	for (j = 0; j < Tw; j++) 
		for (i = Th - 1; i >= 0; i--) {
			fwrite(&T[i][j], 3, 1, out2);
		}

	fclose (out2);

	//90 degree rotation
	FILE *out3 = fopen("piesa_T_90.bmp", "wb");

	fwrite(&T1.fileMarker1, 1, 1, out3);
	fwrite(&T1.fileMarker2, 1, 1, out3);
	fwrite(&T1.bfSize, 4, 1, out3);
	fwrite(&T1.unused1, 2, 1, out3);
	fwrite(&T1.unused2, 2, 1, out3);
	fwrite(&T1.imageDataOffset, 4, 1, out3);

	fwrite(&T2.biSize, 4, 1, out3);
	fwrite(&T2.width, 4, 1, out3);
	fwrite(&T2.height, 4, 1, out3);
	fwrite(&T2.planes, 2, 1, out3);
	fwrite(&T2.bitPix, 2, 1, out3);
	fwrite(&T2.biCompression, 4, 1, out3);
	fwrite(&T2.biSizeImage, 4, 1, out3);
	fwrite(&T2.biXPelsPerMeter, 4, 1, out3);
	fwrite(&T2.biYPelsPerMeter, 4, 1, out3);
	fwrite(&T2.biClrUsed, 4, 1, out3);
	fwrite(&T2.biClrImportant, 4, 1, out3);

	for (i = Tw - 1; i >= 0; i--) 
		for (j = 0; j <= Th - 1; j++) {
			fwrite(&T[j][i], 3, 1, out3);
		}

	fclose (out3);
}

int finalBoard (long int **Board, int H, int Le, int rotation, int column,
	char pieceName, char d) {
	FILE *in;
	char s[30];
	if (pieceName == 'O') {
		if (rotation == 0) 
			strcpy (s, "piesa_O.bmp");
		else if (rotation == 90)
			strcpy (s, "piesa_O_90.bmp");
		else if (rotation == 180)
			strcpy (s, "piesa_O_180.bmp");
		else if (rotation == 270)
			strcpy (s, "piesa_O_270.bmp");
	}

	if (pieceName == 'I') {
		if (rotation == 0) 
			strcpy (s, "piesa_I.bmp");
		else if (rotation == 90)
			strcpy (s, "piesa_I_90.bmp");
		else if (rotation == 180)
			strcpy (s, "piesa_I_180.bmp");
		else if (rotation == 270)
			strcpy (s, "piesa_I_270.bmp");
	}
	if (pieceName == 'S') {
		if (rotation == 0) 
			strcpy (s, "piesa_S.bmp");
		else if (rotation == 90)
			strcpy (s, "piesa_S_90.bmp");
		else if (rotation == 180)
			strcpy (s, "piesa_S_180.bmp");
		else if (rotation == 270)
			strcpy (s, "piesa_S_270.bmp");
	}

	if (pieceName == 'Z') {
		if (rotation == 0) 
			strcpy (s, "piesa_Z.bmp");
		else if (rotation == 90)
			strcpy (s, "piesa_Z_90.bmp");
		else if (rotation == 180)
			strcpy (s, "piesa_Z_180.bmp");
		else if (rotation == 270)
			strcpy (s, "piesa_Z_270.bmp");
	}

	if (pieceName == 'L') {
		if (rotation == 0) 
			strcpy (s, "piesa_L.bmp");
		else if (rotation == 90)
			strcpy (s, "piesa_L_90.bmp");
		else if (rotation == 180)
			strcpy (s, "piesa_L_180.bmp");
		else if (rotation == 270)
			strcpy (s, "piesa_L_270.bmp");
	}

	if (pieceName == 'J') {
		if (rotation == 0) 
			strcpy (s, "piesa_J.bmp");
		else if (rotation == 90)
			strcpy (s, "piesa_J_90.bmp");
		else if (rotation == 180)
			strcpy (s, "piesa_J_180.bmp");
		else if (rotation == 270)
			strcpy (s, "piesa_J_270.bmp");
	}

	if (pieceName == 'T') {
		if (rotation == 0) 
			strcpy (s, "piesa_T.bmp");
		else if (rotation == 90)
			strcpy (s, "piesa_T_90.bmp");
		else if (rotation == 180)
			strcpy (s, "piesa_T_180.bmp");
		else if (rotation == 270)
			strcpy (s, "piesa_T_270.bmp");
	}

	in = fopen (s, "rb");
		if (in == NULL){
			printf("Error.\n");
			return 0;
		}

	/* we need the image's width and height (4 bytes), width starts at byte
	no. 19, immediately followed by height. It won't matter what we read from
	the file up to that point.
	*/
	
	unsigned char a, b, c; 
	int value = 0, Xh, Xw, i, j;
	long int **X; //piece

	for (i = 1; i <= 18; i++) {
		a = fgetc(in);
		
	}

	fread (&Xw, sizeof(int), 1, in);
	fread (&Xh, sizeof(int), 1, in);
	

	X = malloc(Xh * sizeof(long int));
 
	for (i = 0; i < Xh; i++)
		X[i] = malloc (Xw * sizeof(long int));
	for (i = 27; i <= 54; i++)
		a = fgetc(in);
	
	for (i = 0; i < Xh; i++) 
		for (j = 0; j < Xw; j++) {
			if (j == Xw - 1 && (Xw % 4) != 0) {
				a = fgetc(in);
				a = fgetc(in);
				// if we have padding => we read 2 bytes
					
			}
				
			a = fgetc(in);
			b = fgetc(in);
			c = fgetc(in);
			value = (c << 16) + (b << 8) + a;
			X[i][j] = value;
		}
	/*	each color is written on 3 bytes so we read byte by byte as chars
	and we use the int values of the chars to reconstruct the color 
	fiecare culoare este scrisa pe 3 octeti. */

	int row, minRow, col, Game_over = 0;
	minRow = H + 60 - Xh; //H + 40 - Xh + 10;
	row = minRow;
	col = column * 10;
	

	/* we start from the lower end of the board with the piece (on the 
	specifiec column and we check for collisions */
	i = 10;
	while (i < Xh) {
		for (i = 10; i < Xh - 10; i++) {
			for (j = 10; j < Xw - 10; j++) {

				if (X[i][j] != 16777215 && Board[row][col] != 0 &&
					Board[row][col] != 16777215) {
					minRow = minRow + 10;
					row = minRow;
					i = Xh;
					break;

				/* if the pixel of the piece is not white and the
				pixel of the board is not black, there is a collision,
				so the piece goes one row lower and the algorithm starts again
				*/
				}
				else if (row == 0) {
					minRow = 0;
					i = Xh;
					break; 
				}
			

			
				col++;
			}
			col = column * 10;
			row++;
		}
		if (i == Xh) 
			break;
		else {minRow = minRow - 10;
		 	 row = minRow;
	}

	
	if (minRow <= 0) 
		break;
	}	
	//verify if the piece is beyond the black part of the board
	if (minRow != 0)
		row = minRow + 10;
	else row = 0;
	col = column * 10;
	for (i = 10; i < Xh - 10; i++) {
		for (j = 10; j < Xw - 10; j++) {
			if (X[i][j] != 16777215 && Board[row][col] == 16777215)
				Game_over = 1;
			
			col++;
		}
		row++;
		col = column * 10;
	}
	//copy the piece on the board:
	if (minRow != 0)
		row = minRow + 10;
	else row = 0;
	col = column * 10;
	for (i = 10; i < Xh - 10; i++) {
		for (j = 10; j < Xw - 10; j++) {
			if (X[i][j] != 16777215)
				Board[row][col] = X[i][j];
			
			col++;
		}
		row++;
		col = column * 10;
	}
	/* verify if there are full lines and eliminate them
	(if the game isn't over) */
	int ok, k, l;
	if (Game_over == 0) 
		for (i = 0; i < H; i++) {
			if (i % 10 == 0)
				ok = 1;
			for (j = 0; j < Le; j++) {
				if (Board[i][j] == 0) {
					ok = 0;
					
				}

				

				if (i % 10 == 9 && j == Le - 1 && ok == 1) {
					
					for (k = i - 9; k < H + 30; k++)
						for (l = 0; l < Le; l++)
							Board[k][l] = Board[k + 10][l];
					for (k = H + 30; k < H + 40; k++)
						for (l = 0; l < Le; l++)
							Board[k][l] = 16777215;
					for (k = H - 10; k < H; k++)
						for (l = 0; l < Le; l++)
							if (Board[k][l] == 16777215)
								Board[k][l] = 0;
					i = i - 9;
					j = 0;

				}
			}
		}

	

fclose (in);
createFullBoard (Board, H, Le, d);
return Game_over;

}

int main (int argc, char *argv[]) {

	long int **O, **I, **S, **Z, **L, **J, **T;
	//pieces

	int Ow, Oh, Iw, Ih, Sw, Sh, Zw, Zh, Lw, Lh, Jw, Jh, Tw, Th;
	//width and height for each piece
	int Osize, Isize, Ssize, Zsize, Lsize, Jsize, Tsize;
	//size of each piece
	int i;
 
	int N, H, Le; //no. of pieces, Height and board length
	char pieceName, a;
	int rotation, column;
	long int **Board;

	Board = malloc(340 * sizeof(long int *));
 		//H = max 30. *10 (no. of pixels) + 40 (white part)
		for (i = 0; i < 340; i++)
			Board[i] = malloc (200 * sizeof (long int)) ;
		//Le = max 20. *10 (no. of pixels per column)



	Ow = 40;
	Oh = 40;
	Iw = 30;
	Ih = 60;
	Sw = 50;
	Sh = 40;
	Zw = 50;
	Zh = 40;
	Lw = 40;
	Lh = 50;
	Jw = 40;
	Jh = 50;
	Tw = 50;
	Th = 40;
	//pixel values

	Osize = Ow * Oh * 3;
	Isize = (Iw * 3 + 2) * Ih;
	Ssize = (Sw * 3 + 2) * Sh;
	Zsize = (Zw * 3 + 2) * Zh;
	Lsize = Lw * Lh * 3;
	Jsize = Jw * Jh * 3;
	Tsize = (Tw * 3 + 2) * Th;
/*	each matrix' dimension will be height * width * 3 (colors need 3 bytes
for representation). For the matrices where the width is not a multiple of 4,
we add the necessary number of bytes at the end of each line (padding) */

	O = malloc(Oh * sizeof(long int));
 
	for (i = 0; i < Oh; i++)
		O[i] = malloc (Ow * sizeof(long int));

	I = malloc(Ih * sizeof(long int));
 
	for (i = 0; i < Ih; i++)
		I[i] = malloc (Iw * sizeof (long int)) ;

	S = malloc(Sh * sizeof(long int));
 
	for (i = 0; i < Sh; i++)
		S[i] = malloc (Sw * sizeof (long int)) ;

	Z = malloc(Zh * sizeof(long int));
 
	for (i = 0; i < Zh; i++)
		Z[i] = malloc (Zw * sizeof (long int)) ;

	L = malloc(Lh * sizeof(long int));
 
	for (i = 0; i < Lh; i++)
		L[i] = malloc (Lw * sizeof (long int)) ;

	J = malloc(Jh * sizeof(long int));
 
	for (i = 0; i < Jh; i++)
		J[i] = malloc (Jw * sizeof (long int)) ;

	T = malloc(Th * sizeof(long int));
 
	for (i = 0; i < Th; i++)
		T[i] = malloc (Tw * sizeof (long int)) ;

if (argc == 1) {
	createPiece_O (O, Ow, Oh, Osize);
	createPiece_I (I, Iw, Ih, Isize);
	createPiece_S (S, Sw, Sh, Ssize);
	createPiece_Z (Z, Zw, Zh, Zsize);
	createPiece_L (L, Lw, Lh, Lsize);
	createPiece_J (J, Jw, Jh, Jsize);
	createPiece_T (T, Tw, Th, Tsize);

	pieceRotations_O (O, Ow, Oh, Osize);
	pieceRotations_I (I, Iw, Ih, Isize);
	pieceRotations_S (S, Sw, Sh, Ssize);
	pieceRotations_Z (Z, Zw, Zh, Zsize);
	pieceRotations_L (L, Lw, Lh, Lsize);
	pieceRotations_J (J, Jw, Jh, Jsize);
	pieceRotations_T (T, Tw, Th, Tsize);

	FILE *in = fopen ("cerinta3.in", "rt");
	if (in == NULL) {
        printf ("ERROR: Can't open file\n");
        return 0;
    }
	fscanf (in, "%d%d%d", &N, &H, &Le);
	Le = 10 * Le;
	H = 10 * H;
	
	createBoard (Board, H, Le);
	for (i = 1; i <= N; i++) {
		fscanf (in, "%c%c%d%d", &a, &pieceName, &rotation, &column);
		
		if (finalBoard (Board, H, Le, rotation, column, pieceName,'3') == 1)
			break;
	}
	
	fclose (in);

	in = fopen ("cerinta4.in", "rt");
	if (in == NULL) {
        printf("ERROR: Can't open file\n");
        return 0;
    }
	fscanf (in, "%d", &N);
	
	
	readBoard (Board, &H, &Le);
	for (i = 1; i <= N; i++) {
		fscanf (in, "%c%c%d%d", &a, &pieceName, &rotation, &column);
		
		if (finalBoard (Board, H, Le, rotation, column, pieceName,'4') == 1)
			break;
	}
	
	fclose (in);
}
else if (*argv[1] == '1') {
	createPiece_O (O, Ow, Oh, Osize);
	createPiece_I (I, Iw, Ih, Isize);
	createPiece_S (S, Sw, Sh, Ssize);
	createPiece_Z (Z, Zw, Zh, Zsize);
	createPiece_L (L, Lw, Lh, Lsize);
	createPiece_J (J, Jw, Jh, Jsize);
	createPiece_T (T, Tw, Th, Tsize);
}
else if (*argv[1] == '2') {

	createPiece_O (O, Ow, Oh, Osize);
	createPiece_I (I, Iw, Ih, Isize);
	createPiece_S (S, Sw, Sh, Ssize);
	createPiece_Z (Z, Zw, Zh, Zsize);
	createPiece_L (L, Lw, Lh, Lsize);
	createPiece_J (J, Jw, Jh, Jsize);
	createPiece_T (T, Tw, Th, Tsize);

	pieceRotations_O (O, Ow, Oh, Osize);
	pieceRotations_I (I, Iw, Ih, Isize);
	pieceRotations_S (S, Sw, Sh, Ssize);
	pieceRotations_Z (Z, Zw, Zh, Zsize);
	pieceRotations_L (L, Lw, Lh, Lsize);
	pieceRotations_J (J, Jw, Jh, Jsize);
	pieceRotations_T (T, Tw, Th, Tsize);
}
else if (*argv[1] == '3') {
	createPiece_O (O, Ow, Oh, Osize);
	createPiece_I (I, Iw, Ih, Isize);
	createPiece_S (S, Sw, Sh, Ssize);
	createPiece_Z (Z, Zw, Zh, Zsize);
	createPiece_L (L, Lw, Lh, Lsize);
	createPiece_J (J, Jw, Jh, Jsize);
	createPiece_T (T, Tw, Th, Tsize);

	pieceRotations_O (O, Ow, Oh, Osize);
	pieceRotations_I (I, Iw, Ih, Isize);
	pieceRotations_S (S, Sw, Sh, Ssize);
	pieceRotations_Z (Z, Zw, Zh, Zsize);
	pieceRotations_L (L, Lw, Lh, Lsize);
	pieceRotations_J (J, Jw, Jh, Jsize);
	pieceRotations_T (T, Tw, Th, Tsize);

	FILE *in = fopen ("cerinta3.in", "rt");
	if (in == NULL) {
		printf ("ERROR: Can't open file\n");
		return 0;
	}
	fscanf (in, "%d%d%d", &N, &H, &Le);
	Le = 10 * Le;
	H = 10 * H;
	
	createBoard (Board, H, Le);
	for (i = 1; i <= N; i++) {
		fscanf (in, "%c%c%d%d", &a, &pieceName, &rotation, &column);
		
		if (finalBoard (Board, H, Le, rotation, column, pieceName,'3') == 1)
			break;
	}
	
	fclose (in);

}

else if (*argv[1] == '4') {
	createPiece_O (O, Ow, Oh, Osize);
	createPiece_I (I, Iw, Ih, Isize);
	createPiece_S (S, Sw, Sh, Ssize);
	createPiece_Z (Z, Zw, Zh, Zsize);
	createPiece_L (L, Lw, Lh, Lsize);
	createPiece_J (J, Jw, Jh, Jsize);
	createPiece_T (T, Tw, Th, Tsize);

	pieceRotations_O (O, Ow, Oh, Osize);
	pieceRotations_I (I, Iw, Ih, Isize);
	pieceRotations_S (S, Sw, Sh, Ssize);
	pieceRotations_Z (Z, Zw, Zh, Zsize);
	pieceRotations_L (L, Lw, Lh, Lsize);
	pieceRotations_J (J, Jw, Jh, Jsize);
	pieceRotations_T (T, Tw, Th, Tsize);

	FILE *in = fopen ("cerinta4.in", "rt");
	if (in == NULL) {
        printf("ERROR: Can't open file\n");
        return 0;
    }
	fscanf (in, "%d", &N);
	
	
	int e = readBoard (Board, &H, &Le);
	if (e == 0) {
        printf("ERROR: Can't open file\n");
        return 0;
    }
	for (i = 1; i <= N; i++) {
		fscanf (in, "%c%c%d%d", &a, &pieceName, &rotation, &column);
		e = finalBoard (Board, H, Le, rotation, column, pieceName,'4');
		if ( e == 1)
			break;

	}
	
	fclose (in);

}



for (i = 0; i < Oh; i++)
	free(O[i]);
free (O);
O = NULL;

for (i = 0; i < Ih; i++)
	free(I[i]);
free (I);
I = NULL;

for (i = 0; i < Sh; i++)
	free(S[i]);
free (S);
S = NULL;

for (i = 0; i < Zh; i++)
	free(Z[i]);
free (Z);
Z = NULL;

for (i = 0; i < Lh; i++)
	free(L[i]);
free (L);
L = NULL;

for (i = 0; i < Jh; i++)
	free(J[i]);
free (J);
J = NULL;

for (i = 0; i < Th; i++)
	free(T[i]);
free (T);
T = NULL;

for (i = 0; i < 30; i++)
	free(Board[i]);
free (Board);
Board = NULL;


return 0;
}





