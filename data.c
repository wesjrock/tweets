#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tweet.h"

#include "data.h"


int fileExist(){ //checa se o arquivo existe
	
	FILE *test = fopen(FILENAME, "r"); //tenta abrir em modo leitura

	if(test != NULL){ //se conseguiu, feche e retorne TRUE
		fclose(test);
		return 1;
	}

	return 0; //retornar falso caso contrario
}

void output(TWEET *target, int *status){ //funcao para grava em arquivo o que for necessario

	FILE *file = NULL; //ponteiro do arquivo comeca em NULL
	int RRN;		//variavel para auxiliar onde escrever
	int stack_handler = STACK_EMPTY; //variavel que guarda o valor da stack de remocao
	char removed_buffer; //char para ver se um registro foi ou nao removido

	(*status) = GENERAL_ERROR;

	if(fileExist()){ //se o arquivo ja existe, podemos continuar

		file = fopen(FILENAME, "rb+"); //modo rb+ que permite escrita e leitura com privilegio
		
		fread(&(stack_handler), sizeof(int),1,file); //absorve o topo da stack que esta no comeco do arquivo

		if (stack_handler == STACK_EMPTY){ //se a stack esta vazia, 
			//basta adicionar no final do arquivo
			
			fseek(file, 0, SEEK_END); //movendo para o final
			fwrite(target, sizeof(TWEET), 1,file); //escrevendo o registro

			(*status) = SUCCESS;

		} else {

			RRN = stack_handler; //se existe topo da stack, podemos ir para o RRN
			
			if(fseek(file, RRN*sizeof(TWEET), SEEK_CUR) == 0){ 
			//se o fseek NAO falhou, continua

				fread(&removed_buffer, sizeof(char), 1, file);
				//absorve o caracter de remocao

				fread(&(stack_handler), sizeof(int), 1,file);
				//le o novo topo da pilha para gravacao no comeco do arquivo
			
				fseek(file, -(sizeof(stack_handler) + sizeof(removed_buffer)), SEEK_CUR);
				//retorna para antes do inteiro da pilha e do char de remocao
				
				
				//agora podemos escrever nosso registro
				fwrite(target, sizeof(TWEET), 1,file);
				
				rewind(file); //retorna ponteiro para o inicio da arquivo

				fwrite(&(stack_handler), sizeof(int), 1,file); //atualiza topo da pilha
				
				(*status) = SUCCESS;

			} else (*status) = SEEK_ERROR; //falha no fseek
		}

	} else { //se o arquivo nao existe, devemos cria-lo

		file = fopen(FILENAME, "wb+"); //criando arquivo
		if(file != NULL){
			fwrite(&(stack_handler), sizeof(int), 1, file); //escreve o topo da pilha
			fwrite(target, sizeof(TWEET), 1, file); //escreve registro
			(*status) = SUCCESS;

		} else (*status) = FILE_ERROR;
		//se por algum motivo o arquivo nao abriu, retorne erro
	}


	//feche o arquivo
	if(file != NULL) fclose(file);
}

//funcao que a partir de um RRN retorna um registro/tweet
TWEET* inputRRN(int RRN, int *status){

	TWEET *buffer = NULL; //buffer para o tweet

	FILE *file = NULL; //ponteiro do arquivo
	char removed_buffer; //leitura do char de remocao
	size_t fread_error; //tratamento para erro no fread

	(*status) = GENERAL_ERROR; //assumimos que o programa esta em estado de erro

	if(fileExist()){ // se o arquivo existe, continuamos
		file = fopen(FILENAME, "rb");
		
		fseek(file, sizeof(int), SEEK_CUR); //absorvendo topo da pilha do comeco do arquivo
		
		//tentativa de fseek para o RRN fornecido
		if(fseek(file, RRN*sizeof(TWEET), SEEK_CUR) == 0){
			fread_error = fread(&(removed_buffer), sizeof(char), 1, file);
			//checando se o registro nao esta removido

			if(fread_error != 1){
				(*status) = READ_ERROR;
			} else if(removed_buffer != REMOVED_CHAR){
				//se nao esta removido, continue

				buffer = newTweet(); // buffer inicializado

				fseek(file, -sizeof(removed_buffer), SEEK_CUR); 
				//se o registro e valido, volta um char para tras
				//esse char poderia ser a marcacao logica de registro removido
								
				fread_error = fread(buffer, sizeof(TWEET), 1,file);
				//tentamos ler um tweet

				//se na leitura houve erro, deletamos o buffer
				if(fread_error != 1){
					buffer = deleteTweet(buffer);
					(*status) = READ_ERROR;
				} else (*status) = SUCCESS; //se tudo correu bem status eh sucesso

			} else (*status) = REMOVED_ERROR; //tentativa de ler registro removido

		} else (*status) = SEEK_ERROR; //tentativa de fseek em posicao invalida
		
		fclose(file); //fecha o arquivo
	
	} else (*status) = FILE_ERROR; //arquivo nao existe


	return buffer; //retorna o tweet
}

TWEET* inputALL(FILE *file, int* status){

	TWEET* buffer = NULL;
	size_t fread_error;

	if(file != NULL){
		
		buffer = newTweet(); // buffer inicializado

		fread_error = fread(buffer, sizeof(TWEET), 1,file);
		//tentamos ler um tweet

		//se na leitura houve erro, deletamos o buffer
		if(fread_error != 1){
			buffer = deleteTweet(buffer);
			(*status) = END_OF_FILE; //nesse caso para qualquer erro de leitura consideramos EOF
		} else if(buffer->tweet[0] == REMOVED_CHAR){
			buffer = deleteTweet(buffer);
			(*status) = REMOVED_ERROR; //aponta que o registro foi removido
		} else {
			(*status) = SUCCESS; //se tudo correu bem status eh sucesso
		}
	} else {
		(*status) = FILE_ERROR; //se o arquivo nao existe
	}

	return buffer;
}

//funcao que remove um tweet
void removeRRN(int RRN, int *status){

	FILE *file = NULL; //ponteiro do arquivo
	int stack_handler=-1; //leitura de dados da stack
	char removed_buffer; //caracter para remover logicamente

	if(fileExist()){ //se o arquivo existe, continue
		file = fopen(FILENAME, "rb+");
		
		fread(&stack_handler, sizeof(int), 1, file); //ler o topo da stack

		if(fseek(file, RRN*sizeof(TWEET), SEEK_CUR) == 0){
		//tente dar fseek para o registro que sera removido
			fread(&removed_buffer, sizeof(char), 1, file);

			if(removed_buffer == REMOVED_CHAR){
				(*status) = REMOVED_ERROR; //se o registro foi removido
			} else {
				fseek(file, -sizeof(char), SEEK_CUR); // volta um char para compensar 
				//a leitura do possivel char de removido logicamente
				
				//para podermos remover logicamente, um buffer receber o char
				removed_buffer = REMOVED_CHAR;

				//escreve o char de removido
				fwrite(&removed_buffer, sizeof(removed_buffer), 1, file);
				//escreve o antigo topo da pilha
				fwrite(&stack_handler, sizeof(stack_handler), 1, file);
				
				//volta para o inicio do arquivo afim de atualizar o topo da pilha
				rewind(file);
				
				//stack eh atualizada com o utlimo RRN do registro removido
				stack_handler = RRN;

				//escreve o topo da pilha
				fwrite(&stack_handler, sizeof(stack_handler), 1, file);
			
				//removido com sucesso
				(*status) = SUCCESS;
			}

		} else (*status) = SEEK_ERROR; //fseek falhou
	} else (*status) = FILE_ERROR; //arquivo nao existe

	if(file != NULL) 
		fclose(file);
}

