#include "helper.h"

#include <iostream>

unsigned int line = 1;

//Pilha de labels de loop
std::list<LoopLabel> loopStack;

using namespace std;

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
