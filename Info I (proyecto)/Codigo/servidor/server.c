/***
	\file  Spotylinux
	\brief reproductor de audio(envio de musica por TCP)
	\author Mamani Inca Leonel (inca.leonel@gmail.com)
	\author Montaño Marcelo 
	\author Casado Matias
	\date 2015.12.03
	\version version 1.1.10
*/
#include "prototipos.h"

int main ()
{
 FILE *musica, *list;
 struct sockaddr_in my_addr;
 struct sockaddr_in their_addr;
 struct sigaction sa;
 char buf, *line;
 int yes=1, cont=0;
 int sockfd, new_fd;
 int sin_size;
 int numbytes;
 int tema;
 int len;
 int tam=0;
	
// Genero un archivo con las canciones disponibles ===================
	fscandir ("musica");
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
		}
	
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero), '\0', 8);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
	
	if (bind(sockfd, (struct sockaddr *)&my_addr,
			 sizeof (struct sockaddr)) == -1){
		perror ("bind");
		exit (1);
		}
	if (listen (sockfd, BACKLOG) == -1){
		perror ("listen");
		exit(1);
		}
	if (sigaction(SIGCHLD, &sa, NULL) == -1){
		perror ("sigaction");
		exit (1);
		}
// Conecto con cada cliente =========================================
		while (1){
			sin_size = sizeof (struct sockaddr_in);
			
			if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr,
								 &sin_size)) == -1){
				perror ("accept");
				}
				
				printf ("se conecto este usuario: %s\n",
						inet_ntoa(their_addr.sin_addr));
			
// Un proceso por cada uno ===========================================
			if(!fork()){
			while(1){
			seleccionar(new_fd,&musica);
		
			while(!feof(musica))
			{
				if(fread(&buf,sizeof(char),1,musica)!=0)
				{	
					tam++;
				}
			}
			if ((send(new_fd,&tam,4,0)) == -1)
					{
					perror("send");
					}
			rewind(musica);
			while(!feof(musica)){

				if(fread(&buf,sizeof(char),1,musica)!=0)
				{ 
					if ((send(new_fd,&buf,1,0)) == -1)
					{
					perror("send");
					}
				}
			}
			printf("enviado con exito\n");
			fclose(musica);
			}
		close (new_fd);
		}
		}
		close(sockfd);
	return 0;
}
