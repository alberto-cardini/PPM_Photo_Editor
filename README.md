# PPM Photo editor
The primary objective of this project is to create an intuitive and efficient photo editor that can perform essential image editing functions such as cropping, color adjustments, and filters. This project will also serve as a foundational learning tool for understanding image processing algorithms and developing skills in software development, particularly in handling graphical data.

## Restrictions on Image format
<img align="right" columns="141" row="131" src="https://github.com/alberto-cardini/PPM_Photo_Editor/assets/51383388/c4e8fbc9-6acb-4c12-a4e9-ff0911929841)">
When choosing the input image be sure to use images that are in PPM format (P3 to be precise), strictly in ASCII format (https://en.wikipedia.org/wiki/Netpbm). The .ppm file from a text editor must look like the this. It doesn't matter whether the pixels are ordered in a list or in rows of RGB value.

To satisfy these particular requests use an editor like GIMP to export the file in the right format, then open the .ppm file in a text editor and delete the line that GIMP include in exported files. Now you are good to go.

## Future Release 1.0
The following features will be available with the first release. 

### Filters
1. Gaussian Blur: ✅.
2. Colour adjustments: (planned).

### Processing
1. Edge Detection: (work in progress).

### Editing  
1. Crop feature: (planned).

## Sources
A big part of the math applied in the processing of the images loaded is based on the lectures of the Foundamental Course on Computer Vision of the Columbia University (https://fpcv.cs.columbia.edu/Monographs).
