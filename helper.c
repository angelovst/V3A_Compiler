#include "helper.h"

#include <iostream>

Tipo tipo_float = { TIPO_FLOAT_ID, NUMBER_SUBSET*2, sizeof(float), TIPO_FLOAT, NULL, NULL, NULL };
Tipo tipo_int = { TIPO_INT_ID, NUMBER_SUBSET, sizeof(int), TIPO_INT, NULL, NULL, NULL };
Tipo tipo_bool = { TIPO_BOOL_ID, UNCASTABLE, sizeof(unsigned char), TIPO_BOOL, NULL, NULL, NULL };
Tipo tipo_char = { TIPO_CHAR_ID, UNCASTABLE, sizeof(char), TIPO_CHAR, NULL, NULL, NULL };
Tipo tipo_list = { TIPO_LIST_ID, UNCASTABLE, sizeof(size_t)+2*sizeof(void*), TIPO_LIST, NULL, NULL, NULL };
Tipo tipo_ref = { TIPO_REF_ID, 0, sizeof(void*), TIPO_REF, NULL, NULL, NULL};

Tipo tipo_arithmetic_operator = { TIPO_INFIX_OPERATOR_ID, UNCASTABLE, 0, TIPO_INFIX_OPERATOR, &traducaoLAPadrao, NULL, NULL };
Tipo tipo_logic_operator = { TIPO_INFIX_OPERATOR_ID, UNCASTABLE, 0, TIPO_INFIX_OPERATOR, &traducaoLAPadrao, new std::vector<Tipo*>({&tipo_bool}), NULL };
Tipo tipo_atrib_operator = { TIPO_INFIX_OPERATOR_ID, UNCASTABLE, 0, TIPO_INFIX_OPERATOR, &traducaoAtribuicao, NULL, NULL };

unsigned int line = 1;

//Pilha de variaveis
std::list<Context> contextStack;
unsigned int contextDepth = 0;

//Pilha de labels de loop
std::list<LoopLabel> loopStack;

using namespace std;

string ident (void) {
	std::string identation = "";
	for (unsigned int i = 0; i < contextDepth; i++) {
		identation += "\t";
	}
	return identation;	
}

string newLine (const string &line) {
	return ident() + line + ";\n";
}

//FUNCOES DE PROCURA DE VARIAVEL
Tipo* findVar(string &label) {
	list<Context>::iterator i = contextStack.begin();
	while (i != contextStack.end() && !i->vars.count(label)) {
		i++;
	}		
	return (i == contextStack.end()) ? NULL : i->vars[label];
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
		declararLocal(var2->tipo, *label1);
		*label2 = var2->label;
		return newLine(*label1 + " = (" + var2->tipo->label + ")" + var1->label);
	}
	//cast var2 para var1
	*label1 = var1->label;
	*label2 = generateVarLabel();
	declararLocal(var1->tipo, *label2);
	return newLine(*label2 + " = (" + var1->tipo->label + ")" + var2->label);
}

Tipo* resolverTipo (Tipo *a, Tipo *b) {
	if (a == NULL) {
		return b;
	} else if (b == NULL) {
		return a;
	} else if (a->subset < b->subset) {	//b e o tipo do retorno
		return b;
	}
	return a;	//a e o tipo do retorno
}

bool declararGlobal (Tipo *tipo, std::string &label) {
	list<Context>::iterator bottom = contextStack.end()--;
	if (bottom->vars.count(label)) {
		return false;
	}
	bottom->declar += tipo->label + " " + label + ";\n\t";
	bottom->vars[label] = tipo;
	return true;
}

bool declararLocal (Tipo *tipo, std::string &label) {
	list<Context>::iterator top = contextStack.begin();

	if (top->vars.count(label)) {
		return false;
	}

	top->declar += newLine(tipo->label + " " + label);	
	top->vars[label] = tipo;
	//cout << "declaracao " << tipo->label << " " << label << endl;	//debug
	return true;
}

//FUNCOES PARA ENTRADA E SAIDA DE BLOCOS, CONTROLE DO CONTEXTO
void empContexto (void) {
	contextStack.push_front({map<string, Tipo*>(), ""});
	contextDepth++;
}

void desempContexto (void) {
	contextStack.pop_front();
	contextDepth--;
}

//LOOP
void empLoop (void) {
	loopStack.push_front({generateLabel(), generateLabel(), generateLabel()});
}

void desempLoop (void) {
	loopStack.pop_front();
}

LoopLabel* getLoop (unsigned int out) {
	list<LoopLabel>::iterator it = loopStack.begin();
	unsigned int i = 0;
	
	while (i < out && it != loopStack.end()) {
		i++;
		it++;
	}
	
	return (it == loopStack.end()) ? NULL : &(*it);
}

LoopLabel* getOuterLoop (void) {
	if (loopStack.size() > 0) {
		return &(*(loopStack.end()--));
	} else {
		return NULL;
	}
}

string generateLabel (void) {
	static unsigned int i = 0;
	return "LABEL_" + to_string(i++);
}

/*FUNCOES DE OPERADORES*/
string traducaoLAPadrao (void *args)  {
	atributos **atribs = (atributos**)args;
	string **labels = (string**)((atributos**)args+2);
	
	string *retorno = labels[0];
	string *operador = labels[1];
	
	string varALabel;	//labels[1]
	string varBLabel;	//labels[3]
	
	string cast = implicitCast (atribs[0], atribs[1], &varALabel, &varBLabel);
	if (cast == INVALID_CAST) {
		return INVALID_CAST;
	}	
	
	return cast + newLine(*retorno + " = " + varALabel + *operador + varBLabel);
}

string traducaoAtribuicao (void *args) {
	atributos **atribs = (atributos**)args;
	atributos *lvalue = atribs[0];
	atributos *rvalue = atribs[1];
	string *retorno = *((string**)((atributos**)args+2));
	
	lvalue->tipo = findVar(lvalue->label);
	//declarar variavel caso ainda nao tenha sido declarada
	if (lvalue->tipo == NULL) {
		//cout << rvalue->tipo->label << endl;	//debug
		if (!declararLocal(rvalue->tipo, lvalue->label)) {
			return VAR_ALREADY_DECLARED;
		}
		lvalue->tipo = rvalue->tipo;
	}
	
	if (rvalue->tipo->id == lvalue->tipo->id || rvalue->tipo->subset < lvalue->tipo->subset) {
		string cast;
		string rlabel, llabel;
		cast = implicitCast(lvalue, rvalue, &llabel, &rlabel);
		return cast + newLine(llabel + " = " + rlabel) + ((retorno != NULL) ? newLine(*retorno + " = " + llabel) : "");
	}
	return INVALID_CAST;
}
