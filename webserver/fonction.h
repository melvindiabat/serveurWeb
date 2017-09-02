#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#define SIZE 256 //taille max requete

enum http_method {
	HTTP_GET ,
	HTTP_UNSUPPORTED ,
};

typedef struct
{
	enum http_method method ;
	int major_version ;
	int minor_version ;
	char * target ;
}http_request;

void traitement_signal ( int sig );
int premiere_ligne(http_request * request);
int parse_http_request (const char * request_line , http_request * request);
void send_status ( FILE * client , int code , const char * reason_phrase );
char *fgets_or_exit ( char * buffer , int size , FILE * stream );
void skip_headers ( FILE * client );
void send_ok(FILE * client,int fd);
void send_erreur( FILE * client , int code , const char * reason_phrase , const char * message_body);
char * rewrite_target ( char * target );
int check_and_open ( const char * target , const char * document_root );
int get_file_size(int fd);
int copy(int in, int out);

