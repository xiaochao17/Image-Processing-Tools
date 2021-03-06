# Image Denoising

Noises are a common phenomenon in signal processing. To get an image of better quality, we usually need to develop some ways to denoise it. There are several ways commonly used, such as uniform filters, Gaussian filters, bilateral filters and non-local mean filters. Among those, uniform and Gaussian filters can also be used to do image blurring. The latter two filter can preserve the edges better than the first two methods. Another noise is called shot noise and it is usually generated by CMOS. To denoise this, we need to make the noise into a Gaussian noise first with Anscombe root transformation and then do the Gaussian denoising.  

There are few denoising filters implemented here:
* Uniform 
* Gaussian
* Bilateral
* Non-local Mean  

Some useful introductions for basic understanding could be found here:  
&nbsp;&nbsp; https://en.wikipedia.org/wiki/Image_noise  
&nbsp;&nbsp; https://en.wikipedia.org/wiki/Gaussian_blur    
&nbsp;&nbsp; https://en.wikipedia.org/wiki/Bilateral_filter    
&nbsp;&nbsp; https://www.iro.umontreal.ca/~mignotte/IFT6150/Articles/Buades-NonLocal.pdf   


## Run the test

The programs can be invoked as follows (in MacOS):  
&nbsp;&nbsp;&nbsp;&nbsp; g++ -Wall -std=c++17 DenoisingGrayImage.cpp -o DenoisingGrayImage  
&nbsp;&nbsp;&nbsp;&nbsp; ./DenoisingGrayImage pepper.raw pepper_uni 
&nbsp;&nbsp;    
&nbsp;&nbsp;&nbsp;&nbsp; g++ -Wall -std=c++17 DenoisingColorImage.cpp -o DenoisingColorImage  
&nbsp;&nbsp;&nbsp;&nbsp; ./DenoisingColorImage rose_color.raw rose_color_noise.raw  
&nbsp;&nbsp;  
&nbsp;&nbsp;&nbsp;&nbsp; g++ -Wall -std=c++17 RemoveShotNoise.cpp -o RemoveShotNoise  
&nbsp;&nbsp;&nbsp;&nbsp; ./RemoveShotNoise pepper_dark.raw pepper_dark_noise.raw  
&nbsp;&nbsp;  
The output files could be recognized from the filename accordingly


## Authors

* **Xiaochao Gao** - [xiaochao17](https://github.com/xiaochao17)

## Acknowledgement 

* All images could be found on either http://sipi.usc.edu/database/ or http://images.google.com/
