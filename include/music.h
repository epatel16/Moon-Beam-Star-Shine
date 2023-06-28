#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "body.h"
#include "forces.h"
#include "info.h"
#include "scene.h"
#include "sdl_wrapper.h"
#include <math.h>

typedef struct music music_t;


/**
 * Initializes audio subsystem.
 */
void music_init();

/**
 * Initializes audio subsystem.
 * 
 * @param music_file name of audio file.
 * @param repeats number of times audio should be repeated. -1 if repeat forever.
 */
void music_play(char * music_file, int repeats);

/**
 * Stops background music.
 */
void music_bkgd_stop();

#endif