# Mean blur filter implemented on C with the purpose of obtaining knowledge

This repository was made for a homework assignment in the course EA876 - Software
Introduction at Unicamp. The main purpose of the code here is to compare different
approaches of implementing a blur filter. The median blur filter was the default option and i chose
that filter.

## Guide on the files
The _doc_ folder contains the latex template that i used and the intermediate files in obtaining the document.
The _src_ folder contains all the source code for the blur filter
The _data_ folder contains all the images. Feel free to add any .jpg image that you want.
The _parent_ directory contains this file, the Makefile, the test script with /bin/sh environment, a precompiled pdf in my machine if you dont want to run in yours and finally
the original project assignment in portuguese.


## Requirements

- This repository was made on a **Linux** machine and was not tested on **Windows (MinGW)** nor **MacOS**
- You have to run this repository on a desktop, not on a server, because you have to view the image and the pdf document
- For the plots I used GNUPlot
- I opened the images and the pdf with **xdg-open** so you have to have a preferred application on your computer
- Obviously you must have GNU core-utils (make,gcc,...)
- I compiled the final document with **PdfLatex** using the following packages:
  1. float
  2. fancyvrb
  3. graphicx
  4. dvispname
-

## Instructions on how to use

- If you want to run the complete test and just see the pdf run:
``````
make test
``````
