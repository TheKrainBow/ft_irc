/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}	

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	/*		GESTION D'ERREUR		*/
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	/*		GESTION D'ERREUR		*/

	sockfd = socket(AF_INET, SOCK_STREAM, 0);			// CREATION DE LA SOCKET
	if (sockfd < 0) 
		error("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));		// ALLOCATION DE LA STRUCTURE DU SERVEUR
	portno = atoi(argv[1]);								// RECUPERATION DU PORT EN INT
	serv_addr.sin_family = AF_INET;						// ON DEFINIT LE TYPE DE CONNEXION DE NOTRE SERVEUR
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);					// ON CONVERTI NOTRE INT EN PORT POUR AUTHORISER LES CONNEXIONS
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0) 					// ON ASSOCIE LA STRUCTURE ALLOUÉ, AU FD RETOURNÉ PAR SOCKET
			error("ERROR on binding");
	listen(sockfd,5);									// DEFINIT LA SOCKET COMME EN ATTENTE DE 5 CONNEXIONS MAXIMUM
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,							// RECUPERATION DE LA SOCKET D'UN CLIENT. LE SERVEUR EST EN PAUSE ICI
			  (struct sockaddr *) &cli_addr, 
			  &clilen);
	if (newsockfd < 0)									// ON VERFIE QUE LA SOCKET DU CLIENT EST VALIDE
		error("ERROR on accept");
	
	/*					ON LIS LE MESSAGE DU CLIENT DEPUIS SON FD DE SOCKET, PUIS ON LUI ECRIT		*/
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);
	n = write(newsockfd,"I got your message",18);
	if (n < 0) error("ERROR writing to socket");
	/*					ON LIS LE MESSAGE DU CLIENT DEPUIS SON FD DE SOCKET, PUIS ON LUI ECRIT		*/

	close(newsockfd);									// ON FERME LA SOCKET DU CLIENT
	close(sockfd);										// ON FERME LA SOCKET DU SERVEUR
	return 0; 
}