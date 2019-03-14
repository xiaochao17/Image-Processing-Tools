
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import javax.swing.*;
import java.util.ArrayList;


public class VQuantization {

	JFrame frame;
	JLabel lbIm1;
	JLabel lbIm2;
	BufferedImage img,compImg;
	public static int width = 352;
	public static int height = 288;

	public void showIms(String filename,int number,int mode){

		img = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		compImg = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

    ////check mode
    int m = 1;
    int n = 1;
    if(mode==1){
      m=1;
      n=2;
    }
    else if(mode==2){
      m=2;
      n=2;
    }
    else if(mode==3){
      m=4;
      n=4;
    }
    else{
      System.out.println("Wrong Mode");
    }



    ////check file format
    if (filename.contains("rgb")){
      int[][] redpixels = new int[width][height];
      int[][] greenpixels = new int[width][height];
      int[][] bluepixels = new int[width][height];
      int[][] pico = new int[width][height*3];

      try{
        FileInputStream colorimage = new FileInputStream(filename);
        byte[] r = new byte[width*height];
        byte[] g = new byte[width*height];
        byte[] b = new byte[width*height];
        colorimage.read(r);
        colorimage.read(g);
        colorimage.read(b);

        int count = 0;
        for(int y = 0; y < height*3; y=y+3){
          for(int x = 0; x < width; x++){
             int red = r[count];//& 0xff;
             int green = g[count] ;//& 0xff;
             int blue = b[count] ;//& 0xff;
             int pix = 0xff000000 | ((red & 0xff) << 16) | ((green & 0xff) << 8) | (blue & 0xff);
             pico[x][y]=r[count];
             pico[x][y+1]=g[count];
             pico[x][y+2]=b[count];


            img.setRGB(x,y/3,pix);
            count++;
          }
        }
      }catch (FileNotFoundException e) {
        e.printStackTrace();
      } catch (IOException e) {
        e.printStackTrace();
      }

      Clustering.Quan(pico,number,m,n*3);
      ArrayList<int[][]> datVectors = Clustering.finalfinalVectors;
      ArrayList<int[][]> testVectors = Clustering.finalVectors;

      ArrayList<Integer> data = new ArrayList<Integer>();

      for(int k=0;k<(width/m);k++){
        for(int theta=0; theta<m; theta++){
          for (int alpha=0; alpha<(height/n); alpha++){
            for (int beta=0; beta<n*3; beta++){
              data.add(datVectors.get(k*(height/n)+alpha)[theta][beta]);
            }
          }
        }

      }
      Integer[] finaldat = new Integer[data.size()];
      finaldat = data.toArray(finaldat);
      //draw the compressed image
      int index = 0;
      for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
          //for reading .raw image to show as a rgb image
          byte r = (byte)(int)finaldat[index++];
          byte g = (byte)(int)finaldat[index++];
          byte b = (byte)(int)finaldat[index++];
          //set pixel for display original image
          int pix = 0xff000000 | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
          compImg.setRGB(x,y,pix);
        }
      }
    }
    else if (filename.contains("raw")){
      int[][] pixels = new int [width][height];
      try {
        FileInputStream inputDt = new FileInputStream(filename);
        byte[] bytes = new byte[width*height];
        inputDt.read(bytes);

        int ind = 0;
        for(int y = 0; y < height; y++){
          for(int x = 0; x < width; x++){
            ////for reading .raw image to show as a rgb image
            byte r = bytes[ind];
            byte g = bytes[ind];
            byte b = bytes[ind];
            ////set pixel for display original image
            int pix = 0xff000000 | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
            pixels[x][y]=bytes[ind];
            img.setRGB(x,y,pix);
            ind++;
          }
        }
      inputDt.close();
      } catch (FileNotFoundException e) {
        e.printStackTrace();
      } catch (IOException e) {
        e.printStackTrace();
      }
      ////Quantization
      Clustering.Quan(pixels,number,m,n);
      ArrayList<int[][]> datVectors = Clustering.finalfinalVectors;
      ////Get compressed image data
      ArrayList<Integer> data = new ArrayList<Integer>();
      for(int k=0;k<(width/m);k++){
        for(int theta=0; theta<m; theta++){
          for (int alpha=0; alpha<(height/n); alpha++){
            for (int beta=0; beta<n; beta++){
              data.add(datVectors.get(k*(height/n)+alpha)[theta][beta]);
            }
          }
        }
      }
      Integer[] finaldat = new Integer[data.size()];
      finaldat = data.toArray(finaldat);
      //draw the compressed image
      int index = 0;
      for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
          byte r = (byte)(int)finaldat[index];
          byte g = (byte)(int)finaldat[index];
          byte b = (byte)(int)finaldat[index];
          //set pixel for display original image
          int pix = 0xff000000 | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
          compImg.setRGB(x,y,pix);
          index++;
        }
      }

    }
    else{
        System.out.println("wrong filename");
    }

		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		GridBagLayout gLayout = new GridBagLayout();
		frame.getContentPane().setLayout(gLayout);

		JLabel lbText1 = new JLabel("Original image");
		lbText1.setHorizontalAlignment(SwingConstants.CENTER);
		JLabel lbText2 = new JLabel("Quantized Image");
		lbText2.setHorizontalAlignment(SwingConstants.CENTER);

		lbIm1 = new JLabel(new ImageIcon(img));
		lbIm2 = new JLabel(new ImageIcon(compImg));


		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.HORIZONTAL;
		c.anchor = GridBagConstraints.CENTER;
		c.weightx = 0.5;
		c.gridx = 0;
		c.gridy = 0;
		frame.getContentPane().add(lbText1, c);

		c.fill = GridBagConstraints.HORIZONTAL;
		c.anchor = GridBagConstraints.CENTER;
		c.weightx = 0.5;
		c.gridx = 1;
		c.gridy = 0;
		frame.getContentPane().add(lbText2, c);

		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridx = 0;
		c.gridy = 1;
		frame.getContentPane().add(lbIm1, c);

		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridx = 1;
		c.gridy = 1;
		frame.getContentPane().add(lbIm2, c);

		frame.pack();
		frame.setVisible(true);

	}




	public static void main(String[] args) {
    String filename = args[0];
    int number = Integer.parseInt(args[1]);
    int mode = Integer.parseInt(args[2]);
    //compress image
    //1.cluster 2. converge 3. Quantize
    VQuantization lb = new VQuantization();
    lb.showIms(filename,number,mode);

	}

}
