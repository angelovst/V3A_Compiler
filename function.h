#pragma once

#include <map>
#include <string>
#include "struct.h"

typedef struct {
	std::list<std::string> retornosLabel;
	CustomType retornos;
	std::list<std::string> argsLabel;
	CustomType args;
	std::string traducao;
} Funcao;

extern std::map<std::string, Funcao> funcMap;
extern std::string functionDeclars;

Funcao newFunc (void);

bool createFunc (Funcao *f, const std::string &label);

bool addRetorno (Funcao *f, Tipo *retorno, const std::string &retornoLabel);
bool addArg (Funcao *f, Tipo *argT, const std::string &argLabel, const std::string &defaultValue);

Funcao* getFunction (const std::string &label);
