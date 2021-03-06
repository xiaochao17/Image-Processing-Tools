#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
int width = 512;
int height = 512;

vector<vector<int>> findCoordinates(unsigned char *input_image);
vector<double> gaussianElimination(vector<vector<double>> inVector);




int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;

	
	// Check for proper syntax
	if (argc != 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image(512*512 gray image) sub_image_1 sub_image_2 sub_image_3" << endl;
		return 0;
	}
	

	// Allocate image data array
	unsigned char mainImage[width][height];
	unsigned char subImage[3][width/2][height/2];

	// Read image into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(mainImage, sizeof(unsigned char), width*height, file);
	fclose(file);
	for (int i=0; i<3; i++){
		if (!(file=fopen(argv[i+2],"rb"))) {
			cout << "Cannot open file: " << argv[i+2] <<endl;
			exit(1);
		}
		fread(subImage[i], sizeof(unsigned char), width/2*height/2, file);
		fclose(file);
	}

	// change size if the number of blocks change, or just unspecify
	vector<vector<vector<int>>> coordinates(3, vector<vector<int>>(4,vector<int>(2,0)));
	vector<vector<vector<int>>> main_coordinates(3, vector<vector<int>>(4,vector<int>(2,0)));

	for (int i=0; i<3; i++){
		coordinates[i]=findCoordinates(&subImage[i][0][0]);
	}

	//output all four coordinates of three images
	for (int k=0; k<3; k++){
		for (int i=0; i<4; i++){
			for (int j=0; j<2;j++){
				cout<<coordinates[k][i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}

	// detect erased blocks in the original image
	int k=0;
	for (int i=1; i<width-1; i++){
		for (int j=1; j<height-1; j++){
			int flag =0;
			int m=1,n=1;
			// detect the top-left corner of the block
			if (mainImage[i][j]==255 && mainImage[i][j-1]!=255 && mainImage[i-1][j]!=255){
				flag = 1;
				// detect the width and length of the erased block
				while(mainImage[i+m][j]==255 && i+m<width){
					m++;
				}
				while(mainImage[i][j+n]==255 && j+n<height){
					n++;
				}
				// if the block is too small(<50), ignore it
				if (m<50 || n<50){
					flag=0;
				}
				else{
					// if the block is not all white, ignore it
					for(int p=i; p<i+m; p++){
						for (int q=j; q<j+n; q++){
							if(mainImage[p][q]!=255){
								flag = 0;
							}
						}
					}
				}
			}
			//it is the start point of a totally white big block
			if (flag==1){
				main_coordinates[k][0][0]=i;
				main_coordinates[k][0][1]=j;
				main_coordinates[k][1][0]=i;
				main_coordinates[k][1][1]=j+n-1;
				main_coordinates[k][2][0]=i+m-1;
				main_coordinates[k][2][1]=j+n-1;
				main_coordinates[k][3][0]=i+m-1;
				main_coordinates[k][3][1]=j;
				k++;
				// cout<<i<<" "<<j<<"  ";
				// cout<<i+m-1<<" "<<j<<"  ";
				// cout<<i<<" "<<j+n-1<<"  ";
				// cout<<i+m-1<<" "<<j+n-1<<"  ";
				// cout<<endl;
			}
		}
	}
/****
	// match blocks first
	for (int l=0; l<3; l++){
		//get the length of one side of the sub-image
		int xSubRange=coordinates[l][1][0]-coordinates[l][0][0];
		//cout<<xSubRange<<"sub  x Start from"<<coordinates[l][0][0]<<" to"<<coordinates[l][1][0]<<endl;
		int ySubRange=coordinates[l][1][1]-coordinates[l][0][1];
		//cout<<ySubRange<<"sub  x Start from"<<coordinates[l][0][1]<<" to"<<coordinates[l][1][1]<<endl;
		//calculate the mse for pixels
		int minSum=512*512*5;
		//traverse three blocks in the main image
		for (int r=0; r<3; r++){
			// traverse all possible sides
			for (int i=0; i<4; i++){
				int sum = 0;
				int xRange = main_coordinates[r][(i+1)%4][0]-main_coordinates[r][i%4][0];
				int yRange = main_coordinates[r][(i+1)%4][1]-main_coordinates[r][i%4][1];
				// cout<<xRange<<"  "<<yRange<<endl;
				// cout<<"x start from "<<main_coordinates[r][i%4][0]<<endl;
				// cout<<"y start from "<<main_coordinates[r][i%4][1]<<endl;

				// calculate the mse from 5 points of each side
				for (int j=0; j<5; j++){
					//cout<<coordinates[l][0][0]+xSubRange/4*j<<"  ";
					sum += pow(subImage[l][coordinates[l][0][0]+xSubRange/4*j][coordinates[l][0][1]+ySubRange/4*j]
								-mainImage[main_coordinates[r][0][0]+xRange/4*j+(i-2)%2][main_coordinates[r][0][1]+yRange/4*j+(3-j)%2],2);	
				}
				//cout<<endl;
				if (sum<minSum){
					minSum=sum;
					cout<<"minSum "<<minSum<<"  ";
					cout<<"Block "<<r<<" Side"<<i<<endl;
				}
			}
		}
		cout<<endl;
	}
***/
	// get transform matrix
	vector<vector<double>> inVector={{1,1,1,1},{1,161,1,1},{161,161,1,1}};
	double xPixel,yPixel;
	vector<double> answer1,answer2;

	// int ind[3]={3,2,0};
	// int ind2[3]={1,0,2};

	for (int i=0; i<3; i++){
		inVector[i][3]=coordinates[0][(i+3)%4][0];
	}
	answer1 = gaussianElimination(inVector);
	for (int i=0; i<3; i++){
		inVector[i][3]=coordinates[0][(i+3)%4][1];
	}
	answer2 = gaussianElimination(inVector);
	//TODO: Not considering boundary
	for (int i=1; i<161; i++){
		for (int j=1; j<161; j++){
			xPixel = answer1[0]*i+answer1[1]*j+answer1[2]+exp(-10);
			yPixel = answer2[0]*i+answer2[1]*j+answer2[2]+exp(-10);
			double value =(ceil(xPixel)-xPixel)*(ceil(yPixel)-yPixel)*subImage[0][(int)floor(xPixel)][(int)floor(yPixel)]
				+(ceil(xPixel)-xPixel)*(yPixel-floor(yPixel))*subImage[0][(int)floor(xPixel)][(int)ceil(yPixel)]
				+(xPixel-floor(xPixel))*(ceil(yPixel)-yPixel)*subImage[0][(int)ceil(xPixel)][(int)floor(yPixel)]
				+(xPixel-floor(xPixel))*(yPixel-floor(yPixel))*subImage[0][(int)ceil(xPixel)][(int)ceil(yPixel)];
			mainImage[main_coordinates[1][0][0]+i-1][main_coordinates[1][0][1]+j-1]= (int)value;
		}
	}

	// change the boundary line by linear allocation
	for (int i=0;i<2;i++){
		for (int j=0; j<160; j++){
			mainImage[main_coordinates[1][0][0]+i][main_coordinates[1][0][1]+j] = 
				(int)((double)mainImage[main_coordinates[1][0][0]-1][main_coordinates[1][0][1]+j]+ 
					(double)(i+1)/3* (int)(mainImage[main_coordinates[1][0][0]+2][main_coordinates[1][0][1]+j]-mainImage[main_coordinates[1][0][0]-1][main_coordinates[1][0][1]+j]));
			mainImage[main_coordinates[1][3][0]+i][main_coordinates[1][3][1]+j] = 
				(int)((double)mainImage[main_coordinates[1][3][0]-1][main_coordinates[1][3][1]+j]+ 
					(double)(i+1)/3* (int)(mainImage[main_coordinates[1][3][0]+2][main_coordinates[1][3][1]+j]-mainImage[main_coordinates[1][3][0]-1][main_coordinates[1][3][1]+j]));
		}
	}
	
	inVector={{1,1,1,1},{1,163,1,1},{163,163,1,1}};
	for (int i=0; i<3; i++){
		inVector[i][3]=coordinates[1][(i+2)%4][0];
	}
	answer1 = gaussianElimination(inVector);
	for (int i=0; i<3; i++){
		inVector[i][3]=coordinates[1][(i+2)%4][1];
	}
	answer2 = gaussianElimination(inVector);
	for (int i=3; i<163; i++){
		for (int j=3; j<163; j++){
			xPixel = answer1[0]*i+answer1[1]*j+answer1[2]+exp(-10);
			yPixel = answer2[0]*i+answer2[1]*j+answer2[2]+exp(-10);
			double k =(ceil(xPixel)-xPixel)*(ceil(yPixel)-yPixel)*subImage[1][(int)floor(xPixel)][(int)floor(yPixel)]
				+(ceil(xPixel)-xPixel)*(yPixel-floor(yPixel))*subImage[1][(int)floor(xPixel)][(int)ceil(yPixel)]
				+(xPixel-floor(xPixel))*(ceil(yPixel)-yPixel)*subImage[1][(int)ceil(xPixel)][(int)floor(yPixel)]
				+(xPixel-floor(xPixel))*(yPixel-floor(yPixel))*subImage[1][(int)ceil(xPixel)][(int)ceil(yPixel)];
			mainImage[main_coordinates[0][0][0]+i-3][main_coordinates[0][0][1]+j-3]= (int)k;
		}
	}

	inVector={{1,1,1,1},{1,162,1,1},{162,162,1,1}};
	for (int i=0; i<3; i++){
		inVector[i][3]=coordinates[2][i%4][0];
	}
	answer1 = gaussianElimination(inVector);
	for (int i=0; i<3; i++){
		inVector[i][3]=coordinates[2][i%4][1];
	}
	answer2 = gaussianElimination(inVector);
	for (int i=2; i<162; i++){
		for (int j=2; j<162; j++){
			xPixel = answer1[0]*i+answer1[1]*j+answer1[2]+exp(-10);
			yPixel = answer2[0]*i+answer2[1]*j+answer2[2]+exp(-10);
			double k =(ceil(xPixel)-xPixel)*(ceil(yPixel)-yPixel)*subImage[2][(int)floor(xPixel)][(int)floor(yPixel)]
				+(ceil(xPixel)-xPixel)*(yPixel-floor(yPixel))*subImage[2][(int)floor(xPixel)][(int)ceil(yPixel)]
				+(xPixel-floor(xPixel))*(ceil(yPixel)-yPixel)*subImage[2][(int)ceil(xPixel)][(int)floor(yPixel)]
				+(xPixel-floor(xPixel))*(yPixel-floor(yPixel))*subImage[2][(int)ceil(xPixel)][(int)ceil(yPixel)];
			mainImage[main_coordinates[2][0][0]+i-2][main_coordinates[2][0][1]+j-2]= (int)k;
		}
	}




	if (!(file=fopen("filled_lighthouse.raw","wb"))) {
		cout << "Cannot open file: tiger_gray.raw"<< endl;
		exit(1);
	}
	fwrite(mainImage, sizeof(unsigned char), width*height, file);

	return 0;
}

// check four coordinates (TODO: assume it won't appear in four sides)
// assumption : background is white, or change 255 to 0 and four corners are not white
vector<vector<int>> findCoordinates(unsigned char *input_image){
	vector<vector<int>> coordinates(4,vector<int>(2,0));
	int xmin=256, xmax=0, ymin=256,ymax=0;
	for (int i=1; i<width/2-1; i++){
		for (int j=1; j<height/2-1; j++){
			if (input_image[i*width/2+j] != 255){
				if ((input_image[(i-1)*width/2+j]==255||input_image[(i+1)*width/2+j]==255)&&
					(input_image[i*width/2+j-1]==255||input_image[i*width/2+j+1]==255)){
					if (i<xmin){
						xmin = i;
						coordinates[0][0]=i;
						coordinates[0][1]=j;
					}
					if (j>ymax){
						ymax = j;
						coordinates[1][0]=i;
						coordinates[1][1]=j;
					}
					if (i>xmax){
						xmax = i;
						coordinates[2][0]=i;
						coordinates[2][1]=j;
					}
					if (j<ymin){
						ymin = j;
						coordinates[3][0]=i;
						coordinates[3][1]=j;
					}
				}
			}
		}
	}
	// ensure the no-rotation case is included
	if (coordinates[0]==coordinates[3]){
		coordinates[3][0]=xmax;
		coordinates[3][1]=ymin;
		coordinates[2][0]=xmax;
		coordinates[2][1]=ymax;
	}

	for (int i=-3; i<=3;i++){
		if (input_image[(coordinates[0][0])*width/2+coordinates[0][1]+i]<input_image[coordinates[0][0]*width/2+coordinates[0][1]]){
			coordinates[0][1]+=i;
		}
		if (input_image[(coordinates[2][0])*width/2+coordinates[2][1]+i]<input_image[coordinates[2][0]*width/2+coordinates[2][1]]){
			coordinates[2][1]+=i;
		}
		if (input_image[(coordinates[1][0]+i)*width/2+coordinates[1][1]]<input_image[coordinates[1][0]*width/2+coordinates[1][1]]){
			coordinates[1][0]+=i;
		}
		if (input_image[(coordinates[3][0]+i)*width/2+coordinates[3][1]]<input_image[coordinates[3][0]*width/2+coordinates[3][1]]){
			coordinates[3][0]+=i;
		}
	}


	return coordinates;
}

vector<double> gaussianElimination(vector<vector<double>> inVector){
	int rows=inVector.size();
	int cols=inVector[0].size();
	vector<double> answer(rows,0.0);
	if (cols-rows == 1){
		//tranform to diagonal matrix
		for (int k=0; k<rows-1; k++){
			for (int i=k+1; i<rows; i++){
				double coef1=-inVector[i][k]/inVector[k][k];
				for (int j=0; j<cols; j++){
					inVector[i][j]+= coef1*inVector[k][j];
				}
			}
		}
		// solve the equation
		for (int k=rows-1; k>0; k--){
			for (int i=k-1; i>=0; i--){
				double coef2=-inVector[i][k]/inVector[k][k];
				// cout<<coef2<<endl;
				for (int j=cols-1; j>=0; j--){
					inVector[i][j]+= coef2*inVector[k][j];
				}
			}
			double k1=1/inVector[k][k];
			double k2=1/inVector[k-1][k-1];
			for (int j=0; j<cols; j++){
				inVector[k][j] *= k1 ;
				inVector[k-1][j] *= k2;
			}
		}
	}



	// output last second column as the solution
	for (int i=0; i<rows; i++){
		answer[i]=inVector[i][cols-1];
	}

	return answer;
}