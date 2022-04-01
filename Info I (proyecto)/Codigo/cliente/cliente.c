#include <gtk/gtk.h>
#include "prototipos.h"

int main(int argc, char *argv[])
{

 if(!fork()){
	fcliente(argc, argv[1]);
	}	
	
 else{
	GtkWidget *window;
	GtkWidget *box1;
	GtkWidget *box2;
	
	gtk_init (&argc, &argv);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "delete_event",
					  G_CALLBACK (delete_event), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (window), 40);

	box1 = gtk_vbox_new (FALSE, 0);

	box2 = make_box (FALSE, 0, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);

	gtk_container_add (GTK_CONTAINER (window), box1);
	
	gtk_widget_show (box1);
 	gtk_widget_show (window);	
	
	gtk_main ();
	}
	
 return 0;	
}
