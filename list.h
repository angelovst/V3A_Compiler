/*
 * Contem metodos para geracao de codigo intermediario de operacoes com lista
 * A lista e duplamente encadeada
 *		Vitor Andrade, 2017
 */

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define NO_ACCESS_VAR "_memberAccess"
#define NO_DADO "_dado"

#include "helper.h"
#include <string>

//todos os atributos das structs abaixo sao labels de variaveis
typedef struct _No {
	void* dado;
	struct _No *anterior;
	struct _No *proximo;
} No;

typedef struct {
	size_t tamanho;
	No *primeiro;
	No *ultimo;
} Lista;

//NO DA LISTA
std::string generateNodeLabel (void);
std::string no_getData (std::string &label);
std::string no_getMemberAccess (std::string &label);
std::string no_setAccessDado (std::string &label);
std::string no_setAccessAnterior (std::string &label);
std::string no_setAccessProximo (std::string &label);

void no_novo (std::string &label);
std::string no_deletar (std::string &label);
std::string no_atribuir (std::string &label, atributos &dado);	//atribui dado a um no

//construtores
std::string newList (std::string &label);
std::string copyChain (std::string &beginLabel, std::string &endLabel);

std::string add (std::string &lista, std::string &noReferencia, std::string &no);	//adiciona no apos noReferencia
std::string remove (std::string &labelNo);

std::string empty (std::string &lista);


#endif
