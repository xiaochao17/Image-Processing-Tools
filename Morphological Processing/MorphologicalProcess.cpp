#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
int width = 375;
int height = 375;

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

vector<vector<int>> table3={{0,0,0,0,0,0,0,1},{0,0,0,0,0,1,0,0},{0,1,0,0,0,0,0,0},{0,0,0,1,0,0,0,0},
							  {0,0,0,0,0,0,1,0},{1,0,0,0,0,0,0,0},{0,0,0,0,1,0,0,0},{0,0,1,0,0,0,0,0},
							  {1,0,1,0,0,0,0,0},{0,0,1,0,1,0,0,0},{1,0,0,0,0,0,1,0},{0,0,0,0,1,0,1,0},
							  {5,5,1,1,1,5,5,5},{1,5,5,5,5,5,1,1},{1,5,1,5,1,5,5,5},{5,5,1,5,1,5,1,5},
							  {1,5,5,5,1,5,1,5},{1,5,1,5,5,5,1,5},{5,1,5,1,5,6,7,4},{7,4,5,1,5,1,5,6},
							  {5,6,7,4,5,1,5,1},{5,1,5,6,7,4,5,1},{1,0,1,5,0,1,0,5},{0,5,1,0,1,5,0,1},
							  {0,1,0,5,1,0,1,5},{1,5,0,1,0,5,1,0}};
int A=2,B=3,C=4,D=5,E=6,F=7,G=8;
vector<vector<int>> table4={{E,F,0,A,B,C,0,D},{0,A,B,C,0,D,E,F},{0,G,A,B,C,G,0,1},
							{0,1,0,G,A,B,C,G},{C,G,0,1,0,G,A,B},{A,B,C,G,0,1,0,G}};


vector<vector<unsigned char>> thinning(vector<vector<unsigned char>> inputImg);
vector<vector<unsigned char>> shrinking(vector<vector<unsigned char>> inputImg);
vector<vector<unsigned char>> skeletonize(vector<vector<unsigned char>> inputImg);

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;	
	// Check for proper syntax
	if (argc != 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name pattern1.raw pattern2.raw pattern3.raw pattern4.raw (375*375 gray images)" << endl;
		return 0;
	}
	// Allocate image data array
	unsigned char patterns[4][width][height];
	// Read image into image data matrix
	for (int i=0; i<4; i++){
		if (!(file=fopen(argv[i+1],"rb"))) {
			cout << "Cannot open file: " << argv[i+1] <<endl;
			exit(1);
		}
		fread(patterns[i], sizeof(unsigned char), width*height, file);
		fclose(file);
	}

	unsigned char outpatterns[3][width][height];
	vector<vector<vector<unsigned char>>> imageVector(4,vector<vector<unsigned char>>(width,vector<unsigned char>(height,0)));
	vector<vector<vector<unsigned char>>> outVector(3,vector<vector<unsigned char>>(width,vector<unsigned char>(height,0)));
	
	for (int k=0; k<4; k++){
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				imageVector[k][i][j] = patterns[k][i][j];
			}
		}
		outVector[0]=thinning(imageVector[k]);
		outVector[1]=shrinking(imageVector[k]);
		outVector[2]=skeletonize(imageVector[k]);

		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				outpatterns[0][i][j] = outVector[0][i][j];
				outpatterns[1][i][j] = outVector[1][i][j];
				outpatterns[2][i][j] = outVector[2][i][j];
			}
		}
		string filename = "pat"+to_string(k)+"-thin.raw";
		char char_array1[filename.length()+1];
		strcpy(char_array1,filename.c_str());
		if (!(file=fopen(char_array1,"wb"))) {
			cout << "Cannot open file"<< endl;
			exit(1);
		}
		fwrite(outpatterns[0], sizeof(unsigned char), width*height, file);
		filename = "pat"+to_string(k)+"-shrink.raw";
		char char_array2[filename.length()+1];
		strcpy(char_array2,filename.c_str());
		if (!(file=fopen(char_array2,"wb"))) {
			cout << "Cannot open file"<< endl;
			exit(1);
		}
		fwrite(outpatterns[1], sizeof(unsigned char), width*height, file);
		filename = "pat"+to_string(k)+"-skeleton.raw";
		char char_array3[filename.length()+1];
		strcpy(char_array3,filename.c_str());
		if (!(file=fopen(char_array3,"wb"))) {
			cout << "Cannot open file"<< endl;
			exit(1);
		}
		fwrite(outpatterns[2], sizeof(unsigned char), width*height, file);


	}












	return 0;
}


vector<vector<unsigned char>> thinning(vector<vector<unsigned char>> inputImg){
	int flag = 0,iter=0;
	while(flag==0 ){
		vector<vector<unsigned char>> mVector(width,vector<unsigned char>(height,0));
		for (int i=1; i<width-1; i++){
			for (int j=1; j< height-1; j++){
				if (inputImg[i][j]==255){
					int bond=0;
					int block[8] = {inputImg[i][j+1],inputImg[i-1][j+1],inputImg[i-1][j],inputImg[i-1][j-1],
								inputImg[i][j-1],inputImg[i+1][j-1],inputImg[i+1][j],inputImg[i+1][j+1]};
					bond = (block[0]+block[2]+block[4]+block[6])/255*2+(block[1]+block[3]+block[5]+block[7])/255;
					if (bond==4){
						int flag2=0;
						for (int k=0; k<table1[3].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[3][k][n]){
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
							for (int k=0; k<table1[4].size(); k++){
								int mark=0;
								for (int n=0; n<8; n++){
									if (block[n]!=table1[4][k][n]){
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
		for (int i=1; i<width-1; i++){
			for (int j=1; j< height-1; j++){
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
	cout<<"thinning iterations: "<<iter<<endl;

	return inputImg;
}

vector<vector<unsigned char>> shrinking(vector<vector<unsigned char>> inputImg){
	int flag = 0,iter=0;
	while(flag==0 ){
		vector<vector<unsigned char>> mVector(width,vector<unsigned char>(height,0));
		for (int i=1; i<width-1; i++){
			for (int j=1; j< height-1; j++){
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
		for (int i=1; i<width-1; i++){
			for (int j=1; j< height-1; j++){
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


vector<vector<unsigned char>> skeletonize(vector<vector<unsigned char>> inputImg){
	int flag = 0,iter=0;
	while(flag==0 ){
		vector<vector<unsigned char>> mVector(width,vector<unsigned char>(height,0));
		for (int i=1; i<width-1; i++){
			for (int j=1; j< height-1; j++){
				if (inputImg[i][j]==255){
					int bond=0;
					int block[8] = {inputImg[i][j+1],inputImg[i-1][j+1],inputImg[i-1][j],inputImg[i-1][j-1],
								inputImg[i][j-1],inputImg[i+1][j-1],inputImg[i+1][j],inputImg[i+1][j+1]};
					bond = (block[0]+block[2]+block[4]+block[6])/255*2+(block[1]+block[3]+block[5]+block[7])/255;
					if (bond==4){
						int flag2=0;
						for (int k=0; k<table1[3].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[3][k][n]){
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
							for (int k=0; k<table1[4].size(); k++){
								int mark=0;
								for (int n=0; n<8; n++){
									if (block[n]!=table1[4][k][n]){
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
					if (bond==11){
						for (int k=0; k<table1[13].size(); k++){
							int mark=0;
							for (int n=0; n<8; n++){
								if (block[n]!=table1[13][k][n]){
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
		for (int i=1; i<width-1; i++){
			for (int j=1; j< height-1; j++){
				if (mVector[i][j]==1){
					int block[8] = {mVector[i][j+1],mVector[i-1][j+1],mVector[i-1][j],mVector[i-1][j-1],
								mVector[i][j-1],mVector[i+1][j-1],mVector[i+1][j],mVector[i+1][j+1]};
					int flag2=0;
					for (int k=0; k<table3.size(); k++){
						int mark=0;
						for (int n=0; n<8; n++){
							if (table3[k][n]!=5 &&  table3[k][n]!=4 && table3[k][n]!=7){
								if (table3[k][n]==6){
									if (block[n]==0 && block[(n+1)%8]==0 && block[(n+2)%8]==0){
										break;
									}
								}
								else{
									if (block[n]!=table3[k][n]){
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

	vector<vector<int>> pVector(width,vector<int>(height,0));

	for (int i=1; i<width-1; i++){
		for (int j=1; j< height-1; j++){
			if (inputImg[i][j]==0){
				int block[8] = {inputImg[i][j+1]/255,inputImg[i-1][j+1]/255,inputImg[i-1][j]/255,inputImg[i-1][j-1]/255,
								inputImg[i][j-1]/255,inputImg[i+1][j-1]/255,inputImg[i+1][j]/255,inputImg[i+1][j+1]/255};
				int flag3=0;
				int mark=0;
				if(!((block[1]==1&&block[3]==1)||(block[5]==1&&block[3]==1)||(block[1]==1&&block[7]==1))){
					for (int n=0; n<8; n++){
						if (((table4[0][n]==2 || table4[0][n]==5) && table4[0][(n-1)%8]==0 && table4[0][(n+1)%8]==0)||
							((table4[1][n]==2 || table4[1][n]==5) && table4[1][(n-1)%8]==0 && table4[1][(n+1)%8]==0)){
							if (block[n]==1 || block[(n+1)%8]==1 || block[(n+2)%8]==1){
								inputImg[i][j]=255;
								flag3=1;
								break;
							}
						}
					}
				}
				if(flag3==0){
					for (int k=2; k<table4.size();k++){
						mark=0;
						for (int n=0; n<8; n++){
							if (table4[k][n]==2){
								if(block[n]==0 && block[(n+1)%8]==0 && block[(n+2)%8]==0){
									break;
								}
							}
							else if(table4[k][n]==0||table4[k][n]==1){
								if(block[n]!=table4[k][n]){
									break;
								}
							}
							mark++;
						}
						if (mark==8){
							inputImg[i][j]=255;
							break;
						}
					}
				}				
			}


		}
	}


	cout<<"skeletonizing iterations: "<<iter<<endl;
	return inputImg;
}
