#pragma once

#include "struct.h"

#define ROWS_MEMBER "rows"
#define COLUMS_MEMBER "colums"
#define DATA_MEMBER "data"

std::string newMatrix (Tipo *tipo, std::string &label, bool collectGarbage, bool global, const std::string &rows, const std::string &colums);

std::string setIndexAccess (CustomType *matrix, std::string &instance, std::string &rowsVar, std::string &columsVar, const std::string &accessVar);
