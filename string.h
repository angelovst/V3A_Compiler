#pragma once

#include "list.h"
#include "matrix.h"

extern CustomType *str_matrix;
extern CustomType *str_list;

void initializeString (void);
std::string newString (const std::string &label);

std::string castToString (Tipo *t, const std::string &src, const std::string &dst);
std::string attrLiteral (CustomType *list, const std::string &label, const std::string &literal);

std::string concat (Tipo *aT, const std::string &a, Tipo *bT, const std::string &b, const std::string &result);
