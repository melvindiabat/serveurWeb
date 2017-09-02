
#include "fonction.h"

#define READ_BUFF 30

/*premiere ligne de lentete*/
void send_status ( FILE * client , int code , const char * reason_phrase ){

	fprintf(client, "HTTP/1.1 %d %s\r\n", code, reason_phrase);
}

/*affiche la fin l'entete si il sagit d'une erreur*/
void send_erreur( FILE * client , int code , const char * reason_phrase , const char * message_body){

	send_status(client,code,reason_phrase);
	fprintf(client, "Connection: close\r\nContent-Length: %d\r\n\r\n%d %s\r\n",strlen(message_body)+4,code,message_body);
	fflush(client);
}

/*affiche la fin l'entete si il ne sagit pas d'une erreur*/
void send_ok(FILE * client,int fd_in){

	send_status(client,200,"OK");
	fprintf(client, "Content-Length: %d\r\n\r\n",get_file_size(fd_in));
	fflush(client);
		
}

/*content-length du fd*/
int get_file_size(int fd){

	struct stat s;
   	fstat(fd,&s);
 	printf("taille fichier: %d\n",s.st_size);
   return s.st_size;
}

/*copy in vers out*/
int copy(int in, int out){
	char buff[READ_BUFF];
	int r;
	while((r  = read(in,buff,READ_BUFF)) > 0){
		write(out,buff,r);
	}
	write(out,"\r\n\0",3);
	close(in);

	return 0;

}
