#ifndef HELPER_INCLUDED_H
#define HELPER_INCLUDED_H

#include <string>
#include <vector>
#include <map>
#include <stdlib.h>

#define TIPO_INT "int"
#define TIPO_FLOAT "float"
#define TIPO_BOOL "unsigned char"
#define TIPO_CHAR "char"
#define TIPO_LIST "list"
#define TIPO_INFIX_OPERATOR "operator inf"

#define INVALID_CAST "invalid cast"
#define UNCASTABLE -1
#define NUMBER_SUBSET 3

typedef struct {
	std::string label;
	size_t size;
	std::string (*traducaoParcial)(void *args);
	int subset;
} Tipo;

typedef struct atributos {
	std::string label;
	std::string traducao;
	Tipo *tipo;
} atributos;

typedef struct loopLabel {
	std::string inicio;		
	std::string progressao;
	std::string fim;
} loopLabel;


//VARIAVEIS
atributos* findVarOnTop(std::string label);
atributos* findVar(std::string label);
std::string findTmpName(std::string label);
std::string generateVarLabel (void);
bool declaracaoLocal(std::string &tipo, std::string &label, atributos &atrib);
std::string implicitCast (atributos *var1, atributos *var2, std::string *label1, std::string *label2);

//CONTEXTO
void empContexto();
void desempContexto();

//LOOP
void empLoop();
void desempLoop();
loopLabel* getLoop(int tamLoop);
loopLabel* getOuterLoop();
std::string generateLabel (void);

//FUNCOES DE OPERADORES
std::string traducaoInfixaPadrao (void *args);

//VARIAVEIS GLOBAIS
//Pilha de variaveis
extern std::vector<std::map<std::string, atributos>> varMap;

//String para declaracao de var
extern std::string varDeclar;

//Tipos
extern Tipo tipo_float;
extern Tipo tipo_int;

extern Tipo tipo_bool;
extern Tipo tipo_char;
extern Tipo tipo_list;
extern Tipo tipo_inf_operator;

//Pilha de labels de loop
extern std::vector<loopLabel> loopMap;

#endif
