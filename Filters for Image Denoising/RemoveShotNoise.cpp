#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h> 

using namespace std;

static int width = 256;
static int height = 256;


void padding(double *image, double * result_image, int nn);
void non_local_mean(unsigned char *output_image, unsigned char *padding_image, int filter_size, int window_size);
void conv(double *output_image, double *filter, double *padding_image, int nn);
double PSNR(unsigned char *input_image, unsigned char *filtered_image){
	double mse = 0;
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			mse += (double)(input_image[i*height+j]-filtered_image[i*height+j])*(input_image[i*height+j]-filtered_image[i*height+j])/(width*height);

		}
	}
	return 10*log10(255*255/mse);
}

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	
	// Check for proper syntax
	if (argc < 2){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_original.raw input_image_noise.raw" << endl;
		return 0;
	}
		
	// Allocate image data array
	unsigned char Imagedata[width][height];

	unsigned char Imagedata_noise[width][height];

	// Read image_1 (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height, file);
	fclose(file);
	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[2] <<endl;
		exit(1);
	}
	fread(Imagedata_noise, sizeof(unsigned char), width*height, file);
	fclose(file);

	double Data_transformed[width][height];
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			Data_transformed[i][j] = 2*sqrt((double)Imagedata_noise[i][j]+3/8);
		}
	}

	double padding_image[width+6][height+6];
	padding(&Data_transformed[0][0],&padding_image[0][0],7);

	double output_image[width][height];
	double gaussion_filter[7][7];
	double sigma = 1;
	for (int m=0; m<7; m++){
		for (int n=0; n<7; n++){
			gaussion_filter[m][n] = 1/sqrt(2*3.14)/sigma * exp(-((m-(7-1)/2)*(m-(7-1)/2)+(n-(7-1)/2)*(n-(7-1)/2))/(double)2/sigma/sigma);
		}
	}

	conv(&output_image[0][0],&gaussion_filter[0][0],&padding_image[0][0],7);
	unsigned char inverse_output[width][height];
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			inverse_output[i][j] = (int)((output_image[i][j]/2)*(output_image[i][j]/2)-(double)3/8);
		}
	}

	cout<<PSNR(&Imagedata[0][0], &inverse_output[0][0])<<endl;
	
	if (!(file=fopen("pepper_shot.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(inverse_output, sizeof(unsigned char), width*height, file);
	fclose(file);
	



	// Write image data (filename specified by second argument) from image data matri
	return 0;
}

void padding(double *image, double * result_image, int nn){
	for (int i = 0; i<width+nn-1; i++){
		for (int j =nn/2; j<=height+nn/2-1; j++){
			if (i<=nn/2-1){
				result_image[i*(height+nn-1)+j]=image[(nn/2-i)*height+j-nn/2];
			}
			else if (i>=width+nn/2){
				result_image[i*(height+nn-1)+j]=image[(2*width-i-2+nn/2)*height+j-nn/2];
			}
			else{
				result_image[i*(height+nn-1)+j]=image[(i-nn/2)*height+j-nn/2];
			}
		}
	}
	for (int i=0; i<width+nn-1;i++){
		for (int j=0; j<nn/2; j++){
			result_image[i*(height+nn-1)+j] = result_image[i*(height+nn-1)+nn-j-1];
			result_image[i*(height+nn-1)+height+nn-2-j] = result_image[i*(height+nn-1)+(height-1)+j];
		}
	}
}


void conv(double *output_image, double *filter, double *padding_image, int nn){
	double sum = 0;
	for (int m=0; m<nn; m++){
		for (int n=0; n<nn; n++){
			sum += filter[m*nn+n];
		}
	}
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			double convsum = 0;
			for (int m=0; m<nn; m++){
				for (int n=0; n<nn; n++){
					convsum += (double)(filter[m*nn+n]*padding_image[(i+m)*(height+nn-1)+j+n])/sum;
				}
			}
			output_image[i*height+j] = convsum;
		}
	}
}

