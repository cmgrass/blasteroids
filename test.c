#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <allegro5/allegro.h>

void error(char *msg)
{
  fprintf(stderr, "%s: %s (%i)\n", msg, strerror(errno), errno);
  exit(1);
}

int main(int argc, char *argv[])
{
  char ijk = 0;
  ALLEGRO_DISPLAY *display = NULL;

  puts("Hasbro intl. corp.");

  /* Initialize Allegro Library */
  if (!al_init()) {
    error("Failed to initialize Allegro");
  }

  /* Create Display Window */
  display = al_create_display(640, 480);
  if (!display) {
    error("Failed to create display");
  }

  /* Initialize Display Color */
  al_clear_to_color(al_map_rgb(0, 0, 0));

  /* Activate the modified display */
  /*
    Allegro rendering works by togglingt wo display buffers. One buffer is
    displayed, while the other is used to draw on. Once we complete drawing to
    the buffer, we swap them and the buffer used for drawing becomes the buffer
    used for displaying. The buffer previously used as a display becomes
    available for drawing.
  */
  al_flip_display();

  /* testing code */
  for (ijk = 0; ijk < 4; ijk ++) {
    al_rest(0.25);  /* sleep for 3 seconds */
    al_clear_to_color(al_map_rgb(0x00, 0x80, 0x80));
    al_flip_display();
    al_rest(0.25);
    al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));
    al_flip_display();
  }

  /* Clean-up */
  al_destroy_display(display);

  puts("Woohawh!");
  return 0;
}
