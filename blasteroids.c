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

int init_display(ALLEGRO_DISPLAY **display_p,
                 ALLEGRO_EVENT_QUEUE **event_queue_p, int w, int h)
{
  /* Initialize Allegro Library */
  if (!al_init()) {
    error("Failed to initialize Allegro");
  }

  /* Create Display Window */
  *display_p = al_create_display(w, h);
  if (!(*display_p)) {
    error("Failed to create display");
  }

  /* Install Keyboard Driver */
  if (!al_install_keyboard()) {
    error("Could not connect keyboard");
  }
 
  /* Setup Event Queue */
  *event_queue_p = al_create_event_queue();
  if (!(*event_queue_p)) {
    error("Could not create event queue");
  }

  al_register_event_source(*event_queue_p,
                           al_get_display_event_source(*display_p));
  al_register_event_source(*event_queue_p, al_get_keyboard_event_source());

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

  return 0;
} /* init_display */

int main(int argc, char *argv[])
{
  int status = 0;
  spaceship_t spaceship;
  spaceship_t *spaceship_p = &spaceship;
  ALLEGRO_DISPLAY *display_p;
  ALLEGRO_EVENT_QUEUE *event_queue_p;
  ALLEGRO_EVENT event;
  ALLEGRO_TIMEOUT timeout;

  /* Initialize Allegro */
  status = init_display(&display_p, &event_queue_p, 640, 480);
  if (status) {
    error("Could not initialize game environment");
  }
  al_init_timeout(&timeout, 0.06);

  /* ----- T E S T ----- */
  /* Initialize Ship Object */
  status = ship_init(spaceship_p, 0x16, 0xE2, 0x49);
  if (status) {
    error("Could not create spaceship");
  }

  /* Game Loop */
  while(1) {
    bool recvd_event = al_wait_for_event_until(event_queue_p, &event, &timeout);

    if (recvd_event) {
    puts("EVENT!");
      switch (event.type) {
      /* Check for exit event */
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        puts("Exiting");
        status = -1;
        break;

      /* Check for game action events */
      case ALLEGRO_EVENT_KEY_CHAR:
        switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_LEFT:
          status = ship_rotate(spaceship_p, CCW);
          printf("[DEBUG] ship heading: %3.2f\n", spaceship_p->heading);
          break;

        case ALLEGRO_KEY_RIGHT:
          status = ship_rotate(spaceship_p, CW);
          printf("[DEBUG] ship heading: %3.2f\n", spaceship_p->heading);
          break;

        case ALLEGRO_KEY_UP:
          break;

        case ALLEGRO_KEY_DOWN:
          break;

        case ALLEGRO_KEY_SPACE:
          break;
        }
        break;
      }
      /* Exit if requested to exit */
      if (status == -1) {
        break;
      }
    }

    /* Update screen */
    al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));
    status = ship_draw(spaceship_p);
/*
    al_draw_line(-16, 18, 0, -22, spaceship_p->color, 3.0f);
    al_draw_line(0, -22, 16, 18, spaceship_p->color, 3.0f);
    al_draw_line(-12, 8, -2, 8, spaceship_p->color, 3.0f);
    al_draw_line(12, 8, 2, 8, spaceship_p->color, 3.0f);
*/
    al_flip_display();

  } /* while */

  /* Clean-up */
  al_destroy_display(display_p);
  al_destroy_event_queue(event_queue_p);

  return 0;
}
