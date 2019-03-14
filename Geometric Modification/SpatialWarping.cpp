#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
int width = 512;
int height = 512;

vector<vector<double>> initVector(vector<vector<int>>,vector<vector<int>>, int k);
vector<double> gaussianElimination(vector<vector<double>> inVector);


int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;

	
	// Check for proper syntax
	if (argc != 2){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image(512*512 gray image) " << endl;
		return 0;
	}
	

	// Allocate image data array
	unsigned char mainImage[width][height];
	unsigned char warpImage[width][height];

	// Read image into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(mainImage, sizeof(unsigned char), width*height, file);
	fclose(file);

	// change size if the number of blocks change, or just unspecify

	vector<vector<int>> allWarpPoints={{1,1},{1,512},{512,1},{512,512},
							{256,256},{256,257},{257,256},{257,257},
							{128,128},{128,385},{385,128},{385,385},
								{100,256},{256,100},{256,412},{412,256}}; // change last line for different heights
	vector<vector<int>> allOrigPoints={{1,1},{1,512},{512,1},{512,512},
							{256,256},{256,257},{257,256},{257,257},
							{128,128},{128,385},{385,128},{385,385},
								{1,256},{256,1},{256,512},{512,256}};

	// vector<vector<int>> transImage(512,vector<int>(512,0));



	// left part
	vector<vector<int>> warpPoints={allWarpPoints[0],allWarpPoints[8],allWarpPoints[4],
							allWarpPoints[10],allWarpPoints[2],allWarpPoints[13]};
	vector<vector<int>> origPoints={allOrigPoints[0],allOrigPoints[8],allOrigPoints[4],
							allOrigPoints[10],allOrigPoints[2],allOrigPoints[13]};
						
	vector<vector<double>> inVector = initVector(warpPoints,origPoints,0);
	vector<double> answerX = gaussianElimination(inVector);
	inVector = initVector(warpPoints,origPoints,1);
	vector<double> answerY = gaussianElimination(inVector);

	double xPixel;
	double yPixel;
	for (int i=1; i<width+1; i++){
		for (int j=1; j<(i<257?i:514-i); j++){
			if ((pow(i-256,2)+pow(j+277.68,2))>pow(377.68,2)){
				xPixel = answerX[0]+answerX[1]*i+answerX[2]*j+answerX[3]*pow(i,2)
						+answerX[4]*i*j+answerX[5]*pow(j,2)+exp(-20);
				yPixel = answerY[0]+answerY[1]*i+answerY[2]*j+answerY[3]*pow(i,2)
						+answerY[4]*i*j+answerY[5]*pow(j,2)+exp(-20);
				double val = (ceil(xPixel)-xPixel)*(ceil(yPixel)-yPixel)*mainImage[(int)floor(xPixel)][(int)floor(yPixel)]
							+(ceil(xPixel)-xPixel)*(yPixel-floor(yPixel))*mainImage[(int)floor(xPixel)][(int)ceil(yPixel)]
							+(xPixel-floor(xPixel))*(ceil(yPixel)-yPixel)*mainImage[(int)ceil(xPixel)][(int)floor(yPixel)]
							+(xPixel-floor(xPixel))*(yPixel-floor(yPixel))*mainImage[(int)ceil(xPixel)][(int)ceil(yPixel)];
				warpImage[i-1][j-1] = (int)val;
			}
			else{
				warpImage[i-1][j-1] =255;
			}
		}
	}

	// top part
	warpPoints={allWarpPoints[1],allWarpPoints[9],allWarpPoints[5],
							allWarpPoints[8],allWarpPoints[0],allWarpPoints[12]};
	origPoints={allOrigPoints[1],allOrigPoints[9],allOrigPoints[5],
							allOrigPoints[8],allOrigPoints[0],allOrigPoints[12]};
						
	inVector = initVector(warpPoints,origPoints,0);
	answerX = gaussianElimination(inVector);
	inVector = initVector(warpPoints,origPoints,1);
	answerY = gaussianElimination(inVector);
	for (int i=1; i<width/2+1; i++){
		for (int j=i; j<513-i; j++){
			if ((pow(i+277.68,2)+pow(j-256,2))>pow(377.68,2)){
				xPixel = answerX[0]+answerX[1]*i+answerX[2]*j+answerX[3]*pow(i,2)
						+answerX[4]*i*j+answerX[5]*pow(j,2)+exp(-20);
				yPixel = answerY[0]+answerY[1]*i+answerY[2]*j+answerY[3]*pow(i,2)
						+answerY[4]*i*j+answerY[5]*pow(j,2)+exp(-20);
				double val = (ceil(xPixel)-xPixel)*(ceil(yPixel)-yPixel)*mainImage[(int)floor(xPixel)][(int)floor(yPixel)]
							+(ceil(xPixel)-xPixel)*(yPixel-floor(yPixel))*mainImage[(int)floor(xPixel)][(int)ceil(yPixel)]
							+(xPixel-floor(xPixel))*(ceil(yPixel)-yPixel)*mainImage[(int)ceil(xPixel)][(int)floor(yPixel)]
							+(xPixel-floor(xPixel))*(yPixel-floor(yPixel))*mainImage[(int)ceil(xPixel)][(int)ceil(yPixel)];
				warpImage[i-1][j-1] = (int)val;
			}
			else{
				warpImage[i-1][j-1] =255;
			}
		}
	}

	//right part
	warpPoints={allWarpPoints[3],allWarpPoints[11],allWarpPoints[7],
							allWarpPoints[9],allWarpPoints[1],allWarpPoints[14]};
	origPoints={allOrigPoints[3],allOrigPoints[11],allOrigPoints[7],
							allOrigPoints[9],allOrigPoints[1],allOrigPoints[14]};
						
	inVector = initVector(warpPoints,origPoints,0);
	answerX = gaussianElimination(inVector);
	inVector = initVector(warpPoints,origPoints,1);
	answerY = gaussianElimination(inVector);
	for (int i=1; i<width+1; i++){
		for (int j=(i>256?i:513-i); j<height+1; j++){
			if ((pow(i-256,2)+pow(j-790.68,2))>pow(377.68,2)){
				xPixel = answerX[0]+answerX[1]*i+answerX[2]*j+answerX[3]*pow(i,2)
						+answerX[4]*i*j+answerX[5]*pow(j,2)+exp(-20);
				yPixel = answerY[0]+answerY[1]*i+answerY[2]*j+answerY[3]*pow(i,2)
						+answerY[4]*i*j+answerY[5]*pow(j,2)+exp(-20);
				double val = (ceil(xPixel)-xPixel)*(ceil(yPixel)-yPixel)*mainImage[(int)floor(xPixel)][(int)floor(yPixel)]
							+(ceil(xPixel)-xPixel)*(yPixel-floor(yPixel))*mainImage[(int)floor(xPixel)][(int)ceil(yPixel)]
							+(xPixel-floor(xPixel))*(ceil(yPixel)-yPixel)*mainImage[(int)ceil(xPixel)][(int)floor(yPixel)]
							+(xPixel-floor(xPixel))*(yPixel-floor(yPixel))*mainImage[(int)ceil(xPixel)][(int)ceil(yPixel)];
				warpImage[i-1][j-1] = (int)val;
			}
			else{
				warpImage[i-1][j-1] =255;
			}
		}
	}

	//bottom part
	warpPoints={allWarpPoints[2],allWarpPoints[10],allWarpPoints[6],
							allWarpPoints[11],allWarpPoints[3],allWarpPoints[15]};
	origPoints={allOrigPoints[2],allOrigPoints[10],allOrigPoints[6],
							allOrigPoints[11],allOrigPoints[3],allOrigPoints[15]};
						
	inVector = initVector(warpPoints,origPoints,0);
	answerX = gaussianElimination(inVector);
	inVector = initVector(warpPoints,origPoints,1);
	answerY = gaussianElimination(inVector);
	for (int i=257; i<width+1; i++){
		for (int j=513-i; j<i; j++){
			if ((pow(i-790.68,2)+pow(j-256,2))>pow(377.68,2)){
				xPixel = answerX[0]+answerX[1]*i+answerX[2]*j+answerX[3]*pow(i,2)
						+answerX[4]*i*j+answerX[5]*pow(j,2)+exp(-20);
				yPixel = answerY[0]+answerY[1]*i+answerY[2]*j+answerY[3]*pow(i,2)
						+answerY[4]*i*j+answerY[5]*pow(j,2)+exp(-20);
				double val = (ceil(xPixel)-xPixel)*(ceil(yPixel)-yPixel)*mainImage[(int)floor(xPixel)][(int)floor(yPixel)]
							+(ceil(xPixel)-xPixel)*(yPixel-floor(yPixel))*mainImage[(int)floor(xPixel)][(int)ceil(yPixel)]
							+(xPixel-floor(xPixel))*(ceil(yPixel)-yPixel)*mainImage[(int)ceil(xPixel)][(int)floor(yPixel)]
							+(xPixel-floor(xPixel))*(yPixel-floor(yPixel))*mainImage[(int)ceil(xPixel)][(int)ceil(yPixel)];
				warpImage[i-1][j-1] = (int)val;
			}
			else{
				warpImage[i-1][j-1] =255;
			}
		}
	}




	


	if (!(file=fopen("warping_hat.raw","wb"))) {
		cout << "Cannot open file: tiger_gray.raw"<< endl;
		exit(1);
	}
	fwrite(warpImage, sizeof(unsigned char), width*height, file);


	return 0;
}


vector<vector<double>> initVector(vector<vector<int>> warpPoints,vector<vector<int>> origPoints, int a){
	int rows=origPoints.size();
	int cols=rows+1;
	vector<vector<double>> outVector(rows,vector<double>(cols,0.0));
	if(a==0 || a ==1){
		for (int i=0; i<origPoints.size(); i++){
			outVector[i][0]=1;
			outVector[i][1]=warpPoints[i][0];
			outVector[i][2]=warpPoints[i][1];
			outVector[i][3]=pow(warpPoints[i][0],2);
			outVector[i][4]=warpPoints[i][0]*warpPoints[i][1];
			outVector[i][5]=pow(warpPoints[i][1],2);
			outVector[i][6]=origPoints[i][a];
		}
	}
	return outVector;
}


vector<double> gaussianElimination(vector<vector<double>> inVector){
	int rows=inVector.size();
	int cols=inVector[0].size();
	vector<double> answer(rows);
	if (cols-rows == 1){
		// find the max row
		for(int i=0; i<rows; i++){
			double maxVal = abs(inVector[i][i]);
			int maxRow = i;
			for (int k=i+1; k<rows; k++){
				maxVal = abs(inVector[k][i]);
				maxRow = k;
			}
		
			// swap with the max row
			for (int k=i; k<cols; k++){
				double temp = inVector[maxRow][k];
				inVector[maxRow][k] = inVector[i][k];
				inVector[i][k] = temp;
			}
			//tranform to diagonal matrix
			for (int k=i+1; k<rows; k++){
				double coef = - inVector[k][i]/inVector[i][i];
				for (int j=i; j<cols; j++){
					if (i==j){
						inVector[k][j] = 0;
					}
					else{
						inVector[k][j] += coef * inVector[i][j];
					}
				}
			}
		}

		// solve the equation
		for (int k=rows-1; k>0; k--){
			answer[k] = inVector[k][rows]/inVector[k][k];
			for (int i=k-1; i>=0; i--){
				inVector[i][rows] -= inVector[i][k] * answer[k];
			}
		}
	}


	return answer;
}

