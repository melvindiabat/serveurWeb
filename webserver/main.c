#include "socket.h"
#include "fonction.h"

int main(int argc, char const *argv[])
{

	if(argc != 2){
		printf("Mauvaise utilisation argument 1 = chemin du serveur\n");
		return -1;
	}

	int serveur = creer_serveur ( 8080 );
	if(serveur==-1)
	{
		perror("creer_serveur: ");
		return -1;
	}
	
	/* connections */
	http_request request;
	int socket_client ;

	while(1)
	{
		socket_client = accept ( serveur , NULL , NULL );
		FILE *client = fdopen(socket_client,"w+");
	
		if (socket_client == -1)
		{
			perror ("accept"); 
			return -1;
		}

		initialiser_signaux(); //pour ignorer le signal arret quand un traitement est en cours
		
		if(fork()==0)
		{
					
			/* lecture des clients */
			char buff[SIZE];			
			
			/* traitement ligne 1*/		
			fgets_or_exit(buff , SIZE,client);
			printf("<Client> %s",buff);

			int parse = parse_http_request(buff, &request);

			skip_headers(client);

			int err = premiere_ligne(&request); //return l'erreur ou le code 200



			int fd;
			if(err == 200){
				char * tar = rewrite_target(request.target);
				fd = check_and_open (argv[1],tar);
				if(fd == -1){
					err = 404;
				}
				else  {
					send_ok(client,fd);					
					copy(fd,socket_client);
				}
			}
			printf("code: %d\n",err );

			if(err == 400) send_erreur(client,400,"Bad Request","Bad Request\r\n");
			else if(err == 404) send_erreur(client,404,"Not Found","Not Found\r\n");
			else if(err == 405) send_erreur(client,405,"Method Not Allowed","Method Not Allowed\r\n");
			else if (err == 403) send_erreur(client,403,"Forbidden","Forbidden\r\n");
			else if(err == 505) send_erreur(client,505,"HTTP Version Not Supported","HTTP Version Not Supported\r\n");

		
			fclose(client);
			exit(0);
			
		}
		close(socket_client);													
		
	}
	return 0;
}

/*idem que fgets mais quitte le processus si gets == null*/
char *fgets_or_exit ( char * buffer , int size , FILE * stream ){
	char * get = fgets(buffer,size-1,stream);
	if(get == NULL){
		exit(-1);
	}
	buffer[size]='\0';
	return get;
}

