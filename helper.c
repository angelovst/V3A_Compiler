#include "helper.h"

#include <iostream>

Tipo tipo_float = { TIPO_FLOAT, sizeof(float), NULL, NUMBER_SUBSET*2 };
Tipo tipo_int = { TIPO_INT, sizeof(int), NULL, NUMBER_SUBSET };

Tipo tipo_bool = { TIPO_BOOL, sizeof(unsigned char), NULL, UNCASTABLE };
Tipo tipo_char = { TIPO_CHAR, sizeof(char), NULL, -1};
Tipo tipo_list = { TIPO_LIST, sizeof(size_t)+2*sizeof(void*), NULL, UNCASTABLE };
Tipo tipo_inf_operator = { TIPO_INFIX_OPERATOR, 0, &traducaoInfixaPadrao, UNCASTABLE };

//Pilha de variaveis
std::vector<std::map<std::string, atributos>> varMap;

//String para declaracao de var
std::string varDeclar;

//Pilha de labels de loop
std::vector<loopLabel> loopMap;

using namespace std;

//FUNCOES DE PROCURA DE VARIAVEL

atributos* findVarOnTop(string label) {
	if (varMap[varMap.size() - 1].count(label)) {
		return &varMap[varMap.size() - 1][label];
	}
	
	return nullptr;
}

atributos* findVar(string label) {
	for (int i = varMap.size() - 1; i >= 0; i--) {
		if (varMap[i].count(label)) {
			return &varMap[i][label];
		}
	}	
	return nullptr;
}
string findTmpName(string label) {
	for (int i = varMap.size() - 1; i >= 0; i--) {
		if (varMap[i].count(label)) {
			return varMap[i][label].label;
		}
	}	
	return "null";
}

string generateVarLabel (void) {
	static unsigned int i = 0;
	return "tmp" + to_string(i++);
}	

string implicitCast (atributos *var1, atributos *var2, string *label1, string *label2) {
	if (var1->tipo->subset == UNCASTABLE || var2->tipo->subset == UNCASTABLE) {
		return INVALID_CAST;
	}
	int cast = var1->tipo->subset - var2->tipo->subset;
	
	if (cast == 0) {	//nao necessita cast
		*label1 = var1->label;
		*label2 = var2->label;
		return "";
	} else if (cast < 0) {	//cast var1 para var2
		*label1 = generateVarLabel();
		varDeclar += var2->tipo->label + " " + *label1 + ";\n\t";
		*label2 = var2->label;
		return "\t" + *label1 + " = (" + var2->tipo->label + ")" + var1->label + ";\n";
	}
	//cast var2 para var1
	*label1 = var1->label;
	*label2 = generateVarLabel();
	varDeclar += var1->tipo->label + " " + *label2 + ";\n\t";
	return "\t" + *label2 + " = (" + var1->tipo->label + ")" + var2->label + ";\n";
}

string traducaoInfixaPadrao (void *args)  {
	string *operando = (string*)args;
	string &var1 = operando[0];
	string &operador = operando[1];
	string &var2 = operando[2];
	
	return var1 + operador + var2;
}

string generateLabel (void) {
	static unsigned int i = 0;
	return "LABEL_" + to_string(i++);
}

//FUNCOES PARA ENTRADA E SAIDA DE BLOCOS, CONTROLE DO CONTEXTO
void empContexto (void) {
	map<string, atributos> mapa;
	varMap.push_back(mapa);
}

void desempContexto (void) {
	return varMap.pop_back();
}
//FUNCOES PARA CONTROLE DOS BLOCOS DE LOOP
void empLoop() {
	string inicio = generateLabel();
	string progressao = generateLabel();
	string fim = generateLabel();
	loopLabel novo = {inicio, progressao, fim};
	loopMap.push_back(novo);
}

void desempLoop() {
	return loopMap.pop_back();
}

loopLabel* getLoop(int tamLoop) {
	if (loopMap.size() && tamLoop <= loopMap.size() && tamLoop > 0) {
		//cout << loopMap.size() << " " << tamLoop << endl;
		return &loopMap[loopMap.size() - tamLoop];
	} else {
		return nullptr;
	}
}

loopLabel* getOuterLoop() {
	if (loopMap.size()) {
		return &loopMap[0];
	} else {
		return nullptr;
	}
}
