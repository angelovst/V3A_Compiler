#ifndef HELPER_INCLUDED_H
#define HELPER_INCLUDED_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <stdlib.h>

#define TIPO_INT "int"
#define TIPO_INT_ID 0x01
#define TIPO_FLOAT "float"
#define TIPO_FLOAT_ID 0x02
#define TIPO_NUMBER_ID TIPO_INT_ID|TIPO_FLOAT_ID

#define TIPO_BOOL "unsigned char"
#define TIPO_BOOL_ID 0x04
#define TIPO_CHAR "char"
#define TIPO_CHAR_ID 0x08
#define TIPO_LIST "list"
#define TIPO_LIST_ID 0x10
#define TIPO_INFIX_OPERATOR "operator inf"
#define TIPO_INFIX_OPERATOR_ID 0x20
#define TIPO_REF_ID 0x40
#define TIPO_REF "void*"

#define INVALID_CAST "invalid cast"
#define VAR_ALREADY_DECLARED "already declared"
#define UNCASTABLE -1
#define NUMBER_SUBSET 3

#define BOOL_TRUE "true"
#define BOOL_FALSE "false"

typedef struct _Tipo {
	unsigned int id;
	int subset;
	size_t size;
	std::string label;
	std::string (*traducaoParcial)(void *args);
	std::vector<struct _Tipo*> *retornos;		//usado em funcoes
	std::vector<struct _Tipo*> *argumentos;	//usado em funcoes
} Tipo;

typedef struct _LoopLabel {
	std::string inicio;		
	std::string progressao;
	std::string fim;
} LoopLabel;

typedef struct _Context {
	std::map<std::string, Tipo*> vars;
	std::string declar;
} Context;

typedef struct atributos {
	std::string label;
	std::string traducao;
	Tipo *tipo;
} atributos;

std::string ident (void);
std::string newLine (const std::string &line);	//escreve nova linha do codigo intermediario

//VARIAVEIS
Tipo* findVar(std::string &label);
std::string generateVarLabel (void);
std::string implicitCast (atributos *var1, atributos *var2, std::string *label1, std::string *label2);	//faz cast implicito dos tipos var1 e var2 e atribui os labels das variaveis em label1 e label2
Tipo* resolverTipo (Tipo *a, Tipo *b);	//decide implicitamente o tipo do retorno entre uma operacao envolvendo a e b
bool declararLocal (Tipo *tipo, std::string &label);

//CONTEXTO
void empContexto (void);
void desempContexto (void);

//LOOP
void empLoop (void);
void desempLoop (void);
LoopLabel* getLoop (unsigned int out);
LoopLabel* getOuterLoop (void);
std::string generateLabel (void);

//FUNCOES DE OPERADORES
std::string traducaoLAPadrao (void *args);	//args = (atributos *varA, atributos *varB, string *retorno, string *operador)
std::string traducaoAtribuicao (void *args);	//args = (atributos *varA, atributos *varB, string *retorno)

//VARIAVEIS GLOBAIS
extern unsigned int line;	//linha na qual o parser esta, usado para erros

//Pilha de variaveis
extern unsigned int contextDepth;
extern std::list<Context> contextStack;

//Pilha de labels
extern std::list<LoopLabel> loopStack;

//String para declaracao de var
extern std::string varDeclar;

//Tipos
extern Tipo tipo_float;
extern Tipo tipo_int;
extern Tipo tipo_bool;
extern Tipo tipo_char;
extern Tipo tipo_list;
extern Tipo tipo_ref;

extern Tipo tipo_arithmetic_operator;
extern Tipo tipo_logic_operator;
extern Tipo tipo_atrib_operator;

#endif
