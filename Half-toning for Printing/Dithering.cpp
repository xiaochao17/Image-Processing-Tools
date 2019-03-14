#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <array>

using namespace std;

vector<vector<double>> makeIndexMatrix(int size);

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

	///////////////////////// transform to binary image /////////////////////////
	unsigned char halftone[width][height];
	for (int i=0; i<width; i++){
		for (int j=0;j<height;j++){
			if (Imagedata[i][j]>=rand()%256){
				halftone[i][j]=255;
			}
			else{
				halftone[i][j]=0;
			}
		}
	}
	if (!(file=fopen("bridge_random.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(halftone, sizeof(unsigned char), width*height, file);
	fclose(file);

	vector<int> size_arr={2,8,16,32};
	for (int i=0; i<size_arr.size();i++){
		vector<vector<double>> T=makeIndexMatrix(size_arr[i]);
		for (int m=0;m<width;m++){
			for(int n=0;n<height;n++){
				if (Imagedata[m][n]>T[m%size_arr[i]][n%size_arr[i]]){
					halftone[m][n]=255;
				}
				else{
					halftone[m][n]=0;
				}
			}
		}

		string filename = "bridge_"+to_string(size_arr[i])+"_dither.raw";
		char char_array[filename.length()+1];
		strcpy(char_array,filename.c_str());
		if (!(file=fopen(char_array,"wb"))) {
			cout << "Cannot open file"<< endl;
			exit(1);
		}
		fwrite(halftone, sizeof(unsigned char), width*height, file);
		fclose(file);
	}




	return 0;
}

vector<vector<double>> makeIndexMatrix(int size){
	vector<vector<double>> dithering{{1,2},{3,0}};
	vector<vector<double>> dither(size,vector<double>(size,0));

	if(log2(size)-1<=0){
		for (int i=0;i<size;i++){
			for (int j=0;j<size;j++){
				dithering[i][j]=(dithering[i][j]+0.5)/pow(size,2)*255;
			}
		}
		return dithering;
	}
	else{
		int iter=log2(size)-1;
		for (int k=1;k<=iter;k++){
			for (int i=0;i<pow(2,k);i++){
				for (int j=0;j<pow(2,k);j++){
					dither[i][j]=4*dithering[i][j]+1;
					dither[i][j+pow(2,k)]=4*dithering[i][j]+2;
					dither[i+pow(2,k)][j]=4*dithering[i][j]+3;
					dither[i+pow(2,k)][j+pow(2,k)]=4*dithering[i][j];
				}
			}
			dithering.resize(pow(2,k+1));
			for (int i=0;i<pow(2,k+1);i++){
				dithering[i].resize(pow(2,k+1));
				for (int j=0;j<pow(2,k+1);j++){
					dithering[i][j]=dither[i][j];
				}
			}
		}
		for (int i=0;i<size;i++){
			for (int j=0;j<size;j++){
				dither[i][j]=(dither[i][j]+0.5)/pow(size,2)*255;
			}
		}

		return dither;
	}

}

