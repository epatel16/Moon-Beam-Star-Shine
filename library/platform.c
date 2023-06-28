#include "platform.h"
#include "list.h"
#include "draw.h"
#include "body.h"
#include "scene.h"
#include "forces.h"
#include <math.h>
#include <stdlib.h>

const rgb_color_t BLCK = (rgb_color_t){.r = 0.0, .g = 0.0, .b = 0.0};

const double PLAT_MASS = INFINITY;
const double GRV_CNST = 700;
const double WLL_HEIGHT = 16;

const vector_t PLAT_LVLONE1_CENT = (vector_t) {600, 660};
const double PLAT_LVLONE1_LENGTH = 200;
const double PLAT_LVLONE1_HEIGHT = 80;
const vector_t PLAT_LVLONE2_CENT = (vector_t) {700, 590};
const double PLAT_LVLONE2_LENGTH = 200;
const double PLAT_LVLONE2_HEIGHT = 55;
const vector_t PLAT_LVLONE3_CENT = (vector_t) {940, 800};
const double PLAT_LVLONE3_LENGTH = 110;
const vector_t PLAT_LVLONE4_CENT = (vector_t) {60, 360};
const double PLAT_LVLONE4_LENGTH = 120;
const vector_t PLAT_LVLONE5_CENT = (vector_t) {950, 535};
const double PLAT_LVLONE5_LENGTH = 70;
const vector_t PLAT_LVLONE6_CENT = (vector_t) {150, 175};
const double PLAT_LVLONE6_LENGTH = 300;
const vector_t PLAT_LVLONE7_CENT = (vector_t) {250, 300};
const double PLAT_LVLONE7_LENGTH = 500;
const vector_t PLAT_LVLONE8_CENT = (vector_t) {355, 650};
const double PLAT_LVLONE8_LENGTH = 680;
const vector_t PLAT_LVLONE9_CENT = (vector_t) {650, 200};
const double PLAT_LVLONE9_LENGTH = 300;
const vector_t PLAT_LVLONE10_CENT = (vector_t) {500, 250};
const double PLAT_LVLONE10_LENGTH = 115;
const vector_t PLAT_LVLONE11_CENT = (vector_t) {942, 87.5};
const double PLAT_LVLONE11_LENGTH = 100;
const vector_t PLAT_LVLONE12_CENT = (vector_t) {692, 450};
const double PLAT_LVLONE12_LENGTH = 600;
const vector_t PLAT_LVLONE13_CENT = (vector_t) {392, 489};
const double PLAT_LVLONE13_LENGTH = 92;
const vector_t PLAT_LVLONE14_CENT = (vector_t) {295, 527};
const double PLAT_LVLONE14_LENGTH = 200;
const vector_t PLAT_LVLONE15_CENT = (vector_t) {592, 850};
const double PLAT_LVLONE15_LENGTH = 800;

const vector_t PLAT_LVLTWO1_CENT = (vector_t) {375, 300};
const double PLAT_LVLTWO1_LENGTH = 750;
const vector_t PLAT_LVLTWO2_CENT = (vector_t) {550, 125};
const double PLAT_LVLTWO2_LENGTH = 200;
const vector_t PLAT_LVLTWO3_CENT = (vector_t) {250, 125};
const double PLAT_LVLTWO3_LENGTH = 200;
const vector_t PLAT_LVLTWO4_CENT = (vector_t) {584, 600};
const double PLAT_LVLTWO4_LENGTH = 800;
const vector_t PLAT_LVLTWO5_CENT = (vector_t) {216, 800};
const double PLAT_LVLTWO5_LENGTH = 400;
const vector_t PLAT_LVLTWO6_CENT = (vector_t) {690, 800};
const double PLAT_LVLTWO6_LENGTH = 300;
const vector_t PLAT_LVLTWO7_CENT = (vector_t) {902, 106};
const double PLAT_LVLTWO7_LENGTH = 180;
const double PLAT_LVLTWO7_HEIGHT = 180;
const vector_t PLAT_LVLTWO8_CENT = (vector_t) {785.75, 56};
const double PLAT_LVLTWO8_LENGTH = 80;
const double PLAT_LVLTWO8_HEIGHT = 80;


const vector_t PLAT_LVLTHREE1_CENT = (vector_t) {225, 800};
const double PLAT_LVLTHREE1_LENGTH = 434;
const vector_t PLAT_LVLTHREE2_CENT = (vector_t) {770, 800};
const double PLAT_LVLTHREE2_LENGTH = 434;
const vector_t PLAT_LVLTHREE3_CENT = (vector_t) {79, 600};
const double PLAT_LVLTHREE3_LENGTH = 158;
const vector_t PLAT_LVLTHREE4_CENT = (vector_t) {921, 600};
const double PLAT_LVLTHREE4_LENGTH = 158;
const vector_t PLAT_LVLTHREE5_CENT = (vector_t) {150, 302.5};
const double PLAT_LVLTHREE5_LENGTH = 605;
const vector_t PLAT_LVLTHREE6_CENT = (vector_t) {850, 302.5};
const double PLAT_LVLTHREE6_LENGTH = 605;
const vector_t PLAT_LVLTHREE7_CENT = (vector_t) {500, 600};
const double PLAT_LVLTHREE7_LENGTH = 395;
const vector_t PLAT_LVLTHREE8_CENT = (vector_t) {310, 355};
const double PLAT_LVLTHREE8_LENGTH = 470;
const vector_t PLAT_LVLTHREE9_CENT = (vector_t) {690, 355};
const double PLAT_LVLTHREE9_LENGTH = 470;
const vector_t PLAT_LVLTHREE10_CENT = (vector_t) {380, 125};
const double PLAT_LVLTHREE10_LENGTH = 155;
const vector_t PLAT_LVLTHREE11_CENT = (vector_t) {620, 125};
const double PLAT_LVLTHREE11_LENGTH = 155;
const vector_t PLAT_LVLTHREE12_CENT = (vector_t) {500, 410};
const double PLAT_LVLTHREE12_LENGTH = 140;
const vector_t PLAT_LVLTHREE13_CENT = (vector_t) {500, 243};
const double PLAT_LVLTHREE13_LENGTH = 120;
const vector_t PLAT_LVLTHREE14_CENT = (vector_t) {330, 345};
const double PLAT_LVLTHREE14_LENGTH = 50;
const vector_t PLAT_LVLTHREE15_CENT = (vector_t) {670, 345};
const double PLAT_LVLTHREE15_LENGTH = 50;
const vector_t PLAT_LVLTHREE16_CENT = (vector_t) {500, 645};
const double PLAT_LVLTHREE16_LENGTH = 40;
const double PLAT_LVLTHREE16_HEIGHT = 100;

const vector_t PLAT_LVLFOUR1_CENT = (vector_t) {574, 800};
const double PLAT_LVLFOUR1_LENGTH = 820;
const vector_t PLAT_LVLFOUR2_CENT = (vector_t) {212, 685};
const double PLAT_LVLFOUR2_LENGTH = 390;
const vector_t PLAT_LVLFOUR3_CENT = (vector_t) {805, 515};
const double PLAT_LVLFOUR3_LENGTH = 570;
const vector_t PLAT_LVLFOUR4_CENT = (vector_t) {400, 631};
const double PLAT_LVLFOUR4_LENGTH = 116;
const vector_t PLAT_LVLFOUR5_CENT = (vector_t) {285, 230};
const double PLAT_LVLFOUR5_LENGTH = 250;
const vector_t PLAT_LVLFOUR6_CENT = (vector_t) {950, 400};
const double PLAT_LVLFOUR6_LENGTH = 100;
const vector_t PLAT_LVLFOUR7_CENT = (vector_t) {950, 600};
const double PLAT_LVLFOUR7_LENGTH = 100;
const vector_t PLAT_LVLFOUR8_CENT = (vector_t) {505, 580};
const double PLAT_LVLFOUR8_LENGTH = 220;
const vector_t PLAT_LVLFOUR9_CENT = (vector_t) {900, 583};
const double PLAT_LVLFOUR9_LENGTH = 50;
const vector_t PLAT_LVLFOUR10_CENT = (vector_t) {780, 470};
const double PLAT_LVLFOUR10_LENGTH = 50;
const vector_t PLAT_LVLFOUR11_CENT = (vector_t) {60, 60};
const double PLAT_LVLFOUR11_LENGTH = 120;
const double PLAT_LVLFOUR11_HEIGHT = 120;
const vector_t PLAT_LVLFOUR12_CENT = (vector_t) {355, 337.5};
const double PLAT_LVLFOUR12_LENGTH = 110;
const double PLAT_LVLFOUR12_HEIGHT = 195;
const vector_t PLAT_LVLFOUR13_CENT = (vector_t) {884, 65};
const double PLAT_LVLFOUR13_LENGTH = 200;
const double PLAT_LVLFOUR13_HEIGHT = 130;

void add_platform(scene_t *scene, body_t *player1, body_t *player2, body_t *block, vector_t center, double length, double height) {
  body_t *plat = body_init_more_info(
      draw_rect((vector_t){center.x, center.y}, length, height),
      PLAT_MASS, BLCK, length, height);
  scene_add_hidden_body(scene, plat);
  create_plat_collision(scene, GRV_CNST, player1, plat);
  create_plat_collision(scene, GRV_CNST, player2, plat);
  create_plat_collision(scene, GRV_CNST, block, plat);
}

void add_level_one_platforms(scene_t *scene, body_t *player1, body_t *player2, body_t *block){
  //WINDOW:
  add_platform(scene, player1, player2, block, PLAT_LVLONE1_CENT, PLAT_LVLONE1_LENGTH, PLAT_LVLONE1_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE2_CENT, PLAT_LVLONE2_LENGTH, PLAT_LVLONE2_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE3_CENT, PLAT_LVLONE3_LENGTH, PLAT_LVLONE3_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLONE4_CENT, PLAT_LVLONE4_LENGTH, PLAT_LVLONE4_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLONE5_CENT, PLAT_LVLONE5_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE6_CENT, PLAT_LVLONE6_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE7_CENT, PLAT_LVLONE7_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE8_CENT, PLAT_LVLONE8_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE9_CENT, PLAT_LVLONE9_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE10_CENT, WLL_HEIGHT, PLAT_LVLONE10_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLONE11_CENT, PLAT_LVLONE11_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE12_CENT, PLAT_LVLONE12_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE13_CENT, WLL_HEIGHT, PLAT_LVLONE13_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLONE14_CENT, PLAT_LVLONE14_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLONE15_CENT, PLAT_LVLONE15_LENGTH, WLL_HEIGHT);
}

void add_level_two_platforms(scene_t *scene, body_t *player1, body_t *player2, body_t *block){
  //Walls:
  add_platform(scene, player1, player2, block, PLAT_LVLTWO1_CENT, PLAT_LVLTWO1_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTWO2_CENT, PLAT_LVLTWO2_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTWO3_CENT, PLAT_LVLTWO3_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTWO4_CENT, PLAT_LVLTWO4_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTWO5_CENT, PLAT_LVLTWO5_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTWO6_CENT, PLAT_LVLTWO6_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTWO7_CENT, PLAT_LVLTWO7_LENGTH, PLAT_LVLTWO7_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTWO8_CENT, PLAT_LVLTWO8_LENGTH, PLAT_LVLTWO8_HEIGHT);
}

void add_level_three_platforms(scene_t *scene, body_t *player1, body_t *player2, body_t *block){
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE1_CENT, PLAT_LVLTHREE1_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE2_CENT, PLAT_LVLTHREE2_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE3_CENT, PLAT_LVLTHREE3_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE4_CENT, PLAT_LVLTHREE4_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE5_CENT, WLL_HEIGHT, PLAT_LVLTHREE5_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE6_CENT, WLL_HEIGHT, PLAT_LVLTHREE6_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE7_CENT, PLAT_LVLTHREE7_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE8_CENT, WLL_HEIGHT, PLAT_LVLTHREE8_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE9_CENT, WLL_HEIGHT, PLAT_LVLTHREE9_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE10_CENT, PLAT_LVLTHREE10_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE11_CENT, PLAT_LVLTHREE11_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE12_CENT, PLAT_LVLTHREE12_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE13_CENT, PLAT_LVLTHREE13_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE14_CENT, PLAT_LVLTHREE14_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE15_CENT, PLAT_LVLTHREE15_LENGTH, WLL_HEIGHT); 
  add_platform(scene, player1, player2, block, PLAT_LVLTHREE16_CENT, PLAT_LVLTHREE16_LENGTH, PLAT_LVLTHREE16_HEIGHT);
}

void add_level_four_platforms(scene_t *scene, body_t *player1, body_t *player2, body_t *block){
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR1_CENT, PLAT_LVLFOUR1_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR2_CENT, PLAT_LVLFOUR2_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR3_CENT, WLL_HEIGHT, PLAT_LVLFOUR3_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR4_CENT, WLL_HEIGHT, PLAT_LVLFOUR4_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR5_CENT, PLAT_LVLFOUR5_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR6_CENT, PLAT_LVLFOUR6_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR7_CENT, PLAT_LVLFOUR7_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR8_CENT, PLAT_LVLFOUR8_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR9_CENT, WLL_HEIGHT, PLAT_LVLFOUR9_LENGTH);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR10_CENT, PLAT_LVLFOUR10_LENGTH, WLL_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR11_CENT, PLAT_LVLFOUR11_LENGTH, PLAT_LVLFOUR11_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR12_CENT, PLAT_LVLFOUR12_LENGTH, PLAT_LVLFOUR12_HEIGHT);
  add_platform(scene, player1, player2, block, PLAT_LVLFOUR13_CENT, PLAT_LVLFOUR13_LENGTH, PLAT_LVLFOUR13_HEIGHT);
}
