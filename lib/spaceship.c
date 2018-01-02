#include <stdio.h>
#include <allegro5/allegro.h>
#include "spaceship.h"

int main()
{
  spaceship_t spaceship;
  spaceship_t *spaceship_p = &spaceship;

  puts("Let's see if spaceship.h works");

  spaceship_p->sx = 5.1;
  spaceship_p->sy = 72.4;
  spaceship_p->heading = 320.5;
  spaceship_p->speed = 12.5;
  spaceship_p->dead = 0;
  spaceship_p->color = (al_map_rgb(0x32, 0x46, 0x82));

  printf("sx: %3.2f, dead: %i\n", spaceship_p->sx, spaceship_p->dead);
  
  puts("Maybe it worked..");

  return 0;
}
