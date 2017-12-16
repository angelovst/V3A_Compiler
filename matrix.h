#pragma once

#include "struct.h"

#define ROWS_MEMBER "rows"
#define COLUMS_MEMBER "colums"
#define SIZE_MEMBER "data_size"
#define DATA_MEMBER "data"

std::string newMatrix (Tipo *tipo, std::string &label, size_t rows, size_t colums);

std::string setIndexAccess (CustomType *matrix, std::string &instance, std::string &rowsVar, std::string &columsVar);
