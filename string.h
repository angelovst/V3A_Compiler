#pragma once

#include "list.h"
#include "matrix.h"

extern CustomType *str_matrix;

std::string newString (const std::string &label);

std::string attrLiteral (CustomType *list, const std::string &label, const std::string &literal);

std::string concat (CustomType *listA, const std::string &a, CustomType *listB, const std::string &b, const std::string &result);
