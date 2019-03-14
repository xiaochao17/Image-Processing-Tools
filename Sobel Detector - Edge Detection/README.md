# Histogram Equalization

Image edge detection is very useful in daily application and it is the fundamental technique for other more advanced image processing topics. With edge detection, we can reduce the unnecessary information but preserve the structure and extract some important image features like corners, lines and curves. Moreover, it can be applied to object recognition, segmentation, image retrieval, scene parsing and so on.  

Here, a simple Sobel detector without using any extra libraries was implemented to check the results for two gray images. A introduction to it could be found here : https://en.wikipedia.org/wiki/Sobel_operator

The general procedures are as followed:
*  Using the Sobel mask (Gx, Gy) to computer the finite difference at the center pixel by convolution;
*  Find the minimum and maximum values of two difference arrays from (1), normalize it and output it then;
*  Generate the magnitude image by sqrt(〖Gx〗^2+〖Gy〗^2 ) and find the minimum and maximum values
*  Set different thresholds to the magnitude image and compare the results



## Run the test

The program can be invoked as follows (in MacOS):  
&nbsp;&nbsp;&nbsp;&nbsp;$ g++ -Wall -std=c++17 Sobel.cpp -o Sobel
&nbsp;&nbsp;&nbsp;&nbsp;$ ./Sobel  tiger_image pig_image threshold_1(0.35) threshold_2(0.35)

The output files could be recognized from the filename accordingly


## Authors

* **Xiaochao Gao** - [xiaochao17](https://github.com/xiaochao17)

## Acknowledgement 

* All images could be found on either http://sipi.usc.edu/database/ or http://images.google.com/
