test: test.c
	gcc test.c -o test `pkg-config --cflags --libs allegro-5`
