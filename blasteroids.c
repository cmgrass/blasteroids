#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"

void error(char *msg)
{
  fprintf(stderr, "%s: %s (%i)\n", msg, strerror(errno), errno);
  exit(1);
}

int init_display(ALLEGRO_DISPLAY *display, int w, int h)
{
  /* Initialize Allegro Library */
  if (!al_init()) {
    error("Failed to initialize Allegro");
  }

  /* Create Display Window */
  display = al_create_display(w, h);
  if (!display) {
    error("Failed to create display");
  }

  /* Initialize Display Color */
/*
  al_clear_to_color(al_map_rgb(0, 0, 0));
*/

  /* Activate the modified display */
  /*
    Allegro rendering works by togglingt wo display buffers. One buffer is
    displayed, while the other is used to draw on. Once we complete drawing to
    the buffer, we swap them and the buffer used for drawing becomes the buffer
    used for displaying. The buffer previously used as a display becomes
    available for drawing.
  */
/*
  al_flip_display();
*/

  return 0;
} /* init_display */

int main(int argc, char *argv[])
{
  int status = 0;
  spaceship_t spaceship;
  spaceship_t *spaceship_p = &spaceship;
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *event_queue;
  ALLEGRO_EVENT event;
  ALLEGRO_TIMEOUT timeout;

  /* Initialize Allegro */
/*
  status = init_display(display, 640, 480);
*/

  al_init();

  display = al_create_display(800, 600);

  /* Setup Event Queue */
  event_queue = al_create_event_queue();
  if (!event_queue) {
    error("Could not create event queue");
  }

  puts("122");

  al_register_event_source(event_queue, al_get_display_event_source(display));

  puts("232");

  al_init_timeout(&timeout, 0.06);

  puts("531");

  /* ----- T E S T ----- */
  /* Initialize Ship Object */
  status = ship_init(spaceship_p, 0x16, 0xE2, 0x49);

  puts("675");

  al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));

  puts("789");

  al_flip_display();

  puts("801");

  /* Game Loop */
  while(1) {
    bool recvd_event = al_wait_for_event_until(event_queue, &event, &timeout);

    puts("event cleared");

    /* Check for exit event */
    if (recvd_event && (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)) {
      puts("Exiting");
      break;
    }

    al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));
    al_draw_line(-16, 18, 0, -22, spaceship_p->color, 3.0f);
    al_draw_line(0, -22, 16, 18, spaceship_p->color, 3.0f);
    al_draw_line(-12, 8, -2, 8, spaceship_p->color, 3.0f);
    al_draw_line(12, 8, 2, 8, spaceship_p->color, 3.0f);
    al_flip_display();

  } /* while */

  al_rest(3);

  /* Clean-up */
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);

  return 0;
}
