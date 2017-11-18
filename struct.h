/*
 * Um struct consiste em uma colecao de valores
 * Dado um valor "tipo nome" declarado dentro do struct, sua declaracao sera:
 *		tipo struct_label_nome; onde struct e o nome dado para o struct e label uma variavel do struct
 *
 */

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include "helper.h"

CustomType* findCustomType (std::string &label);

bool declareVarIn (CustomType *custom, Tipo *tipo, std::string &label);

bool declareLocalOfType (std::string &customType, std::string &label);

#endif
