#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <array>

using namespace std;


int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int width = 400;
	int height = 600;
	
	// Check for proper syntax
	if (argc != 2){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name bridge.raw " << endl;
		return 0;
	}
	
	// Allocate image data array
	unsigned char Imagedata[width][height];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height, file);
	fclose(file);

	///////////////////////// floyd-steinberg /////////////////////////
	unsigned char halftone[width][height];
	double pixel[width][height];
	for(int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			pixel[i][j]=Imagedata[i][j];
		}
	}
	double error=0;
	for (int i=0; i<width; i++){
		if (i%2==0){
			for (int j=0;j<height;j++){
				if (pixel[i][j]>=rand()%256){
					halftone[i][j]=255;
				}
				else{
					halftone[i][j]=0;
				}
				error=pixel[i][j]-halftone[i][j];
				if(j<height-1){
					pixel[i][j+1]+=error*7/16;
				}
				if(i<width-1){
					if(j>0){
						pixel[i+1][j-1]+=error*3/16;
					}
					pixel[i+1][j]+=error*5/16;
					if(j<height-1){
						pixel[i+1][j+1]+=error/16;
					}
				}
			}
		}
		else{
			for (int j=height-1;j>=0;j--){
				if (pixel[i][j]>=rand()%256){
					halftone[i][j]=255;
				}
				else{
					halftone[i][j]=0;
				}
				error=pixel[i][j]-halftone[i][j];
				if(j>0){
					pixel[i][j-1]+=error*7/16;
				}
				if(i<width-1){
					if(j<height-1){
						pixel[i+1][j+1]+=error*3/16;
					}
					pixel[i+1][j]+=error*5/16;
					if(j>0){
						pixel[i+1][j-1]+=error/16;
					}
				}
			}
		}
	}
	if (!(file=fopen("bridge_fs.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(halftone, sizeof(unsigned char), width*height, file);
	fclose(file);
	///////////////////////// JJN /////////////////////////
	for(int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			pixel[i][j]=Imagedata[i][j];
		}
	}
	for (int i=0; i<width; i++){
		if (i%2==0){
			for (int j=0;j<height;j++){
				if (pixel[i][j]>=rand()%256){
					halftone[i][j]=255;
				}
				else{
					halftone[i][j]=0;
				}
				error=pixel[i][j]-halftone[i][j];
				if(j<height-1){
					pixel[i][j+1]+=error*7/48;
				}
				if(j<height-2){
					pixel[i][j+2]+=error*5/48;
				}
				if(i<width-2){
					if(j>0){
						pixel[i+1][j-1]+=error*5/48;
					}
					if(j>1){
						pixel[i+1][j-2]+=error*3/48;
					}
					pixel[i+1][j]+=error*7/48;
					if(j<height-1){
						pixel[i+1][j+1]+=error*5/48;
					}
					if(j<height-2){
						pixel[i+1][j+2]+=error*3/48;
					}
				}
				if(i<width-1){
					if(j>0){
						pixel[i+1][j-1]+=error*3/48;
					}
					if(j>1){
						pixel[i+1][j-2]+=error/48;
					}
					pixel[i+1][j]+=error*5/48;
					if(j<height-1){
						pixel[i+1][j+1]+=error*3/48;
					}
					if(j<height-2){
						pixel[i+1][j+2]+=error/48;
					}
				}
			}
		}
		else{
			for (int j=height-1;j>=0;j--){
				if (pixel[i][j]>=rand()%256){
					halftone[i][j]=255;
				}
				else{
					halftone[i][j]=0;
				}
				error=pixel[i][j]-halftone[i][j];
				if(j>0){
					pixel[i][j-1]+=error*7/48;
				}
				if(j>1){
					pixel[i][j-2]+=error*5/48;
				}
				if(i<width-2){
					if(j<height-1){
						pixel[i+1][j+1]+=error*5/48;
					}
					if(j<height-2){
						pixel[i+1][j+2]+=error*3/48;
					}
					pixel[i+1][j]+=error*7/48;
					if(j>0){
						pixel[i+1][j-1]+=error*5/48;
					}
					if(j>1){
						pixel[i+1][j-2]+=error*3/48;
					}
				}
				if(i<width-1){
					if(j<height-1){
						pixel[i+1][j+1]+=error*3/48;
					}
					if(j<height-2){
						pixel[i+1][j+2]+=error/48;
					}
					pixel[i+1][j]+=error*5/48;
					if(j>0){
						pixel[i+1][j-1]+=error*3/48;
					}
					if(j>1){
						pixel[i+1][j-2]+=error/48;
					}
				}
			}
		}
	}
	if (!(file=fopen("bridge_JJN.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(halftone, sizeof(unsigned char), width*height, file);
	fclose(file);

	///////////////////////// Stucki /////////////////////////
	for(int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			pixel[i][j]=Imagedata[i][j];
		}
	}
	for (int i=0; i<width; i++){
		if (i%2==0){
			for (int j=0;j<height;j++){
				if (pixel[i][j]>=rand()%256){
					halftone[i][j]=255;
				}
				else{
					halftone[i][j]=0;
				}
				error=pixel[i][j]-halftone[i][j];
				if(j<height-1){
					pixel[i][j+1]+=error*8/42;
				}
				if(j<height-2){
					pixel[i][j+2]+=error*4/42;
				}
				if(i<width-2){
					if(j>0){
						pixel[i+1][j-1]+=error*4/42;
					}
					if(j>1){
						pixel[i+1][j-2]+=error*2/42;
					}
					pixel[i+1][j]+=error*8/48;
					if(j<height-1){
						pixel[i+1][j+1]+=error*4/42;
					}
					if(j<height-2){
						pixel[i+1][j+2]+=error*2/42;
					}
				}
				if(i<width-1){
					if(j>0){
						pixel[i+1][j-1]+=error*2/42;
					}
					if(j>1){
						pixel[i+1][j-2]+=error/42;
					}
					pixel[i+1][j]+=error*4/42;
					if(j<height-1){
						pixel[i+1][j+1]+=error*2/42;
					}
					if(j<height-2){
						pixel[i+1][j+2]+=error/42;
					}
				}
			}
		}
		else{
			for (int j=height-1;j>=0;j--){
				if (pixel[i][j]>=rand()%256){
					halftone[i][j]=255;
				}
				else{
					halftone[i][j]=0;
				}
				error=pixel[i][j]-halftone[i][j];
				if(j>0){
					pixel[i][j-1]+=error*8/42;
				}
				if(j>1){
					pixel[i][j-2]+=error*4/42;
				}
				if(i<width-2){
					if(j<height-1){
						pixel[i+1][j+1]+=error*4/42;
					}
					if(j<height-2){
						pixel[i+1][j+2]+=error*2/42;
					}
					pixel[i+1][j]+=error*8/42;
					if(j>0){
						pixel[i+1][j-1]+=error*4/42;
					}
					if(j>1){
						pixel[i+1][j-2]+=error*2/42;
					}
				}
				if(i<width-1){
					if(j<height-1){
						pixel[i+1][j+1]+=error*2/42;
					}
					if(j<height-2){
						pixel[i+1][j+2]+=error/42;
					}
					pixel[i+1][j]+=error*4/42;
					if(j>0){
						pixel[i+1][j-1]+=error*2/42;
					}
					if(j>1){
						pixel[i+1][j-2]+=error/42;
					}
				}
			}
		}
	}
	if (!(file=fopen("bridge_Stucki.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(halftone, sizeof(unsigned char), width*height, file);
	fclose(file);



	return 0;
}


