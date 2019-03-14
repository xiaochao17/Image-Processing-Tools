#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
int width = 691;
int height = 550;

int T=255;



vector<vector<vector<int>>> table1={{{0,T,0,0,0,0,0,0},{0,0,0,T,0,0,0,0},{0,0,0,0,0,T,0,0},{0,0,0,0,0,0,0,T}},
								{{T,0,0,0,0,0,0,0},{0,0,T,0,0,0,0,0},{0,0,0,0,T,0,0,0},{0,0,0,0,0,0,T,0}},
								{{T,T,0,0,0,0,0,0},{0,T,T,0,0,0,0,0},{0,0,T,T,0,0,0,0},{0,0,0,T,T,0,0,0},{0,0,0,0,T,T,0,0}
									,{0,0,0,0,0,T,T,0},{0,0,0,0,0,0,T,T},{T,0,0,0,0,0,0,T}},
								{{T,0,T,0,0,0,0,0},{0,0,T,0,T,0,0,0},{0,0,0,0,T,0,T,0},{T,0,0,0,0,0,T,0}},
								{{T,T,0,0,0,0,0,T},{0,T,T,T,0,0,0,0},{0,0,0,T,T,T,0,0},{0,0,0,0,0,T,T,T}},
								{{T,0,T,T,0,0,0,0},{T,0,T,0,0,0,0,T},{0,T,T,0,T,0,0,0},{T,T,0,0,0,0,T,0}},
								{{T,T,T,0,0,0,0,0},{0,0,T,T,T,0,0,0},{0,0,0,0,T,T,T,0},{T,0,0,0,0,0,T,T}},
								{{T,0,T,T,0,0,0,T},{0,T,T,0,T,T,0,0}},
								{{T,T,T,T,0,0,0,0},{T,T,T,0,0,0,0,T},{0,T,T,T,T,0,0,0},{0,0,T,T,T,T,0,0},
									{0,0,0,T,T,T,T,0},{0,0,0,0,T,T,T,T},{T,0,0,0,0,T,T,T},{T,T,0,0,0,0,T,T}},
								{{T,T,T,T,0,0,0,T},{0,T,T,T,T,T,0,0},{0,0,0,T,T,T,T,T},{T,T,0,0,0,T,T,T}},
								{{T,T,T,0,0,0,T,T},{T,T,T,T,T,0,0,0},{0,0,T,T,T,T,T,0},{T,0,0,0,T,T,T,T}},
								{{T,T,T,T,0,0,T,T},{T,T,T,0,0,T,T,T},{T,T,T,T,T,T,0,0},{T,T,T,T,T,0,0,T},{0,T,T,T,T,T,T,0}
									,{0,0,T,T,T,T,T,T},{T,0,0,T,T,T,T,T},{T,T,0,0,T,T,T,T}},
								{{T,T,T,T,0,T,T,T},{T,T,T,T,T,T,0,T},{0,T,T,T,T,T,T,T},{T,T,0,T,T,T,T,T}},
								{{T,T,T,T,T,0,T,T},{T,T,T,T,T,T,T,0},{T,0,T,T,T,T,T,T},{T,T,T,0,T,T,T,T}}};
//A=2/6,B=3/7,C=4,D=5;
vector<vector<int>> table2={{0,1,0,0,0,0,0,0},{0,0,0,1,0,0,0,0},{0,0,0,0,0,0,1,0},{1,0,0,0,0,0,0,0},
							  {1,1,0,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,0,1,1,0,0,0,0},{0,0,0,1,1,0,0,0},
							  {0,0,0,0,1,1,0,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,0,1,1},{1,0,0,0,0,0,0,1},
							  {0,1,1,0,1,0,0,0},{1,0,1,1,0,0,0,0},{1,0,1,0,0,0,0,1},{1,1,0,0,0,0,1,0},
							  {2,1,3,0,0,1,0,0},{0,0,2,1,3,0,0,1},{0,1,0,0,2,1,3,0},{3,0,0,1,0,0,2,1},
							  {5,5,1,1,1,5,5,5},{1,0,1,5,1,5,0,0},{1,5,1,0,1,0,0,5},{1,5,0,0,1,0,1,5},
							  {1,0,0,5,1,5,1,0},{0,5,1,5,1,0,1,0},{0,0,1,0,1,5,1,5},{1,0,1,0,0,5,1,5},
							  {1,5,1,5,0,0,1,0},{5,1,5,1,5,6,7,4},{7,4,5,1,5,1,5,6},{5,6,7,4,5,1,5,1},
							  {5,1,5,6,7,4,5,1},{1,0,1,5,0,1,0,5},{0,5,1,0,1,5,0,1},{0,1,0,5,1,0,1,5},{1,5,0,1,0,5,1,0}};


vector<vector<unsigned char>> shrinking(vector<vector<unsigned char>> inputImg);

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;	
	// Check for proper syntax
	if (argc != 2){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name deerImage.raw " << endl;
		return 0;
	}
	// Allocate image data array
	unsigned char imageData[width][height];
	// Read image into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(imageData, sizeof(unsigned char), width*height, file);
	fclose(file);

	unsigned char outpatterns[width][height];
	unsigned char outpattern2[width][height];
	vector<vector<unsigned char>> imageVector(width+2,vector<unsigned char>(height+2,0));
	vector<vector<unsigned char>> outVector(width+2,vector<unsigned char>(height+2,0));
	



	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			imageVector[i+1][j+1] = 255-imageData[i][j];
			outpattern2[i][j] = imageData[i][j];
		}
	}

	for (int i=1;i<height+1;i++){
		imageVector[0][i]=imageData[0][i-1];
		imageVector[width+1][i]=imageData[width-1][i-1];
	}
	for (int i=0;i<width+2;i++){
		imageVector[i][0]=imageVector[i][1];
		imageVector[i][height+1]=imageVector[i][height];
	}

	outVector=shrinking(imageVector);
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			outpatterns[i][j] = outVector[i+1][j+1];
		}
	}


	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			if (outpatterns[i][j]==255){
				int sum=0;
				for (int m=-1; m<2; m++){
					for (int n=-1; n<2; n++){
						sum +=imageData[i+m][j+n];
					}
				}
				if (sum>=(255*7)){
					imageData[i][j]=255;
				}
			}

		}
	}
	int flag=0;
	while(flag==0){
		flag=1;
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				if (outpattern2[i][j]==0){
					int sum=0;
					for (int m=-1; m<2; m++){
						for (int n=-1; n<2; n++){
							sum +=outpattern2[i+m][j+n];
						}
					}
					if (sum>=(255*7)){
						flag=0;
						outpattern2[i][j]=255;
					}
				}


			}
		}
	}

	if (!(file=fopen("deer1.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(outpatterns, sizeof(unsigned char), width*height, file);

	if (!(file=fopen("deer2.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(imageData, sizeof(unsigned char), width*height, file);

	if (!(file=fopen("deer3.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(outpattern2, sizeof(unsigned char), width*height, file);



	return 0;
}



vector<vector<unsigned char>> shrinking(vector<vector<unsigned char>> inputImg){
	int flag = 0,iter=0;
	while(flag==0 ){
		vector<vector<unsigned char>> mVector(width+2,vector<unsigned char>(height+2,0));
		for (int i=1; i<width+1; i++){
			for (int j=1; j< height+1; j++){
				if (inputImg[i][j]==255){
					int bond=0;
					int block[8] = {inputImg[i][j+1],inputImg[i-1][j+1],inputImg[i-1][j],inputImg[i-1][j-1],
								inputImg[i][j-1],inputImg[i+1][j-1],inputImg[i+1][j],inputImg[i+1][j+1]};
					bond = (block[0]+block[2]+block[4]+block[6])/255*2+(block[1]+block[3]+block[5]+block[7])/255;
					if (bond==1){
						for (int k=0; k<table1[0].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[0][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								mVector[i][j]=1;
								break;
							}
						}
					}
					if (bond==2){
						for (int k=0; k<table1[1].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[1][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								mVector[i][j]=1;
								break;
							}
						}
					}
					if (bond==3){
						for (int k=0; k<table1[2].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[2][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								mVector[i][j]=1;
								break;
							}
						}
					}
					if (bond==4){
						for (int k=0; k<table1[4].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[4][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								mVector[i][j]=1;
								break;
							}
						}
					}
					if (bond==5){
						int flag2=0;
						for (int k=0; k<table1[5].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[5][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								flag2=1;
								mVector[i][j]=1;
								break;
							}
						}
						if (flag2==0){
							for (int k=0; k<table1[6].size(); k++){
								int mark=0;
								for (int n=0; n<8; n++){
									if (block[n]!=table1[6][k][n]){
										break;
									}
									mark++;
								}
								if (mark==8){
									flag2=1;
									mVector[i][j]=1;
									break;
								}
							}
						}

					}
					if (bond==6){
						int flag2=0;
						for (int k=0; k<table1[7].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[7][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								flag2=1;
								mVector[i][j]=1;
								break;
							}
						}
						if (flag2==0){
							for (int k=0; k<table1[8].size(); k++){
								int mark=0;
								for (int n=0; n<8; n++){
									if (block[n]!=table1[8][k][n]){
										break;
									}
									mark++;
								}
								if (mark==8){
									mVector[i][j]=1;
									break;
								}
							}
						}
					}
					if (bond==7){
						for (int k=0; k<table1[9].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[9][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								mVector[i][j]=1;
								break;
							}
						}
					}
					if (bond==8){
						for (int k=0; k<table1[10].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[10][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								mVector[i][j]=1;
								break;
							}
						}
					}
					if (bond==9){
						for (int k=0; k<table1[11].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[11][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								mVector[i][j]=1;
								break;
							}
						}
					}
					if (bond==10){
						for (int k=0; k<table1[12].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[12][k][n]){
									break;
								}
								mark++;
							}
							if (mark==8){
								mVector[i][j]=1;
								break;
							}
						}
					}
				}
			}
		}

		flag=1;
		for (int i=1; i<width+1; i++){
			for (int j=1; j< height+1; j++){
				if (mVector[i][j]==1){
					int block[8] = {mVector[i][j+1],mVector[i-1][j+1],mVector[i-1][j],mVector[i-1][j-1],
								mVector[i][j-1],mVector[i+1][j-1],mVector[i+1][j],mVector[i+1][j+1]};
					int flag2=0;
					for (int k=0; k<table2.size(); k++){
						int mark=0;
						for (int n=0; n<8; n++){
							if (table2[k][n]!=5 && table2[k][n]!=3 && table2[k][n]!=4 && table2[k][n]!=7){
								if (table2[k][n]==2){
									if (block[n]==0 && block[(n+2)%8]==0){
										break;
									}
								}
								else if (table2[k][n]==6){
									if (block[n]==0 && block[(n+1)%8]==0 && block[(n+2)%8]==0){
										break;
									}
								}
								else{
									if (block[n]!=table2[k][n]){
										break;
									}
								}
							}
							mark+=1;
						}
						if (mark==8){
							flag2=1;
							break;
						}
					}
					if (flag2==0){
						flag=0;
						inputImg[i][j]=0;
					}
				}
			}
		}
		iter++;
	}
	cout<<"shrinking iterations: "<<iter<<endl;

	return inputImg;
}

