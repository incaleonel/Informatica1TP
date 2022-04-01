#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <gtk/gtk.h>
#include "prototipos.h"

int fcliente (int argc, char *argv)
{
	int sockfd, numbytes, sockudp;
	char buf;
	int tema;
	FILE* music=NULL;
	int num=0;
	
	
	struct hostent *he;
	struct sockaddr_in their_addr; /* información de la dirección
									  de destino*/
	if (argc != 2){
		fprintf(stderr,"No se ingreso la direccion IP\n");
		exit(1);
		}
		
	if ((he=gethostbyname(argv)) == NULL){ // obtener información
		perror("gethostbyname");			  // de la máquina
		exit(1);
		}
		
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
		}
	their_addr.sin_family = AF_INET;//Ordenación de bytes de la máquina
	their_addr.sin_port = htons(PORT); //Ordenación de bytes de la red
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), 8,0); /* poner a cero el resto de 
											la estructura*/
	if (connect(sockfd,(struct sockaddr *)&their_addr,
						sizeof(struct sockaddr)) == -1){
		perror("connect");
		exit(1);
		}/*el dilema lo tengo a partir de aqui para enviar
		   o recibir datos */

			music=fopen("music.mp3","w");
			printf("selecione la musica:\n");
			scanf("%d",&tema);
			if ((numbytes=send(sockfd,&tema,4, 0)) == -1){
				perror("recv");
				}
			while(1){
			
			if ((numbytes=recv(sockfd,&buf,1, 0)) == -1){
				perror("recv");
				break;
				}
				
			if(numbytes==0) break;	
			
			fwrite(&buf,sizeof(char),1,music);
			}			
		
		printf("musica recibida\n");
		fclose(music);
			
}
