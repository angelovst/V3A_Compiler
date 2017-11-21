#ifndef HELPER_INCLUDED_H
#define HELPER_INCLUDED_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <stdlib.h>
#include "tipo.h"

typedef struct _LoopLabel {
	std::string inicio;		
	std::string progressao;
	std::string fim;
} LoopLabel;

//LOOP
void empLoop (void);
void desempLoop (void);
LoopLabel* getLoop (unsigned int out);
LoopLabel* getOuterLoop (void);
std::string generateLabel (void);

//VARIAVEIS GLOBAIS
extern unsigned int line;	//linha na qual o parser esta, usado para erros

//Pilha de labels
extern std::list<LoopLabel> loopStack;

#endif
