#include<stdio.h>
#include<gtk/gtk.h>

// Funciones llamadas tras la captura del evento "clicked"
// Solo imprimen por consola para demostrar que el evento es capturado
//=========================================================
//=========================================================
static f_play ()
{
 g_print ("play/stop\n");
}

static f_sig ()
{
 g_print ("sig\n");
}

static f_prev ()
{
 g_print("prev\n");
}
//=========================================================
//=========================================================

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
        gtk_main_quit ();
        return FALSE;
}
//=========================================================
//=========================================================

GtkWidget *make_box( gboolean homogeneous,
                     gint     spacing,
                     gboolean expand,
                     gboolean fill,
                     guint    padding )
{
 GtkWidget *box;
 GtkWidget *button;
 int estado = 0;

 box = gtk_hbox_new (FALSE, 0);

 button = gtk_button_new_with_label (" < ");
 gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
 gtk_widget_show (button);

 g_signal_connect(G_OBJECT (button), "clicked",
				  G_CALLBACK (f_prev), NULL);

 button = gtk_button_new_with_label ("Play/Stop");
 gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
 gtk_widget_show (button);

 g_signal_connect(G_OBJECT (button), "clicked",
				  G_CALLBACK (f_play), &estado);

 button = gtk_button_new_with_label (" > ");
 gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 0);
 gtk_widget_show (button);

 g_signal_connect(G_OBJECT (button), "clicked",
				  G_CALLBACK (f_sig), NULL);
 
 return box;
}
//=========================================================
//=========================================================

int main (int argc, char *argv[])
{
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

 return 0;
}
