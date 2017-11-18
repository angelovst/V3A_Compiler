#include "helper.h"

#include <iostream>

Tipo tipo_float = { TIPO_FLOAT_ID, sizeof(float), TIPO_FLOAT_TRAD, NULL, NULL, NULL };
Tipo tipo_int = { TIPO_INT_ID, sizeof(int), TIPO_INT_TRAD, NULL, NULL, NULL };
Tipo tipo_bool = { TIPO_BOOL_ID, sizeof(unsigned char), TIPO_BOOL_TRAD, NULL, NULL, NULL };
Tipo tipo_char = { TIPO_CHAR_ID, sizeof(char), TIPO_CHAR_TRAD, NULL, NULL, NULL };
Tipo tipo_list = { TIPO_LIST_ID, sizeof(size_t)+2*sizeof(void*), TIPO_LIST_TRAD, NULL, NULL, NULL };

Tipo tipo_arithmetic_operator = { TIPO_INF_OP_ID, 0, TIPO_INF_OP_TRAD, &traducaoLAPadrao, NULL, NULL };
Tipo tipo_logic_operator = { TIPO_INF_OP_ID, 0, TIPO_INF_OP_TRAD, &traducaoLAPadrao, new std::vector<Tipo*>({&tipo_bool}), NULL };
Tipo tipo_atrib_operator = { TIPO_INF_OP_ID, 0, TIPO_INF_OP_TRAD, &traducaoAtribuicao, NULL, NULL };

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
string generateVarLabel (void) {
	static unsigned int i = 0;
	return "_tmp" + to_string(i++);
}

int getGroup (Tipo *tipo) {
	return tipo->id&0xFF000000;
}

bool belongsTo (Tipo *tipo, int group) {
	return getGroup(tipo)==group;
}

Tipo* resolverTipo (Tipo *a, Tipo *b) {
	if (a == NULL) {
		return b;
	} else if (b == NULL) {
		return a;
	} else if (a->id < b->id) {	//b e o tipo do retorno
		return b;
	}
	return a;	//a e o tipo do retorno
}

string implicitCast (atributos *var1, atributos *var2, string *label1, string *label2) {
	if (getGroup(var1->tipo) != getGroup(var2->tipo)) {
		return INVALID_CAST;
	}
	int cast = var1->tipo->id - var2->tipo->id;
	
	if (cast == 0) {	//nao necessita cast
		*label1 = var1->label;
		*label2 = var2->label;
		return "";
	} else if (cast < 0) {	//cast var1 para var2
		*label1 = generateVarLabel();
		declararLocal(var2->tipo, *label1);
		*label2 = var2->label;
		return newLine(*label1 + " = (" + var2->tipo->trad + ")" + var1->label);
	}
	//cast var2 para var1
	*label1 = var1->label;
	*label2 = generateVarLabel();
	declararLocal(var1->tipo, *label2);
	return newLine(*label2 + " = (" + var1->tipo->trad + ")" + var2->label);
}

//CONTEXTO
void empContexto (void) {
	contextStack.push_front({map<string, Tipo*>(), ""});
	contextDepth++;
}

void desempContexto (void) {
	contextStack.pop_front();
	contextDepth--;
}

Tipo* findVar(string &label) {
	list<Context>::iterator i = contextStack.begin();
	while (i != contextStack.end() && !i->vars.count(label)) {
		i++;
	}		
	return (i == contextStack.end()) ? NULL : i->vars[label];
}

bool declararGlobal (Tipo *tipo, std::string &label) {
	list<Context>::iterator bottom = contextStack.end()--;
	if (bottom->vars.count(label)) {
		return false;
	}
	bottom->declar += tipo->trad + " " + label + ";\n\t";
	bottom->vars[label] = tipo;
	return true;
}

bool declararLocal (Tipo *tipo, std::string &label) {
	list<Context>::iterator top = contextStack.begin();

	if (top->vars.count(label)) {
		return false;
	}

	top->declar += newLine(tipo->trad + " " + label);	
	top->vars[label] = tipo;
	//cout << "declaracao " << tipo->trad << " " << label << endl;	//debug
	return true;
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
	string cast;
	string rlabel, llabel;
	
	lvalue->tipo = findVar(lvalue->label);
	//declarar variavel caso ainda nao tenha sido declarada
	if (lvalue->tipo == NULL) {
		//cout << rvalue->tipo->trad << endl;	//debug
		if (!declararLocal(rvalue->tipo, lvalue->label)) {
			return VAR_ALREADY_DECLARED;
		}
		lvalue->tipo = rvalue->tipo;
	} else {
		bool rightGroup = belongsTo(rvalue->tipo, getGroup(lvalue->tipo));
		if (!rightGroup || rightGroup && rvalue->tipo->id > lvalue->tipo->id) {
			return INVALID_CAST;
		}
	}	
	
	cast = implicitCast(lvalue, rvalue, &llabel, &rlabel);
	return cast + newLine(llabel + " = " + rlabel) + ((retorno != NULL) ? newLine(*retorno + " = " + llabel) : "");
}
