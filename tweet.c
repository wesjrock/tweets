#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tweet.h"


TWEET *newTweet(){

	//alocando um novo tweet zerado
	TWEET* chirp = (TWEET*) calloc(1,sizeof(TWEET));

	return chirp; //retorna o novo tweet
}

TWEET* deleteTweet(TWEET *foo){
	
	if(foo != NULL){ //trata se o parametro eh invalido
		free(foo); //libera o espaco alocado
		foo = NULL; //para retornar NULL
	}

	return foo; //retornando foo
}

void renewTweet(TWEET *foo){
	if(foo != NULL) memset(foo,0,sizeof(TWEET)); //edita o espaco de memoria como zero
}

void printTweet(TWEET *foo){
	if(foo != NULL){
		printf("User: %s\n", foo->user); // imprimindo uma variavel por vez
		printf("Tweet: \"%s\"\n", foo->tweet);
		printf("Local: %s\n", foo->coordinates);
		printf("Favorite: %d || Retweet: %d\n", foo->favorite_count, foo->retweet_count);
		printf("Total views: %ld\n", foo->view_count);
		printf("Language: %s\n", foo->language);
	}
}

int setTweet(TWEET *target, char *content){
	//uma funcao que alem de copiar o conteudo do que foi passado 
	//retorna o sucesso ou erro da operacao atraves de uma AND
	return !((target != NULL) && (target->tweet == strcpy( target->tweet, content)));
}

int setUser(TWEET *target, char *content){
	//uma funcao que alem de copiar o conteudo do que foi passado 
	//retorna o sucesso ou erro da operacao atraves de uma AND
	return !((target != NULL) && (target->user == strcpy( target->user, content)));
}


int setCoordinates(TWEET *target, char* content){
	//uma funcao que alem de copiar o conteudo do que foi passado 
	//retorna o sucesso ou erro da operacao atraves de uma AND
	return !((target != NULL) && (target->coordinates == strcpy( target->coordinates, content)));
}

int setFavoriteCount(TWEET *target, int count){
	//uma funcao que alem de copiar o conteudo do que foi passado 
	//retorna o sucesso ou erro da operacao atraves de uma AND
	return !((target != NULL) && (target->favorite_count = count));
}

int setLanguage(TWEET *target, char *content){
	//uma funcao que alem de copiar o conteudo do que foi passado 
	//retorna o sucesso ou erro da operacao atraves de uma AND
	return !((target != NULL) && (target->language == strcpy( target->language, content)));
}

int setViewCount(TWEET *target, long int count){
	//uma funcao que alem de copiar o conteudo do que foi passado 
	//retorna o sucesso ou erro da operacao atraves de uma AND
	return !((target != NULL) && (target->view_count = count));
}

int setRetweetCount(TWEET *target, int count){
	//uma funcao que alem de copiar o conteudo do que foi passado 
	//retorna o sucesso ou erro da operacao atraves de uma AND
	return !((target != NULL) && (target->retweet_count = count));
}


char* getTweet(TWEET *source){
	//retorna o campo especificado
	char *foo = NULL;

	if(source != NULL)
		foo = source->tweet;

	return foo;
	
} 

char* getUser(TWEET *source){
	//retorna o campo especificado
	char *foo = NULL;

	if(source != NULL)
		foo = source->user;

	return foo;
}

char* getCoordinates(TWEET *source){
	//retorna o campo especificado
	char *foo = NULL;

	if(source != NULL)
		foo = source->coordinates;

	return foo;

}

int getFavoriteCount(TWEET *source){
	//retorna o campo especificado
	if(source != NULL)
		return source->favorite_count;
	else return -1; //erro
}

char* getLanguage(TWEET *source){
	//retorna o campo especificado
	char *foo = NULL;

	if(source != NULL)
		foo = source->language;

	return foo;
}

long int getViewCount(TWEET *source){
	//retorna o campo especificado
	if(source != NULL) return source->view_count;
	else return -1;
}

int getRetweetCount(TWEET *source){
	//retorna o campo especificado
	if(source != NULL) return source->retweet_count;
	else return -1;
}

