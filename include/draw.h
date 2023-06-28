#ifndef __DRAW_H__
#define __DRAW_H__

#include "list.h"
#include "vector.h"

/**
 * Returns the points that create a rectangle at the desired center
 * of the desired length and height.
 *
 * @param center the center of the rectangle to be drawn
 * @param length the length of the rectangle to be drawn (x direction)
 * @param height the height of the rectangle to be drawn (y direction)
 * @return the list of points that create the rectangle
 */
list_t *draw_rect(vector_t center, double length, double height);

/**
 * Returns the points that create a gem shape at the desired 
 * center of the desired radius
 *
 * @param center the center of the gem to be drawn
 * @param radius the radius of the gem to be drawn
 * @return the list of points that create the gem
 */
list_t *draw_gem(size_t radius, vector_t centroid);

#endif // #ifndef __DRAW_H__
