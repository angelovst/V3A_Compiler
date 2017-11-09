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

using namespace std;

void empContexto() {
	map<string, atributos> novoMapa;
	varMap.push_back(novoMapa);
}

void desempContexto() {
	return varMap.pop_back();
}
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

string generateLabel (void) {
	static unsigned int i = 0;
	return "TMP" + to_string(i++);
}	

bool declaracaoLocal(Tipo *tipo, string &label, struct atributos &atrib){

	std::map<string, atributos> *mapLocal = &varMap.back();

	if(mapLocal->find(label) != mapLocal->end()) return false;

	atrib.label = generateLabel();
	atrib.tipo = tipo;
	(*mapLocal)[label] = atrib;

	//cout << atrib.label << endl;	//debug
	return true;
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
		*label1 = generateLabel();
		varDeclar += var2->tipo->label + " " + *label1 + "\n\t";
		*label2 = var2->label;
		return *label1 + " = (" + var2->tipo->label + ")" + var1->label + "\n";
	}
	//cast var2 para var1
	*label1 = var1->label;
	*label2 = generateLabel();
	varDeclar += var1->tipo->label + " " + *label2 + "\n\t";
	return *label2 + " = (" + var1->tipo->label + ")" + var2->label + "\n";
}

string traducaoInfixaPadrao (void *args)  {
	atributos *operando = (atributos*)args;
	atributos self = operando[0];
	atributos t1 = operando[1];
	atributos t2 = operando[2];
	
	return t1.label + self.label + t2.label;
}
