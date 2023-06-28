#include "music.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "body.h"
#include "forces.h"
#include "info.h"
#include "scene.h"
#include "sdl_wrapper.h"
#include <math.h>

typedef struct music music_t;

void music_init(){
  SDL_Init(SDL_INIT_AUDIO);
  Mix_AllocateChannels(3);
}

void music_play(char * music_file, int repeats){
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048);
  Mix_Chunk *bkgd_music1;
  bkgd_music1 = Mix_LoadWAV(music_file);
  if (!bkgd_music1) {
    printf("Mix_LoadWAV(music_file): %s\n", music_file, Mix_GetError());
  }
  if(repeats == -1) {
    Mix_PlayChannel(0, bkgd_music1, repeats);
  }
  else {
    Mix_PlayChannel(-1, bkgd_music1, repeats);
  }
}

void music_bkgd_stop() {
  Mix_HaltChannel(0);
  if (Mix_GetChunk(0)) {
    Mix_FreeChunk(Mix_GetChunk(0));
  }
}