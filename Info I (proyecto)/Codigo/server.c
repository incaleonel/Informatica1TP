#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define MAXDATASIZE 20
#define MYPORT 3494// Puerto al que conectarán los usuarios
#define BACKLOG 10// Cuántas conexiones pendientes se mantienen en cola
void sigchld_handler(int s)
{
while(wait(NULL) > 0);
}
int main(void)
{
	int sockfd,sockudp, new_fd,new_udp; // Escuchar sobre sock_fd, nuevas conexiones sobre new_fd
	struct sockaddr_in my_addr;// información sobre mi dirección
	struct sockaddr_in their_addr; // información sobre la dirección del cliente
	int sin_size;
	struct sigaction sa;
	int yes=1;
	int dato=0;
	int numbytes;
	char buf;
	FILE *musica=NULL;
	
	musica=fopen("music.mp3","r");
	
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		}
		my_addr.sin_family = AF_INET;// Ordenación de bytes de la máquina
		my_addr.sin_port = htons(MYPORT);// short, Ordenación de bytes de la red
		my_addr.sin_addr.s_addr = INADDR_ANY; // Rellenar con mi dirección IP
		memset(&(my_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura
		setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
		if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
		perror("bind");
		exit(1);
		}
		if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
		}
		if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
		}
		
		
			sin_size = sizeof(struct sockaddr_in);
			if ((new_fd = accept(sockfd,(struct sockaddr *)&their_addr,&sin_size)) == -1) {
			perror("accept");
			}//y aqui comiensa el envio o recibir datos
			printf("server:se conecto este wacho  %s\n",inet_ntoa(their_addr.sin_addr));
		while(!feof(musica))
		{
			fread(&buf,sizeof(char),1,musica);
			dato++;
		}
		fclose(musica);
		musica=fopen("music.mp3","r");
		
			if ((send(new_fd,&dato,4,0)) == -1){
				perror("send");
				exit(0);}
				
			while(!feof(musica)){
				if((fread(&buf,sizeof(char),1,musica))>0){
				if ((send(new_fd,&buf,1,0)) == -1){
				perror("send");
				exit(0);}
				}
				else{ exit(0);}
			/*sin_size = sizeof(struct sockaddr_in);
			if ((new_fd = accept(sockfd,(struct sockaddr *)&their_addr,&sin_size)) == -1) {
			perror("accept");
			continue;
			}
			printf("server:se conecto este wa  %s\n",inet_ntoa(their_addr.sin_addr));
			while(1){
				scanf("%s",chat);
				if (send(new_fd,chat, 14,0) == -1){
				perror("send");
				exit(0);}
				if ((numbytes=recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
			perror("recv");
			exit(1);
			}		
			if(numbytes>0){
			buf[numbytes] ='\0';
			printf("mensaje: %s\n",buf);
			}
			}*/
			}
			printf("enviado con exito");
			
		fclose(musica);
		close(sockfd);
		close(new_fd); // El proceso padre no lo necesita
return 0;
}
