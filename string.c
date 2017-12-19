#include "string.h"
#include <iostream>

CustomType *str_matrix = NULL;

std::string newString (const std::string &label) {
	std::string traducao = "";
	Tipo *t;
	if (str_matrix == NULL) {
		CustomType matrix = newCustomType();
		
		//create matrix
		addVar(&matrix, &tipo_int, ROWS_MEMBER, "");
		addVar(&matrix, &tipo_int, COLUMS_MEMBER, "");
	
		addVar(&matrix, &tipo_char, DATA_MEMBER, "");
	
		matrix.tipo.size -= tipo_char.size;
	
		customTypes[matrix.tipo.id] = matrix;
		str_matrix = &customTypes[matrix.tipo.id];
		
	}
	traducao += newList(newPtr(&str_matrix->tipo), label);
	
	return traducao;
}

std::string attrLiteral (CustomType *list, const std::string &label, const std::string &literal) {
	std::string traducao = "";
	std::string matrix;
	std::string rows, colums, index;
	
	matrix = generateVarLabel();
	
	rows = generateVarLabel();
	colums = generateVarLabel();
	index = generateVarLabel();
	declararLocal(&tipo_int, rows);
	declararLocal(&tipo_int, colums);
	declararLocal(&tipo_ptr, index);
	
	//delete current list
	traducao += delete_list(list, label);
	
	//initialize matrix
	traducao += newLine(rows+" = "+std::to_string(literal.length()-1));
	traducao += newLine(colums+" = 1");
	traducao += newMatrix(&tipo_char, matrix, true, rows, colums);
	
	//storing string
	traducao += setAccess(str_matrix, matrix, DATA_MEMBER, index);
	traducao += newLine("strcpy("+index+", "+literal+")");
	
	//atribute matrix to list
	traducao += push_back(list, label, matrix);
	
	return traducao;
	
}
