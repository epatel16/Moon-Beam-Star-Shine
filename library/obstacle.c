#include "obstacle.h"
#include "draw.h"
#include "list.h"
#include "body.h"
#include "scene.h"
#include "forces.h"
#include <math.h>
#include <stdlib.h>

const size_t OBSTACLE_BASE = 50;
const size_t OBSTACLE_HEIGHT = 15;
const double OBSTACLE_MASS = INFINITY;

const vector_t OBSTACLE_LVLONE1_CENT = (vector_t) {710, 200};
const vector_t OBSTACLE_LVLONE2_CENT = (vector_t) {360, 8};
const vector_t OBSTACLE_LVLONE3_CENT = (vector_t) {50, 412};

const vector_t OBSTACLE_LVLTWO1_CENT = (vector_t) {250, 8};
const vector_t OBSTACLE_LVLTWO2_CENT = (vector_t) {550, 8};
const vector_t OBSTACLE_LVLTWO3_CENT = (vector_t) {250, 125};
const vector_t OBSTACLE_LVLTWO4_CENT = (vector_t) {550, 125};
const vector_t OBSTACLE_LVLTWO5_CENT = (vector_t) {700, 800};
const vector_t OBSTACLE_LVLTWO6_CENT = (vector_t) {300, 800};
const vector_t OBSTACLE_LVLTWO7_CENT = (vector_t) {500, 300};

const vector_t OBSTACLE_LVLTHREE1_CENT = (vector_t) {350, 8};
const vector_t OBSTACLE_LVLTHREE2_CENT = (vector_t) {650, 8};
const vector_t OBSTACLE_LVLTHREE3_CENT = (vector_t) {200, 800};
const vector_t OBSTACLE_LVLTHREE4_CENT = (vector_t) {800, 800};
const vector_t OBSTACLE_LVLTHREE5_CENT = (vector_t) {500, 245};

const vector_t OBSTACLE_LVLFOUR1_CENT = (vector_t) {500, 800};
const vector_t OBSTACLE_LVLFOUR2_CENT = (vector_t) {950, 120};
const vector_t OBSTACLE_LVLFOUR3_CENT = (vector_t) {50, 680};

const rgb_color_t BLUE = (rgb_color_t){.r = 0.0, .g = 0.0, .b = 1.0};
const rgb_color_t YELLOW = (rgb_color_t){.r = 1.0, .g = 1.0, .b = 0.0};
const rgb_color_t PURPLE = (rgb_color_t){.r = 0.75, .g = 0.0, .b = 1.0};

void add_obstacle(scene_t *scene, body_t *player, vector_t center, double base, double height, rgb_color_t color) {
  body_t *new_obstacle = body_init(draw_rect((vector_t){center.x, center.y + height/2}, base, height),
                                   OBSTACLE_MASS, color);
  scene_add_hidden_body(scene, new_obstacle);
  create_exit_collision(scene, player, new_obstacle);
}

void add_obstacle2(scene_t *scene, body_t *player1, body_t *player2, vector_t center, double base, double height, rgb_color_t color) {
  body_t *new_obstacle = body_init(draw_rect((vector_t){center.x, center.y + height/2}, base, height),
                                   OBSTACLE_MASS, color);
  scene_add_hidden_body(scene, new_obstacle);
  create_exit_collision(scene, player1, new_obstacle);
  create_exit_collision(scene, player2, new_obstacle);
}

void add_level_one_obstacles(scene_t *scene, body_t *player1, body_t *player2){
  add_obstacle(scene, player1, OBSTACLE_LVLONE1_CENT , OBSTACLE_BASE, OBSTACLE_HEIGHT, BLUE);
  add_obstacle(scene, player2, OBSTACLE_LVLONE2_CENT, OBSTACLE_BASE, OBSTACLE_HEIGHT, YELLOW);
  add_obstacle2(scene, player1, player2, OBSTACLE_LVLONE3_CENT, OBSTACLE_BASE, OBSTACLE_HEIGHT, PURPLE);
}

void add_level_two_obstacles(scene_t *scene, body_t *player1, body_t *player2){
  add_obstacle(scene, player2, OBSTACLE_LVLTWO1_CENT, 3 * OBSTACLE_BASE, OBSTACLE_HEIGHT, YELLOW);
  add_obstacle(scene, player1, OBSTACLE_LVLTWO2_CENT, 3 * OBSTACLE_BASE, OBSTACLE_HEIGHT, BLUE);
  add_obstacle(scene, player1, OBSTACLE_LVLTWO3_CENT, 3 * OBSTACLE_BASE, OBSTACLE_HEIGHT, BLUE);
  add_obstacle(scene, player2, OBSTACLE_LVLTWO4_CENT, 3 * OBSTACLE_BASE, OBSTACLE_HEIGHT, YELLOW);
  add_obstacle(scene, player2, OBSTACLE_LVLTWO5_CENT, OBSTACLE_BASE, OBSTACLE_HEIGHT, YELLOW);
  add_obstacle(scene, player1, OBSTACLE_LVLTWO6_CENT, OBSTACLE_BASE, OBSTACLE_HEIGHT, BLUE);
  add_obstacle2(scene, player1, player2, OBSTACLE_LVLTWO7_CENT, 3 * OBSTACLE_BASE, OBSTACLE_HEIGHT, PURPLE);
}

void add_level_three_obstacles(scene_t *scene, body_t *player1, body_t *player2){
  add_obstacle(scene, player1, OBSTACLE_LVLTHREE1_CENT, 2 * OBSTACLE_BASE, OBSTACLE_HEIGHT, BLUE);
  add_obstacle(scene, player2, OBSTACLE_LVLTHREE2_CENT, 2 * OBSTACLE_BASE, OBSTACLE_HEIGHT, YELLOW);
  add_obstacle(scene, player1, OBSTACLE_LVLTHREE3_CENT, 4 * OBSTACLE_BASE, OBSTACLE_HEIGHT, BLUE);
  add_obstacle(scene, player2, OBSTACLE_LVLTHREE4_CENT, 4 * OBSTACLE_BASE, OBSTACLE_HEIGHT, YELLOW);
  add_obstacle2(scene, player1, player2, OBSTACLE_LVLTHREE5_CENT, OBSTACLE_BASE, OBSTACLE_HEIGHT, PURPLE);
}

void add_level_four_obstacles(scene_t *scene, body_t *player1, body_t *player2){
  add_obstacle(scene, player1, OBSTACLE_LVLFOUR1_CENT, OBSTACLE_BASE, OBSTACLE_HEIGHT, BLUE);
  add_obstacle(scene, player2, OBSTACLE_LVLFOUR2_CENT, OBSTACLE_BASE, OBSTACLE_HEIGHT, YELLOW);
  add_obstacle2(scene, player1, player2, OBSTACLE_LVLFOUR3_CENT, OBSTACLE_BASE, OBSTACLE_HEIGHT, PURPLE);
}