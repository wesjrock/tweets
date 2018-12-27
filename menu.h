#ifndef MENU_H
#define MENU_H

/**
 * Funcao que entra no menu principal da aplicacao
 * Todas as funcoes sao listadas para interagir com o usuario
 */
void menu();

/**
 * Adiciona um registro apos ser chamada por menu.
 */
void menu_add();

/**
 * Exibe um registro conforme a escolha do usuario
 */
void menu_exibir();

/**
 * Exibe todos os registros contidos no arquivo de dados
 */
void menu_exibir_all();

/**
 * Busca um registro atraves de um campo especificado pelo usuario
 */
void menu_buscar();

/**
 * Remove um registro por RRN
 */
void menu_remover();

/**
 * Compacta o arquivo eliminando fragmentacao externa
 */
void menu_compactar();

/**
 * Checa os erros retornados por uma operacao de "data"
 * imprime na tela o erro identificado
 * @return 1 para erro e 0 para sucesso
 */
int checkError();

/**
 * Le uma string do teclado. Essa funcao concentra todas as
 * chamadas para ler strings
 * @return um ponteiro para a string que deve ser liberado depois
 */
char* readString();

/**
 * Concentra todas as chamadas para ler inteiros, absorvendo \n
 * @return um inteiro valido
 */
int readInt();

/**
 * Concentra todas as chamadas para ler inteiros do tipo long,
 * absorvendo \n
 * @return um long int valido
 */
long int readLongInt();

/**
 * Absorve uma tecla qualquer do teclado
 */
void ignoreTecla();


#endif