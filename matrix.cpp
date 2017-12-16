#include "matix.h"

std::string newMatrix (Tipo *tipo, std::string &label, size_t rows, size_t colums) {
	Tipo array = {GROUP_PTR|tipo->id, rows*colums, TIPO_PTR_TRAD, &castPadrao, NULL, NULL, NULL};
	CustomType t = newCustomType();
	
	addVar(&t, &tipo_int, ROWS_MEMBER);
	addVar(&t, &tipo_int, COLUMS_MEMBER);
	addVar(&t, &array, DATA_MEMBER);
	
	createCustomType (&t, label);
	
	return newInstanceOf (&t, label, true);
	
}
