#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

void reproducir_cancion()
{
	FILE *fd;
	Mix_Music *musica;
	int canal,volAnt;
	int flag, cont=0;
	int vol;

	if ( SDL_Init (SDL_INIT_AUDIO) < 0){
		printf("Error en SDL_Init: %s\n", SDL_GetError());
		exit(1);
		}
		
	atexit(SDL_Quit);
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)){
		printf("No se puede inicializar SDL_mixer %s\n",Mix_GetError());
		exit(1);
		}
	
	atexit(Mix_CloseAudio);
	
// Cargamos la música. ===============================================
	
	musica = Mix_LoadMUS("music.mp3");
	
	if ( musica == NULL ){
		printf("No pude cargar musica: %s\n", Mix_GetError());
		exit(1);
		}
		
// Reproducción la música. ===========================================

	vol = check_out("volumen");
	volAnt=Mix_VolumeMusic(vol);
	
// Esta función devuelve el canal por el que se reproduce la música.==

	canal = Mix_PlayMusic(musica, 0);
	
	
// Liberamos recursos. ===============================================

	
}
