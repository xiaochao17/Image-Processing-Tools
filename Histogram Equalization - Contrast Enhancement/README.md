# Histogram Equalization

There are a lot of situations that we want to increase the contrast of an image. There are two main ways to adjust the contrast of an image using histogram equalization method. The first one is using a transfer function to stretch the value range of an image to a wider range. The second one is to cumulate probability and equally divide them into a range like a bucket filling.

Procedures of doing transfer-function-based histogram equalization are as followed:  
&nbsp;&nbsp;(1)	Read the RAW image and put all pixels with the same value into one vector and there should be 256 vectors in total;  
&nbsp;&nbsp;(2)	Calculate the probability of each vector from (1) in terms of total pixels of the image;  
&nbsp;&nbsp;(3)	Calculate the cumulative distribution function of those vectors and multiple 255 for all values so that the result would be integers in the range between 0 and 255;  
&nbsp;&nbsp;(4)	Remap the original pixel value to the new pixel value according to the transfer function from (2);  
Procedures of doing cumulative-probability-based histogram equalization are as followed:  
&nbsp;&nbsp;(1)	Read the RAW image and put all pixels with the same value into one vector and there should be 256 vectors in total;  
&nbsp;&nbsp;(2)	Connect all vectors from (1) into one vector;  
&nbsp;&nbsp;(3)	Divide the number of all pixels of the image by 256 to get the number of pixels for each value from 0 to 255;  
&nbsp;&nbsp;(4)	Equally allocate the same number of pixels to all values and assign the new value to those original pixels;  


## Run the test

The program can be invoked as follows (in MacOS):  
&nbsp;&nbsp;&nbsp;&nbsp;$ g++ -Wall -std=c++17 HistogramEqualization.cpp -o HistogramEqualization  
&nbsp;&nbsp;&nbsp;&nbsp;$ ./HistogramEqualization rose_dark.raw rose_bright.raw rose_mix.raw   
The output files could be recognized from the filename accordingly


## Authors

* **Xiaochao Gao** - [xiaochao17](https://github.com/xiaochao17)

## Acknowledgement 

* All images could be found on either http://sipi.usc.edu/database/ or http://images.google.com/