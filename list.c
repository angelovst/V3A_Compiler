#include "lista.h"

std::string generateNodeLabel (void); {
	static unsigned int i = 0;
	return "_no" + to_string(i++);
}

std::string no_getMemberAccess (std::string &label) {
	return label + "_memberAccess";
}

std::string no_setAccessDado (std::string &label, std::string &accessVar) {
	return label+NO_ACCESS_VAR + " = " + label + "[0];\n\t";
}
std::string no_setAccessAnterior (std::string &label, std::string &accessVar) {
	return label+NO_ACCESS_VAR + " = " + label + "[1];\n\t";
}
std::string no_setAccessProximo (std::string &label, std::string &accessVar) {
	return label+NO_ACCESS_VAR + " = " + label + "[2];\n\t";
}

void no_novo (std::string &label) {
	if (label == "") {
		label = generateNodeLabel();
	}
	
	//declarar no
	varDeclar += "\n//declaracao de no\n\tvoid* " + label + "[3];\n\t"
	varDeclar += "void* " + accessVar + "\n\t";
	varDeclar += no_setAccessDado(label, label+NO_ACCESS_VAR) + "; " + label+NO_ACCESS_VAR + " = NULL;\n\t";
	varDeclar += no_setAccessAnterior(label, label+NO_ACCESS_VAR) + "; " + label+NO_ACCESS_VAR + " = NULL;\n\t";
	varDeclar += no_setAccessProximo(label, label+NO_ACCESS_VAR) + "; " + label+NO_ACCESS_VAR + " = NULL;\n\n\t";
}

std::string no_deletar (std::string &label) {
	return no_setAccessDado(label) + "free(" + label+NO_ACCESS_VAR + ");\n\t"; 
}

std::string no_atribuir (std::string &label, atributos &dado) {
	std::string traducao = no_deletar(label);	//deletar qualquer valor existente em no
	std::string addr = generateVarLabel();
	
	varDeclar += "void *" + addr + ";\n\t";
	
	traducao += no_setAccessDado(label, label+NO_ACCESS_VAR) + "\n\t";	//pegar endereco do espaco no no
	traducao += addr + " = " + "&" + dado.label + ";\n\t";	//pegar endereco do dado
	traducao += label+NO_ACCESS_VAR + " = " + "malloc(" + to_string(dado.tipo->size) + ");\n\t";	//alocar espaco em no
	traducao += "memcpy(" + addr + ", " + label+NO_ACCESS_VAR + ", " + to_string(dado.tipo->size) + ");\n\t";	//atribuir dado em no
	
	return traducao;
}
