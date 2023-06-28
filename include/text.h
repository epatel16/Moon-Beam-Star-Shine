#ifndef __TEXT_H__
#define __TEXT_H__

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

typedef struct text text_t;


/**
 * Initializes the truetype font API.
 */
void draw_init();

/**
 * Adds a gem of a specific center that can collide with a player,
 * and has an image laid over it.
 * 
 * @param scene the scene that holds information regarding the bodies.
 * @param worldText the time elapsed since start of game, in minutes:seconds string format.
 */
void draw_text(scene_t *scene, char *worldText);

/**
 * Adds a gem of a specific center that can collide with a player,
 * and has an image laid over it.
 * 
 * @param display_time the time elapsed since start of game, in minutes:seconds string format.
 * @param curr_gem_ct number of gems collected at end of game.
 * @param grade letter grade (A-F) received at end of game.
 */
void draw_win(char *display_time, size_t curr_gem_ct, char grade);

#endif