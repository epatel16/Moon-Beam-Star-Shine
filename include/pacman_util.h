#ifndef __STAR_BODY_H__
#define __STAR_BODY_H__

#include "list.h"
#include "polygon.h"
#include "sdl_wrapper.h"
#include "state.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Returns a random position for a pellet in the pacman window.
 * 
 * @param max the largest position that the pellet's center could be
 * @return a random float to represent a dimension of the pellet's location
 */
float get_rand_pos(int max);

/**
 * Returns the points that create a pacman shape at the desired 
 * center of the desired radius
 *
 * @param radius the radius of the pacman to be drawn
 * @param centroid the center of the pacman to be drawn
 * @return the list of points that create the pacman
 */
list_t *draw_pacman(size_t radius, vector_t centroid);

/**
 * Returns the points that create a pellet shape at the desired 
 * center of the desired radius
 *
 * @param radius the radius of the pellet to be drawn
 * @param centroid the center of the pellet to be drawn
 * @return the list of points that create the pellet
 */
list_t *draw_pellet(size_t radius, vector_t centroid);

#endif
