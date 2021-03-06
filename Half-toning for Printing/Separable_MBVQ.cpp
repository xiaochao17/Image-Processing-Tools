
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <array>

using namespace std;
int channel=3;
int width = 375;
int height = 500;

vector<vector<vector<double>>> fs_error_diffusion(vector<vector<vector<double>>> pixel);
int MBVQ(int r, int g, int b);
vector<double> nearestV(int mbvq, double r, double g, double b);

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;

	
	// Check for proper syntax
	if (argc != 2){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name brid.raw " << endl;
		return 0;
	}
	
	// Allocate image data array
	unsigned char Imagedata[width][height][channel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height*channel, file);
	fclose(file);

	///////////////////////// floyd-steinberg /////////////////////////
	unsigned char halftone[width][height][channel];
	vector<vector<vector<double>>> pixel(width,vector<vector<double>>(height, vector<double>(3)));
	for(int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			for (int c=0;c<3;c++){
				pixel[i][j][c]=1-(double)Imagedata[i][j][c]/255;
			}
		}
	}


	vector<vector<vector<double>>> toning = fs_error_diffusion(pixel);
	//go back to rgb
	for(int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			for (int c=0;c<3;c++){
				halftone[i][j][c]=(1-toning[i][j][c])*255;
			}
		}
	}
	if (!(file=fopen("brid_separable.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(halftone, sizeof(unsigned char), width*height*channel, file);
	fclose(file);

	// using quadruples
	for(int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			for (int c=0;c<3;c++){
				pixel[i][j][c]=(double)Imagedata[i][j][c]/255;
			}
		}
	}
	int quad=0;
	vector<double> vert(3),error_3(3,0);
	vector<vector<vector<double>>> vertex_final(width,vector<vector<double>>(height, vector<double>(3)));
	for(int i=0;i<width;i++){
		if(i%2==0){
			for (int j=0;j<height;j++){
				quad=MBVQ((int)Imagedata[i][j][0],(int)Imagedata[i][j][1],(int)Imagedata[i][j][2]);
				vert=nearestV(quad,pixel[i][j][0],pixel[i][j][1],pixel[i][j][2]);
				vertex_final[i][j]=vert;
				error_3= {pixel[i][j][0]-vert[0],pixel[i][j][1]-vert[1],pixel[i][j][2]-vert[2]};
			
				if(j<height-1){
					pixel[i][j+1][0]+=error_3[0]*7/16;
					pixel[i][j+1][1]+=error_3[1]*7/16;
					pixel[i][j+1][2]+=error_3[2]*7/16;
				}
				if(i<width-1){
					if(j>0){
						pixel[i+1][j-1][0]+=error_3[0]*3/16;
						pixel[i+1][j-1][1]+=error_3[1]*3/16;
						pixel[i+1][j-1][2]+=error_3[2]*3/16;

					}
					pixel[i+1][j][0]+=error_3[0]*5/16;
					pixel[i+1][j][1]+=error_3[1]*5/16;
					pixel[i+1][j][2]+=error_3[2]*5/16;
					if(j<height-1){
						pixel[i+1][j+1][0]+=error_3[0]/16;
						pixel[i+1][j+1][1]+=error_3[1]/16;
						pixel[i+1][j+1][2]+=error_3[2]/16;
					}
				}
			}
		}
		
		else{
			for (int j=height-1;j>=0;j--){
				quad=MBVQ((int)Imagedata[i][j][0],(int)Imagedata[i][j][1],(int)Imagedata[i][j][2]);
				vert=nearestV(quad,pixel[i][j][0],pixel[i][j][1],pixel[i][j][2]);
				vertex_final[i][j]=vert;
				error_3= {pixel[i][j][0]-vert[0],pixel[i][j][1]-vert[1],pixel[i][j][2]-vert[2]};
			
				if(j>0){
					pixel[i][j-1][0]+=error_3[0]*7/16;
					pixel[i][j-1][1]+=error_3[1]*7/16;
					pixel[i][j-1][2]+=error_3[2]*7/16;
				}
				if(i<width-1){
					if(j<height-1){
						pixel[i+1][j+1][0]+=error_3[0]*3/16;
						pixel[i+1][j+1][1]+=error_3[1]*3/16;
						pixel[i+1][j+1][2]+=error_3[2]*3/16;
					}
					pixel[i+1][j][0]+=error_3[0]*5/16;
					pixel[i+1][j][1]+=error_3[1]*5/16;
					pixel[i+1][j][2]+=error_3[2]*5/16;
					if(j>0){
						pixel[i+1][j-1][0]+=error_3[0]/16;
						pixel[i+1][j-1][1]+=error_3[1]/16;
						pixel[i+1][j-1][2]+=error_3[2]/16;
					}
				}
			}
		}

	}
	for(int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			for (int c=0;c<3;c++){
				halftone[i][j][c]=vertex_final[i][j][c]*255;
			}
		}
	}

	if (!(file=fopen("brid_NMVQ.raw","wb"))) {
		cout << "Cannot open file"<< endl;
		exit(1);
	}
	fwrite(halftone, sizeof(unsigned char), width*height*channel, file);
	fclose(file);



	return 0;
}

vector<vector<vector<double>>> fs_error_diffusion(vector<vector<vector<double>>> pixel){
	vector<vector<vector<double>>> halftone(width,vector<vector<double>>(height, vector<double>(3)));
	double error=0;
	for (int c=0;c<3;c++){
		for (int i=0; i<width; i++){
			if (i%2==0){
				for (int j=0;j<height;j++){
					if (pixel[i][j][c]>=0.5){
						halftone[i][j][c]=1;
					}
					else{
						halftone[i][j][c]=0;
					}
					error=pixel[i][j][c]-halftone[i][j][c];
					if(j<height-1){
						pixel[i][j+1][c]+=error*7/16;
					}
					if(i<width-1){
						if(j>0){
							pixel[i+1][j-1][c]+=error*3/16;
						}
						pixel[i+1][j][c]+=error*5/16;
						if(j<height-1){
							pixel[i+1][j+1][c]+=error/16;
						}
					}
				}
			}
			else{
				for (int j=height-1;j>=0;j--){
					if (pixel[i][j][c]>=0.5){
						halftone[i][j][c]=1;
					}
					else{
						halftone[i][j][c]=0;
					}
					error=pixel[i][j][c]-halftone[i][j][c];
					if(j>0){
						pixel[i][j-1][c]+=error*7/16;
					}
					if(i<width-1){
						if(j<height-1){
							pixel[i+1][j+1][c]+=error*3/16;
						}
						pixel[i+1][j][c]+=error*5/16;
						if(j>0){
							pixel[i+1][j-1][c]+=error/16;
						}
					}
				}
			}
		}
	}
	return halftone;
}

int MBVQ(int r, int g, int b){
	if((r+g)>255){
		if((g+b)>255){
			if((r+g+b)>510){
				return 1; //CMYW
			}
			else{
				return 2; //MYGV
			}
		}
		else{
			return 3; //RGMY
		}
	}
	else{
		if(!((g+b)>255)){
			if(!((r+g+b)>255)){
				return 4; //KRGB
			}
			else{
				return 5; //RGBM
			}
		}
		else{
			return 6; //CMGB
		}
	}
}

vector<double> nearestV(int mbvq, double R, double G, double B){

	vector<double> vertex(3);
	vector<double> red{1,0,0};
	vector<double> green{0,1,0};
	vector<double> blue{0,0,1};
	vector<double> white{1,1,1};
	vector<double> cyan{0,1,1};
	vector<double> magenta{1,0,1};
	vector<double> yellow{1,1,0};
	vector<double> black{0,0,0};
	//no 1 for CMYW
	if (mbvq == 1){
        vertex = white;
        if (B < 0.5){
            if (B <= R){
                if (B <= G){
                    vertex = yellow;
                }
            }
        }
        if (G < 0.5){
            if (G <= B){
                if (G <= R){
                    vertex = magenta;
                }
            }
        }
        if (R < 0.5){
            if (R <= B){
                if (R <= G){
                    vertex = cyan;
                }
            }
        }
    }
	// No.2 for MYGC
    if (mbvq == 2){
        vertex = magenta; 
        if (G >= B){
            if (R >= B){
                if (R >= 0.5){
                    vertex = yellow;
                }
                else{
                    vertex = green;
                }
			}
		}
        if (G >= R){
            if (B >= R){
                if (B >= 0.5){
                    vertex = cyan; 
                }
                else{
                    vertex = green;
                }
            }
        }
    }
	// No.3 for RGMY
    if (mbvq == 3){
        if (B > 0.5){
            if (R > 0.5){
                if (B >= G){
                    vertex = magenta;
                }
                else{
                    vertex = yellow;
                }
            }
            else{
                if (G > B + R){
                    vertex = green;
                }
                else{ 
                    vertex = magenta;
                }
            }
        }
        else{
            if (R >= 0.5){
                if (G >= 0.5){
                    vertex = yellow;
                }
                else{
                    vertex = red;
                }
            }
            else{
                if (R >= G){
                    vertex = red;
                }
                else{
                    vertex = green;
                }
            }
        }
    }
	// No.4 for KRGB
    if (mbvq == 4){
        vertex = black;
        if (B > 0.5){
            if (B >= R){
                if (B >= G){
                    vertex = blue;
                }
            }
        }
        if (G > 0.5){
            if (G >= B){
                if (G >= R){
                    vertex = green;
                }
            }
        }
        if (R > 0.5){
            if (R >= B){
                if (R >= G){
                    vertex = red;
                }
            }
        }
    }
	// No.5 for RGBM
    if (mbvq == 5){
        vertex = green;
        if (R > G){
            if (R >= B){
                if (B < 0.5){
                    vertex = red;
                }
                else{
                    vertex = magenta;
                }
            }
        }
        if (B > G){
            if (B >= R){
                if (R < 0.5){
                    vertex = blue;
                }
                else{
                    vertex = magenta;
                }
            }
        }
    }
	// No.6 for CMGB
    if (mbvq == 6){
        if (B > 0.5){
            if ( R > 0.5){
                if (G >= R){
                    vertex = cyan;
                }
                else{
                    vertex = magenta;
                }
            }
            else{
                if (G > 0.5){
                    vertex = cyan;
                }
                else{
                    vertex = blue;
                }
            }
        }
        else{
            if ( R > 0.5){
                if (R - G + B >= 0.5){
                    vertex = magenta;
                }
                else{
                    vertex = green;
                }
            }
            else{
                if (G >= B){
                    vertex = green;
                }
                else{
                    vertex = blue;
                }
            }
        }
    }
    return vertex;
}




