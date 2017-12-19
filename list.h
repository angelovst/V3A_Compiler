#pragma once

#define FIRST_MEMBER "first"
#define LAST_MEMBER "last"
#define TYPE_MEMBER "tipo"

#define NODE_DATA_MEMBER "content"
#define NEXT_MEMBER "next"
#define PREVIOUS_MEMBER "previous"

#include "struct.h"

CustomType* nodeType (Tipo *tipo);
std::string newList (Tipo *tipo, const std::string &label);

std::string iterator_end (const std::string &iterator, const std::string &result);
std::string iterator_inbounds (const std::string &iterator, const std::string &result);

std::string iterator_pushAfter (CustomType *list, const std::string &listLabel, CustomType *node, const std::string &iterator, const std::string &data);
std::string iterator_pushBefore (CustomType *list, const std::string &listLabel, CustomType *node, const std::string &iterator, const std::string &data);
std::string iterator_remove (CustomType *list, const std::string &listLabel, CustomType *node, const std::string &iterator, const std::string &removed);

std::string push_back (CustomType *list, const std::string &label, const std::string &data);
std::string push_front (CustomType *list, const std::string &label, const std::string &data);

std::string pop_back (CustomType *list, const std::string &label, const std::string &removed);
std::string pop_front (CustomType *list, const std::string &label, const std::string &removed);

std::string delete_list (CustomType *list, const std::string &label);
