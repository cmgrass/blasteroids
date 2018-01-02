spaceship.o: ./lib/spaceship.c
	gcc -Wall -g -I./include -c ./lib/spaceship.c -o ./lib/spaceship.o `pkg-config --cflags --libs allegro-5`

spaceship: ./lib/spaceship.o
	gcc ./lib/spaceship.o -o spaceship `pkg-config --cflags --libs allegro-5`

blasteroids.o: blasteroids.c
	gcc -Wall -g -c blasteroids.c -o blasteroids.o

blasteroids: blasteroids.o
	gcc blasteroids.o -o blasteroids `pkg-config --cflags --libs allegro-5`
