# Makefile

# Compilation macros
CC = gcc
DIR = src
TARGET = ./main

# Tests macros
BASH = sh
TEST_SCRIPT = ./tests.sh
VERBOSE ?= 1

# Zip file macros
ZIP = zip
USERNAME = maruan_trabalho2_222025
ZIPFILE = $(USERNAME).zip



simple:
	$(CC) -o main $(DIR)/main.c $(DIR)/imageprocessing.c -I./ -lfreeimage
	$(TARGET) $(img) &> /dev/null
	#xdg-open out.jpg
	#xdg-open data/lena.jpg

process:
	$(CC) -o main $(DIR)/process.c $(DIR)/imageprocessing.c -I./ -lfreeimage
	$(TARGET) $(img) &> /dev/null
	#xdg-open out.jpg
	#xdg-open data/lena.jpg

threads:
	$(CC) -lpthread -o main $(DIR)/thread.c $(DIR)/imageprocessing.c -I./ -lfreeimage
	$(TARGET) $(img) &> /dev/null
	#xdg-open out.jpg
	#xdg-open data/lena.jpg

test:
	$(TEST_SCRIPT) $(img)

git:
	git commit -am 'auto'
	git push origin master

clear:
	rm main
	rm out.jpg

rm:
	rm doc/*.png doc/*.txt doc/*.dat doc/*.log
	rm data/out.jpg

zip:
	$(ZIP) $(ZIPFILE) ./*
