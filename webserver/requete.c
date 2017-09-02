#include "fonction.h"

int nbEspace(const char * str){
	int res = 0;
	int i = 0;
	while(str[i]!='\n'){
		if(str[i]==' '){
			res++;
		}
		i++;
	}
	return res;
}

/* analyse la premiere ligne return le code */
int premiere_ligne(http_request * request){

	if(request->method == HTTP_UNSUPPORTED)
		return 405;
	else if(request->major_version == -1 || request->minor_version ==-1)
		return 505;

	else if(request->method == HTTP_GET){

		if(strstr(request->target,"..")!=NULL) 
			return 403;

		return 200;
			
	} 	
	return 400;
}


/*analyser la première ligne de la requête et la range dans la structure return 0 si invalide 1 sinon*/
int parse_http_request (const char * request_line , http_request * request){

	char * requete = strdup(request_line);
	if(nbEspace(request_line) != 2) return 0;

	char * met = strtok(requete," ");
	if(strcmp(met,"GET") == 0) request->method = HTTP_GET;			
	
	else{
		request->method = HTTP_UNSUPPORTED;
		free(requete);
		return 0;
	}

	char * tar = strtok(NULL," ");	
	char * ver = strtok(NULL," ");


	request->target = strdup(tar);

	if(strcmp(ver,"HTTP/1.0\n") == 0 || strcmp(ver,"HTTP/1.0\r\n") == 0){
		request->major_version = 1;
		request->minor_version = 0;
	}
	else if(strcmp(ver,"HTTP/1.1\n") == 0 || strcmp(ver,"HTTP/1.1\r\n")== 0) {
		request->major_version = 1;
		request->minor_version = 1;

	}
	else{
		request->major_version = -1;
		request->minor_version = -1;
		free(requete);
		return 0;
	}
	free(requete);
	return 1;
}

/*ignore les headers des clients*/
void skip_headers ( FILE * client ){
	
	char buff[SIZE];
	int arret = 0; 					//detecte quand \n ou \r\n et stop la boucle
	char * get = fgets_or_exit(buff , SIZE,client);
			
	while(arret != 1){
 				
		if(strcmp(buff,"\n") == 0 || strcmp(buff,"\r\n") == 0 ) arret = 1;

		else printf("<Client> %s",buff); //affiche dans le term du serveur les ligne ignorer

		if(arret != 1) get = fgets_or_exit(buff , SIZE,client);
	
	}
}

