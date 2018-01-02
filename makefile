blasteroids.o: blasteroids.c
	gcc -Wall -g -c blasteroids.c -o blasteroids.o

blasteroids: blasteroids.o
	gcc blasteroids.o -o blasteroids `pkg-config --cflags --libs allegro-5`
