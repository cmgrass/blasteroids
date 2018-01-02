#include <stdio.h>
#include <allegro5/allegro.h>
#include "spaceship.h"

int main()
{
  spaceship_t spaceship;
  spaceship_t *spaceship_p = &spaceship;

  puts("Let's see if spaceship.h works");

  ship_init(spaceship_p, 0x16, 0xE2, 0x49);

  printf("sx: %3.2f, dead: %i\n", spaceship_p->sx, spaceship_p->dead);
  
  puts("Maybe it worked..");

  return 0;
}
