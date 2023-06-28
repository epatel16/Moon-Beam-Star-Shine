#include "star_body.h"
#include "list.h"
#include "polygon.h"
#include "sdl_wrapper.h"
#include "state.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const double star_ratio = 38.2 / 100;
const size_t STAR_RADIUS = 50;

const double MIN_ELAS = .75;
const double ELAS_RANGE = 0.1;

float get_rand_col() { return (float)rand() / (float)RAND_MAX; }

float get_rand_elas() {
  return (float)rand() / (float)RAND_MAX * ELAS_RANGE + MIN_ELAS;
}

list_t *draw_star(vector_t centroid, size_t radius, size_t n) {
  double angle = (2 * 3.14159 / n);
  list_t *new_points = list_init(n * 2, free);
  for (size_t i = 0; i < n; i++) {
    vector_t *out = malloc(sizeof(vector_t));
    *out = (vector_t){.x = radius * cos(angle * i) + centroid.x,
                      .y = radius * sin(angle * i) + centroid.y};
    vector_t *in = malloc(sizeof(vector_t));
    *in = (vector_t){
        .x = (star_ratio * radius * cos(angle * i + angle / 2) + centroid.x),
        .y = (star_ratio * radius * sin(angle * i + angle / 2) + centroid.y)};
    list_add(new_points, out);
    list_add(new_points, in);
  }
  return new_points;
}

bool generate_new_star(list_t *arr, int index, double yvelocity,
                       double new_velocity, int max_size) {
  if (index == list_size(arr) - 1 && list_size(arr) < max_size &&
      yvelocity > 0 && new_velocity <= 0) {
    return true;
  }
  return false;
}

void generate_star(list_t *arr, size_t num_points, vector_t window) {
  vector_t center = (vector_t){.x = STAR_RADIUS, .y = window.y - STAR_RADIUS};

  polygon_t *poly = malloc(sizeof(polygon_t));
  poly->centroid = center;
  poly->points = draw_star(center, STAR_RADIUS, num_points);
  poly->red = get_rand_col();
  poly->green = get_rand_col();
  poly->blue = get_rand_col();
  poly->elas = get_rand_elas();
  vector_t start_velocity = (vector_t){.x = 1, .y = 0};
  poly->velocity = start_velocity;
  list_add(arr, poly);
}
