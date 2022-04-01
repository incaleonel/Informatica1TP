/***
	\file  Spotylinux
	\brief reproductor de audio(recibe musica por TCP)
	\author Mamani Inca Leonel (inca.leonel@gmail.com)
	\author Montaño Marcelo 
	\author Casado Matias
	\date 2015.12.03
	\version version 1.1.10
*/
#include "libplayer.h"

int fcliente (int argc, char *argv)
{
	FILE *music=NULL;
	struct hostent *he;
	struct sockaddr_in their_addr; 
	char buf;
	int sockfd, numbytes;
	int tema=0, num=0;
	int tam;
	int i=0;

	if (argc != 2){
		fprintf(stderr,"No se ingreso la direccion IP\n");
		exit(1);
		}
		
	if ((he=gethostbyname(argv)) == NULL){
		perror("gethostbyname");
		exit(1);
		}
		
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
		}
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(PORT);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), 8,0);
											
// Conecto con el servidor ===========================================

	if (connect(sockfd,(struct sockaddr *)&their_addr,
						sizeof(struct sockaddr)) == -1){
		perror("connect");
		exit(1);
		}
//Elijo la musica**************************************
	while(1){
		check_in ("tema", 0);
		tema = 0;
		printf("Elija una cancion\n");
		while (tema==0){
			tema = check_out ("tema");
			}
		
			music=fopen("music.mp3","w");
		if ((numbytes=send(sockfd, &tema, 4, 0)) == -1){
			perror("send");
			}
		if ((numbytes=recv(sockfd,&tam,4, 0)) == -1){
				perror("recv");
				}
				
// Recibo la cancion =================================================
		while(i<tam){
			if ((numbytes=recv(sockfd,&buf,1, 0)) == -1){
				perror("recv");
				}	
			
			fwrite(&buf,sizeof(char),1,music);
			i++;
			}	
		printf ("musica recibida\n");
		fclose (music);
		} // While(1)... Para pedir mas temas =====================	
		
	
	close (sockfd);
	return 0;	
}
