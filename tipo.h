#ifndef TIPO_H_INCLUDED
#define TIPO_H_INCLUDED

#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <list>

#define TIPO_INT_TRAD "int"
#define TIPO_FLOAT_TRAD "float"
#define TIPO_BOOL_TRAD "unsigned char"
#define TIPO_CHAR_TRAD "char"
#define TIPO_LIST_TRAD "void*"
#define TIPO_PTR_TRAD "char*"
#define TIPO_INF_OP_TRAD ""

//id consiste em duas partes, primeiros 8bits definem a qual grupo o tipo pertence, os demais definem qual nivel ele esta
//tipos podem ser convertidos de um para outro caso pertencam ao mesmo grupo, um tipo pode ser implicitamente convertido para outro caso tenha nivel menor
#define GROUP_PTR			0x01000000
#define GROUP_NUMBER		0x40000000
#define GROUP_BOOL			0x02000000
#define GROUP_CHAR			0x04000000
#define GROUP_CONTAINER 	0x08000000
#define GROUP_FUNCTION		0x10000000
#define GROUP_STRUCT		0x20000000

#define GROUP_UNCASTABLE	0x80000000

#define TIPO_INT_ID		GROUP_NUMBER|0x01
#define TIPO_FLOAT_ID	GROUP_NUMBER|0x04

#define TIPO_BOOL_ID	GROUP_BOOL|0x01

#define TIPO_CHAR_ID	GROUP_CHAR|0x01

#define TIPO_LIST_ID	GROUP_CONTAINER|0x01

#define TIPO_INF_OP_ID	GROUP_FUNCTION|0x01

#define TIPO_STRUCT_ID	GROUP_STRUCT|GROUP_UNCASTABLE|0x00

#define INVALID_CAST "invalid cast"
#define VAR_ALREADY_DECLARED "already declared"
#define VOID_POINTER "void pointer"
#define VAR_UNDECLARED "var undeclared"

#define BOOL_TRUE "true"
#define BOOL_FALSE "false"

typedef struct _Tipo {
	unsigned int id;
	size_t size;
	std::string trad;
	std::string (*cast)(std::string &dst, struct _Tipo *selfT, struct _Tipo *fromT, std::string &fromL);	//faz cast de from para uma instancia de self
	std::string (*traducaoParcial)(void *args);
	std::vector<struct _Tipo*> *retornos;		//usado em funcoes
	std::vector<struct _Tipo*> *argumentos;	//usado em funcoes
} Tipo;


typedef struct atributos {
	std::string label;
	std::string traducao;
	Tipo *tipo;
} atributos;

typedef struct {
	std::map<std::string, Tipo*> vars;
	std::string declar;
	std::string garbageCollect;
} Context;

std::string generateVarLabel (void);

std::string ident (void);
std::string newLine (const std::string &line);	//escreve nova linha do codigo intermediario

int getGroup (Tipo *tipo);
bool belongsTo (Tipo *tipo, int group);
Tipo* resolverTipo (Tipo *a, Tipo *b);	//decide implicitamente o tipo do retorno entre uma operacao envolvendo a e b

Tipo* newPtr (Tipo *pointsTo);

Tipo nonPtr (Tipo *ptr);

std::string implicitCast (atributos *var1, atributos *var2, std::string *label1, std::string *label2);	//faz cast implicito dos tipos var1 e var2 e atribui os labels das variaveis em label1 e label2

//FUNCOES DE CAST
std::string castPadrao (std::string &dst, struct _Tipo *selfT, struct _Tipo *fromT, std::string &fromL);

//FUNCOES DE OPERADORES
std::string traducaoLAPadrao (void *args);	//args = (atributos *varA, atributos *varB, string *retorno, string *operador)
std::string traducaoAtribuicao (void *args);	//args = (atributos *varA, atributos *varB, string *retorno)
std::string traducaoOperadores( atributos atr1, atributos atr2, atributos atr3, atributos *atrRetorno);

//CONTEXTO
void empContexto (void);
void desempContexto (void);
Tipo* findVar(std::string &label);
bool declararGlobal (Tipo *tipo, const std::string &label);
bool declararLocal (Tipo *tipo, const std::string &label);

//Tipos
extern Tipo tipo_float;
extern Tipo tipo_int;
extern Tipo tipo_bool;
extern Tipo tipo_char;
extern Tipo tipo_list;
extern Tipo tipo_ptr;

extern Tipo tipo_arithmetic_operator;
extern Tipo tipo_logic_operator;
extern Tipo tipo_atrib_operator;

//mapa de tipos de ponteiros
extern std::map<Tipo*, Tipo> tipo_ptrs;

//Pilha de variaveis
extern std::list<Context> contextStack;
extern unsigned int contextDepth;

#endif
