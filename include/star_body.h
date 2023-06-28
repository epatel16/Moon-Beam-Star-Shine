#ifndef __STAR_BODY_H__
#define __STAR_BODY_H__

#include "list.h"
#include "sdl_wrapper.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Gets the random color of a star.
 *
 * @return the float for color of the star
 */
float get_rand_col();

/**
 * Gets the random elasticity of a star.
 *
 * @return the float for elasticty of the star
 */
float get_rand_elas();

/**
 * Creates and returns a list of vector points that represent the star
 *
 * @param centroid a vector for the center of the star
 * @param radius a size for the the radius of the star
 * @param n a size to indicated the number of points of the star
 * @return a list of points that is the star of n points centered around
 * centroid
 */
list_t *draw_star(vector_t centroid, size_t radius, size_t n);

/**
 * Checks to see if a new star should be generated on the screen
 *
 * @param arr a list of stars that are on the screen
 * @param index an int of the position of the most recent star generated
 * @param yvelocity a double of the current velocity vector
 * @param new_velocity a double of the next generated velocity vector
 * @param max_size an int of the maximum size of the array of stars
 * @return a boolean to indicate whether to generate a new star
 */
bool generate_new_star(list_t *arr, int index, double yvelocity,
                       double new_velocity, int max_size);

/**
 * Adds the drawn star to the array of the stars
 *
 * @param arr a list of stars
 * @param num_points a size of the number of points in the star being added
 * @param window a vector representing the dimensions of the window
 */
void generate_star(list_t *arr, size_t num_points, vector_t window);

#endif
