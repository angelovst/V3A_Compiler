#include "struct.h"

using namespace std;

map<string, unsigned int> customTypesIds;
map<unsigned int, CustomType> customTypes;

CustomType newCustomType (void) {
	static unsigned int id = 1;
	CustomType c;
	
	c.tipo = { GROUP_STRUCT|id, 0, "void*", NULL, NULL, NULL };
	id++;
	
	return c;
}

bool createCustomType (CustomType *type, std::string &label) {
	if (customTypesIds.count(label) != 0) {
		return false;
	}
	customTypesIds[label] = type->tipo.id;
	customTypes[type->tipo.id] = *type;
	return true;
}

bool addVar (CustomType *type, Tipo *tipo, std::string &label) {
	if (type->memberOffset.count(label)) {
		return false;
	}
	
	type->memberOffset[label] = type->tipo.size;
	type->memberType[label] = *tipo;
	type->memberType[label].id |= GROUP_PTR;
	
	type->tipo.size += tipo->size;
	return true;
}

Tipo* getTipo (CustomType *type, std::string &member) {
	if (type->memberType.count(member) == 0) {
		return NULL;
	}
	return &(type->memberType[member]);
}

std::string setAccess (CustomType *type, std::string &instance, std::string &member) {
	std::string traducao;
	std::string accessVar = "_"+instance+ACCESS_VAR;
	size_t offset = type->memberOffset[member];
	Tipo *t = getTipo(type, member);
	
	traducao = newLine(accessVar + " = " + instance + "+" + std::to_string(offset));	//armazenar local de memoria onde membro se encontra
	
	return traducao;
}

std::string newInstanceOf (CustomType *type, std::string &label, bool collectGarbage) {
	std::string traducao = "";
	std::string accessVar = "_"+label+ACCESS_VAR;
	
	if (!declararLocal(&type->tipo, label)) {
		return VAR_ALREADY_DECLARED;
	}
	declararLocal(&tipo_ptr, accessVar);
	
	traducao += newLine(label + " = " + "malloc("+std::to_string(type->tipo.size)+")");
	
	if (collectGarbage) {
		contextStack.begin()->garbageCollect += newLine("free("+label+")");
	}
	
	return traducao;
}
