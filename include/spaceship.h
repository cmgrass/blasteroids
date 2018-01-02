#include <allegro5/allegro.h>

typedef struct {
  float sx;
  float sy;
  float heading;
  float speed;
  int dead;
  ALLEGRO_COLOR color;
} spaceship_t;
