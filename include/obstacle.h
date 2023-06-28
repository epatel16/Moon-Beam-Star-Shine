#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "list.h"
#include "body.h"
#include "draw.h"
#include "scene.h"
#include "vector.h"

/**
 * Adds a obstacle of a specific center, height, and length
 * that can collide with one players with a color.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body collides with the obstacle
 * @param center the center of the obstacle
 * @param length the length of the obstacle
 * @param height the height of the obstacle
 * @param color the color of the obstacle
 */
void add_obstacle(scene_t *scene, body_t *player1, vector_t center, double length, double height, rgb_color_t color);

/**
 * Adds a obstacle of a specific center, height, and length
 * that can collide with two players with a color.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body collides with the obstacle
 * @param player2 a body that collides with the obstacle
 * @param center the center of the obstacle
 * @param length the length of the obstacle
 * @param height the height of the obstacle
 * @param color the color fo the obstacle
 */
void add_obstacle2(scene_t *scene, body_t *player1, body_t *player2, vector_t center, double length, double height, rgb_color_t color);

/**
 * Adds obstacles specifically for level 1.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body that collide with obstacles
 * @param player2 a body that collides with obstacles
 */
void add_level_one_obstacles(scene_t *scene, body_t *player1, body_t *player2);

/**
 * Adds obstacles specifically for level 2.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body that collide with obstacles
 * @param player2 a body that collides with obstacles
 */
void add_level_two_obstacles(scene_t *scene, body_t *player1, body_t *player2);

/**
 * Adds obstacles specifically for level 3.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body that collide with obstacles
 * @param player2 a body that collides with obstacles
 */
void add_level_three_obstacles(scene_t *scene, body_t *player1, body_t *player2);

/**
 * Adds obstacles specifically for level 4.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body that collide with obstacles
 * @param player2 a body that collides with obstacles
 */
void add_level_four_obstacles(scene_t *scene, body_t *player1, body_t *player2);

#endif // #ifndef __OBSTACLE_H__
