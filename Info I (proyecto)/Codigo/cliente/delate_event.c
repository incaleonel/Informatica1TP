#include<stdio.h>
#include<gtk/gtk.h>

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
		remove("music.mp3");
        gtk_main_quit ();
        return FALSE;
}
