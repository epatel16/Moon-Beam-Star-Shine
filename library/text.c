#include "text.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"

#include "body.h"
#include "draw.h"
#include "forces.h"
#include "info.h"
#include "scene.h"
#include "sdl_wrapper.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const SDL_Color TEXT_WHITE = {255, 255, 255};
const SDL_Color TEXT_BLACK = {0, 0, 0};
static TTF_Font* FONT1 = NULL;
static TTF_Font* FONT2 = NULL;
static TTF_Font* FONT3 = NULL;
static TTF_Font* FONT4 = NULL;

const int FONT_SIZE_1 = 24;
const int FONT_SIZE_2 = 45;
const int FONT_SIZE_3 = 40;
const int FONT_SIZE_4 = 25;

const int DRAW_TEXT_X1 = 550;
const int DRAW_TEXT_Y1 = 5;
const int DRAW_TEXT_X2 = 400;
const int DRAW_TEXT_Y2 = 5;

const int DRAW_WIN_X1 = 418;
const int DRAW_WIN_Y1 = 100;
const int DRAW_WIN_X2 = 442;
const int DRAW_WIN_Y2 = 160;
const int DRAW_WIN_X3 = 423;
const int DRAW_WIN_Y3 = 190;
const int DRAW_WIN_X4 = 423;
const int DRAW_WIN_Y4 = 225;

const size_t GEM_TEXT_SIZE1 = 10;
const size_t GEM_TEXT_SIZE2 = 15;
const size_t DISPLAY_TIME_SIZE = 15;
const size_t GRADE_TEXT_SIZE = 10;
const size_t WIN_SIZE = 9;

typedef struct text text_t;

void draw_init(){
    TTF_Init();
}

void draw_text(scene_t *scene, char *worldText){
  SDL_Surface* text;
  if (!FONT1){
    FONT1 = TTF_OpenFont("assets/Armstrong.ttf", FONT_SIZE_1);
  }
  if ( !FONT1 ) {
    printf("FONT1 fail\n");
  }

  text = TTF_RenderText_Solid( FONT1, worldText, TEXT_WHITE );
  if ( !text ) {
    printf("text fail\n");
  }
  SDL_Texture* text_texture;
  text_texture = SDL_CreateTextureFromSurface(get_renderer(), text );
  int *width = malloc(sizeof(int));
  int *height = malloc(sizeof(int));
  TTF_SizeText(FONT1, worldText, width, height);
  SDL_Rect *text_rect = malloc(sizeof(SDL_Rect));
  *text_rect = (SDL_Rect){(int) DRAW_TEXT_X1, (int)DRAW_TEXT_Y1, *width, *height};

  SDL_RenderCopy(get_renderer(), text_texture, NULL, text_rect);

  char* gem_text = malloc(sizeof(char) * GEM_TEXT_SIZE1);
  sprintf(gem_text, "gems: %zu", scene_counter(scene));
  SDL_Surface* text2;
  text2 = TTF_RenderText_Solid(FONT1, gem_text, TEXT_WHITE);
  if ( !text2 ) {
    printf("text fail\n");
  }
  SDL_Texture* text_texture2;
  text_texture2 = SDL_CreateTextureFromSurface(get_renderer(), text2);
  width = malloc(sizeof(int));
  height = malloc(sizeof(int));
  TTF_SizeText(FONT1, worldText, width, height);
  SDL_Rect *text_rect2 = malloc(sizeof(SDL_Rect));
  *text_rect2 = (SDL_Rect){(int) DRAW_TEXT_X2, (int)DRAW_TEXT_Y2, *width, *height};

  SDL_RenderCopy(get_renderer(), text_texture2, NULL, text_rect2);
  
  SDL_DestroyTexture(text_texture);
  SDL_FreeSurface(text);
  free(worldText);

  SDL_DestroyTexture(text_texture2);
  SDL_FreeSurface(text2);
  free(gem_text);
}

void draw_win(char *display_time, size_t curr_gem_ct, char grade){
  if (!FONT2){
    FONT2 = TTF_OpenFont("assets/Armstrong.ttf", FONT_SIZE_2);
  }
  if (!FONT2 ) {
    printf("font fail\n");
  }
  SDL_Surface* text;
  char* congrats = malloc(sizeof(*congrats) * WIN_SIZE);
  congrats = "YOU WIN!";

  text = TTF_RenderText_Solid( FONT2, congrats, TEXT_BLACK);
  if ( !text ) {
    printf("text fail\n");
  }
  SDL_Texture* text_texture;
  text_texture = SDL_CreateTextureFromSurface(get_renderer(), text);
  int *width = malloc(sizeof(int));
  int *height = malloc(sizeof(int));
  TTF_SizeText(FONT2, congrats, width, height);
  SDL_Rect *text_rect = malloc(sizeof(SDL_Rect));
  *text_rect = (SDL_Rect){(int) DRAW_WIN_X1, (int) DRAW_WIN_Y1, *width, *height};
  SDL_RenderCopy(get_renderer(), text_texture, NULL, text_rect);

  if (!FONT4){
    FONT4 = TTF_OpenFont("assets/Armstrong.ttf", FONT_SIZE_4);
  }
  if (!FONT4 ) {
    printf("font fail\n");
  }
  char* time_text = malloc(sizeof(char) * DISPLAY_TIME_SIZE);
  strcpy(time_text, display_time);
  SDL_Surface* text2;
  text2 = TTF_RenderText_Solid(FONT4, time_text, TEXT_BLACK);
  if ( !text2 ) {
    printf("text fail 1 \n");
  }
  SDL_Texture* text_texture2;
  text_texture2 = SDL_CreateTextureFromSurface(get_renderer(), text2);
  width = malloc(sizeof(int));
  height = malloc(sizeof(int));
  TTF_SizeText(FONT4, time_text, width, height);
  SDL_Rect *text_rect2 = malloc(sizeof(SDL_Rect));
  *text_rect2 = (SDL_Rect){(int) DRAW_WIN_X2, (int)DRAW_WIN_Y2, *width, *height};

  SDL_RenderCopy(get_renderer(), text_texture2, NULL, text_rect2);

  char* gem_text = malloc(sizeof(char) * GEM_TEXT_SIZE2);
  sprintf(gem_text, "gem count: %zu", curr_gem_ct);
  SDL_Surface* text3;
  text3 = TTF_RenderText_Solid(FONT4, gem_text, TEXT_BLACK);
  if ( !text3 ) {
    printf("text fail\n");
  }
  SDL_Texture* text_texture3;
  text_texture3 = SDL_CreateTextureFromSurface(get_renderer(), text3);
  width = malloc(sizeof(int));
  height = malloc(sizeof(int));
  TTF_SizeText(FONT4, gem_text, width, height);
  SDL_Rect *text_rect3 = malloc(sizeof(SDL_Rect));
  *text_rect3 = (SDL_Rect){(int) DRAW_WIN_X3, (int)DRAW_WIN_Y3, *width, *height};

  SDL_RenderCopy(get_renderer(), text_texture3, NULL, text_rect3);

  if (!FONT3){
    FONT3 = TTF_OpenFont("assets/Armstrong.ttf", FONT_SIZE_3);
  }
  if (!FONT3) {
    printf("font fail\n");
  }
  char* grade_text = malloc(sizeof(char) * GRADE_TEXT_SIZE);
  sprintf(grade_text, "grade: %c", grade);
  SDL_Surface* text4;
  text4 = TTF_RenderText_Solid(FONT3, grade_text, TEXT_BLACK);
  if ( !text4 ) {
    printf("text fail\n");
  }
  SDL_Texture* text_texture4;
  text_texture4 = SDL_CreateTextureFromSurface(get_renderer(), text4);
  width = malloc(sizeof(int));
  height = malloc(sizeof(int));
  TTF_SizeText(FONT3, grade_text, width, height);
  SDL_Rect *text_rect4 = malloc(sizeof(SDL_Rect));
  *text_rect4 = (SDL_Rect){(int) DRAW_WIN_X4, (int)DRAW_WIN_Y4, *width, *height};

  SDL_RenderCopy(get_renderer(), text_texture4, NULL, text_rect4);

  SDL_DestroyTexture(text_texture);
  SDL_FreeSurface(text);

  SDL_DestroyTexture(text_texture2);
  SDL_FreeSurface(text2);
  free(time_text);

  SDL_DestroyTexture(text_texture3);
  SDL_FreeSurface(text3);
  free(gem_text);

  SDL_DestroyTexture(text_texture4);
  SDL_FreeSurface(text4);
  free(grade_text);
}
