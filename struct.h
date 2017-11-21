/*
 * Um struct consiste em uma colecao de membros alinhados sequencialmente em memoria
 * Em c os structs serao armazenados na heap
 *
 */

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#define UNDEFINED_MEMBER "undefined member"

#include "tipo.h"
#include <list>
#include <map>

typedef struct {
	Tipo tipo;
	std::map<std::string, size_t> memberOffset;
	std::map<std::string, Tipo*> memberType;
} CustomType;

CustomType newCustomType (void);
bool addVar (CustomType *type, Tipo *tipo, std::string &label);	//declara nova variavel dentro do tipo, retorna false se variavel ja esta declarada

Tipo* getTipo (CustomType *type, std::string &member);	//retorna tipo do membro do struct ou NULL caso struct nao possua membro

std::string setAccess (std::string &accessVar, CustomType *type, std::string &instance, std::string &member);	//atribui valor do membro a variavel de acesso

std::string newInstanceOf (CustomType *type, std::string &label, bool collectGarbage);	//declara nova instancia do struct e marca a instancia para ser excluida ao fim do bloco ou nao

#endif
