#include <unistd.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "prototipos.h"

// Captura del evento play/stop ======================================

static f_play ()
{
	reproducir_cancion();
}

static f_prev ()
{
 	Mix_ResumeMusic();
}

static f_sig ()
{
 	Mix_PauseMusic();
}

// Ordenamiento de los widgets que se muestran en la ventana =========

GtkWidget *make_box( gboolean homogeneous,
                     gint     spacing,
                     gboolean expand,
                     gboolean fill,
                     guint    padding )
{
 GtkWidget *box;
 GtkWidget *button;
 int estado = 0;
 int fd[2];

 if(pipe(fd) == -1){
 	perror("pipe");
 	exit(1);
 	}
 
 write(fd[0], &estado, sizeof(int));

 box = gtk_hbox_new (FALSE, 0);

 button = gtk_button_new_with_label (" RESUME ");
 gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
 gtk_widget_show (button);

 g_signal_connect(G_OBJECT (button), "clicked",
				  G_CALLBACK (f_prev), NULL);

 button = gtk_button_new_with_label ("PLAY");
 gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
 gtk_widget_show (button);

 g_signal_connect(G_OBJECT (button), "clicked",
				  G_CALLBACK (f_play), NULL);

 button = gtk_button_new_with_label (" STOP ");
 gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
 gtk_widget_show (button);

 g_signal_connect(G_OBJECT (button), "clicked",
				  G_CALLBACK (f_sig), NULL);
 
 return box;
}
