#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#define PORT 3493
#define MAXDATASIZE 20 
#define appGET(xx) \
app->xx=GTK_WIDGET(gtk_builder_get_object(builder,#xx))

void fcliete (int, char*);
void reproducir_cancion ();
void parar_cancion ();
int check_in (char*, int);
int check_out (char*);
int get_val (char*, char*);
gint delete_event (GtkWidget*,GdkEvent*,gpointer);
