#include "matrix.h"
#include "helper.h"

std::string newMatrixInstance (CustomType *type, const std::string &label, bool collectGarbage, const std::string &rowsVar, const std::string &columsVar) {
	std::string traducao = "";
	std::string accessVar;
	std::string size, ptr;
	
	if (!declararLocal(&type->tipo, label)) {
		return VAR_ALREADY_DECLARED;
	}
	accessVar = generateVarLabel();
	declararLocal(&type->tipo, accessVar);
	
	size = generateVarLabel();
	declararLocal(&tipo_int, size);
	
	traducao += newLine(size + " = " + rowsVar + "*" + columsVar);
	traducao += newLine(size + " = " + size + "*" + std::to_string(type->memberType[DATA_MEMBER].tipo.size));
	traducao += newLine(size + " = " + size + "+" + std::to_string(type->tipo.size));
	traducao += newLine(label + " = " + "("+TIPO_PTR_TRAD+")"+"malloc("+size+")");
	
	//atribuir valores default as variaveis
	traducao += ident() + "//DEFAULT VALUES\n";
	ptr = generateVarLabel();
	declararLocal(&tipo_ptr, ptr);
	for (std::map<std::string, CustomTypeMember>::iterator i = type->memberType.begin(); i != type->memberType.end(); i++) {
		if (i->second.defaultValue != "") {
			traducao += newLine(ptr + " = " + "("+TIPO_PTR_TRAD+")"+"&"+i->second.defaultValue);
			traducao += setAccess(type, label, i->first, accessVar);
			traducao += newLine("memcpy(" + accessVar + ", " + ptr + ", " + std::to_string(i->second.tipo.size) + ")");
		}
	}
	traducao += "\n";
	
	if (collectGarbage) {
		contextStack.begin()->garbageCollect += newLine("free("+label+")");
	}
	
	return traducao;
}

std::string newMatrix (Tipo *tipo, std::string &label, const std::string &rows, const std::string &colums) {
	CustomType t = newCustomType();
	std::string traducao;

	addVar(&t, &tipo_int, ROWS_MEMBER, rows);
	addVar(&t, &tipo_int, COLUMS_MEMBER, colums);
	
	addVar(&t, tipo, DATA_MEMBER, "");
	
	t.tipo.size -= tipo->size;
	
	if (!createCustomType (&t, label)) {
		return VAR_ALREADY_DECLARED;
	}
	
	traducao += newMatrixInstance (&customTypes[t.tipo.id], label, true, rows, colums);
	return traducao;
	
}

std::string setIndexAccess (CustomType *matrix, std::string &instance, std::string &rowsVar, std::string &columsVar, const std::string &accessVar) {
	std::string rows, colums, ptr;
	std::string boolTmp1, boolTmp2;
	std::string label;
	std::string traducao;
	
	rows = generateVarLabel();
	colums = generateVarLabel();
	ptr = generateVarLabel();
	declararLocal(&tipo_int, rows);
	declararLocal(&tipo_int, colums);
	declararLocal(&tipo_ptr, ptr);
	
	boolTmp1 = generateVarLabel();
	boolTmp2 = generateVarLabel();
	declararLocal(&tipo_bool, boolTmp1);
	declararLocal(&tipo_bool, boolTmp2);
	
	label = generateLabel();
	
	//get bounds
	traducao = "\n" + ident() + "//acessando membro\n";
	traducao += newLine(ptr+" = " + "("+TIPO_PTR_TRAD+")" + "&"+rows);
	traducao += setAccess(matrix, instance, ROWS_MEMBER, accessVar);
	traducao += newLine("memcpy("+ptr+", "+accessVar+", "+std::to_string(tipo_int.size)+")");
	traducao += newLine(ptr+" = " + "("+TIPO_PTR_TRAD+")" + "&"+colums);
	traducao += setAccess(matrix, instance, COLUMS_MEMBER, accessVar);
	traducao += newLine("memcpy("+ptr+", "+accessVar+", "+std::to_string(tipo_int.size)+")");
	
	//check bounds in range
	traducao += newLine(boolTmp1 + " = " + rowsVar + "<" + rows);
	traducao += newLine(boolTmp2 + " = " + columsVar + "<" + colums);
	traducao += newLine(boolTmp1 + " = " + boolTmp1 + "&&" + boolTmp2);
	
	traducao += newLine("if (" + boolTmp1 + ") goto " + label);
	traducao += newLine("\tstd::cout << \"Error: Accessing index of " + instance + " beyond boundaries\" << std::endl");
	traducao += newLine("\treturn 1");
	traducao += ident() + label + ":\n";
	
	//set access to index
	traducao += newLine(colums + " = " + rowsVar + "*" + rows);
	traducao += newLine(colums + " = " + colums + "+" + columsVar);
	traducao += newLine(colums + " = " + colums + "*" + std::to_string(matrix->memberType[DATA_MEMBER].tipo.size));
	
	traducao += setAccess(matrix, instance, DATA_MEMBER, accessVar);
	traducao += newLine(accessVar + " = " + accessVar + "+" + colums) + "\n";
	
	return traducao;
	
}
