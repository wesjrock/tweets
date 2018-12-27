#ifndef DATA_H
#define DATA_H

#define FILENAME "tweets.db" //nome estatico do arquivo
#define REMOVED_CHAR	07 	//char especial para removidos

#define STACK_EMPTY		-1 	//Indicador de stack vazia

/**
 * Enum para tratamento de erros
 */
enum ERRORS{
	SUCCESS,
	GENERAL_ERROR,
	READ_ERROR,
	SEEK_ERROR,
	FILE_ERROR,
	REMOVED_ERROR,
	END_OF_FILE
};

/**
 * Funcao que verifica a existencia do arquivo
 * @return retorna 1 se existe e 0 caso contrario
 */
int fileExist();

/**
 * Escreve no arquivo um tweet qualquer
 * @param target >> Tweet que sera armazenado
 * @param status >> Flag de erro
 */
void output(TWEET *target, int *status);

/**
 * Funcao que le do arquivo um tweet
 * @param  RRN    >> eh o RRN do tweet pretendido
 * @param  status >> flag de erro
 * @return        << retorna um tweet. Se eh uma leitura
 *                   invalida retorna NULL
 */
TWEET* inputRRN(int RRN, int *status);

/**
 * Funcao que le todos os registros, um por vez,
 * @param  file   >> ponteiro para o arquivo
 * @param  status >> status de erro
 * @return        << retorna um tweet lido
 */
TWEET* inputALL(FILE* file, int *status);

/**
 * funcao que remove um tweet a partir do seu RRN
 * @param RRN    >> RRN do tweet que sera removido
 * @param status >> flag de erro
 */
void removeRRN(int RRN, int *status);

#endif