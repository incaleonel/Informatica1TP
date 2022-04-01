#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define PORT 3494 // puerto al que vamos a conectar
#define MAXDATASIZE 20 // máximo número de bytes que se pueden leer de una vez
int main(int argc, char *argv[])
{
	int sockfd, numbytes, sockudp;
	char buf[20];
	FILE* music=NULL;
	
	music=fopen("ja.mp3","w");
	struct hostent *he;
	struct sockaddr_in their_addr; // información de la dirección de destino
	if (argc != 2) {
		fprintf(stderr,"no pusiste la ip \n");
		exit(1);
	}
	if ((he=gethostbyname(argv[1])) == NULL) { // obtener información de máquina
		perror("gethostbyname");
		exit(1);
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	if ((sockudp = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	their_addr.sin_family = AF_INET;// Ordenación de bytes de la máquina
	their_addr.sin_port = htons(PORT); // Ordenación de bytes de la red
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), 8,0); // poner a cero el resto de la estructura
	if (connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}///el dilema lo tengo a partir de aqui para enviar o recibir datos 
		while(1){
		if ((numbytes=recv(sockfd,buf,21, 0)) == -1) {
		perror("recv");
		exit(1);
		}
		if(numbytes>0){
		fwrite(buf,21*sizeof(char),1,music);
		}}
	/*}	if(numbytes>0){
		buf[numbytes] ='\0';
		printf("mensaje: %s\n",buf);
		}
		scanf("%s",chat);
		if (send(sockfd,chat, 14,0)== -1){
		perror("send");
		exit(0);}	
	}*/
		printf("llego\n");
		fclose(music);
		close(sockudp);
		close(sockfd);

return 0;	
}
