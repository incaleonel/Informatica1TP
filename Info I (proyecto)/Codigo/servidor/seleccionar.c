#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

void seleccionar (int socket, FILE** archivo)//segun el valor elegido abre el archivo correspondiente
{
	int tema;
	int tam=0;
	char buf;
	
	if (recv (socket, &tema, 4, 0) == -1) perror("recv");
			
	printf ("el cliente quiere el tema %d\n", tema);
			
	switch (tema)
	{
		case 1:
			 *archivo = fopen ("musica/musica1.mp3", "r");
			break;
		case 2:
			*archivo = fopen ("musica/musica2.mp3", "r");
			break;
		default: printf("el cliente pidio un tema que no tenemos u.u\n");
			 exit(0);
			
	}
}
