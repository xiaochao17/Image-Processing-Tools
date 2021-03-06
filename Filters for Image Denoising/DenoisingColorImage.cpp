#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h> 

using namespace std;

static int width = 256;
static int height = 256;

double PSNR(unsigned char *input_image, unsigned char *filtered_image);
void padding(unsigned char *image, unsigned char * result_image, int nn);
void uni_conv(unsigned char *output_image, unsigned char *padding_image, int nn);
void bi_conv(unsigned char *output_image, unsigned char *padding_image, int nn);
void gao_conv(unsigned char *output_image, unsigned char *padding_image, int nn);
void non_local_mean(unsigned char *output_image, unsigned char *padding_image, int filter_size, int window_size);
void get_best_way(unsigned char *output_image, unsigned char *input_image, unsigned char * original,int fs, int ws);

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	
	// Check for proper syntax
	if (argc < 2){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_color_image_w/o_noise.raw input_color_image_noise.raw" << endl;
		return 0;
	}
		
	// Allocate image data array
	unsigned char Imagedata[width][height][3];
	unsigned char Imagedata_noise[width][height][3];

	// Read image_1 (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height*3, file);
	fclose(file);
	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata_noise, sizeof(unsigned char), width*height*3, file);
	fclose(file);

	int filter_size = 7;
	int window_size = 21;
	unsigned char red_channel[width][height];
	unsigned char green_channel[width][height];
	unsigned char blue_channel[width][height];
	unsigned char red_original[width][height];
	unsigned char green_original[width][height];
	unsigned char blue_original[width][height];
	for (int i=0; i<width; i++){
		for(int j=0; j<height; j++){
			red_channel[i][j]=Imagedata_noise[i][j][0];
			green_channel[i][j]=Imagedata_noise[i][j][1];
			blue_channel[i][j]=Imagedata_noise[i][j][2];
			red_original[width][height] = Imagedata[i][j][0];
			green_original[width][height] = Imagedata[i][j][1];
			blue_original[width][height] = Imagedata[i][j][2];

		}
	}
	unsigned char red_padding[width+filter_size-1][height+filter_size-1];
	unsigned char green_padding[width+filter_size-1][height+filter_size-1];
	unsigned char blue_padding[width+filter_size-1][height+filter_size-1];
	padding(&red_channel[0][0],&red_padding[0][0],filter_size);
	padding(&green_channel[0][0],&green_padding[0][0],filter_size);
	padding(&blue_channel[0][0],&blue_padding[0][0],filter_size);

	unsigned char redout_channel[width][height];
	unsigned char greenout_channel[width][height];
	unsigned char blueout_channel[width][height];


	get_best_way(&redout_channel[0][0],&red_padding[0][0], &red_original[0][0], filter_size, window_size);
	get_best_way(&greenout_channel[0][0],&green_padding[0][0], &green_original[0][0], filter_size, window_size);
	get_best_way(&blueout_channel[0][0],&blue_padding[0][0], &blue_original[0][0], filter_size, window_size);


	unsigned char output[width][height][3];
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			output[i][j][0]= redout_channel[i][j];
			output[i][j][1]= greenout_channel[i][j];
			output[i][j][2]= blueout_channel[i][j];


		}
	}

	
	if (!(file=fopen("color_rose_output.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(output, sizeof(unsigned char), width*height*3, file);
	fclose(file);



	// Write image data (filename specified by second argument) from image data matri
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

void uni_conv(unsigned char *output_image, unsigned char *padding_image, int nn){
	double filter[nn*nn];
		for (int m=0; m<nn; m++){
			for (int n=0; n<nn; n++){
				filter[m*nn+n] = 1;
			}
		}
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

void gao_conv(unsigned char *output_image, unsigned char *padding_image, int nn){
	double filter[nn*nn];
	double sigma = 1.8;
	for (int m=0; m<nn; m++){
		for (int n=0; n<nn; n++){
			filter[m*nn+n] = 1/sqrt(2*3.14)/sigma * exp(-((m-(nn-1)/2)*(m-(nn-1)/2)+(n-(nn-1)/2)*(n-(nn-1)/2))/(double)2/sigma/sigma);
		}
	}
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

void  bi_conv(unsigned char *output_image, unsigned char *padding_image, int nn){
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

void non_local_mean(unsigned char *output_image, unsigned char *padding_image, int f_s, int w_s)
{

	double h = 8;
	double sigma = 100;
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			double convsum = 0;
			double sum = 0;		
			for (int p=0; p<w_s; p++){
				for (int q=0; q<w_s; q++){
					double weight = 0;	
					for (int m=0; m<f_s; m++){
						for (int n=0; n<f_s; n++){
							weight += exp(-((m-(f_s-1)/2)*(m-(f_s-1)/2)+(n-(f_s-1)/2)*(n-(f_s-1)/2))/(2*sigma*sigma))
								/sqrt(2*3.14)/sigma*
								(padding_image[(i+(w_s-1)/2+m)*(height+f_s+w_s-2)+j+(w_s-1)/2+n] 
									- padding_image[(i+p+m)*(height+f_s+w_s-2)+j+q+n])
								*(padding_image[(i+(w_s-1)/2+m)*(height+f_s+w_s-2)+j+(w_s-1)/2+n] 
									- padding_image[(i+p+m)*(height+f_s+w_s-2)+j+q+n]);
						}
					}
					weight = exp(-weight/h/h);
					sum+=weight;
					convsum += weight*padding_image[(i+p+(f_s-1)/2)*(height+f_s+w_s-2)+j+q+(f_s-1)/2];
				}
			}
			output_image[i*height+j] = convsum/sum;
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

void get_best_way(unsigned char *output_image, unsigned char *input_image, unsigned char * original, int fs, int ws){
	
	double psnr_values[6]={0,0,0,0,0,0};
	unsigned char new_padding[width+fs-1][height+fs-1];
	gao_conv(&output_image[0],&input_image[0],fs);
	padding(&output_image[0],&new_padding[0][0],fs);
	bi_conv(&output_image[0],&new_padding[0][0],fs);
	psnr_values[0] = PSNR(&original[0],&output_image[0]);
	cout<<psnr_values[0]<<"  ";

	unsigned char output_channel[width][height];
	uni_conv(&output_channel[0][0],&input_image[0],fs);
	padding(&output_channel[0][0],&new_padding[0][0],fs);
	bi_conv(&output_channel[0][0],&new_padding[0][0],fs);
	psnr_values[1] = PSNR(&original[0],&output_channel[0][0]);
	cout<<psnr_values[1]<<"  ";

	unsigned char output_third[width][height];
	uni_conv(&output_third[0][0],&input_image[0],fs);
	padding(&output_third[0][0],&new_padding[0][0],fs);
	gao_conv(&output_third[0][0],&new_padding[0][0],fs);
	psnr_values[2] = PSNR(&original[0],&output_third[0][0]);
	cout<<psnr_values[2]<<"  ";

	unsigned char big_padding[width+fs+ws-2][height+fs+ws-2];

	unsigned char output_forth[width][height];
	uni_conv(&output_forth[0][0],&input_image[0],fs);
	padding(&output_forth[0][0],&big_padding[0][0],fs+ws-1);
	non_local_mean(&output_forth[0][0],&big_padding[0][0],fs,ws);
	psnr_values[3] = PSNR(&original[0],&output_forth[0][0]);
	cout<<psnr_values[3]<<"  ";

	unsigned char output_fifth[width][height];
	gao_conv(&output_fifth[0][0],&input_image[0],fs);
	padding(&output_fifth[0][0],&big_padding[0][0],fs+ws-1);
	non_local_mean(&output_fifth[0][0],&big_padding[0][0],fs,ws);
	psnr_values[4] = PSNR(&original[0],&output_fifth[0][0]);
	cout<<psnr_values[4]<<"  ";

	unsigned char output_sixth[width][height];
	bi_conv(&output_sixth[0][0],&input_image[0],fs);
	padding(&output_sixth[0][0],&big_padding[0][0],fs+ws-1);
	non_local_mean(&output_sixth[0][0],&big_padding[0][0],fs,ws);
	psnr_values[5] = PSNR(&original[0],&output_sixth[0][0]);
	cout<<psnr_values[5]<<"  ";

	if (psnr_values[0]<psnr_values[1] && psnr_values[2]<psnr_values[1] ){//&& psnr_values[1]>psnr_values[3] && psnr_values[1]>psnr_values[4] && psnr_values[1]>psnr_values[5]) {
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				output_image[i*height+j] = output_channel[i][j];
			}
		}
	}
	if (psnr_values[0]<psnr_values[2] && psnr_values[2]>psnr_values[1] ){//&& psnr_values[3]<psnr_values[2]&& psnr_values[2]>psnr_values[4] && psnr_values[2]>psnr_values[5] ){
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				output_image[i*height+j] = output_third[i][j];
			}
		}
	}
	if (psnr_values[0]<psnr_values[3] && psnr_values[3]>psnr_values[1] && psnr_values[2]<psnr_values[3] && psnr_values[3]>psnr_values[4] && psnr_values[3]>psnr_values[5]){
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				output_image[i*height+j] = output_forth[i][j];
			}
		}
	}
	if (psnr_values[0]<psnr_values[4] && psnr_values[4]>psnr_values[1] && psnr_values[2]<psnr_values[4] && psnr_values[4]>psnr_values[3] && psnr_values[4]>psnr_values[5]){
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				output_image[i*height+j] = output_fifth[i][j];
			}
		}
	}
	if (psnr_values[0]<psnr_values[5] && psnr_values[5]>psnr_values[1] && psnr_values[2]<psnr_values[5] && psnr_values[5]>psnr_values[4] && psnr_values[5]>psnr_values[3]){
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				output_image[i*height+j] = output_sixth[i][j];
			}
		}
	}
}
