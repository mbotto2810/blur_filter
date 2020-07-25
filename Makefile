#Makefile
simples:
	gcc -omain src/main.c src/imageprocessing.c -I./ -lfreeimage
	./main
	xdg-open cachorro-out.jpg
	xdg-open data/cachorro.jpg

thread:

process:

test:

git:
	git commit -am 'auto'
	git push origin master

clear:
	rm main
	rm cachorro-out.jpg
