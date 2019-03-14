#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>

using namespace std;
int width = 500;
int height = 690;

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
	unsigned char imageData[width][height][3];
	// Read image into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(imageData, sizeof(unsigned char), width*height*3, file);
	fclose(file);

	unsigned char outpatterns[width][height];


 	int bgR=imageData[0][0][0];
 	int bgG=imageData[0][0][1];
 	int bgB=imageData[0][0][2];

	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			if (abs(bgR - imageData[i][j][0])>30 || abs(bgG - imageData[i][j][1])>30 || abs(bgB - imageData[i][j][2])>30){
				outpatterns[i][j]=255;
			}
			else{
				outpatterns[i][j]=0;
			}
		}
	}

	// find the coordinates of each sub image - horizontal
	int flag1=0, flag2=0;
	vector<int> index1,index2;
	for (int i=0; i<width; i++){
		int j=0;
		while(outpatterns[i][j]==0&&j<height){
			j++;
		}
		if (j<height){
			if (flag1==0 ){
				flag1=1;
				if (i!=0){
					index1.push_back(i);
				}
				flag2=0;
			}
		}
		else{
			if(flag2==0){
				flag2=1;
				if (i!=0){
					index2.push_back(i);
				}
				flag1=0;
			}
		}
	}


	// find the coordinates of each sub image - vertical
	int flag3=0,typeCount=0;
	vector<vector<int>> index3(index1.size());

	for (int i=0; i<index1.size(); i++){
		int colCount=0;
		index3[i].push_back(1);
		for (int n=0; n<height; n++){
			int j= index1[i]-1;
			while(outpatterns[j][n]==0&&j<index2[i]){
				j++;
			}
			
			if (j==index2[i]){
				colCount++;
				if (colCount>=20 && flag3==0){
					flag3=1;
					if (n!=19){
						index3[i].push_back(n);
						typeCount++;
					}
				}
			}
			else{
				colCount=0;
				flag3=0;
			}
		}

	}

	// for (int i=0; i<index1.size(); i++){
	// 	cout<<index1[i]<<" ";
	// }
	// cout<<endl;
	// for (int i=0; i<index2.size(); i++){
	// 	cout<<index2[i]<<" ";
	// }
	// cout<<endl;
	// for (int i=0; i<index3.size(); i++){
	// 	for (int j=0; j<index3[i].size(); j++){
	// 	cout<<index3[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// cout<<endl;



	// get rid of defects
	int flag=0;
	while(flag==0){
		flag=1;
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				if (outpatterns[i][j]==0){
					int sum=0;
					for (int m=-1; m<2; m++){
						for (int n=-1; n<2; n++){
							sum +=outpatterns[i+m][j+n];
						}
					}
					if (sum>=(255*5)){
						flag=0;
						outpatterns[i][j]=255;
					}
				}


			}
		}
	}


	// shrink the image
	vector<vector<unsigned char>> outVector(width,vector<unsigned char>(height,0));
	vector<vector<unsigned char>> imageVector(width,vector<unsigned char>(height,0));
	unsigned char shrinkPat[width][height];
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			imageVector[i][j] = outpatterns[i][j];
		}
	}
	outVector=shrinking(imageVector);
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			shrinkPat[i][j] = outVector[i][j];
		}
	}

	int num=0;
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			if (shrinkPat[i][j]==255){
				num++;
			}
		}
	}
	cout<<"the total number of rice grains is "<<num<<endl;

	map<double, int,less <double>> riceSize;
	int partNum=0;

	for (int k=0; k<index1.size(); k++){
		for (int l=0; l<index3[k].size()-1; l++){
			partNum++;
			int sizeNum=0;
			int countNum=0;
			for(int i=index1[k]; i<index2[k]; i++){
				for (int j=index3[k][l]; j<index3[k][l+1]; j++){
					if (outpatterns[i][j]==255){
						sizeNum++;
					}
					if (shrinkPat[i][j]==255){
						countNum++;
					}

				}

			}
			riceSize.insert({ (double)sizeNum/countNum, partNum });
		}
	}

	cout<<"Ranking the grain's size(by average pixels size) in ascending order:"<<endl;
	map<double,int> :: iterator it; 
	for (it=riceSize.begin() ; it!=riceSize.end() ; it++){
		cout << "Rice " << (*it).second << " (Size:"
             << (*it).first << ")" << endl;
	}




	if (!(file=fopen("ricemilk.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(outpatterns, sizeof(unsigned char), width*height, file);





	return 0;
}



vector<vector<unsigned char>> shrinking(vector<vector<unsigned char>> inputImg){
	int flag = 0;//,iter=0;
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
		//iter++;
	}
	//cout<<"shrinking iterations: "<<iter<<endl;

	return inputImg;
}

