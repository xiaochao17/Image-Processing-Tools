# Half-toning

Since most printing devices are not able to reproduce different shadows of grey and only have black and white for grey images, we can print with only one color of ink in dots of different size or spacing but the result should still look continuous because humans have continuous tones. For gray images, we can set a threshold to turn all color values into 0 and 255. This threshold can be fixed or random. Also, we can use error diffusion to make the result look better. For color images, we can do the same thing to three channels and thus we can get 8 colors, which should be enough to draw an image to some extent. However, humans are more sensitive to color brightness variations, which means we need to come up with good ways to limit the brightness to a good range while preserving the average color when doing color halftoning.


## Approaches

* Dithering: Two methods are explored here - with fixed and random threshold  
* Error Diffusion: Three different types are explored here: 1. Floyd-Steinberg; 2. Jarvis, Judice, and Ninke (JJN) 3. Stucki;  
* Color Halftoning with Error Diffusion : Two ways are explored here: 1. Separable error diffusion 2. MBVQ-based error diffusion (More information here : https://pdfs.semanticscholar.org/c67f/37a2ab36bab46bb632b65dc8dc3866f7c80e.pdf?_ga=2.90943645.689519858.1552526550-462987849.1552526550);


## Run the test

The program can be invoked as follows (in MacOS):  

&nbsp;&nbsp;$ g++ -Wall -std=c++17 Dithering.cpp -o Dithering  
&nbsp;&nbsp;$ ./Dithering bridge.raw  

&nbsp;&nbsp;$g++ -Wall -std=c++17 ErrorDiffusion.cpp -o ErrorDiffusion  
&nbsp;&nbsp;$ ./ErrorDiffusion bridge.raw   

&nbsp;&nbsp;$g++ -Wall -std=c++17 Separable_MBVQ.cpp -o Separable_MBVQ  
&nbsp;&nbsp;$ ./Separable_MBVQ bird.raw  

The output files could be recognized from the filename accordingly


## Authors

* **Xiaochao Gao** - [xiaochao17](https://github.com/xiaochao17)

## Acknowledgement 

* All images could be found on either http://sipi.usc.edu/database/ or http://images.google.com/
