#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "list.h"
#include "body.h"
#include "draw.h"
#include "scene.h"
#include "vector.h"

/**
 * Adds a platform of a specific center, height, and length
 * that can collide with two players and a block.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body collides with the platform
 * @param player2 a body that collides with the platform
 * @param block a body that collides with the platform
 * @param center the center of the platform
 * @param length the length of the platform
 * @param height the height of the platform
 */
void add_platform(scene_t *scene, body_t *player1, body_t *player2, body_t *block, vector_t center, double length, double height);

/**
 * Adds platforms specifically for level 1.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body that collide with platforms
 * @param player2 a body that collides with platforms
 * @param block a body that collides with platforms
 */
void add_level_one_platforms(scene_t *scene, body_t *player1, body_t *player2, body_t *block);

/**
 * Adds platforms specifically for level 2.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body that collide with platforms
 * @param player2 a body that collides with platforms
 * @param block a body that collides with platforms
 */
void add_level_two_platforms(scene_t *scene, body_t *player1, body_t *player2, body_t *block);

/**
 * Adds platforms specifically for level 3.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body that collide with platforms
 * @param player2 a body that collides with platforms
 * @param block a body that collides with platforms
 */
void add_level_three_platforms(scene_t *scene, body_t *player1, body_t *player2, body_t *block);

/**
 * Adds platforms specifically for level 4.
 * 
 * @param scene the scene that holds the bodies and forces
 * @param player1 a body that collide with platforms
 * @param player2 a body that collides with platforms
 * @param block a body that collides with platforms
 */
void add_level_four_platforms(scene_t *scene, body_t *player1, body_t *player2, body_t *block);

#endif // #ifndef __PLATFORM_H__
