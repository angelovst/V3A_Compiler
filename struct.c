#include "struct.h"

using namespace std;

map<string, unsigned int> customTypesIds;
map<unsigned int, CustomType> customTypes;

CustomType newCustomType (void) {
	static unsigned int id = 1;
	CustomType c;
	
	c.tipo = { GROUP_STRUCT|id, 0, TIPO_PTR_TRAD, NULL, NULL, NULL };
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

bool addVar (CustomType *type, Tipo *tipo, const std::string &label, const std::string &defaultValue) {
	if (type->memberType.count(label)) {
		return false;
	}
	
	type->memberType[label].offset = type->tipo.size;
	type->memberType[label].tipo = *tipo;
	type->memberType[label].tipo.id |= GROUP_PTR;
	
	type->tipo.size += tipo->size;
	return true;
}

Tipo* getTipo (CustomType *type, const std::string &member) {
	if (type->memberType.count(member) == 0) {
		return NULL;
	}
	return &(type->memberType[member].tipo);
}

std::string setAccess (CustomType *type, const std::string &instance, const std::string &member) {
	std::string traducao;
	std::string accessVar = "_"+instance+ACCESS_VAR;
	size_t offset = type->memberType[member].offset;
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
	
	//atribuir valores default as variaveis
	traducao += ident() + "//DEFAULT VALUES";
	for (std::map<std::string, CustomTypeMember>::iterator i = type->memberType.begin(); i != type->memberType.end(); i++) {
		if (i->second.defaultValue != "") {
			traducao += setAccess(type, label, i->first);
			traducao += newLine("memcpy(" + accessVar + ", " + i->second.defaultValue + ", " + to_string(i->second.tipo.size) + ")");
		}
	}
	traducao += "\n";
	
	if (collectGarbage) {
		contextStack.begin()->garbageCollect += newLine("free("+label+")");
	}
	
	return traducao;
}
