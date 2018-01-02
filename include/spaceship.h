#include <allegro5/allegro.h>

typedef struct {
  float sx;
  float sy;
  float heading;
  float speed;
  int dead;
  ALLEGRO_COLOR color;
} spaceship_t;

int ship_init(spaceship_t *spaceship_p, unsigned char r, unsigned char g,
              unsigned char b)
{
  spaceship_p->sx = 0;
  spaceship_p->sy = 0;
  spaceship_p->heading = 0;
  spaceship_p->speed = 0;
  spaceship_p->dead = 0;
  spaceship_p->color = (al_map_rgb(r, g, b));

  return 0;
} /* ship_init */
