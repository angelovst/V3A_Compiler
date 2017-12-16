#include "matix.h"

std::string newMatrix (Tipo *tipo, std::string &label, size_t rows, size_t colums) {
	Tipo array = {GROUP_PTR|tipo->id, rows*colums, TIPO_PTR_TRAD, &castPadrao, NULL, NULL, NULL};
	CustomType t = newCustomType();
	std::string traducao;
	std::string tmp;
	
	tmp = generateVarLabel();
	declararLocal(&tipo_int, tmp);
	traducao = newLine(tmp + " = " + to_string(rows));
	addVar(&t, &tipo_int, ROWS_MEMBER, tmp);
	
	tmp = generateVarLabel();
	declararLocal(&tipo_int, tmp);
	traducao += newLine(tmp + " = " + to_string(colums));
	addVar(&t, &tipo_int, COLUMS_MEMBER, tmp);
	
	tmp = generateVarLabel();
	declararLocal(&tipo_int, tmp);
	traducao += newLine(tmp + " = " + tipo->size);
	addVar(&t, &tipo_int, SIZE_MEMBER, tmp);
	
	addVar(&t, &array, DATA_MEMBER, "");
	
	createCustomType (&t, label);
	
	traducao += newInstanceOf (&t, label, true);
	
	return traducao;
	
}

std::string setIndexAccess (CustomType *matrix, std::string &instance, std::string &rowsVar, std::string &columsVar) {
	std::string accessVar = "_"+instance+ACCESS_VAR;
	std::string rows, colums, size;
	std::string boolTmp1, boolTmp2;
	std::string label;
	std::string traducao;
	
	rows = generateVarLabel();
	colums = generateVarLabel();
	size = generateVarLabel();
	declararLocal(&tipo_int, rows);
	declararLocal(&tipo_int, colums);
	declararLocal(&tipo_int, size);
	
	boolTmp1 = generateVarLabel();
	boolTmp2 = generateVarLabel();
	declararLocal(&tipo_bool, boolTmp1);
	declararLocal(&tipo_bool, boolTmp2);
	
	label = generateLabel();
	
	//get bounds
	traducao = setAccess(matrix, instance, ROWS_MEMBER);
	traducao += newLine("memcpy("+rows+", "+accessVar+", "+to_string(tipo_int.size)+")");
	traducao += setAccess(matrix, instance, COLUMS_MEMBER);
	traducao += newLine("memcpy("+colums+", "+accessVar+", "+to_string(tipo_int.size)+")");
	
	//check bounds in range
	traducao += newLine(boolTmp1 + " = " + rowsVar + "<" + rows);
	traducao += newLine(boolTmp2 + " = " + columsVar + "<" + colums);
	traducao += newLine(boolTmp1 + " = " + boolTmp1 + "&&" + boolTmp2);
	
	traducao += newLine("if (" + boolTmp1 + ") goto " + label);
	traducao += newLine("\tstd::cout << \"Error: Accessing index of " + instance + " beyond boundaries\" << std::endl");
	traducao += newLine("\treturn 1");
	traducao += ident() + label + ":\n";
	
	traducao += setAccess(matrix, instance, SIZE_MEMBER);
	traducao += newLine("memcpy("+size+", "+accessVar+", "+to_string(tipo_int.size)+")");
	
	traducao += newLine(colums + " = " + rowsVar + "*" + rows);
	traducao += newLine(colums + " = " + colums + "+" + columsVar);
	traducao += newLine(colums + " = " + colums + "*" + size);
	
	traducao += setAccess(matrix, instance, DATA_MEMBER);
	traducao += newLine(accessVar + " = " + accessVar + "+" + colums);
	
	return traducao;
	
}
