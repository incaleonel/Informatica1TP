#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int fscandir (char *dir)
{
	FILE *fp;
	struct dirent **directorio;
	int n;
	
	n = scandir (dir, &directorio, NULL, alphasort);
				  
	if(n==0){
		perror("scandir");
		}
		
	else{
		fp = fopen("list", "w");
		while (n--){
		fprintf(fp, "%s\n", directorio[n]->d_name);
		free(directorio[n]);
		}
	free(directorio);
	fclose(fp);
	}
}
