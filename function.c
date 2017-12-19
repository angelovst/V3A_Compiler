#include "function.h"

std::map<std::string, Funcao> funcMap;
std::string functionDeclars = "";

Funcao newFunc (void) {
	Funcao f;
	f.retornos = newCustomType();
	f.args = newCustomType();
	f.traducao = "";
	return f;
}

bool createFunc (Funcao *f, const std::string &label) {
	if (funcMap.count(label) != 0) {
		return false;
	}
	funcMap[label] = *f;
	functionDeclars += "char *"+label+"(char *args) {\n";
	for (std::string argL : f->argsLabel) {
		Tipo *t = getTipo(&f->args, argL);
		functionDeclars += "\t" + t->trad + " " + argL + ";\n";
		functionDeclars += retrieveFrom(&f->args, "args", argL, argL);
	}
	if (f->retornos.tipo.size > 0) functionDeclars += newInstanceOf(&f->retornos, "_ret", false, false);
	functionDeclars += f->traducao + "}\n\n";
	return true;
}

bool addRetorno (Funcao *f, Tipo *retorno, const std::string &retornoLabel) {
	f->retornosLabel.push_back(retornoLabel);
	
	return addVar(&f->retornos, retorno, retornoLabel, "");
}

bool addArg (Funcao *f, Tipo *argT, const std::string &argLabel, const std::string &defaultValue) {
	f->argsLabel.push_back(argLabel);
	
	return addVar(&f->args, argT, argLabel, defaultValue);
}

Funcao* getFunction (const std::string &label) {
	if (funcMap.count(label) != 0) {
		return &funcMap[label];
	}
	return NULL;
}
