# Geometric Modification

Some specific situations for geometric modifications are explored here:

&nbsp;&nbsp; 1. Tring to solve a "puzzle" - refilling missing parts in an image through finding those missing parts and doing some basic transformations like rotating, scaling and translating with **Gaussion elimination**. Since some errors may be introduced into the edge part, two methods are tested here to make up for that :  a. enlarging the image by 1 pixel b. do bilinear interpolation for the edge part.  

&nbsp;&nbsp; 2. Using the same technique to do an interesting transformation - spatial warping. It's more math-involved.  

&nbsp;&nbsp; 3. Using linear regression to do lens distortion. The main aim is to see how the geometric modification can be applied to nonlinear transform.


## Run the test

The program can be invoked as follows (in MacOS):  

&nbsp;&nbsp;$ g++ -Wall -std=c++17 GeometricTransformation.cpp -o GeometricTransformation.cpp  
&nbsp;&nbsp;$ ./GeometricTransformation.cpp lighthouse.raw lighthouse1.raw lighthouse2.raw lighthouse3.raw

&nbsp;&nbsp;$g++ -Wall -std=c++17 SpatialWarping.cpp -o SpatialWarping  
&nbsp;&nbsp;$ ./SpatialWarping hat.raw   

&nbsp;&nbsp; run the program in MATLAB

The output files could be recognized from the filename accordingly


## Authors

* **Xiaochao Gao** - [xiaochao17](https://github.com/xiaochao17)

## Acknowledgement 

* All images could be found on either http://sipi.usc.edu/database/ or http://images.google.com/
