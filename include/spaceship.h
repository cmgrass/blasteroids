#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

typedef struct {
  float sx;
  float sy;
  float heading;
  float speed;
  int dead;
  ALLEGRO_COLOR color;
} spaceship_t;

typedef enum {
  CCW,
  CW
} rotation_dir_t;

typedef enum {
  ACCEL,
  DECEL
} accel_t;

int ship_init(spaceship_t *spaceship_p, unsigned char r, unsigned char g,
              unsigned char b)
{
  spaceship_p->sx = 320;
  spaceship_p->sy = 240;
  spaceship_p->heading = 0;
  spaceship_p->speed = 0.5;
  spaceship_p->dead = 0;
  spaceship_p->color = (al_map_rgb(r, g, b));

  return 0;
} /* ship_init */

int ship_rotate(spaceship_t *spaceship_p, rotation_dir_t rotation_dir_d)
{
  if (spaceship_p->heading >= 6.28310) {
    spaceship_p->heading = 0.2;
  } else if (spaceship_p->heading < 0) {
    spaceship_p->heading = 6.0;
  } else {
    if (!rotation_dir_d) {
      spaceship_p->heading -= 0.2;
    } else {
      spaceship_p->heading += 0.2;
    }
  }
  return 0;
}

int ship_accelerate(spaceship_t *spaceship_p, accel_t accel_d)
{
  float speed_iteration_c = 0.05;
  float speed_max_c = 1.0;
  float speed_min_c = 0.01;

  if (accel_d == ACCEL) {
    spaceship_p->speed += speed_iteration_c;
  } else {
    spaceship_p->speed -= speed_iteration_c;
  }

  if (spaceship_p->speed > speed_max_c) {
    spaceship_p->speed = (speed_max_c);
  } else if (spaceship_p->speed < speed_min_c) {
    spaceship_p->speed = (speed_min_c);
  }

  return 0;
}

int ship_draw(spaceship_t *spaceship_p)
{
  ALLEGRO_TRANSFORM transform_t;
  al_identity_transform(&transform_t);
  al_rotate_transform(&transform_t, spaceship_p->heading);
  al_translate_transform(&transform_t, spaceship_p->sx, spaceship_p->sy);
  al_use_transform(&transform_t);
  al_draw_line(-16, 18, 0, -22, spaceship_p->color, 3.0f);
  al_draw_line(0, -22, 16, 18, spaceship_p->color, 3.0f);
  al_draw_line(-12, 8, -2, 8, spaceship_p->color, 3.0f);
  al_draw_line(12, 8, 2, 8, spaceship_p->color, 3.0f);
  return 0;
}
