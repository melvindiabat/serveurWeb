#include "fonction.h"


/*return target sans la partie apres le ? et si = / return /index.html*/
char * rewrite_target (char * target ){
	char * tar = strtok(target,"?");;
	
	if(strcmp(tar,"/") == 0){
		 tar = "/index.html";
	}
	printf("Fichier demander : %s\n",tar);

	return tar;
}
/*ouvre et return le fd du fichier si il existe*/
int check_and_open ( const char * target , const char * document_root ){
	
	char * tar = strdup(target);
	char * root = strdup(document_root);
	strcat(tar,root);
	int fd = open(tar,O_RDONLY);
	return fd;

}

