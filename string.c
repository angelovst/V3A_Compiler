#include "string.h"
#include "helper.h"
#include <iostream>

CustomType *str_matrix = NULL;
CustomType *str_list = NULL;

std::string newString (const std::string &label) {
	std::string traducao = "";
	
	if (str_matrix == NULL) {
		CustomType matrix = newCustomType();
		CustomType str = newCustomType();
		Tipo t;
		
		//create matrix
		addVar(&matrix, &tipo_int, ROWS_MEMBER, "");
		addVar(&matrix, &tipo_int, COLUMS_MEMBER, "");
	
		addVar(&matrix, &tipo_char, DATA_MEMBER, "");
	
		matrix.tipo.size -= tipo_char.size;
		
		customTypes[matrix.tipo.id] = matrix;
		str_matrix = &customTypes[matrix.tipo.id];
		
		//create list
		t = *(newPtr(&str_matrix->tipo));
		t.id |= GROUP_STRUCT|GROUP_PTR;
		t.trad = TIPO_PTR_TRAD;
		t.size = sizeof(char*);
	
		addVar(&str, &t, FIRST_MEMBER, NULL_VAR);
		addVar(&str, &t, LAST_MEMBER, NULL_VAR);
		addVar(&str, newPtr(&str_matrix->tipo), TYPE_MEMBER, "");
	
		customTypes[str.tipo.id] = str;
		str_list = &customTypes[str.tipo.id];
		
	}
	traducao += newInstanceOf(str_list, label, true, false);
	
	return traducao;
}

std::string castToString (Tipo *t, const std::string &src, const std::string &dst) {
	Tipo *nPtr;
	std::string traducao = "";
	std::string var;
	
	if (belongsTo(t, GROUP_PTR)) {
		std::string varAddr;
		
		nPtr = nonPtr(t);
		
		var = generateVarLabel();
		varAddr = generateVarLabel();
		declararLocal(nPtr, var);
		declararLocal(&tipo_ptr, varAddr);
		
		traducao += newLine(varAddr+" = ("+TIPO_PTR_TRAD+")&"+var);
		traducao += newLine("memcpy("+varAddr+", "+src+", "+std::to_string(t->size));
	} else {
		nPtr = t;
		var = src;
	}
	
	if (nPtr->id == tipo_int.id) {
		std::string size;
		std::string log;
		
		size = generateVarLabel();
		log = generateVarLabel();
		declararLocal(&tipo_int, size);
		declararLocal(&tipo_float, log);
		
		//descobrir tamanho da string que armazene o numero
		traducao += newLine(log+" = (float)log10("+var+")");
		traducao += newLine(size+" = (int)floor("+log+")");
		traducao += newLine(size+" = 1+"+size);
		traducao += newLine(dst+" = (char*)malloc("+size+")");
		
		//copiar valor para string
		traducao += newLine("sprinf("+dst+", \"%d\", "+var+")");
		
	} else if (nPtr->id == tipo_float.id) {
		std::string size;
		std::string intPart;
		std::string log;
		
		size = generateVarLabel();
		log = generateVarLabel();
		intPart = generateVarLabel();
		declararLocal(&tipo_int, size);
		declararLocal(&tipo_float, log);
		declararLocal(&tipo_int, intPart);
		
		//descobrir tamanho da string que armazene o numero
		traducao += newLine(intPart+" = (int)"+var);
		traducao += newLine(log+" = (float)log10("+intPart+")");
		traducao += newLine(size+" = (int)floor("+log+")");
		traducao += newLine(size+" = 7+"+size);	//1 para \0, 1 para ., 5 para digitos
		traducao += newLine(dst+" = (char*)malloc("+size+")");
		
		//copiar valor para string
		traducao += newLine("sprinf("+dst+", \"%.5f\", "+var+")");
	} else if (nPtr->id == tipo_bool.id) {
		std::string check;
		std::string ifLabel, elseLabel;
		
		ifLabel = generateLabel();
		elseLabel = generateLabel();
		
		traducao += newLine(dst+" = (char*)malloc(6)");
		traducao += newLine(check+" = "+var+"!=0");
		traducao += newLine("if ("+check+") goto "+ifLabel);
		traducao += "\t" + newLine("strcpy("+dst+", \"false\")");
		traducao += newLine("goto "+elseLabel);
		
		traducao += ident() + ifLabel + ":\n";
		traducao += "\t" + newLine("strcpy("+dst+", \"true\")");
		traducao += newLine(elseLabel+":");
		
	} else if (nPtr->id == tipo_char.id) {
		traducao += newLine(dst+" = (char*)malloc(2)");
		traducao += newLine("sprinf("+dst+", \"%c\", "+var+")");
	} else {
		return INVALID_CAST;
	}
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
	traducao += ident() + "//CLEANING STRING FOR INSERTION\n";
	traducao += delete_list(list, label);
	
	//initialize matrix
	traducao += ident() + "//INITIALIZING STRING PART\n";
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

std::string concat (Tipo *aT, const std::string &a, Tipo *bT, const std::string &b, const std::string &result) {
	std::string traducao = "";
	CustomType *ctA, *ctB, *nt;
	std::string stra, strb, literal, node, matrix, check;
	std::string loopBegin, loopEnd;
	bool needsCast;
	
	//se tipos nao sao strings criar strings contendo os tipos
	needsCast = customTypes.count(aT->id) == 0;
	if (!needsCast) {
		needsCast = getTipo(&customTypes[aT->id], TYPE_MEMBER) == NULL;
	}
	if (needsCast) {
		std::string cast;
		Tipo *t;
		
		stra = generateVarLabel();
		literal = generateVarLabel();
		declararLocal(newPtr(&tipo_char), literal);
		
		traducao += newString(stra);
		t = findVar(stra);
		ctA = &customTypes[t->id];
		
		cast = castToString(aT, a, literal);
		if (cast == INVALID_CAST) return cast;
		traducao += ident() + "//CASTING 1ST ARG\n";
		traducao += cast + attrLiteral(ctA, stra, literal);
		traducao += newLine("free("+literal+")");
	} else {
		stra = a;
		ctA = &customTypes[aT->id];
	}
	
	needsCast = customTypes.count(bT->id) == 0;
	if (!needsCast) {
		needsCast = getTipo(&customTypes[bT->id], TYPE_MEMBER) == NULL;
	}
	if (needsCast) {
		std::string cast;
		Tipo *t;
		
		strb = generateVarLabel();
		literal = generateVarLabel();
		declararLocal(newPtr(&tipo_char), literal);
		
		traducao += newString(strb);
		t = findVar(strb);
		ctB = &customTypes[t->id];
		
		cast = castToString(bT, b, literal);
		if (cast == INVALID_CAST) return cast;
		traducao += ident() + "//CASTING 2ND ARG\n";
		traducao += cast + attrLiteral(ctB, strb, literal);
		traducao += newLine("free("+literal+")");
	} else {
		strb = b;
		ctB = &customTypes[bT->id];
	}
	
	node = generateVarLabel();
	matrix = generateVarLabel();
	check = generateVarLabel();
	declararLocal(&tipo_ptr, node);
	declararLocal(&tipo_ptr, matrix);
	declararLocal(&tipo_bool, check);
	
	loopBegin = generateLabel();
	loopEnd = generateLabel();
	
	nt = nodeType(&str_matrix->tipo);
	
	traducao += retrieveFrom(ctA, stra, FIRST_MEMBER, node);
	//for all m in stra: result push back m
	traducao += ident() + "//LOOPING 1ST ARG\n";
	traducao += ident() + loopBegin + ":\n";
	traducao += iterator_end(node, check);
	traducao += newLine("if ("+check+") goto "+loopEnd);
	traducao += retrieveFrom(nt, node, NODE_DATA_MEMBER, matrix);
	traducao += push_back(ctA, result, matrix);
	traducao += retrieveFrom(nt, node, NEXT_MEMBER, node);
	traducao += newLine("goto "+loopBegin);
	traducao += ident() + loopEnd + ":\n";
	
	loopBegin = generateLabel();
	loopEnd = generateLabel();
	
	traducao += retrieveFrom(ctB, strb, FIRST_MEMBER, node);
	//for all m in strb: result push back m
	traducao += ident() + "//LOOPING 2ND ARG\n";
	traducao += ident() + loopBegin + ":\n";
	traducao += iterator_end(node, check);
	traducao += newLine("if ("+check+") goto "+loopEnd);
	traducao += retrieveFrom(nt, node, NODE_DATA_MEMBER, matrix);
	traducao += push_back(ctA, result, matrix);
	traducao += retrieveFrom(nt, node, NEXT_MEMBER, node);
	traducao += newLine("goto "+loopBegin);
	traducao += newLine(loopEnd+":");
	
	return traducao;
}
