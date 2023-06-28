#include "gem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "draw.h"
#include "list.h"
#include "body.h"
#include "scene.h"
#include "forces.h"
#include "sdl_wrapper.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

const size_t GEM_RADIUS = 15;
const size_t GEM_MASS = 1;
const size_t GEM_INC = 2;
const size_t GEM_DEC = 5;

const vector_t GEM_LVLONE1_CENT = (vector_t) {250, 100};
const vector_t GEM_LVLONE2_CENT = (vector_t) {750, 300};
const vector_t GEM_LVLONE3_CENT = (vector_t) {250, 585};
const vector_t GEM_LVLONE4_CENT = (vector_t) {750, 775};
const vector_t GEM_LVLONE5_CENT = (vector_t) {250, 925};
const vector_t GEM_LVLONE6_CENT = (vector_t) {750, 100};
const vector_t GEM_LVLONE7_CENT = (vector_t) {250, 400};
const vector_t GEM_LVLONE8_CENT = (vector_t) {750, 515};
const vector_t GEM_LVLONE9_CENT = (vector_t) {250, 750};
const vector_t GEM_LVLONE10_CENT = (vector_t) {750, 925};

const vector_t GEM_LVLTWO1_CENT = (vector_t) {250, 60};
const vector_t GEM_LVLTWO2_CENT = (vector_t) {550, 180};
const vector_t GEM_LVLTWO3_CENT = (vector_t) {250, 400};
const vector_t GEM_LVLTWO4_CENT = (vector_t) {75, 550};
const vector_t GEM_LVLTWO5_CENT = (vector_t) {710, 700};
const vector_t GEM_LVLTWO6_CENT = (vector_t) {250, 900};
const vector_t GEM_LVLTWO7_CENT = (vector_t) {550, 60};
const vector_t GEM_LVLTWO8_CENT = (vector_t) {250, 180};
const vector_t GEM_LVLTWO9_CENT = (vector_t) {600, 400};
const vector_t GEM_LVLTWO10_CENT = (vector_t) {75, 400};
const vector_t GEM_LVLTWO11_CENT = (vector_t) {300, 700};
const vector_t GEM_LVLTWO12_CENT = (vector_t) {710, 900};

const vector_t GEM_LVLTHREE1_CENT = (vector_t) {800, 900};
const vector_t GEM_LVLTHREE2_CENT = (vector_t) {775, 700};
const vector_t GEM_LVLTHREE3_CENT = (vector_t) {775, 500};
const vector_t GEM_LVLTHREE4_CENT = (vector_t) {775, 300};
const vector_t GEM_LVLTHREE5_CENT = (vector_t) {775, 100};
const vector_t GEM_LVLTHREE6_CENT = (vector_t) {375, 200};
const vector_t GEM_LVLTHREE7_CENT = (vector_t) {200, 900};
const vector_t GEM_LVLTHREE8_CENT = (vector_t) {225, 700};
const vector_t GEM_LVLTHREE9_CENT = (vector_t) {225, 500};
const vector_t GEM_LVLTHREE10_CENT = (vector_t) {225, 300};
const vector_t GEM_LVLTHREE11_CENT = (vector_t) {225, 100};
const vector_t GEM_LVLTHREE12_CENT = (vector_t) {625, 200};

const vector_t GEM_LVLFOUR1_CENT = (vector_t) {300, 100};
const vector_t GEM_LVLFOUR2_CENT = (vector_t) {850, 300};
const vector_t GEM_LVLFOUR3_CENT = (vector_t) {850, 700};
const vector_t GEM_LVLFOUR4_CENT = (vector_t) {500, 925};
const vector_t GEM_LVLFOUR5_CENT = (vector_t) {700, 100};
const vector_t GEM_LVLFOUR6_CENT = (vector_t) {850, 500};
const vector_t GEM_LVLFOUR7_CENT = (vector_t) {200, 350};
const vector_t GEM_LVLFOUR8_CENT = (vector_t) {200, 550};

const rgb_color_t BLK = (rgb_color_t){.r = 0.0, .g = 0.0, .b = 0.0};

void add_gem(scene_t *scene, body_t *coll, vector_t center, char *draw){
  double width = GEM_RADIUS * sqrt(3);
  double height = 2 * GEM_RADIUS - GEM_DEC + GEM_INC * sqrt(3)/2;
  double shift = GEM_INC * sqrt(3)/4;
  body_t *gem = body_init_more_info(draw_gem(GEM_RADIUS, (vector_t) {center.x, center.y + shift}), GEM_MASS, BLK,
                                    width, height);
  body_set_texture(gem, sdl_load_image(draw));
  scene_add_body(scene, gem);
  create_disappear_collision(scene, gem, coll);
}

void add_level_one_gems(scene_t *scene, body_t *player1, body_t *player2) {
  add_gem(scene, player1, GEM_LVLONE1_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLONE2_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLONE3_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLONE4_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLONE5_CENT, "assets/stargem.png");
  add_gem(scene, player2, GEM_LVLONE6_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLONE7_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLONE8_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLONE9_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLONE10_CENT, "assets/moongem.png");
}

void add_level_two_gems(scene_t *scene, body_t *player1, body_t *player2) {
  add_gem(scene, player1, GEM_LVLTWO1_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTWO2_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTWO3_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTWO4_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTWO5_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTWO6_CENT, "assets/stargem.png");
  add_gem(scene, player2, GEM_LVLTWO7_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTWO8_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTWO9_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTWO10_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTWO11_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTWO12_CENT, "assets/moongem.png");
}

void add_level_three_gems(scene_t *scene, body_t *player1, body_t *player2) {
  add_gem(scene, player1, GEM_LVLTHREE1_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTHREE2_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTHREE3_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTHREE4_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTHREE5_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLTHREE6_CENT, "assets/stargem.png");
  add_gem(scene, player2, GEM_LVLTHREE7_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTHREE8_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTHREE9_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTHREE10_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTHREE11_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLTHREE12_CENT, "assets/moongem.png");
}

void add_level_four_gems(scene_t *scene, body_t *player1, body_t *player2) {
  add_gem(scene, player1, GEM_LVLFOUR1_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLFOUR2_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLFOUR3_CENT, "assets/stargem.png");
  add_gem(scene, player1, GEM_LVLFOUR4_CENT, "assets/stargem.png");
  add_gem(scene, player2, GEM_LVLFOUR5_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLFOUR6_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLFOUR7_CENT, "assets/moongem.png");
  add_gem(scene, player2, GEM_LVLFOUR8_CENT, "assets/moongem.png");
}