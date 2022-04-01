#include <stdio.h>
#include <gtk/gtk.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "libplayer.h"

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
		Mix_Music *musica;
		
		musica = Mix_LoadMUS("music.mp3");
		Mix_FreeMusic(musica);
		
		remove("music.mp3");
		
		check_in("estado", 0);
		check_in("tema", 0);
		check_in("volumen", 50);
		
        gtk_main_quit ();
        return FALSE;
}
