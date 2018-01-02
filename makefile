blasteroids: blasteroids.c
	gcc blasteroids.c -o blasteroids `pkg-config --cflags --libs allegro-5`
