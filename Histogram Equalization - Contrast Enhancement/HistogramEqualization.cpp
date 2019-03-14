#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

static int width = 400;
static int height = 400;

int *initial_histgram();
int *get_histgram(unsigned char *data,int *pixel_values);
void cdf(unsigned char *data, unsigned char *cdf_out);
void tf_boys(unsigned char *data, unsigned char *tf_out, int *t_f);


int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;	
	// Check for proper syntax
	if (argc < 4){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image_1.raw input_image_2.raw input_image_3.raw" << endl;
		return 0;
	}		
	// Allocate image data array
	unsigned char Imagedata[width][height];
	// Read image_1 (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height, file);
	fclose(file);


	unsigned char cdf_out[width][height];
	unsigned char tf_out[width][height];
	int *pixel_values = initial_histgram();


	cdf(&Imagedata[0][0],&cdf_out[0][0]);
	int transfer_function[256];
	tf_boys(&Imagedata[0][0],&tf_out[0][0], &transfer_function[0]);
	if (!(file=fopen("rose_dark_tf.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(tf_out, sizeof(unsigned char), width*height, file);
	fclose(file);
	if (!(file=fopen("rose_dark_cdf.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(cdf_out, sizeof(unsigned char), width*height, file);
	fclose(file);
	if (!(file=fopen("rose_dark_transfer.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(transfer_function, sizeof(int), 256, file);
	fclose(file);

	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height, file);
	fclose(file);
	cdf(&Imagedata[0][0],&cdf_out[0][0]);
	tf_boys(&Imagedata[0][0],&tf_out[0][0], &transfer_function[0]);
	if (!(file=fopen("rose_bright_tf.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(tf_out, sizeof(unsigned char), width*height, file);
	fclose(file);
	if (!(file=fopen("rose_bright_cdf.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(cdf_out, sizeof(unsigned char), width*height, file);
	fclose(file);
	if (!(file=fopen("rose_bright_transfer.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(transfer_function, sizeof(int), 256, file);
	fclose(file);
	
	if (!(file=fopen(argv[3],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height, file);
	fclose(file);
	cdf(&Imagedata[0][0],&cdf_out[0][0]);
	tf_boys(&Imagedata[0][0],&tf_out[0][0],&transfer_function[0]);
	if (!(file=fopen("rose_mix_tf.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(tf_out, sizeof(unsigned char), width*height, file);
	fclose(file);
	if (!(file=fopen("rose_mixt_cdf.raw","wb"))) {
		cout << "Cannot open file " << endl;
		exit(1);
	}
	fwrite(cdf_out, sizeof(unsigned char), width*height, file);
	fclose(file);




	return 0;
}


int * initial_histgram(){
	static int pixel_values[256];
	for (int i=0; i<256; i++){
		pixel_values[i]=0;
	}
	return pixel_values;
}

int * get_histgram(unsigned char *data,int *pixel_values){
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			int k = data[i*height+j];
			if (k>=0 || k<=255){
				pixel_values[k] +=1;
			}
		}
	}
	return pixel_values;

}

void cdf(unsigned char *data, unsigned char *cdf_out){
	vector<vector<int>> new_order(256);
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			int k = data[i*height+j];
			if (k>=0 || k<=255){
				new_order[k].push_back(i*height+j);
			}
		}
	}
	vector<int> new_image;
	for (int i=0; i<256; i++){
		new_image.insert(new_image.end(),new_order[i].begin(),new_order[i].end());
	}

	int number_for_each = height * width / 256;
	for (int i=0; i<256; i++){
		for (int j=0; j<number_for_each;j++){
			cdf_out[new_image[i*number_for_each+j]] = i;
		}
	}

}

void tf_boys(unsigned char *data, unsigned char *tf_out, int *result){
	vector<vector<int>> new_order(256);
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			int k = data[i*height+j];
			if (k>=0 || k<=255){
				new_order[k].push_back(i*height+j);
			}
		}
	}
	double prob[256];
	for(int i=0; i<256; i++){
		prob[i] = (double)new_order[i].size()/(height*width);
	}
	result[0] = prob[0]*255;
	for(int i=1; i<256; i++){
		prob[i] += prob[i-1];
		result[i] = prob[i]*255;
	}
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			tf_out[i*height+j] = result[data[i*height+j]];
		}
	}
}

