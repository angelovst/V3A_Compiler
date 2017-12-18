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
	size_t offset;
	Tipo tipo;
	std::string defaultValue;
} CustomTypeMember;

typedef struct {
	Tipo tipo;
	std::map<std::string, CustomTypeMember> memberType;
} CustomType;

CustomType newCustomType (void);
bool createCustomType (CustomType *type, const std::string &label);
bool addVar (CustomType *type, Tipo *tipo, const std::string &label, const std::string &defaultValue);	//declara nova variavel dentro do tipo, retorna false se variavel ja esta declarada

Tipo* getTipo (CustomType *type, const std::string &member);	//retorna tipo do membro do struct ou NULL caso struct nao possua membro

std::string setAccess (CustomType *type, const std::string &instance, const std::string &member, const std::string &accessVar);	//atribui endereco do membro a variavel de acesso
std::string attrTo (CustomType *type, const std::string &instance, const std::string &member, const std::string &value);	//atribui valor de value ao membro
std::string retrieveFrom (CustomType *type, const std::string &instance, const std::string &member, const std::string &dst);	//atribui valor do membro a dst

std::string newInstanceOf (CustomType *type, std::string &label, bool collectGarbage);	//declara nova instancia do struct e marca a instancia para ser excluida ao fim do bloco ou nao

//mapa de tipos criados
extern std::map<std::string, unsigned int> customTypesIds;
extern std::map<unsigned int, CustomType> customTypes;

#endif
