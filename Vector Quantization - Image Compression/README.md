# Vector Quantization

Unlike JPEG compression, which works by transforming the image to the frequency domain and quantizing the frequency coefficients in that domain, Vector quantization on the contrary codes a group or block of samples (or a vector of samples) using a single discrete value or index.
Why does this work, or why should this work? Most natural images are not a random collection of pixels but have very smooth varying areas – where pixels are not changing rapidly.   
Consequently, we could pre-decide a codebook of vectors, each vector represented by a block of two pixels (or four pixels etc.) and then replace all similar looking blocks in the image with one of the code vectors. The number of vectors, or the length of the code book used, will depend on how much error you are willing to tolerate in your compression. More vectors will result in larger coding indexes (and hence less compression) but results are perceptually better and vice versa. Thus, vector quantization may be described as a lossy compression technique where groups of samples are given one index that represents a code word.   
In general, this can work in n dimensions, here I start the implementation on two dimensions to perform vector quantization on an image and later extend it to higher dimensions.   


Here are the specific steps to do it:  
&nbsp;&nbsp;1. Understanding the two pixel vector space to see what vectors the image contains  
&nbsp;&nbsp;2. Initialization of codewords - select N (16 in this case) initial codewords  
&nbsp;&nbsp;3. Clustering vectors around each code word  
&nbsp;&nbsp;4. Refine and Update code words depending on outcome of step 3.  
&nbsp;&nbsp;Repeat steps 3 and 4 until code words don’t change or the change is very minimal  
&nbsp;&nbsp;5. Quantize input vectors to produce output image  

## Getting Started

The program can be invoked as follows:  
&nbsp;&nbsp;&nbsp;&nbsp;MyCompression.exe myImage.ext N mode  
The result would present images side by side – original and output. The output would be
computed depending on three parameters:  
&nbsp;&nbsp;• An input image, all images are standard CIF size 352x288 and supplied in two formats – myImage.raw (if it is a single channel 8 bit per pixel image) or myImage.rgb (if it is a color three channel 24 bits per pixel image). Please refer to the readme.txt with the images for the format.  
&nbsp;&nbsp;• N which gives you several vectors for quantization, so that each vector in the input can ultimately use log2N bits. Expect this input to be a power of 2.  
&nbsp;&nbsp;• Mode, which suggests how pixels should be grouped to form vectors. For this implementation, these are the following values the variable can take  
&nbsp;&nbsp;&nbsp;&nbsp;o 1 – suggesting two side by side pixels (whether gray or color) form a vector  
&nbsp;&nbsp;&nbsp;&nbsp;o 2 – suggesting a 2x2 block of pixels (whether gray or color) form a vector  
&nbsp;&nbsp;&nbsp;&nbsp;o 3 – suggesting a 4x4 block of pixels (whether gray or color) form a vector  



## Running the tests
javac VQuantization.java
java VQuantization myImage.raw 16 1

## Authors

* **Xiaochao Gao** - [xiaochao17](https://github.com/xiaochao17)

## Acknowledgments
* This project is inspired by the assignment from CSCI 576 - Multimedia Systems Design class in USC
