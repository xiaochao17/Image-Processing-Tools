
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import javax.swing.*;
import java.util.ArrayList;


public class Clustering {

	public static ArrayList<int[][]> finalfinalVectors = new ArrayList<int[][]>();
  	public static ArrayList<int[][]> finalVectors = new ArrayList<int[][]>();
	public static void Quan(int[][] pixel,int number, int row, int col){	
		ArrayList<int[][]> blocks = new ArrayList<int[][]>();
	    blocks = GenerateVectors(pixel, row, col);

		Cluster(number,blocks,finalVectors, row, col);
		Converging(finalVectors,blocks, row, col);
	}

	private static ArrayList<int[][]> GenerateVectors(int[][] pixels, int row, int col) {
		ArrayList<int[][]> vectors = new ArrayList<int[][]>();
		int m = row;
		int n = col;

		for(int y = 0; y < pixels.length; y+=m){
			for(int x = 0; x < pixels[0].length; x+=n){
					int[][] vector = new int[m][n];
					for (int i=0;i<m;i++){
						for (int j=0;j<n;j++){
							vector[i][j]=pixels[y+i][x+j];
						}
					}
					//System.out.println(vector[0][0]);
					vectors.add(vector);
			}
		}

		return vectors;
	}

	private static void Cluster(int num, ArrayList<int[][]> blocks,ArrayList<int[][]> finalVectors, int row, int col){
		if(num==1){
			float[][] floatfinal=Averaging(blocks,row,col);
			int[][] intfinal= new int[row][col];
			for (int i=0;i<row;i++){
				for (int j=0;j<col;j++){
					intfinal[i][j] = (int) floatfinal[i][j];
				}
			}
			finalVectors.add(intfinal);
			return;
		}

		float[][] unit = Averaging(blocks,row,col);
		int[][] sub1 = new int[row][col];
		int[][] sub2 = new int[row][col];
		for (int r=0;r<row;r++){
			for (int c=0;c<col;c++){
					sub1[r][c] = (int)Math.floor(unit[r][c]);
					sub2[r][c] = (int)Math.ceil(unit[r][c]);


			}
		}

		ArrayList<int[][]> sub1s = new ArrayList<int[][]>();
		ArrayList<int[][]> sub2s = new ArrayList<int[][]>();

		for (int i=0; i<blocks.size();i++){
			int[][] blk = (int[][])blocks.get(i);
			float distance_1 = EuclidDistance(blk,sub1);
			float distance_2 = EuclidDistance(blk,sub2);
			if(distance_1<=distance_2){
				sub1s.add(blk);
			}
			else{
				sub2s.add(blk);
			}
		}
		Cluster(num/2,sub1s,finalVectors,row,col);
		Cluster(num/2,sub2s,finalVectors,row,col);
	}

	private static float[][] Averaging(ArrayList blocks,int row, int col){
		float[][] unit = new float[row][col];
		for (int i=0; i<row;i++){
			for (int j=0;j<col;j++){
				for (int n=0;n<blocks.size();n++){
					unit[i][j] += (float)((int[][])blocks.get(n))[i][j];
				}
				unit[i][j]=unit[i][j]/blocks.size();
			}
		}
		return unit;
	}

	private static float EuclidDistance(int[][] block, int[][] sub){
		int row = block.length;
		int col = block[0].length;
		float eDistance = 0;
		for (int r=0;r<row;r++){
			for (int c=0;c<col;c++){
					eDistance += Math.pow((block[r][c]-sub[r][c]),2);
			}
		}
		return eDistance;
	}

	private static void Converging(ArrayList<int[][]> finalVectors, ArrayList<int[][]> blocks, int row, int col){
			int[] place = new int[blocks.size()];
			ArrayList<ArrayList<int[][]>> iterVectors = new ArrayList<ArrayList<int[][]>>();
			for (int i=0;i<blocks.size();i++){
				int serial=0;
				float minD = EuclidDistance(blocks.get(i),finalVectors.get(0));
				for (int j=1;j<finalVectors.size();j++){
					float newD = EuclidDistance(blocks.get(i),finalVectors.get(j));
					if (newD<minD){
						minD=newD;
						serial=j;
					}
				}
				place[i] = serial;
			}
			for (int p=0;p<finalVectors.size();p++){
				ArrayList<int[][]> category = new ArrayList<int[][]>();
				for (int q=0;q<blocks.size();q++){
						if(place[q]==p){
							category.add(blocks.get(q));
						}
				}
				iterVectors.add(category);
			}
			ArrayList<int[][]> tempVectors = new ArrayList<int[][]>();
			for (int s=0; s<iterVectors.size();s++){
					float[][] newpoint = Averaging(iterVectors.get(s),row,col);
					int[][] newintpoint= new int[row][col];
					for (int i=0;i<row;i++){
						for (int j=0;j<col;j++){
							newintpoint[i][j] = (int) newpoint[i][j];
						}
					}
					if (EuclidDistance(newintpoint,finalVectors.get(s))>1){
						tempVectors.add(newintpoint);
					}
					else{
						tempVectors.add(finalVectors.get(s));
					}
			}
			if (tempVectors.equals(finalVectors)){
				finalVectors = tempVectors;
				Matching(place,finalVectors);
				return;
			}
			else{
				finalVectors = tempVectors;
				Converging(finalVectors,blocks,row,col);
			}
	}

	private static void Matching(int[] place, ArrayList<int[][]> finalVectors){
		for (int i =0; i<place.length; i++){
			finalfinalVectors.add(finalVectors.get(place[i]));
		}
	}


}
