#include "matrix.h"
#include "helper.h"

std::string newMatrix (Tipo *tipo, std::string &label, const std::string &rows, const std::string &colums) {
	Tipo *array = newPtr(tipo);
	
	CustomType t = newCustomType();
	std::string traducao;

	addVar(&t, &tipo_int, ROWS_MEMBER, rows);
	addVar(&t, &tipo_int, COLUMS_MEMBER, colums);
	
	addVar(&t, array, DATA_MEMBER, "");
	
	createCustomType (&t, label);
	
	return newInstanceOf (&t, label, true);
	
}

std::string setIndexAccess (CustomType *matrix, std::string &instance, std::string &rowsVar, std::string &columsVar) {
	std::string accessVar = "_"+instance+ACCESS_VAR;
	std::string rows, colums;
	std::string boolTmp1, boolTmp2;
	std::string label;
	std::string traducao;
	
	rows = generateVarLabel();
	colums = generateVarLabel();
	declararLocal(&tipo_int, rows);
	declararLocal(&tipo_int, colums);
	
	boolTmp1 = generateVarLabel();
	boolTmp2 = generateVarLabel();
	declararLocal(&tipo_bool, boolTmp1);
	declararLocal(&tipo_bool, boolTmp2);
	
	label = generateLabel();
	
	//get bounds
	traducao = setAccess(matrix, instance, ROWS_MEMBER);
	traducao += newLine("memcpy("+rows+", "+accessVar+", "+std::to_string(tipo_int.size)+")");
	traducao += setAccess(matrix, instance, COLUMS_MEMBER);
	traducao += newLine("memcpy("+colums+", "+accessVar+", "+std::to_string(tipo_int.size)+")");
	
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
	
	traducao += setAccess(matrix, instance, DATA_MEMBER);
	traducao += newLine(accessVar + " = " + accessVar + "+" + colums);
	
	return traducao;
	
}
