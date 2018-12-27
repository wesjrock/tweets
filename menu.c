#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tweet.h"
#include "data.h"

#include "menu.h"

#define ENTER 10

/**
 * Funcao que exibe o menu principal do programa
 */
void menu(){

	int escolha;	//auxliar para escolha do usuario

	do{

		printf("\nMENU\n");
		printf("1- Adicionar tweet\n");
		printf("2- Exibir um tweet\n");
		printf("3- Exibir todos os tweets\n");
		printf("4- Buscar e exibir tweets pelo nome de usuario\n");
		printf("5- Remover um tweet\n");
		
		printf("0- Sair\n");
		
		printf(">> ");
		escolha = readInt(); //usuario escolhe a opcao

		if(escolha == 1){
			menu_add();
		} else if(escolha == 2){
			menu_exibir();
		} else if(escolha == 3){
			menu_exibir_all();
		} else if(escolha == 4){
			menu_buscar();
		} else if(escolha == 5){
			menu_remover();
		}

	}while(escolha); //enquanto a escolha nao for sair, continue
}

/**
 * Funcao para adicionar um registro no banco de registros
 */
void menu_add(){

	char *buffer;	//buffer de leitura para strings
	TWEET *tweet = newTweet(); //buffer do tweet a ser gravado em disco
	int status;

	printf("\n");
	printf("Entre com o usuario: ");
	buffer = readString(); //le string
	setUser(tweet, buffer); //funcao para setar usuario
	free(buffer);	//libera o buffer apos ser salvo no tweet

	printf("Entre com o seu tweet: "); 
	buffer = readString(); //vide acima
	setTweet(tweet, buffer);
	free(buffer);

	printf("Quais são as coordenadas do tweet? ");
	buffer = readString();
	setCoordinates(tweet, buffer);
	free(buffer);

	printf("Digite o número de favoritos do tweet: ");
	setFavoriteCount(tweet, readInt());

	printf("Em qual lingua esta o tweet? ");
	buffer = readString();
	setLanguage(tweet, buffer);
	free(buffer);

	printf("Quantos retweets? ");
	setRetweetCount(tweet, readInt());

	printf("Digite o número de visualizacoes do tweet: ");
	setViewCount(tweet, readLongInt());

	output(tweet, &status);

	if( status == SUCCESS) //Se conseguimos gravar
		printf("\nRegistro adicionado com sucesso!\n\n");
	else printf("\nHouve uma falha desconhecida...\n\n");

	deleteTweet(tweet); //liberando o espaco alocado
}

/**
 * funcao para exibir um tweet completo
 */
void menu_exibir(){

	int RRN; //input do usuario
	int status; //variavel auxiliar de erros
	TWEET *buffer; //buffer temporario para o tweet lido

	printf("\nPor favor, entre com o RRN do tweet: ");
	scanf("%d", &RRN);

	buffer = inputRRN(RRN, &status); //recebendo o tweet e passando RRN e 
	//status, que eh uma variavel auxiliar para tratar erros

	printf("\n");

	//tratamento de erros e comunicacao com usuario
	if(!checkError(status)){
		printTweet(buffer);//funcao para printar tweet
		printf("\n");
	}

	deleteTweet(buffer); //se foi lido com sucesso, delete

	printf("Pressione qualquer tecla para voltar ao menu...\n");
	ignoreTecla();
}

void menu_exibir_all(){

	int status;			//status de erro
	TWEET *buffer;		//buffer do tweet
	FILE *file;			//ponteiro do arquivo
	int rrn_count=0;	//contador de RRN
	char rrn_escolha; //flag para escolha do usuario

	file = fopen(FILENAME, "rb"); //abrindo em modo de leitura
	
	if(file != NULL){

		fseek(file, sizeof(int), SEEK_CUR); //pulando comeco da pilha

		printf("\nVocê deseja exibir o RRN dos tweets? (S/N)");
		scanf("%c", &rrn_escolha);
		ignoreTecla(); //absorve \n

		//escolha do usuario como verdadeiro ou falso
		if(rrn_escolha == 'S' || rrn_escolha == 's') 
			rrn_escolha = 1;
		else rrn_escolha = 0;

		printf("\nExibindo todos os tweets...\n\n");
		
		do{
			
			buffer = inputALL(file, &status);

			//exibindo tweet se eh valido
			if(buffer != NULL){
				if(rrn_escolha) //se o usuario quer RRN, imprima
					printf("RRN: %d\n", rrn_count);
				printTweet(buffer);
				printf("\nPara o próximo tweet pressione qualquer tecla...\n");
				ignoreTecla();			

				buffer = deleteTweet(buffer); //deletando buffer
			}

			rrn_count++; //contador para exibicao do RRN
		}while(status != END_OF_FILE);

		printf("Fim dos tweets\n");
		fclose(file); //fechando arquivo

	} else {
		printf("O arquivo ainda não existe.\n");
	}
	
	printf("Pressione qualquer tecla para voltar ao menu...\n");
	ignoreTecla();
	//ignora qualquer tecla
}

void menu_buscar(){

	int status; //para tratar erro de leitura e EOF
	TWEET *tweet_buffer; // buffer do tweet lido
	FILE *file; //ponteiro do arquivo
	int rrn_count=0; //contador de rrn
	char rrn_escolha; //flag para exibir ou nao RRN
	char *user_buffer; //nick do usuario desejado

	file = fopen(FILENAME, "rb"); //abre o arquivo no modo de leitura
	
	if(file != NULL){

		//pula o topo da pilha no comeco do arquivo
		fseek(file, sizeof(int), SEEK_CUR);

		//pergunta ao usuario o nome do campo desejado
		printf("\nDigite o nome do usuario: ");
		user_buffer = readString();

		//pergunta ao usuario sobre a exibicao dos tweets
		printf("\nVocê deseja exibir o RRN dos tweets? (S/N)");
		scanf("%c", &rrn_escolha);
		ignoreTecla();

		//trata como verdadeiro ou falso a resposta do usuario
		if(rrn_escolha == 'S' || rrn_escolha == 's') rrn_escolha = 1;
		else rrn_escolha = 0;

		printf("\nExibindo todos os tweets...\n\n");
		
		do{
			
			tweet_buffer = inputALL(file, &status);

			if(tweet_buffer != NULL){ //se eh um tweet valido
				//se eh um tweet do usuario desejado
				if(!strcmp(user_buffer, tweet_buffer->user)){

					if(rrn_escolha)
						printf("RRN: %d\n", rrn_count);

					printTweet(tweet_buffer);
					//imprimindo tweet
					printf("\nPara o próximo tweet pressione qualquer tecla...\n");
					ignoreTecla();
				}

				//buffer de tweet
				tweet_buffer = deleteTweet(tweet_buffer);
			}

			rrn_count++; //conta o RRN para impressao
		} while(status != END_OF_FILE); //enquanto o arquivo nao chega ao fim

		printf("Fim dos tweets\n");

		free(user_buffer); //libera o espaco alocado para leitura do nick
		fclose(file); //fecha o arquivo

	} else { //erro arquivo nao existe
		printf("O arquivo ainda não existe.\n");	
	}
	
	printf("Pressione qualquer tecla para voltar ao menu...\n");
	ignoreTecla();
	//apenas absorve um char qualquer
}

void menu_remover(){

	int RRN; //input do usuario
	int status; //variavel auxiliar de erros
	TWEET *target; //tweet auxiliar que guarda o registro para exclusao

	printf("\nPor favor, entre com o RRN do tweet: ");
	scanf("%d", &RRN);
	ignoreTecla();

	target = inputRRN(RRN, &status);
	//checa se o registro existe

	if(!checkError(status)){
		removeRRN(RRN, &status);
		printf("Tweet removido com sucesso!\n");
		printf("\n");
	}

	deleteTweet(target);
	//liberando espaco alocado

	printf("Pressione qualquer tecla para voltar ao menu...\n");
	ignoreTecla();
	//apenas absorve um char qualquer
}

int checkError(int status){
	
	//tratando todos os erros

	if(status == SUCCESS){
		return 0;
	} else if(status == GENERAL_ERROR){
		printf("Desculpe, um erro desconhecido foi identificado...\n");
	} else if(status == READ_ERROR || status == SEEK_ERROR){
		printf("O registro requisitado não pode ser encontrado.\n");
	} else if(status == FILE_ERROR){
		printf("O arquivo de dados não existe!\n");
	} else if(status == REMOVED_ERROR){
		printf("O registro foi permanentemente excluido.\n");
	}

	return 1;
}

void ignoreTecla(){ 
	//funcao que elimina um char
	//interessante para absorver \n ou quando eh necessario
	//parar o fluxo de dados na tela
	scanf("%*c");
}

char* readString(){
	int i = 0;
	char c;
	char *buffer = (char*)calloc(141, sizeof(char));
	do{
		c = fgetc(stdin);
		buffer[i++] = c;
	}while(c != ENTER);
	buffer[i-1] = '\0';

	return buffer;
}

int readInt(){
	int buffer;
	
	scanf("%d", &buffer);
	ignoreTecla();
	
	return buffer;
}

long int readLongInt(){
	
	long int buffer;
	
	scanf("%ld", &buffer);
	ignoreTecla();

	return buffer;
}

