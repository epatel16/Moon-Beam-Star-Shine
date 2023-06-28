#ifndef __GEM_H__
#define __GEM_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl_wrapper.h"
#include "list.h"
#include "draw.h"
#include "body.h"
#include "scene.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Adds a gem of a specific center that can collide with a player,
 * and has an image laid over it.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 the body that can collect the gem and make it disappear
 * @param center the center of the gem
 * @param draw the path for the image that represents the gem
 */
void add_gem(scene_t *scene, body_t *player1, vector_t center, char *draw);

/**
 * Adds gems specifically for level 1.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 the body that can collect some of the gems and make them disappear
 * @param player2 the other body that can collect some of the gems and make them disappear
 */
void add_level_one_gems(scene_t *scene, body_t *player1, body_t *player2);

/**
 * Adds gems specifically for level 2.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 the body that can collect some of the gems and make them disappear
 * @param player2 the other body that can collect some of the gems and make them disappear
 */
void add_level_two_gems(scene_t *scene, body_t *player1, body_t *player2);

/**
 * Adds gems specifically for level 3.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 the body that can collect some of the gems and make them disappear
 * @param player2 the other body that can collect some of the gems and make them disappear
 */
void add_level_three_gems(scene_t *scene, body_t *player1, body_t *player2);

/**
 * Adds gems specifically for level 4.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 the body that can collect some of the gems and make them disappear
 * @param player2 the other body that can collect some of the gems and make them disappear
 */
void add_level_four_gems(scene_t *scene, body_t *player1, body_t *player2);

#endif // #ifndef __GEM_H__
