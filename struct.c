#include "struct.h"

using namespace std;

CustomType newCustomType (void) {
	static unsigned int id = 1;
	CustomType c;
	
	c.tipo = { GROUP_STRUCT|id, 0, "void*", NULL, NULL, NULL };
	id++;
	
	return c;
}

bool addVar (CustomType *type, Tipo *tipo, std::string &label) {
	if (type->memberOffset.count(label)) {
		return false;
	}
	
	type->memberOffset[label] = type->tipo.size;
	type->memberType[label] = tipo;
	
	type->tipo.size += tipo->size;
	return true;
}

Tipo* getTipo (CustomType *type, std::string &member) {
	if (type->memberType.count(member) == 0) {
		return NULL;
	}
	return type->memberType[member];
}

std::string setAccess (std::string &accessVar, CustomType *type, std::string &instance, std::string &member) {
	if (type->memberOffset.count(member) == 0) {
		return UNDEFINED_MEMBER;
	}
	std::string traducao = "";
	std::string memberAddr = generateVarLabel();
	std::string varAddr = generateVarLabel();
	size_t offset = type->memberOffset[member];
	Tipo *t = type->memberType[member];
	
	declararLocal(&tipo_ptr, memberAddr);
	declararLocal(&tipo_ptr, varAddr);
	
	traducao += newLine(memberAddr + " = " + instance + "+" + std::to_string(offset));	//armazenar local de memoria onde membro se encontra
	traducao += newLine(varAddr + " = &" + accessVar);	//armazenar local de memoria onde variavel de acesso se encontra
	traducao += newLine("memcpy("+varAddr+", "+memberAddr+", "+std::to_string(t->size)+")");
	
	return traducao;
}

std::string newInstanceOf (CustomType *type, std::string &label, bool collectGarbage) {
	std::string traducao = "";
	
	declararLocal(&type->tipo, label);
	
	traducao += newLine(label + " = " + "malloc("+std::to_string(type->tipo.size)+")");
	
	return traducao;
}
