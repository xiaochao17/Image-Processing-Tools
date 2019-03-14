#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h> 

using namespace std;

static int width = 256;
static int height = 256;


void padding(unsigned char *image, unsigned char * result_image, int nn);
void conv(unsigned char *output_image, double *filter, unsigned char *padding_image, int nn);
void nonlinear_conv(unsigned char *output_image, unsigned char *padding_image, int nn);
double PSNR(unsigned char *input_image, unsigned char *filtered_image);


int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw input_image_noisr.raw" << endl;
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

	int noise[width][height];
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			noise[i][j] = Imagedata_noise[i][j]-Imagedata[i][j];
		}
	}
	if (!(file=fopen("noise_diff.raw","wb"))) {
			cout << "Cannot open file " << endl;
			exit(1);
		}
	fwrite(noise, sizeof(unsigned char), width*height, file);
	fclose(file);


	// uniform doing padding
	double psnr_values[7];
	double psnr_values_2[7];
	for (int i=3; i<=15; i+=2){
		double uniform_filter[i][i];
		for (int m=0; m<i; m++){
			for (int n=0; n<i; n++){
				uniform_filter[m][n] = 1;
			}
		}

		double gaussion_filter[i][i];
		double sigma = 1.8;
		for (int m=0; m<i; m++){
			for (int n=0; n<i; n++){
				gaussion_filter[m][n] = 1/sqrt(2*3.14)/sigma * exp(-((m-(i-1)/2)*(m-(i-1)/2)+(n-(i-1)/2)*(n-(i-1)/2))/(double)2/sigma/sigma);
			}
		}

		unsigned char padding_image[width+i-1][height+i-1];
		padding(&Imagedata_noise[0][0],&padding_image[0][0],i);

		unsigned char output_image[width][height];
		unsigned char output_image_2[width][height];
		unsigned char output_image_3[width][height];

		conv(&output_image[0][0],&uniform_filter[0][0],&padding_image[0][0],i);
		conv(&output_image_2[0][0],&gaussion_filter[0][0],&padding_image[0][0],i);
		nonlinear_conv(&output_image_3[0][0],&padding_image[0][0],i);


		string filename = "pepper_"+to_string(i)+"_uni.raw";
		string filename_2 = "pepper_"+to_string(i)+"_gaussion.raw";
		string filename_3 = "pepper_"+to_string(i)+"_lateral.raw";


		char char_array[filename.length()+1];
		char char_array_2[filename.length()+1];
		char char_array_3[filename.length()+1];

		strcpy(char_array,filename.c_str());
		strcpy(char_array_2,filename_2.c_str());
		strcpy(char_array_3,filename_3.c_str());
		
		if (!(file=fopen(char_array,"wb"))) {
			cout << "Cannot open file " << endl;
			exit(1);
		}
		fwrite(output_image, sizeof(unsigned char), width*height, file);
		fclose(file);
		if (!(file=fopen(char_array_2,"wb"))) {
			cout << "Cannot open file " << endl;
			exit(1);
		}
		fwrite(output_image_2, sizeof(unsigned char), width*height, file);
		fclose(file);
		if (!(file=fopen(char_array_3,"wb"))) {
			cout << "Cannot open file " << endl;
			exit(1);
		}
		fwrite(output_image_3, sizeof(unsigned char), width*height, file);
		fclose(file);

		psnr_values[i/2-1]=PSNR(&Imagedata[0][0],&output_image[0][0]);
		cout<<psnr_values[i/2-1]<<"  ";
		psnr_values_2[i/2-1]=PSNR(&Imagedata[0][0],&output_image_2[0][0]);
		cout<<psnr_values_2[i/2-1]<<endl;

	}
	return 0;
}

void padding(unsigned char *image, unsigned char * result_image, int nn){
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

void conv(unsigned char *output_image, double *filter, unsigned char *padding_image, int nn){
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

double PSNR(unsigned char *input_image, unsigned char *filtered_image){
	double mse = 0;
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			mse += (double)(input_image[i*height+j]-filtered_image[i*height+j])*(input_image[i*height+j]-filtered_image[i*height+j])/(width*height);

		}
	}
	return 10*log10(255*255/mse);
}

void nonlinear_conv(unsigned char *output_image, unsigned char *padding_image, int nn){
	double weight = 0;
	double sigma_1 = 1.8;
	double sigma_2 = 100;
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			double convsum = 0;
			double sum = 0;
			for (int m=0; m<nn; m++){
				for (int n=0; n<nn; n++){
					weight = exp(-((m-(nn-1)/2)*(m-(nn-1)/2)+(n-(nn-1)/2)*(n-(nn-1)/2))/(double)2/sigma_1/sigma_1
						-(padding_image[(i+(nn-1)/2)*(height+nn-1)+j+(nn-1)/2] - padding_image[(i+m)*(height+nn-1)+j+n])*(padding_image[(i+(nn-1)/2)*(height+nn-1)+j+(nn-1)/2] - padding_image[(i+m)*(height+nn-1)+j+n])
						/(double)2/sigma_2/sigma_2);
					sum += weight;
					convsum += weight*padding_image[(i+m)*(height+nn-1)+j+n];
				}
			}
			output_image[i*height+j] = convsum/sum;
		}
	}
}

