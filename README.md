# Median blur filter implemented on C with the purpose of obtaining knowledge

This repository was made for a homework assignment in the course EA876 - Software
Introduction at Unicamp. The main purpose of the code here is to compare different
approaches of implementing a blur filter. The median blur filter was the default option
and i chose that filter.

## Guide on the files
The _doc_ folder contains the latex template that i used and the intermediate
files in obtaining the document after running. The _src_ folder contains all the source code
for the blur filter. The source code are the libraries and one main.c file to implement the blur filter
with one line of execution, one in multiprocess (process.c) and one in multithreads (thread.c). The _data_
folder contains all the images. Feel free to add any .jpg image that you want. The out.jpg image on
the parent directory is the final result of the filter after running the program. The default image that i am testing on is lena.jpg.
The _parent_ directory contains this file, the Makefile, the test script with #!/bin/sh environment, a
precompiled pdf in my machine (if you dont want to run in yours) and finally
the original project assignment in portuguese.


## Requirements

- This repository was made on a **Linux** machine and was not tested on **Windows** nor **MacOS**
- You have to run this repository on a desktop, not on a server, because you have to view the image and the pdf document
- For the plots I used GNUPlot
- Free image library
- I opened the images and the pdf with **xdg-open** so you have to have a preferred application on your computer
- Obviously you must have GNU core-utils (make,gcc,...)
- The image must be on **jpg** format
- I compiled the final document with **pdflatex** using the following packages:
  1. float
  2. fancyvrb
  3. graphicx
  4. dvispname

## Instructions on how to use
Remember that the default image is lena.jpg but feel free to change to any foobar.jpg on your computer.

- If you want to run the complete test and just see the PDF result type this:
``````
make test
``````
- If you want to run the complete test as above but choose what image you are testing on type this:
``````
make test img=<image path>
``````
One example is _img=~/Pictures/foobar.jpg_ or _img=data/foobar.jpg_
- If you want to run one specific test on one approach type one of these:
``````
make simple
make process
make thread
``````
- If you want to run one specific test on one approach and choose the image file type one of these:
``````
make simple img=<image path>
make process img=<image path>
make thread img=<image path>
``````
- If you want to clear the executable ./main and the output file type this:
``````
make clear
``````
- If you want to clear all the intermediate files on the process of building the document type this:
``````
make rm
``````
Remeber to always use ``````make clear`````` and ``````make rm ``````after running the program =).
