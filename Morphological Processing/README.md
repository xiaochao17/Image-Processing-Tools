# Morphological Processing

Three mainly morphological processing methods are applied here:
* Thinning
* Shrinking
* Skeletonizing  

The corresponding matrices for each one could be found in the book "Digital Image Processing" by William K. Pratt

Few binary images with simple shapes are tested first. Also, the shrinking method is used to identify the defects in the binary image next. Moreover, an extra defection-detection matrix is explored meanwhile. A more useful application here is to count to number of rices in a image and rank the size of different rice types. Certain division of the rice image needs to be processed first.  


## Run the test

The program can be invoked as follows (in MacOS):  

&nbsp;&nbsp;$ g++ -Wall -std=c++17 MorphologicalProcess -o MorphologicalProcess  
&nbsp;&nbsp;$ ./MorphologicalProcess pattern1.raw pattern2.raw pattern3.raw pattern4.raw   

&nbsp;&nbsp;$g++ -Wall -std=c++17 DefectDetection.cpp -o DefectDetection  
&nbsp;&nbsp;$ ./DefectDetection deer.raw  

&nbsp;&nbsp;$g++ -Wall -std=c++17 RiceCount.cpp -o RiceCount  
&nbsp;&nbsp;$./RiceCount rice.raw

The output files could be recognized from the filenames accordingly


## Authors

* **Xiaochao Gao** - [xiaochao17](https://github.com/xiaochao17)

## Acknowledgement 

* All images could be found on either http://sipi.usc.edu/database/ or http://images.google.com/
