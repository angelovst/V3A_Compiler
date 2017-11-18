#include "struct.h"

CustomType* findCustomType (std::string &label) {
	std::list<Context> it = contextStack.begin();
	while (it->customTypes.count(label) == 0 && it != contextStack.end()) {
		it++;
	}
	if (it == contextStack.end()) {
		return NULL;
	}
	return &(*it);
}

bool declareVarIn (CustomType *custom, Tipo *tipo, std::string &label) {
	if (custom->signature.count(label)) {
		return false;
	}
	custom->signature[label] = tipo;
	return true;
}

bool declareVarInWithValue (CustomType *custom, Tipo *tipo, std::string &label, std::string &value) {
	if (custom->signature.count(label)) {
		return false;
	}
	custom->signature[label] = tipo;
	custom->defaultValue[label] = value;
	return true;	
}

bool declareGlobalOfType (std::string &customType, std::string &label) {
	CustomType *type = findCustomType(customType);
	map<std::string, Tipo*>::iterator it;
	std::string declar;
	if (type == NULL) {
		return false;
	}
	
	//declarar todas as variaveis do tipo
	it = type->signature.begin();
	while (it != type->signature.end()) {
		declar = customType+"_"+label+"_"+it->first;
		declararGlobal(it->second, declar);
	}
	//declarar variavel
	declararGlobal(&type->tipo, label);
	return true;
	
}

bool declareLocalOfType (std::string &customType, std::string &label) {
	CustomType *type = findCustomType(customType);
	map<std::string, Tipo*>::iterator it;
	std::string declar;
	if (type == NULL) {
		return false;
	}
	
	//declarar todas as variaveis do tipo
	it = type->signature.begin();
	while (it != type->signature.end()) {
		declar = customType+"_"+label+"_"+it->first;
		declararLocal(it->second, declar);
	}
	//declarar variavel
	declararLocal(&type->tipo, label);
	return true;
	
}
