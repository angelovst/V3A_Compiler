#include "struct.h"
#include <iostream>

using namespace std;

map<string, unsigned int> customTypesIds;
map<unsigned int, CustomType> customTypes;

CustomType newCustomType (void) {
	static unsigned int id = 1;
	CustomType c;
	
	c.tipo = { GROUP_STRUCT|GROUP_PTR|id, 0, TIPO_PTR_TRAD, NULL, NULL, NULL };
	id++;
	
	return c;
}

bool createCustomType (CustomType *type, const std::string &label) {
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
	type->memberType[label].defaultValue = defaultValue;
	if (belongsTo(tipo, GROUP_STRUCT)) type->memberType[label].tipo.size = tipo_ptr.size;
	
	type->tipo.size += tipo->size;
	return true;
}

Tipo* getTipo (CustomType *type, const std::string &member) {
	if (type->memberType.count(member) == 0) {
		return NULL;
	}
	return &(type->memberType[member].tipo);
}

std::string setAccess (CustomType *type, const std::string &instance, const std::string &member, const std::string &accessVar) {
	std::string traducao;
	size_t offset = type->memberType[member].offset;
	Tipo *t = getTipo(type, member);
	
	traducao = newLine(accessVar + " = " + instance + "+" + std::to_string(offset));	//armazenar local de memoria onde membro se encontra
	
	return traducao;
}

std::string attrTo (CustomType *type, const std::string &instance, const std::string &member, const std::string &value) {
	std::string accessVar;
	std::string valueAddr;
	std::string traducao;
	Tipo *t = getTipo(type, member);
	
	accessVar = generateVarLabel();
	valueAddr = generateVarLabel();
	declararLocal(&tipo_ptr, accessVar);
	declararLocal(&tipo_ptr, valueAddr);
	
	traducao = newLine(valueAddr+" = ("+TIPO_PTR_TRAD+")&"+value);
	traducao += setAccess(type, instance, member, accessVar);
	traducao += newLine("memcpy("+accessVar+", "+valueAddr+", "+std::to_string(t->size)+")");
	
	return traducao;
}

std::string retrieveFrom (CustomType *type, const std::string &instance, const std::string &member, const std::string &dst) {
	std::string accessVar;
	std::string valueAddr;
	std::string traducao;
	Tipo *t = getTipo(type, member);
	
	accessVar = generateVarLabel();
	valueAddr = generateVarLabel();
	declararLocal(&tipo_ptr, accessVar);
	declararLocal(&tipo_ptr, valueAddr);
	
	traducao = newLine(valueAddr+" = ("+TIPO_PTR_TRAD+")&"+dst);
	traducao += setAccess(type, instance, member, accessVar);
	traducao += newLine("memcpy("+valueAddr+", "+accessVar+", "+std::to_string(t->size)+")");
	
	return traducao;
}

std::string newInstanceOf (CustomType *type, const std::string &label, bool collectGarbage, bool global) {
	std::string traducao = "";
	std::string accessVar, ptr;
	std::string alloc;
	
	if (!global) {
		if (!declararLocal(&type->tipo, label)) {
			return VAR_ALREADY_DECLARED;
		}
	} else {
		if (!declararGlobal(&type->tipo, label)) {
			return VAR_ALREADY_DECLARED;
		}		
	}
	accessVar = generateVarLabel();
	alloc = generateVarLabel();
	declararLocal(&tipo_ptr, accessVar);
	declararLocal(&tipo_ptr, alloc);
	
	traducao += newLine(alloc + " = " + "("+TIPO_PTR_TRAD+")"+"malloc("+std::to_string(type->tipo.size)+")");
	traducao += newLine(label + " = " + alloc);
	
	//atribuir valores default as variaveis
	traducao += ident() + "//DEFAULT VALUES\n";
	ptr = generateVarLabel();
	declararLocal(&tipo_ptr, ptr);
	for (std::map<std::string, CustomTypeMember>::iterator i = type->memberType.begin(); i != type->memberType.end(); i++) {
		if (i->second.defaultValue != "" /*&& !belongsTo(&i->second.tipo, GROUP_STRUCT)*/) {
			traducao += newLine(ptr + " = " + "("+TIPO_PTR_TRAD+")"+"&"+i->second.defaultValue);
			traducao += setAccess(type, label, i->first, accessVar);
			traducao += newLine("memcpy(" + accessVar + ", " + ptr + ", " + std::to_string(i->second.tipo.size) + ")");
		} else if (belongsTo(&i->second.tipo, GROUP_STRUCT) && i->second.offset < type->tipo.size && !belongsTo(&i->second.tipo, GROUP_PURE_PTR) ) {
			std::string instance;
			if (true) {
				instance = generateVarLabel();

				traducao += ident() + "//INICIALIZANDO MEMBRO INTERNO\n";
				traducao += newInstanceOf(&customTypes[i->second.tipo.id], instance, true, false);
				traducao += attrTo(type, label, i->first, instance);
			}
		}
	}
	traducao += "\n";
	
	if (collectGarbage) {
		if (!global) {
			contextStack.begin()->garbageCollect += newLine("free("+alloc+")");
		} else {
			std::list<Context>::iterator i = contextStack.end();
			i--;
			i->garbageCollect += newLine("free("+alloc+")");
		}	
	}
	
	return traducao;
}
