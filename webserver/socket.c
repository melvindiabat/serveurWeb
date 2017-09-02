#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#include "socket.h"


int creer_serveur ( int port ){
	
	int socket_serveur ;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1)
	{
		/* traitement de l ’ erreur */
		perror ( " socket_serveur " );
		return -1;
	}
	/* Utilisation de la socket serveur */

	int optval = 1;
	//ajout de l'option SO_REUSEADDR pour redemarrer le serveur sans erreur	
	if ( setsockopt ( socket_serveur, SOL_SOCKET , SO_REUSEADDR , & optval , sizeof ( int )) == -1)
	{
		perror ( " Can not set SO_REUSEADDR option " );
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET ; /* Socket ipv4 */
	saddr.sin_port = htons (port); /* Port d ’é coute */
	saddr.sin_addr.s_addr = INADDR_ANY ; /* é coute sur toutes les interfaces */

	if (bind(socket_serveur,(struct sockaddr*)& saddr, sizeof(saddr)) == -1)
	{
		perror ( " bind socker_serveur " );
		/* traitement de l ’ erreur */
		return -1;
	}
	
	if (listen(socket_serveur , 10) == -1)
	{
		perror ( " listen socket_serveur " );
		/* traitement d ’ erreur */
		return -1;
	}

	printf("Serveur en cours....\n");

	return socket_serveur;

}