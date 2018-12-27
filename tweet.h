#ifndef TWEET_H
#define TWEET_H

//tamanhos dos campos do registro
#define TWEET_TEXT_SIZE 	141 //140 + \0
#define USER_SIZE 			21 
#define LANG_SIZE			21
#define COORD_SIZE 			12

//registro principal
typedef struct tweet{

	char tweet[TWEET_TEXT_SIZE];
	char user[USER_SIZE];
	char coordinates[COORD_SIZE];
	int favorite_count;
	char language[LANG_SIZE];
	long int view_count;
	int retweet_count;

}TWEET;

/**
 * Cria um tweet novo
 * @return retorna um ponteiro para onde esta o tweet
 */
TWEET* newTweet();

/**
 * Destroi um tweet
 * @param  foo >> tweet a ser destruido
 * @return     << retorna NULL
 */
TWEET* deleteTweet(TWEET *foo);

/**
 * Apaga todos os campos de um tweet 
 * @param foo >> tweet
 */
void renewTweet(TWEET *foo);

/**
 * Imprime um tweet
 * @param foo >> tweet
 */
void printTweet(TWEET *foo);


/////////////////////////
// BASIC SET FUNCTIONS //
/////////////////////////

	/**
	 * Edita o conteudo do campo tweet no registro dado
	 * @param  target  >> registro
	 * @param  content >> conteudo do tweet
	 * @return         << retorna 0 para sucesso e 1 para erro
	 */
	int setTweet(TWEET *target, char *content);
	

	/**
	 * Edita o campo user 
	 * @param  target  >> registro
	 * @param  content >> nick do usuario
	 * @return         << 0 para sucesso e 1 para erro
	 */
	int setUser(TWEET *target, char *content);
	

	/**
	 * Edita o campo coordenadas 
	 * @param  target  >> registro
	 * @param  content >> coordenadas
	 * @return         << 0 para sucesso e 1 para erro
	 */
	int setCoordinates(TWEET *target, char* content);
	

	/**
	 * Edita a contagem de favoritos do registro
	 * @param  target >> registro
	 * @param  count  >> contador
	 * @return        << 0 para sucesso e 1 para erro
	 */
	int setFavoriteCount(TWEET *target, int count);
	

	/**
	 * Edita a lingua do registro
	 * @param  target  >> registro
	 * @param  content >> conteudo
	 * @return		   << 0 para sucesso e 1 para erro
	 */
	int setLanguage(TWEET *target, char *content);
	

	/**
	 * Edita o campo view do registro
	 * @param  target >> registro
	 * @param  count  >> contador
	 * @return		  << 0 para sucesso e 1 para erro
	 */
	int setViewCount(TWEET *target,long int count);
	

	/**
	 * Edita o campo retweet do registro
	 * @param  target >> registro
	 * @param  count  >> contador
	 * @return		  << 0 para sucesso e 1 para erro
	 */
	int setRetweetCount(TWEET *target, int count);


/////////////////////////
// BASIC GET FUNCTIONS //
/////////////////////////

	/**
	 * Retorna a string do tweet
	 * @param  source >> registro
	 * @return        << retorna a string do tweet
	 */
	char* getTweet(TWEET *source);

	/**
	 * Retorna a string do campo usuario
	 * @param  source >> registro
	 * @return        << retorna a string user
	 */
	char* getUser(TWEET *source);

	/**
	 * Retorna a string do campo coordenadas
	 * @param  source >> registro
	 * @return        << retorna a string coordinates
	 */
	char* getCoordinates(TWEET *source);

	/**
	 * Retorna a string do campo contador favoritos
	 * @param  source >> registro
	 * @return        << retorna o inteiro favorite_count
	 */
	int getFavoriteCount(TWEET *source);
	
	/**
	 * Retorna a string do campo lingua
	 * @param  source >> registro
	 * @return        << retorna a string language
	 */	
	char* getLanguage(TWEET *source);
	
	/**
	 * Retorna a string do campo contador de visualizacoes
	 * @param  source >> registro
	 * @return        << retorna o inteiro view_count
	 */
	long int getViewCount(TWEET *source);
	
	/**
	 * Retorna a string do campo contador de retweets
	 * @param  source >> registro
	 * @return        << retorna o inteiro retweet_count
	 */
	int getRetweetCount(TWEET *source);

#endif
