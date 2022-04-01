/* Esta funcion recibe el nombre de un dato a buscar y la linea del 
   archivo "config" donde se encuentra el dato. devuelve el
   valor entero asociado a dicho dato */
   
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get_val (char *buf, char *pal)
{
 int i=0, j=0;
 int len1 = strlen(pal), len2 = strlen(buf);
 int dato;
 char bufc[10];
 
 while (i <= len1) i++;
 while (i <= len2){
 	bufc[j] = buf[i];
 	i++, j++;
 	}
 	
 bufc[j]='\0';
 
 dato = atoi(bufc);
 
 return dato;
}
