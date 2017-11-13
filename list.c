#include "list.h"

std::string generateNodeLabel (void) {
	static unsigned int i = 0;
	return "_no" + std::to_string(i++);
}

std::string no_getMemberAccess (std::string &label) {
	return label + "_memberAccess";
}

std::string no_setAccessDado (std::string &label, std::string &accessVar) {
	return label+std::string(NO_ACCESS_VAR) + " = " + label + "[0];\n\t";
}
std::string no_setAccessAnterior (std::string &label, std::string &accessVar) {
	return label+NO_ACCESS_VAR + " = " + label + "[1];\n\t";
}
std::string no_setAccessProximo (std::string &label, std::string &accessVar) {
	return label+NO_ACCESS_VAR + " = " + label + "[2];\n\t";
}

void no_novo (std::string &label) {
	std::string accessVar;
	if (label == "") {
		label = generateNodeLabel();
	}
	accessVar = label+std::string(NO_ACCESS_VAR);
	
	//declarar no
	varDeclar += "\n//declaracao de no\n\tvoid* " + label + "[3];\n\t";
	varDeclar += "void* " + label+NO_ACCESS_VAR + "\n\t";
	varDeclar += no_setAccessDado(label, accessVar) + "; " + accessVar + " = NULL;\n\t";
	varDeclar += no_setAccessAnterior(label, accessVar) + "; " + accessVar + " = NULL;\n\t";
	varDeclar += no_setAccessProximo(label, accessVar) + "; " + accessVar + " = NULL;\n\n\t";
}

std::string no_deletar (std::string &label) {
	std::string accessVar = label+std::string(NO_ACCESS_VAR);
	return no_setAccessDado(label, accessVar) + "free(" + accessVar + ");\n\t"; 
}

std::string no_atribuir (std::string &label, atributos &dado) {
	std::string traducao = no_deletar(label);	//deletar qualquer valor existente em no
	std::string addr = generateVarLabel();
	std::string accessVar = label+std::string(NO_ACCESS_VAR);
	
	varDeclar += "void *" + addr + ";\n\t";
	
	traducao += no_setAccessDado(label, accessVar) + "\n\t";	//pegar endereco do espaco no no
	traducao += addr + " = " + "&" + dado.label + ";\n\t";	//pegar endereco do dado
	traducao += accessVar + " = " + "malloc(" + std::to_string(dado.tipo->size) + ");\n\t";	//alocar espaco em no
	traducao += "memcpy(" + addr + ", " + accessVar + ", " + std::to_string(dado.tipo->size) + ");\n\t";	//atribuir dado em no
	
	return traducao;
}
