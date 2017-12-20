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

bool declareFunc (Funcao *f, const std::string &label) {
	if (funcMap.count(label) != 0) {
		return false;
	}
	
	funcMap[label] = *f;
}

bool createFunc (Funcao *f, const std::string &label) {
	std::string traducao;
	traducao = "";
	
	for (std::string argL : f->argsLabel) {
		Tipo *t = getTipo(&f->args, argL);
		traducao += "\t" + t->trad + " " + argL + ";\n";
		traducao += retrieveFrom(&f->args, "args", argL, argL);
	}
	if (f->retornos.tipo.size > 0) traducao += newInstanceOf(&f->retornos, RETURN_STRUCT, false, false);
	
	functionDeclars += "char *"+label+"(char *args) {\n"+contextStack.begin()->declar+"\n"+traducao+"\n";
	functionDeclars += f->traducao + "}\n\n";
	createCustomType(&f->retornos, std::to_string(f->retornos.tipo.id));
	createCustomType(&f->args, std::to_string(f->args.tipo.id));
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

Tipo* getRetorno (Funcao *f, int returnIndex) {
	return getTipo(&f->retornos, f->retornosLabel[returnIndex]);
}

Tipo* getArg (Funcao *f, int argIndex) {
	return getTipo(&f->args, f->argsLabel[argIndex]);
}

Funcao* getFunction (const std::string &label) {
	if (funcMap.count(label) != 0) {
		return &funcMap[label];
	}
	return NULL;
}
