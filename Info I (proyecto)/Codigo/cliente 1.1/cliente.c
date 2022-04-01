#include "libplayer.h"
//entorno grafico
static f_entry (GtkWidget *widget, GtkWidget *entry)
{
 gchar *song;
 
 song = gtk_entry_get_text (GTK_ENTRY(entry));
 
 printf("entry activate capturado: %s", song);
}
//====================================================================
static f_play (GtkWidget *widget, GtkWidget *entry)
{

 gchar *song;
 int estado, tema;
 
 song = gtk_entry_get_text (GTK_ENTRY(entry));
 
 check_in ("tema", atoi(song));
 estado = check_out ("estado");
 
 if(estado == 0){
	reproducir_cancion();
	estado = 1;
	check_in ("estado", 1);
	}
 else{
	Mix_ResumeMusic();
	}
}
//====================================================================
static f_pause ()
{
 Mix_PauseMusic();
}
//====================================================================
static f_stop ()
{
 int estado = 0;
 
 check_in("estado", 0);
 Mix_HaltMusic();
}
//====================================================================
static f_popup ()
{
 int vol, volAnt;
 
 printf("popup capturado\n");
 vol = check_out("volumen");
 if(vol<98){
	 vol = vol + 2;
	 volAnt=Mix_VolumeMusic(vol);
	 check_in ("volumen", vol);
	 }
}
//====================================================================

int main(int argc, char *argv[])
{
 
 if(!fork()){
	fcliente(argc, argv[1]);
	}
	
 else{
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *entry;
	
	gtk_init (&argc, &argv);
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "interfaz.glade", NULL);
	window = GTK_WIDGET (gtk_builder_get_object(builder,"player"));
	g_signal_connect (G_OBJECT (window), "delete_event",
					  G_CALLBACK (delete_event), NULL);
	
	entry = GTK_WIDGET (gtk_builder_get_object (builder, "entry"));
	g_signal_connect (GTK_OBJECT(entry), "activate",
					  G_CALLBACK(f_entry), entry);
	
	button = GTK_WIDGET (gtk_builder_get_object (builder, "play"));
	g_signal_connect (GTK_OBJECT(button), "clicked",
					   G_CALLBACK(f_play), entry);
					   
	button = GTK_WIDGET (gtk_builder_get_object (builder, "pause"));
	g_signal_connect (GTK_OBJECT(button), "clicked",
					   G_CALLBACK(f_pause), NULL);

	button = GTK_WIDGET (gtk_builder_get_object (builder, "stop"));
	g_signal_connect (GTK_OBJECT(button), "clicked",
					   G_CALLBACK(f_stop), NULL);

	
	button = GTK_WIDGET (gtk_builder_get_object (builder, "volumen"));
	g_signal_connect (GTK_OBJECT(button), "value_changed",
					   G_CALLBACK(f_popup), NULL);

	
	gtk_builder_connect_signals (builder, NULL);
	g_object_unref(G_OBJECT (builder));
 	gtk_widget_show (window);

	gtk_main();
	}
	
 return 0;
}
