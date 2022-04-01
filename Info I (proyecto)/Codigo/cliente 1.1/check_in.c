/* Esta funcion recibe el nombre de un parametro a modificar y el valor
   que se le desea asignar. esto es modicado en el archivo 'config'.
   devuelve 0 en caso de guardar los datos correctamente y -1 en caso
   de no encontrar el parametro a modificar */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check_in (char *pal, int val)
{
 FILE *fp;
 fpos_t *pos=malloc(sizeof(fpos_t));
 int flag = 0;
 char buf[50];
 
 fp = fopen ("config", "r+");
 
 while (!feof(fp)){
 	fgetpos (fp, pos);
 	fgets (buf, 50, fp);
 	if(strncmp (pal, buf, strlen(pal)) == 0){
 		flag = 1;
 		fsetpos (fp, pos);
 		fprintf (fp, "%s: %d", pal, val);
 		}
 	}
 
 if (flag == 0) return -1;
 	
 fclose(fp);
 
 return 0;
 
}
