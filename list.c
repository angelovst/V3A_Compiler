#include "list.h"

std::string generateNodeLabel (void) {
	static unsigned int i = 0;
	return "_no" + std::to_string(i++);
}

std::string no_getMemberAccess (std::string &label) {
	return label + "_memberAccess";
}

std::string no_setAccessDado (std::string &label, std::string &accessVar) {
	return newLine(label+std::string(NO_ACCESS_VAR) + " = " + label + "[0]");
}
std::string no_setAccessAnterior (std::string &label, std::string &accessVar) {
	return newLine(label+NO_ACCESS_VAR + " = " + label + "[1]");
}
std::string no_setAccessProximo (std::string &label, std::string &accessVar) {
	return newLine(label+NO_ACCESS_VAR + " = " + label + "[2]");
}

void no_novo (std::string &label) {
	std::string accessVar;
	std::string varDeclar = contextStack.begin()->declar;
	if (label == "") {
		label = generateNodeLabel();
	}
	accessVar = label+std::string(NO_ACCESS_VAR);
	
	//declarar no
	varDeclar += "\n//declaracao de no\n\tvoid* " + label + "[3];\n\t";
	varDeclar += "void* " + label+NO_ACCESS_VAR + ";\n\t";
	varDeclar += no_setAccessDado(label, accessVar) + newLine(accessVar + " = NULL");
	varDeclar += no_setAccessAnterior(label, accessVar) + newLine(accessVar + " = NULL");
	varDeclar += no_setAccessProximo(label, accessVar) + newLine(accessVar + " = NULL") + "\n";
}

std::string no_deletar (std::string &label) {
	std::string accessVar = label+std::string(NO_ACCESS_VAR);
	return no_setAccessDado(label, accessVar) + newLine("free(" + accessVar + ")"); 
}

std::string no_atribuir (std::string &label, atributos &dado) {
	std::string traducao = no_deletar(label);	//deletar qualquer valor existente em no
	std::string addr = generateVarLabel();
	std::string accessVar = label+std::string(NO_ACCESS_VAR);
	std::string varDeclar = contextStack.begin()->declar;
	
	varDeclar += newLine("void* " + addr);
	
	traducao += no_setAccessDado(label, accessVar);	//pegar endereco do espaco no no
	traducao += newLine(addr + " = " + "&" + dado.label);	//pegar endereco do dado
	traducao += newLine(accessVar + " = " + "malloc(" + std::to_string(dado.tipo->size) + ")");	//alocar espaco em no
	traducao += newLine("memcpy(" + addr + ", " + accessVar + ", " + std::to_string(dado.tipo->size) + ")");	//atribuir dado em no
	
	return traducao;
}
