#include "draw.h"
#include "list.h"
#include <math.h>
#include <stdlib.h>

const size_t RECT_POINTS = 4;

const size_t GEM_INCREASE = 2;
const size_t GEM_DECREASE = 5;
const size_t GEM_POINTS = 5;
const double GEM_SHIFT = M_PI / 6.0;

const double CIRC = 360.0;
const double ROTATION = M_PI / 180.0;
const double SHIFT = M_PI / -2.0;

list_t *draw_rect(vector_t center, double length, double height) {
  size_t n = RECT_POINTS;
  list_t *new_points = list_init(n, free);
  vector_t *bottom_right = malloc(sizeof(vector_t));
  bottom_right->x = center.x - length / 2.0;
  bottom_right->y = center.y - height/2;
  vector_t *top_right = malloc(sizeof(vector_t));
  top_right->x = center.x - length / 2.0;
  top_right->y = center.y + height/2;
  vector_t *top_left = malloc(sizeof(vector_t));
  top_left->x = center.x + length / 2.0;
  top_left->y = center.y + height/2;
  vector_t *bottom_left = malloc(sizeof(vector_t));
  bottom_left->x = center.x + length / 2.0;
  bottom_left->y = center.y - height/2;
  list_add(new_points, bottom_right);
  list_add(new_points, top_right);
  list_add(new_points, top_left);
  list_add(new_points, bottom_left);
  return new_points;
}

list_t *draw_gem(size_t radius, vector_t centroid) {
  size_t n = GEM_POINTS;
  list_t *new_points = list_init(n, free);
  double shift = GEM_INCREASE * sqrt(3)/4;
  vector_t *first = malloc(sizeof(vector_t));
    *first = (vector_t){
        .x = (radius - GEM_DECREASE) * cos(SHIFT) + centroid.x,
        .y = (radius - GEM_DECREASE) * sin(SHIFT) + centroid.y - shift};
  list_add(new_points, first);
  vector_t *second = malloc(sizeof(vector_t));
    *second = (vector_t){
        .x = radius * cos(ROTATION * CIRC / n * 1 + SHIFT) + centroid.x,
        .y = radius * sin(ROTATION * CIRC / n * 1 + SHIFT) + centroid.y - shift};
  list_add(new_points, second);
  vector_t *third = malloc(sizeof(vector_t));
    *third = (vector_t){
        .x = (radius + GEM_INCREASE) * cos(ROTATION * CIRC / n * 1 + GEM_SHIFT + SHIFT) + centroid.x,
        .y = (radius + GEM_INCREASE) * sin(ROTATION * CIRC / n * 1 + GEM_SHIFT + SHIFT) + centroid.y - shift};
  list_add(new_points, third);
  vector_t *fourth = malloc(sizeof(vector_t));
    *fourth = (vector_t){
        .x = (radius + GEM_INCREASE) * cos(ROTATION * CIRC / n * 2 - GEM_SHIFT + SHIFT) + centroid.x,
        .y = (radius + GEM_INCREASE) * sin(ROTATION * CIRC / n * 2 - GEM_SHIFT + SHIFT) + centroid.y - shift};
  list_add(new_points, fourth);
  vector_t *fifth = malloc(sizeof(vector_t));
    *fifth = (vector_t){
        .x = radius * cos(ROTATION * CIRC / n * 2 + SHIFT) + centroid.x,
        .y = radius * sin(ROTATION * CIRC / n * 2 + SHIFT) + centroid.y - shift};
  list_add(new_points, fifth);
  return new_points;
}
