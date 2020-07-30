#Makefile
simples:
	gcc -omain src/main.c src/imageprocessing.c -I./ -lfreeimage
	./main
	xdg-open out.jpg
	xdg-open data/lena.jpg

process:
	gcc -omain src/main_process.c src/imageprocessing.c -I./ -lfreeimage
	./main
	xdg-open out.jpg
	xdg-open data/lena.jpg

thread:
	gcc -omain src/main_thread.c src/imageprocessing.c -I./ -lfreeimage
	./main
	xdg-open out.jpg
	xdg-open data/lena.jpg

test:

git:
	git commit -am 'auto'
	git push origin master

clear:
	rm main
	rm cachorro-out.jpg
