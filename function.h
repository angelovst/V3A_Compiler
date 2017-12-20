#pragma once

#define RETURN_STRUCT "_ret"

#include <map>
#include <string>
#include <vector>
#include "struct.h"

typedef struct {
	std::vector<std::string> retornosLabel;
	CustomType retornos;
	std::vector<std::string> argsLabel;
	CustomType args;
	std::string traducao;
} Funcao;

extern std::map<std::string, Funcao> funcMap;
extern std::string functionDeclars;

Funcao newFunc (void);

bool declareFunc (Funcao *f, const std::string &label);
bool createFunc (Funcao *f, const std::string &label);

bool addRetorno (Funcao *f, Tipo *retorno, const std::string &retornoLabel);
bool addArg (Funcao *f, Tipo *argT, const std::string &argLabel, const std::string &defaultValue);

Tipo* getRetorno (Funcao *f, int returnIndex);
Tipo* getArg (Funcao *f, int argIndex);

Funcao* getFunction (const std::string &label);
