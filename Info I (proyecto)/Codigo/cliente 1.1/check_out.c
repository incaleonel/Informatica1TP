/* Esta funcion resibe el nombre de un parametro guardado en el archivo
   "config" y devuelve el valor entero asociado a ese parametro */

#include<stdio.h>
#include<string.h>
#include<gtk/gtk.h>
#include"libplayer.h"

int check_out (char *pal)
{
 FILE *fp;
 char buf[50];
 int dato;
 
 fp = fopen ("config", "r");
 
 while (fgets(buf, 50, fp) != NULL){
 	if (strncmp (buf, pal, strlen(pal)) == 0){
 		dato = get_val (buf, pal);
 		}
 	}
 	
 fclose(fp);
 
 return dato;
}



