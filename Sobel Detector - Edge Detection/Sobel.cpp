#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;


int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int width = 321;
	int height = 481;
	
	// Check for proper syntax
	if (argc != 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name tiger.raw pig.raw threshold_1_percentage threshold_2_percentage" << endl;
		return 0;
	}
	
	double percentage_1 = atof(argv[3]);
	double percentage_2 = atof(argv[4]);
	// Allocate image data array
	unsigned char Imagedata[width][height][BytesPerPixel];
	unsigned char Imagedata_1[width][height][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height*BytesPerPixel, file);
	fclose(file);
	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[2] <<endl;
		exit(1);
	}
	fread(Imagedata_1, sizeof(unsigned char), width*height*BytesPerPixel, file);
	fclose(file);

	///////////////////////// transform to gray image /////////////////////////
	unsigned char grayImage[width][height];
	unsigned char grayImage_1[width][height];
	unsigned char grayImage_x[width-2][height-2];
	unsigned char grayImage_y[width-2][height-2];
	unsigned char grayImage_1x[width-2][height-2];
	unsigned char grayImage_1y[width-2][height-2];
	double edge_1[width-2][height-2];
	double edge_2[width-2][height-2];
	unsigned char edgeout_1[width-2][height-2];
	unsigned char edgeout_2[width-2][height-2];
	int min_11=255,max_11=0,min_21=255,max_21=0,min_12=255,max_12=0,min_22=255,max_22=0;

	for (int i=0; i<width; i++){
		for (int j=0;j<height;j++){
			grayImage[i][j]= Imagedata[i][j][0]*0.299+ Imagedata[i][j][1]*0.587+ Imagedata[i][j][2]*0.114;
			grayImage_1[i][j]= Imagedata_1[i][j][0]*0.299+ Imagedata_1[i][j][1]*0.587+ Imagedata_1[i][j][2]*0.114;

		}
	}
	for (int i=1; i<width-1; i++){
		for (int j=1;j<height-1;j++){
			grayImage_x[i-1][j-1]= 0.25*abs(grayImage[i-1][j+1]-grayImage[i-1][j-1]
									+2*(grayImage[i][j+1]-grayImage[i][j-1])
									+grayImage[i+1][j+1]-grayImage[i+1][j-1]);
			grayImage_y[i-1][j-1]= 0.25*abs(grayImage[i-1][j-1]-grayImage[i+1][j-1]
									+2*(grayImage[i-1][j]-grayImage[i+1][j])
									+grayImage[i-1][j+1]-grayImage[i+1][j+1]);

			grayImage_1x[i-1][j-1]= 0.25*abs(grayImage_1[i-1][j+1]-grayImage_1[i-1][j-1]
									+2*(grayImage_1[i][j+1]-grayImage_1[i][j-1])
									+grayImage_1[i+1][j+1]-grayImage_1[i+1][j-1]);
			grayImage_1y[i-1][j-1]= 0.25*abs(grayImage_1[i-1][j-1]-grayImage_1[i+1][j-1]
									+2*(grayImage_1[i-1][j]-grayImage_1[i+1][j])
									+grayImage_1[i-1][j+1]-grayImage_1[i+1][j+1]);

			if (grayImage_x[i-1][j-1]<min_11){
				min_11 = grayImage_x[i-1][j-1];
			}
			if (grayImage_x[i-1][j-1]>max_11){
				max_11 = grayImage_x[i-1][j-1];
			}
			if (grayImage_y[i-1][j-1]<min_12){
				min_12 = grayImage_y[i-1][j-1];
			}
			if (grayImage_y[i-1][j-1]>max_12){
				max_12 = grayImage_y[i-1][j-1];
			}
			if (grayImage_1x[i-1][j-1]<min_21){
				min_21 = grayImage_1x[i-1][j-1];
			}
			if (grayImage_1x[i-1][j-1]>max_21){
				max_21 = grayImage_1x[i-1][j-1];
			}
			if (grayImage_1y[i-1][j-1]<min_22){
				min_22 = grayImage_1y[i-1][j-1];
			}
			if (grayImage_1y[i-1][j-1]>max_22){
				max_22 = grayImage_1y[i-1][j-1];
			}
		}
	}


	double min_1=500,min_2=500,max_1=0,max_2=0;

	for (int i=0; i<width-2; i++){
		for (int j=0;j<height-2;j++){
			grayImage_x[i][j] = 255*(grayImage_x[i][j]-min_11)/(max_11-min_11);
			grayImage_y[i][j] = 255*(grayImage_y[i][j]-min_12)/(max_12-min_12);
			grayImage_1x[i][j] = 255*(grayImage_1x[i][j]-min_21)/(max_21-min_21);
			grayImage_1y[i][j] = 255*(grayImage_1y[i][j]-min_22)/(max_22-min_22);

			edge_1[i][j] = sqrt((double)pow(grayImage_x[i][j],2)+(double)pow(grayImage_y[i][j],2));
			edge_2[i][j] = sqrt((double)pow(grayImage_1x[i][j],2)+(double)pow(grayImage_1y[i][j],2));
			if (edge_1[i][j]>max_1){
				max_1=edge_1[i][j];
			}
			if (edge_1[i][j]<min_1){
				min_1=edge_1[i][j];
			}
			if (edge_2[i][j]>max_2){
				max_2=edge_2[i][j];
			}
			if (edge_2[i][j]<min_2){
				min_2=edge_2[i][j];
			}
		}
	}

	if (!(file=fopen("tiger_x.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(grayImage_x, sizeof(unsigned char), (width-2)*(height-2), file);
	fclose(file);
	if (!(file=fopen("tiger_y.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(grayImage_y, sizeof(unsigned char), (width-2)*(height-2), file);
	fclose(file);
	if (!(file=fopen("pig_x.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(grayImage_1x, sizeof(unsigned char), (width-2)*(height-2), file);
	fclose(file);
	if (!(file=fopen("pig_y.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(grayImage_1y, sizeof(unsigned char), (width-2)*(height-2), file);
	fclose(file);





	double threshold_1 = (max_1-min_1)*percentage_1+min_1;
	double threshold_2 = (max_2-min_2)*percentage_2+min_2;
	for (int i=0; i<width-2; i++){
		for (int j=0;j<height-2;j++){
			if(edge_1[i][j]>threshold_1){
				edgeout_1[i][j]=0;
			}
			else{
				edgeout_1[i][j]=255;
			}
			if(edge_2[i][j]>threshold_2){
				edgeout_2[i][j]=0;
			}
			else{
				edgeout_2[i][j]=255;
			}
		}
	}




	if (!(file=fopen("tiger_edge.raw","wb"))) {
		cout << "Cannot open file: tiger_gray.raw"<< endl;
		exit(1);
	}
	fwrite(edgeout_1, sizeof(unsigned char), (width-2)*(height-2), file);
	fclose(file);
	if (!(file=fopen("pig_edge.raw","wb"))) {
		cout << "Cannot open file: pig_gray.raw"<< endl;
		exit(1);
	}
	fwrite(edgeout_2, sizeof(unsigned char), (width-2)*(height-2), file);
	fclose(file);

	return 0;
}

