# PPM Photo editor
The primary objective of this project is to create an intuitive and efficient photo editor that can perform essential image editing functions such as cropping, color adjustments, and filters. This project will also serve as a foundational learning tool for understanding image processing algorithms and developing skills in software development, particularly in handling graphical data.

## Restrictions on Image format
<img align="right" columns="141" row="131" src="https://github.com/alberto-cardini/PPM_Photo_Editor/.github/assets/file-format.png">
When choosing the input image be sure to use images that are in PPM or PGM format (P3 or P2), strictly in ASCII format (https://en.wikipedia.org/wiki/Netpbm). The .ppm/.pgm file from a text editor must look like the this. It doesn't matter whether the pixels are ordered in a list or in rows of RGB/gray scale value.

To satisfy these particular requests use an editor like GIMP to export the file in the right format, then open the .ppm/.pgm file in a text editor and delete the line that GIMP included in exported files. Now you are good to go.

## Right now you can use:

### Gaussian Blur:
The intensity of the blur can be regulated through the σ value given as a parameter during the constructor call. The σ given in input is the standard deviation of the Gaussian that characterizes the filter itself. the higher the value the more intense the blurring. Following the result with σ = 2, σ = 3, σ = 7 and σ = 14. (images will come)
<br/>
<img src="https://github.com/alberto-cardini/PPM_Photo_Editor/.github/assets/BlurSigma0.png">
<img src="https://github.com/alberto-cardini/PPM_Photo_Editor/.github/assets/BlurSigma2.png">
<img src="https://github.com/alberto-cardini/PPM_Photo_Editor/.github/assets/BlurSigma3.png">
<img src="https://github.com/alberto-cardini/PPM_Photo_Editor/.github/assets/BlurSigma7.png">
<img src="https://github.com/alberto-cardini/PPM_Photo_Editor/.github/assets/BlurSigma14.png">
### Edge Detection:
This filter is base on the famous and used Canny Edge Detection algorithm. Through the interpretation and manipulation of the image's gradient the algorithm is able to find the edges of the objects in the image. The implementation is based on the documentation that you can find at the following wikipedia link (https://en.wikipedia.org/wiki/Canny_edge_detector). (images will come)

## Sources
A big part of the math applied in the implementation of the image processing features is based on the lectures of the First Principles of Computer Vision course of the Columbia University (https://fpcv.cs.columbia.edu/Monographs) and on the related stuff that you can find on wikipedia.
