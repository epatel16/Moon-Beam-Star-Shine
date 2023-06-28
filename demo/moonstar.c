#include "body.h"
#include "forces.h"
#include "info.h"
#include "scene.h"
#include "draw.h"
#include "platform.h"
#include "obstacle.h"
#include "gem.h"
#include "sdl_wrapper.h"
#include "music.h"
#include "text.h"
#include <math.h>
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const vector_t WINDOW = (vector_t){.x = 1000, .y = 1000};

const double PLAYER_HORIZ_SPEED = 200.0;
const double PLAYER_VERT_SPEED = 400.0;
const double PLAYER1 = 1;
const double PLAYER2 = 2;
const double BLOCK_NUM = 3;

const size_t PLAYER_LENGTH = 60;
const size_t PLAYER_HEIGHT = 80;
const size_t PLAYER_MASS = 1000;

const size_t FDOOR_LENGTH = 10;
const size_t FDOOR_HEIGHT = 10;

const size_t BLOCK_LENGTH = 100;
const size_t BLOCK_MASS = 2000;

const size_t WALL_HEIGHT = 16;
const double WALL_MASS = INFINITY;

const size_t GEMS1 = 10;
const size_t GEMS2 = 12;
const size_t GEMS3 = 12;
const size_t GEMS4 = 8;

const size_t BUTTON_BASE = 30;
const size_t BUTTON_HEIGHT = 15;

const size_t PULLEY_LENGTH = 150;
const size_t PULLEY_HEIGHT = 25;
const size_t PULLEY_MASS = 100;
const vector_t PULLEY1 = (vector_t){500,410};
const vector_t PULLEY2 = (vector_t){700,30};
const rgb_color_t PULL_COLOR = (rgb_color_t){0.72, 0.72, 0.8};

const double GRAV_CONST = 700;
const double FAN_CONST = 15;
const double PULL_CONST = 700;

const double START_X = 250.0;
const double FACTOR = 2.0;

const size_t MAP = 0;
const size_t LEVEL1 = 1;
const size_t LEVEL2 = 2;
const size_t LEVEL3 = 3;
const size_t LEVEL4 = 4;
const size_t WIN = 5;
const size_t LOSE = 6;
const size_t INSTRUCT = 7;

const int LENGTH_DISPLAY_TIME = 14;
const int MSEC_TO_SEC = 1000;
const int SEC_TO_MIN = 60;
const int SEC_TO_TENS = 10;

const int GRADE_B_SEC = 60;
const int GRADE_C_SEC = 90;
const int GRADE_D_SEC = 120;
const int GRADE_E_SEC = 150;
const size_t GRADE_B = 66;
const size_t GRADE_C = 67;
const size_t GRADE_D = 68;
const size_t GRADE_E = 69;
const size_t GRADE_F = 70;

const int MAX_TIME_LEVEL_ONE = 60;
const int MAX_TIME_LEVEL_TWO = 60;
const int MAX_TIME_LEVEL_THREE = 60;
const int MAX_TIME_LEVEL_FOUR = 60;

const vector_t LEVEL_ONE_DOOR1 = {880, 910};
const vector_t LEVEL_ONE_DOOR2 = {950, 910};
const vector_t LEVEL_ONE_BODY1_CENTROID = {120, 56};
const vector_t LEVEL_ONE_BODY2_CENTROID = {120, 223};
const vector_t LEVEL_ONE_BLOCK = {400, 710};

const vector_t LEVEL_TWO_DOOR1 = {120, 860};
const vector_t LEVEL_TWO_DOOR2 = {50, 860};
const vector_t LEVEL_TWO_BODY1_CENTROID = {120, 56};
const vector_t LEVEL_TWO_BODY2_CENTROID = {50, 56};
const vector_t LEVEL_TWO_BLOCK = {600, 650};
const vector_t LEVEL_TWO_FANS = {85, 450};
const size_t LEVEL_TWO_FANS_LENGTH = 120;
const size_t LEVEL_TWO_FANS_HEIGHT = 300;

const vector_t LEVEL_THREE_DOOR1 = {470, 468};
const vector_t LEVEL_THREE_DOOR2 = {530, 468};
const vector_t LEVEL_THREE_BUTTON = {50, 810};
const vector_t LEVEL_THREE_BODY1_CENTROID = {950, 648};
const vector_t LEVEL_THREE_BODY2_CENTROID = {50, 640};
const vector_t LEVEL_THREE_BLOCK = {410, 830};

const vector_t LEVEL_THREE_FAN1 = {230, 300};
const size_t LEVEL_THREE_FAN1_LENGTH = 120;
const size_t LEVEL_THREE_FAN1_HEIGHT = 600;
const vector_t LEVEL_THREE_FAN2 = {770, 300};
const size_t LEVEL_THREE_FAN2_LENGTH = 120;
const size_t LEVEL_THREE_FAN2_HEIGHT = 600;

const vector_t LEVEL_FOUR_DOOR1 = {950, 860};
const vector_t LEVEL_FOUR_DOOR2 = {950, 658};
const vector_t LEVEL_FOUR_BUTTON = {350, 16};
const vector_t LEVEL_FOUR_BODY1_CENTROID = {960, 648};
const vector_t LEVEL_FOUR_BODY2_CENTROID = {60, 160};
const vector_t LEVEL_FOUR_BLOCK = {360, 485};

const vector_t LEVEL_FOUR_FAN1 = {200, 380};
const size_t LEVEL_FOUR_FAN1_LENGTH = 80;
const size_t LEVEL_FOUR_FAN1_HEIGHT = 300;
const vector_t LEVEL_FOUR_FAN2 = {850, 385};
const size_t LEVEL_FOUR_FAN2_LENGTH = 60;
const size_t LEVEL_FOUR_FAN2_HEIGHT = 530;

const size_t FANF_SHIFT = 2;
const size_t FANL_SHIFT = 1;

const rgb_color_t BLU = (rgb_color_t){.r = 0.0, .g = 0.0, .b = 1.0};
const rgb_color_t YLLOW = (rgb_color_t){.r = 1.0, .g = 1.0, .b = 0.0};
const rgb_color_t GREEN = (rgb_color_t){.r = 0.0, .g = 1.0, .b = 0.0};
const rgb_color_t GRAY = (rgb_color_t){.r = 0.2, .g = 0.2, .b = 0.2};
const rgb_color_t WHITE = (rgb_color_t){.r = 1.0, .g = 1.0, .b = 1.0};
const rgb_color_t BLACK = (rgb_color_t){.r = 0.0, .g = 0.0, .b = 0.0};
const rgb_color_t BACKGROUND = (rgb_color_t){.r = 0.36, .g = 0.27, .b = 0.035};

typedef struct state {
  scene_t *scene;
  size_t time_elapsed;
  size_t scene_num;
  size_t last_lvl;
  size_t curr_gem_ct;
  char *lvl1;
  char *lvl2;
  char *lvl3;
  char *lvl4;
  bool fan_off;
  bool grav;
  int start_time;
  int delt_time;
  char *display_time;
} state_t;

void create_gravity(state_t *s){
  create_fall(s->scene, GRAV_CONST, scene_get_body(s->scene, PLAYER1));
  create_fall(s->scene, GRAV_CONST, scene_get_body(s->scene, PLAYER2));
  create_fall(s->scene, GRAV_CONST, scene_get_body(s->scene, BLOCK_NUM));
}

void on_key(state_t *s, char key, key_event_type_t type, double held_time) {
  if (s->scene_num >= LEVEL1 && s->scene_num <= LEVEL4) {
    if (type == KEY_PRESSED) {
      switch (key) {
        case RIGHT_ARROW:
          body_set_xvelocity(scene_get_body(s->scene, PLAYER1), PLAYER_HORIZ_SPEED);
          if (!s->grav){
            create_gravity(s);
            s->grav = true;
          }
          break;
        case LEFT_ARROW:
          body_set_xvelocity(scene_get_body(s->scene, PLAYER1), -1 * PLAYER_HORIZ_SPEED);
          if (!s->grav){
            create_gravity(s);
            s->grav = true;
          }
          break;
        case UP_ARROW:
          if (fabs(body_get_velocity(scene_get_body(s->scene, PLAYER1)).y) == 0.0){
            body_add_impulse(scene_get_body(s->scene, PLAYER1), (vector_t){0, PLAYER_VERT_SPEED * PLAYER_MASS});
            if (!s->grav){
              create_gravity(s);
              s->grav = true;
            }
            music_play("assets/jump.wav", 0);
          }

          break;
        case 'd':
          body_set_xvelocity(scene_get_body(s->scene, PLAYER2), PLAYER_HORIZ_SPEED);
          if (!s->grav){
            create_gravity(s);
            s->grav = true;
          }
          break;
        case 'a':
          body_set_xvelocity(scene_get_body(s->scene, PLAYER2), -1 * PLAYER_HORIZ_SPEED);
          if (!s->grav){
            create_gravity(s);
            s->grav = true;
          }
          break;
        case 'w':
          if (fabs(body_get_velocity(scene_get_body(s->scene, PLAYER2)).y) == 0.0){
            body_add_impulse(scene_get_body(s->scene, PLAYER2), (vector_t){0, PLAYER_VERT_SPEED * PLAYER_MASS});
            if (!s->grav){
              create_gravity(s);
              s->grav = true;
            }
            music_play("assets/jump.wav", 0);
          }
          break;
      } 
    } 
    if (type == KEY_RELEASED) {
      switch (key) {
      case RIGHT_ARROW:
        body_set_xvelocity(scene_get_body(s->scene, PLAYER1), 0.0);
        body_set_xvelocity(scene_get_body(s->scene, BLOCK_NUM), 0.0);
        break;
      case LEFT_ARROW:
        body_set_xvelocity(scene_get_body(s->scene, PLAYER1), 0.0);
        body_set_xvelocity(scene_get_body(s->scene, BLOCK_NUM), 0.0);
        break;
      case 'd':
        body_set_xvelocity(scene_get_body(s->scene, PLAYER2), 0.0);
        body_set_xvelocity(scene_get_body(s->scene, BLOCK_NUM), 0.0);
        break;
      case 'a':
        body_set_xvelocity(scene_get_body(s->scene, PLAYER2), 0.0);
        body_set_xvelocity(scene_get_body(s->scene, BLOCK_NUM), 0.0);
        break;
      }
    }
  }
}

void add_doors(state_t *state, body_t *player1, body_t *player2, vector_t center1, vector_t center2) {
  body_t *fake_door_yellow = body_init(draw_rect(center1, FDOOR_LENGTH, FDOOR_HEIGHT), WALL_MASS, YLLOW);
  body_t *fake_door_blue = body_init(draw_rect(center2, FDOOR_LENGTH, FDOOR_HEIGHT), WALL_MASS, BLU);
  scene_add_hidden_body(state->scene, fake_door_yellow);
  scene_add_hidden_body(state->scene, fake_door_blue);
  create_door_collision(state->scene, fake_door_yellow, player1, fake_door_blue, player2);
}

void add_fan(state_t *state, body_t *player1, body_t *player2, vector_t center, double length, double height) {
  body_t *fan = body_init_more_info(draw_rect(center, length, height), WALL_MASS, GRAY, length, height);
  scene_add_body(state->scene, fan);
  create_fan(state->scene, FAN_CONST, player1, fan);
  create_fan(state->scene, FAN_CONST, player2, fan);
}

void add_button(state_t *state, body_t *player1, body_t *player2, body_t *block, vector_t center) {
  body_t *button = body_init(draw_rect(center, BUTTON_BASE, BUTTON_HEIGHT), WALL_MASS, GREEN);
  scene_add_hidden_body(state->scene, button);
  create_button(state->scene, player1, button);
  create_button(state->scene, player2, button);
  create_button(state->scene, block, button);
}

char * calculate_time(state_t *state){
  char* text = malloc(sizeof(char) * LENGTH_DISPLAY_TIME);
  int current_time = SDL_GetTicks();
  state-> delt_time = (current_time- state->start_time) / MSEC_TO_SEC;
  int time_left = state->delt_time;
  int minutes;
  int tens;
  if((int)(time_left / SEC_TO_MIN)==0){
    minutes = 0;
  }
  else{
    minutes = (int)(time_left / SEC_TO_MIN);
  }
  time_left -= minutes * SEC_TO_MIN;
  if((int)(time_left / SEC_TO_TENS)==0){
    tens = 0;
  }
  else{
    tens = (int)(time_left / SEC_TO_TENS);
  }
  time_left -= tens * SEC_TO_TENS;
  sprintf(text ,"time: %d:%d%d", minutes, tens, time_left);

  return text;
}

char calculate_grade(state_t *state){
  int grade;
  if (state->delt_time < GRADE_B_SEC){
    grade = GRADE_B;
  }
  else if (state->delt_time < GRADE_C_SEC){
    grade = GRADE_C;
  }
  else if (state->delt_time < GRADE_D_SEC){
    grade = GRADE_D;
  }
  else if (state->delt_time < GRADE_E_SEC){
    grade = GRADE_E;
  }
  else{
    grade = GRADE_F;
  }
  if((state->last_lvl == LEVEL1 && state->curr_gem_ct == GEMS1) || (state->last_lvl == LEVEL2 && state->curr_gem_ct == GEMS2) || (state->last_lvl == LEVEL3 && state->curr_gem_ct == GEMS3) ||  (state->last_lvl == LEVEL4 && state->curr_gem_ct == GEMS4)){
    grade--;
  }
  char final_grade;
  final_grade = (char) grade;
  return final_grade;
}

void level_one_set_up(state_t *state, body_t *player1, body_t *player2, body_t *block){
  state->scene_num = LEVEL1;
  state->last_lvl = LEVEL1;
  add_level_one_platforms(state->scene, player1, player2, block);
  add_level_one_obstacles(state->scene, player1, player2);
  add_level_one_gems(state->scene, player1, player2);
  add_doors(state, player1, player2, (vector_t)LEVEL_ONE_DOOR1, (vector_t)LEVEL_ONE_DOOR2);
  body_set_centroid(player1, (vector_t) LEVEL_ONE_BODY1_CENTROID);
  body_set_centroid(player2, (vector_t) LEVEL_ONE_BODY2_CENTROID);
  body_set_centroid(block, (vector_t) LEVEL_ONE_BLOCK);
}

void level_two_set_up(state_t *state, body_t *player1, body_t *player2, body_t *block){
  state->scene_num = LEVEL2;
  state->last_lvl = LEVEL2;
  add_level_two_platforms(state->scene, player1, player2, block);
  add_level_two_obstacles(state->scene, player1, player2);
  add_level_two_gems(state->scene, player1, player2);
  add_doors(state, player1, player2, (vector_t)LEVEL_TWO_DOOR1, (vector_t)LEVEL_TWO_DOOR2);
  add_fan(state, player1, player2, (vector_t)LEVEL_TWO_FANS, LEVEL_TWO_FANS_LENGTH, LEVEL_TWO_FANS_HEIGHT);
  body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/wind2.png"));
  body_set_centroid(player1, (vector_t) LEVEL_TWO_BODY1_CENTROID);
  body_set_centroid(player2, (vector_t) LEVEL_TWO_BODY2_CENTROID);
  body_set_centroid(block, (vector_t) LEVEL_TWO_BLOCK);
}

void level_three_set_up(state_t *state, body_t *player1, body_t *player2, body_t *block){
  state->scene_num = LEVEL3;
  state->last_lvl = LEVEL3;
  add_level_three_platforms(state->scene, player1, player2, block);
  add_level_three_obstacles(state->scene, player1, player2);
  add_level_three_gems(state->scene, player1, player2);
  add_doors(state, player1, player2, (vector_t)LEVEL_THREE_DOOR1, (vector_t)LEVEL_THREE_DOOR2);
  add_button(state, player1, player2, block, (vector_t)LEVEL_THREE_BUTTON);
  add_fan(state, player1, player2, (vector_t)LEVEL_THREE_FAN1, LEVEL_THREE_FAN1_LENGTH, LEVEL_THREE_FAN1_HEIGHT );
  add_fan(state, player1, player2, (vector_t)LEVEL_THREE_FAN2, LEVEL_THREE_FAN2_LENGTH, LEVEL_THREE_FAN2_HEIGHT);
  body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/wind3.png"));
  body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANF_SHIFT), sdl_load_image("assets/wind3.png"));
  body_set_centroid(player1, (vector_t) LEVEL_THREE_BODY1_CENTROID);
  body_set_centroid(player2, (vector_t) LEVEL_THREE_BODY2_CENTROID);
  body_set_centroid(block, (vector_t) LEVEL_THREE_BLOCK);
}

void level_four_set_up(state_t *state, body_t *player1, body_t *player2, body_t *block){
  state->scene_num = LEVEL4;
  state->last_lvl = LEVEL4;
  add_level_four_platforms(state->scene, player1, player2, block);
  add_level_four_obstacles(state->scene, player1, player2);
  add_level_four_gems(state->scene, player1, player2);
  add_doors(state, player1, player2, (vector_t)LEVEL_FOUR_DOOR1, (vector_t)LEVEL_FOUR_DOOR2);
  add_button(state, player1, player2, block, (vector_t)LEVEL_FOUR_BUTTON);
  add_fan(state, player1, player2, (vector_t)LEVEL_FOUR_FAN1, LEVEL_FOUR_FAN1_LENGTH , LEVEL_FOUR_FAN1_HEIGHT);
  add_fan(state, player1, player2, (vector_t)LEVEL_FOUR_FAN2, LEVEL_FOUR_FAN2_LENGTH, LEVEL_FOUR_FAN2_HEIGHT);
  body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/wind4r.png"));
  body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANF_SHIFT), sdl_load_image("assets/wind4l.png"));
  body_set_centroid(player1, (vector_t) LEVEL_FOUR_BODY1_CENTROID);
  body_set_centroid(player2, (vector_t) LEVEL_FOUR_BODY2_CENTROID);
  body_set_centroid(block, (vector_t) LEVEL_FOUR_BLOCK);
}

void init_levels(state_t *state, size_t lvl) {
  music_bkgd_stop();
  state->time_elapsed = 0;
  state->grav = false;
  state->scene = scene_init();
  state->curr_gem_ct = 0;
  state->start_time = SDL_GetTicks();
  state->display_time = malloc(sizeof(char) * LENGTH_DISPLAY_TIME);

  body_t *b = body_init_more_info(draw_rect((vector_t){WINDOW.x/2, WINDOW.y/2}, WINDOW.x, WINDOW.y), WALL_MASS, WHITE,
                                  WINDOW.x, WINDOW.y);
  scene_add_body(state->scene, b);    

  body_t *player1 = body_init_more_info(draw_rect((vector_t){0,0}, PLAYER_LENGTH, PLAYER_HEIGHT), PLAYER_MASS, YLLOW, PLAYER_LENGTH, PLAYER_HEIGHT);
  body_set_texture(player1, sdl_load_image("assets/starshine.png"));
  scene_add_body(state->scene, player1);
  
  body_t *player2 = body_init_more_info(draw_rect((vector_t){0,0}, PLAYER_LENGTH, PLAYER_HEIGHT), PLAYER_MASS, BLU, PLAYER_LENGTH, PLAYER_HEIGHT);
  body_set_texture(player2, sdl_load_image("assets/moonbeam.png"));
  scene_add_body(state->scene, player2);

  body_t *block = body_init_more_info(draw_rect((vector_t){0,0}, BLOCK_LENGTH, BLOCK_LENGTH), BLOCK_MASS, GRAY, BLOCK_LENGTH, BLOCK_LENGTH);
  body_set_texture(block, sdl_load_image("assets/block.png"));
  scene_add_body(state->scene, block);
  
  body_t *ground = body_init_more_info(
    draw_rect((vector_t){WINDOW.x / 2, WALL_HEIGHT/2}, WINDOW.x, WALL_HEIGHT),
    WALL_MASS, BLACK, WINDOW.x, WALL_HEIGHT);
  scene_add_hidden_body(state->scene, ground);

  create_plat_collision(state->scene, GRAV_CONST, player1, ground);
  create_plat_collision(state->scene, GRAV_CONST, player2, ground);
  create_plat_collision(state->scene, GRAV_CONST, block, ground);

  body_t *ceiling = body_init_more_info(
    draw_rect((vector_t){WINDOW.x / 2, WINDOW.y - WALL_HEIGHT/2}, WINDOW.x, WALL_HEIGHT),
    WALL_MASS, BLACK, WINDOW.x, WALL_HEIGHT);
  scene_add_hidden_body(state->scene, ceiling);
  create_plat_collision(state->scene, GRAV_CONST, player1, ceiling);
  create_plat_collision(state->scene, GRAV_CONST, player2, ceiling);
  create_plat_collision(state->scene, GRAV_CONST, block, ceiling);

  body_t *left_wall = body_init_more_info(
      draw_rect((vector_t){WALL_HEIGHT/2, WINDOW.y/2}, WALL_HEIGHT, WINDOW.y),
      WALL_MASS, BLACK, WALL_HEIGHT, WINDOW.y);
  scene_add_hidden_body(state->scene, left_wall);
  create_plat_collision(state->scene, GRAV_CONST, player1, left_wall);
  create_plat_collision(state->scene, GRAV_CONST, player2, left_wall);
  create_plat_collision(state->scene, GRAV_CONST, block, left_wall);

  body_t *right_wall = body_init_more_info(
      draw_rect((vector_t){WINDOW.x - WALL_HEIGHT/2, WINDOW.y/2}, WALL_HEIGHT, WINDOW.y),
      WALL_MASS, BLACK, WALL_HEIGHT, WINDOW.y);
  scene_add_hidden_body(state->scene, right_wall);
  create_plat_collision(state->scene, GRAV_CONST, player1, right_wall);
  create_plat_collision(state->scene, GRAV_CONST, player2, right_wall); 
  create_plat_collision(state->scene, GRAV_CONST, block, right_wall);

  create_plat_collision(state->scene, GRAV_CONST, player1, block);
  create_plat_collision(state->scene, GRAV_CONST, player2, block);

  if (lvl == LEVEL1) { 
    body_set_texture(b, sdl_load_image("assets/level1.png"));
    level_one_set_up(state, player1, player2, block);
  }
  if (lvl == LEVEL2) {
    body_set_texture(b, sdl_load_image("assets/level2.png"));
    level_two_set_up(state, player1, player2, block);
  }
  if (lvl == LEVEL3) {
    body_set_texture(b, sdl_load_image("assets/level3.png"));
    level_three_set_up(state, player1, player2, block);
  }
  if (lvl == LEVEL4) {
    body_set_texture(b, sdl_load_image("assets/level4.png"));
    body_t *pulley1 = body_init_more_info(
        draw_rect(PULLEY1, PULLEY_LENGTH, PULLEY_HEIGHT),
        PULLEY_MASS, PULL_COLOR, PULLEY_LENGTH, PULLEY_HEIGHT);
    scene_add_body(state->scene, pulley1);
    body_t *pulley2 = body_init_more_info(
        draw_rect(PULLEY2, PULLEY_LENGTH, PULLEY_HEIGHT),
        PULLEY_MASS, PULL_COLOR, PULLEY_LENGTH, PULLEY_HEIGHT);
    scene_add_body(state->scene, pulley2);

    create_pulley_collision(state->scene, player1, PULL_CONST, pulley1, pulley2);
    create_pulley_collision(state->scene, player2, PULL_CONST, pulley1, pulley2);
    create_pulley_collision(state->scene, block, PULL_CONST, pulley1, pulley2);

    create_pulley_collision(state->scene, ground, PULL_CONST, pulley1, pulley2);
    
    level_four_set_up(state, player1, player2, block);
  }
  music_play("assets/background.wav", -1);
}

void map(state_t *s) {
  music_bkgd_stop();
  s->time_elapsed = 0;
  s->scene_num = MAP;
  s->scene = scene_init();
  body_t *b = body_init_more_info(draw_rect((vector_t){WINDOW.x/2, WINDOW.y/2}, WINDOW.x, WINDOW.y), WALL_MASS, BACKGROUND,
                                  WINDOW.x, WINDOW.y);
  body_set_texture(b, sdl_load_image("assets/home.png"));
  scene_add_body(s->scene, b);
  body_t *b1 = body_init_more_info(draw_rect((vector_t){3 * WINDOW.x/8, 11 * WINDOW.y/16}, BLOCK_LENGTH, BLOCK_LENGTH), WALL_MASS, BLACK,
                                   BLOCK_LENGTH, BLOCK_LENGTH);
  scene_add_body(s->scene, b1);
  body_set_texture(b1, sdl_load_image(s->lvl1));
  body_t *b2 = body_init_more_info(draw_rect((vector_t){5 * WINDOW.x/8, 11 * WINDOW.y/16}, BLOCK_LENGTH, BLOCK_LENGTH), WALL_MASS, BLACK,
                                   BLOCK_LENGTH, BLOCK_LENGTH);
  scene_add_body(s->scene, b2);
  body_set_texture(b2, sdl_load_image(s->lvl2));
  body_t *b3 = body_init_more_info(draw_rect((vector_t){3 * WINDOW.x/8, 7 * WINDOW.y/16}, BLOCK_LENGTH, BLOCK_LENGTH), WALL_MASS, BLACK,
                                   BLOCK_LENGTH, BLOCK_LENGTH);
  scene_add_body(s->scene, b3);
  body_set_texture(b3, sdl_load_image(s->lvl3));
  body_t *b4 = body_init_more_info(draw_rect((vector_t){5 * WINDOW.x/8, 7 * WINDOW.y/16}, BLOCK_LENGTH, BLOCK_LENGTH), WALL_MASS, BLACK,
                                   BLOCK_LENGTH, BLOCK_LENGTH);
  scene_add_body(s->scene, b4);
  body_set_texture(b4, sdl_load_image(s->lvl4));
  music_play("assets/map.wav", -1);
}

void check_gem(state_t*s) {
  if (s->curr_gem_ct < scene_counter(s->scene)) {
    s -> curr_gem_ct ++;
    music_play("assets/gem.wav", 0);
  }
}

void win(state_t *s) {
  music_bkgd_stop();
  s->display_time = calculate_time(s);
  s->time_elapsed = 0;
  s->scene_num = WIN;
  s->scene = scene_init();
  body_t *b = body_init_more_info(draw_rect((vector_t){WINDOW.x/2, WINDOW.y/2}, WINDOW.x, WINDOW.y), WALL_MASS, BACKGROUND, WINDOW.x, WINDOW.y);
  body_set_texture(b, sdl_load_image("assets/win.png"));
  scene_add_body(s->scene, b); 
  sdl_render_scene(s->scene);
  music_play("assets/win.wav", 0);
}

void lose(state_t *s) {
  music_bkgd_stop();
  s->time_elapsed = 0;
  s->scene_num = LOSE;
  s->scene = scene_init();
  body_t *b = body_init_more_info(draw_rect((vector_t){WINDOW.x/2, WINDOW.y/2}, WINDOW.x, WINDOW.y), WALL_MASS, BACKGROUND, WINDOW.x, WINDOW.y);
  scene_add_body(s->scene, b);
  body_set_texture(b, sdl_load_image("assets/lose.png"));
  sdl_render_scene(s->scene);
  music_play("assets/lose.wav", 0);
}

void instruct(state_t *s) {
  s->time_elapsed = 0;
  s->scene_num = INSTRUCT;
  s->scene = scene_init();
  body_t *b = body_init_more_info(draw_rect((vector_t){WINDOW.x/2, WINDOW.y/2}, WINDOW.x, WINDOW.y), WALL_MASS, BACKGROUND, WINDOW.x, WINDOW.y);
  scene_add_body(s->scene, b);
  body_set_texture(b, sdl_load_image("assets/instructions.png"));
}

void on_mouse(state_t *s, double x, double y) {
  if (s->scene_num == MAP)
  {
    if (x >= (3 * WINDOW.x/8 - BLOCK_LENGTH/2)/FACTOR + START_X && x <= (3 * WINDOW.x/8 + BLOCK_LENGTH/2)/FACTOR + START_X &&
        y >= (1000 - (11 * WINDOW.y/16 + BLOCK_LENGTH/2))/FACTOR && y <= (1000 - (11 * WINDOW.y/16 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      init_levels(s, LEVEL1);
    }
    if (x >= (5 * WINDOW.x/8 - BLOCK_LENGTH/2)/FACTOR + START_X && x <= (5 * WINDOW.x/8 + BLOCK_LENGTH/2)/FACTOR + START_X &&
        y >= (1000 - (11 * WINDOW.y/16 + BLOCK_LENGTH/2))/FACTOR && y <= (1000 - (11 * WINDOW.y/16 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      init_levels(s, LEVEL2);
    }
    if (x >= (3 * WINDOW.x/8 - BLOCK_LENGTH/2)/FACTOR + START_X && x <= (3 * WINDOW.x/8 + BLOCK_LENGTH/2)/FACTOR + START_X &&
        y >= (1000 - (7 * WINDOW.y/16 + BLOCK_LENGTH/2))/FACTOR && y <= (1000 - (7 * WINDOW.y/16 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      init_levels(s, LEVEL3);
    }
    if (x >= (5 * WINDOW.x/8 - BLOCK_LENGTH/2)/FACTOR + START_X && x <= (5 * WINDOW.x/8 + BLOCK_LENGTH/2)/FACTOR + START_X &&
        y >= (WINDOW.y - (7 * WINDOW.y/16 + BLOCK_LENGTH/2))/FACTOR && y <= (WINDOW.y - (7 * WINDOW.y/16 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      init_levels(s, LEVEL4);
    }
    if (x >= (WINDOW.x/2 - BLOCK_LENGTH * 2)/FACTOR + START_X && x <= (WINDOW.x/2 + BLOCK_LENGTH * 2)/FACTOR + START_X &&
        y >= (WINDOW.y - (WINDOW.y/4 + BLOCK_LENGTH/2))/FACTOR && y <= (WINDOW.y - (WINDOW.y/4 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      instruct(s);
    }
  }
  else if (s->scene_num == WIN) {
    if (x >= (WINDOW.x/2 - BLOCK_LENGTH * 2)/FACTOR + START_X && x <= (WINDOW.x/2 + BLOCK_LENGTH * 2)/FACTOR + START_X &&
        y >= (WINDOW.y - (WINDOW.y/4 + BLOCK_LENGTH/2))/FACTOR && y <= (WINDOW.y - (WINDOW.y/4 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      map(s);
    }
  }
  else if (s->scene_num == LOSE) {
    if (x >= (WINDOW.x/2 - BLOCK_LENGTH * 2)/FACTOR + START_X && x <= (WINDOW.x/2 + BLOCK_LENGTH * 2)/FACTOR + START_X &&
        y >= (WINDOW.y - (3 * WINDOW.y/8 + BLOCK_LENGTH/2))/FACTOR && y <= (WINDOW.y - (3 * WINDOW.y/8 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      init_levels(s, s->last_lvl);
    }
    if (x >= (WINDOW.x/2 - BLOCK_LENGTH * 2)/FACTOR + START_X && x <= (WINDOW.x/2 + BLOCK_LENGTH * 2)/FACTOR + START_X &&
        y >= (WINDOW.y - (WINDOW.y/4 + BLOCK_LENGTH/2))/FACTOR && y <= (WINDOW.y - (WINDOW.y/4 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      map(s);
    }
  }
  else if (s->scene_num == INSTRUCT) {
    if (x >= (WINDOW.x/2 - BLOCK_LENGTH * 2)/FACTOR + START_X && x <= (WINDOW.x/2 + BLOCK_LENGTH * 2)/FACTOR + START_X &&
        y >= (1000 - (WINDOW.y/4 + BLOCK_LENGTH/2))/FACTOR && y <= (1000 - (WINDOW.y/4 - BLOCK_LENGTH/2))/FACTOR)
    {
      scene_free(s->scene);
      map(s);
    }
  }
}

void check_param(state_t *s){
  if(s->scene_num == LEVEL1){
    s->lvl1 = "assets/good.png";
    if (s->delt_time >= MAX_TIME_LEVEL_ONE || scene_counter(s->scene) < GEMS1)
    {
      s->lvl1 = "assets/ok.png";
    }
  }
  else if(s->scene_num == LEVEL2){
    s->lvl2 = "assets/good.png";
    if (s->delt_time >= MAX_TIME_LEVEL_TWO || scene_counter(s->scene) < GEMS2)
    {
      s->lvl2 = "assets/ok.png";
    }
  }
  else if(s->scene_num == LEVEL3){
    s->lvl3 = "assets/good.png";
    if (s->delt_time >= MAX_TIME_LEVEL_THREE || scene_counter(s->scene) < GEMS3)
    {
      s->lvl3 = "assets/ok.png";
    }
  }
  else if(s->scene_num == LEVEL4) {
    s->lvl4 = "assets/good.png";
    if (s->delt_time >= MAX_TIME_LEVEL_FOUR || scene_counter(s->scene) < GEMS4)
    {
      s->lvl4 = "assets/ok.png";
    }
  }
}

void check_display_timer(state_t *state){
  if((state->scene_num == LEVEL1) || (state->scene_num == LEVEL2) || (state->scene_num == LEVEL3) || (state->scene_num == LEVEL4)){
    draw_text(state->scene, calculate_time(state));
    sdl_show();
  }
}

state_t *emscripten_init() {
  vector_t min = (vector_t){.x = 0, .y = 0};
  vector_t max = WINDOW;
  sdl_init(min, max);
  sdl_on_key(on_key);
  music_init();
  draw_init();
  SDL_Init(SDL_INIT_TIMER);
  sdl_on_mouse(on_mouse);
  state_t *state = malloc(sizeof(state_t));
  state->last_lvl = 1;
  state->lvl1 = "assets/unplayed.png";
  state->lvl2 = "assets/unplayed.png";
  state->lvl3 = "assets/unplayed.png";
  state->lvl4 = "assets/unplayed.png";
  state->fan_off = false;
  state->grav = false;
  state->scene_num = 0;

  map(state);
  return state;
}

void emscripten_main(state_t *state) {
  sdl_render_scene(state->scene);
  check_display_timer(state);
  scene_tick(state->scene, time_since_last_tick());
  check_gem(state);
  
  if (scene_get_lose(state->scene)){
    lose(state);
  }
  if (scene_get_win(state->scene)){
    check_param(state);
    win(state);
  }
  if(state->scene_num == WIN){
    draw_win(state->display_time, state->curr_gem_ct, calculate_grade(state));
  }
  if (state->scene_num == LEVEL2) {
    if (!(state->fan_off) && (body_get_fan(scene_get_body(state->scene, PLAYER1)) || body_get_fan(scene_get_body(state->scene, PLAYER2)) || body_get_fan(scene_get_body(state->scene, BLOCK_NUM)))) {
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/twind2.png"));
      state->fan_off = true;
    }
    else if (state->fan_off && !body_get_fan(scene_get_body(state->scene, PLAYER1)) && !body_get_fan(scene_get_body(state->scene, PLAYER2)) && !body_get_fan(scene_get_body(state->scene, BLOCK_NUM))) {
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/wind2.png"));
      state->fan_off = false;
    }
  }
  if (state->scene_num == LEVEL3) {
    if (!(state->fan_off) && (body_get_fan(scene_get_body(state->scene, PLAYER1)) || body_get_fan(scene_get_body(state->scene, PLAYER2)) || body_get_fan(scene_get_body(state->scene, BLOCK_NUM)))) {
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/twind3.png"));
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANF_SHIFT), sdl_load_image("assets/twind3.png"));
      state->fan_off = true;
    }
    else if (state->fan_off && !body_get_fan(scene_get_body(state->scene, PLAYER1)) && !body_get_fan(scene_get_body(state->scene, PLAYER2)) && !body_get_fan(scene_get_body(state->scene, BLOCK_NUM))) {
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/wind3.png"));
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANF_SHIFT), sdl_load_image("assets/wind3.png"));
      state->fan_off = false;
    }
  }
  if (state->scene_num == LEVEL4) {
    if (!(state->fan_off) && (body_get_fan(scene_get_body(state->scene, PLAYER1)) || body_get_fan(scene_get_body(state->scene, PLAYER2)) || body_get_fan(scene_get_body(state->scene, BLOCK_NUM)))) {
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/twind4r.png"));
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANF_SHIFT), sdl_load_image("assets/twind4l.png"));
      state->fan_off = true;
    }
    else if (state->fan_off && !body_get_fan(scene_get_body(state->scene, PLAYER1)) && !body_get_fan(scene_get_body(state->scene, PLAYER2)) && !body_get_fan(scene_get_body(state->scene, BLOCK_NUM))) {
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANL_SHIFT), sdl_load_image("assets/wind4r.png"));
      body_set_texture(scene_get_body(state->scene, scene_bodies(state->scene) - FANF_SHIFT), sdl_load_image("assets/wind4l.png"));
      state->fan_off = false;
    }
  }
  state->time_elapsed += 1;
}

void emscripten_free(state_t *state) {
  scene_free(state->scene);
  free(state);
}