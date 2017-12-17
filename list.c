#include "list.h"
#include "helper.h"

CustomType* nodeType (Tipo *tipo) {
	Tipo t = *tipo;
	t.id |= GROUP_NODE;
	if (customTypes.count(t.id) == 0) {
		CustomType add = newCustomType();
		
		addVar(&add, tipo, DATA_MEMBER, "");
		addVar(&add, &tipo_ptr, NEXT_MEMBER, "NULL");
		addVar(&add, &tipo_ptr, PREVIOUS_MEMBER, "NULL");
		
		createCustomType(&add, std::to_string(tipo->id));
	}
	return &customTypes[t.id];
}

std::string newList (Tipo *tipo, std::string &label) {
	CustomType t = newCustomType();
	std::string traducao;
	
	addVar(&t, &tipo_ptr, FIRST_MEMBER, "NULL");
	addVar(&t, &tipo_ptr, LAST_MEMBER, "NULL");
	addVar(&t, tipo, TYPE_MEMBER, "");
	
	t.tipo.size -= tipo->size;
	
	if (!createCustomType(&t, label)) {
		return VAR_ALREADY_DECLARED;
	}
	traducao = newInstanceOf (&customTypes[t.tipo.id], label, true);
	return traducao;
}

std::string list_first (CustomType *list, const std::string &label, const std::string &iterator) {
	std::string traducao;
	std::string accessVar, itAddr;
	Tipo *t = getTipo(list, FIRST_MEMBER);
	
	accessVar = generateVarLabel();
	itAddr = generateVarLabel();
	declararLocal(&tipo_ptr, accessVar);
	declararLocal(&tipo_ptr, itAddr);
	
	traducao = setAccess(list, label, FIRST_MEMBER, accessVar);
	traducao += newLine(itAddr+" = ("+TIPO_PTR_TRAD+")&"+iterator);
	traducao += newLine("memcpy("+itAddr+", "+accessVar+", "+std::to_string(t->size)+")");
	return traducao;
}

std::string list_last (CustomType *list, const std::string &label, const std::string &iterator) {
	std::string traducao;
	std::string accessVar, itAddr;
	Tipo *t = getTipo(list, FIRST_MEMBER);
	
	accessVar = generateVarLabel();
	itAddr = generateVarLabel();
	declararLocal(&tipo_ptr, accessVar);
	declararLocal(&tipo_ptr, itAddr);
	
	traducao = setAccess(list, label, LAST_MEMBER, accessVar);
	traducao += newLine(itAddr+" = ("+TIPO_PTR_TRAD+")&"+iterator);
	traducao += newLine("memcpy("+itAddr+", "+accessVar+", "+std::to_string(t->size)+")");
	return traducao;
}

std::string iterator_next (CustomType *node, const std::string &iterator, const std::string &next) {
	std::string traducao = ident() + "//ITERATOR NEXT\n";
	std::string accessVar, nextAddr;
	Tipo *t = getTipo(node, NEXT_MEMBER);
	
	accessVar = generateVarLabel();
	nextAddr = generateVarLabel();
	declararLocal(&tipo_ptr, accessVar);
	declararLocal(&tipo_ptr, nextAddr);
	
	traducao += setAccess(node, iterator, NEXT_MEMBER, accessVar);
	traducao += newLine(nextAddr+" = ("+TIPO_PTR_TRAD+")&"+next);
	traducao += newLine("memcpy("+nextAddr+", "+accessVar+", "+std::to_string(t->size)+")") + "\n";
	
	return traducao;
}

std::string iterator_prev (CustomType *node, const std::string &iterator, const std::string &prev) {
	std::string traducao = ident() + "//ITERATOR PREVIOUS\n";
	std::string accessVar, prevAddr;
	Tipo *t = getTipo(node, PREVIOUS_MEMBER);
	
	accessVar = generateVarLabel();
	prevAddr = generateVarLabel();
	declararLocal(&tipo_ptr, accessVar);
	declararLocal(&tipo_ptr, prevAddr);
	
	traducao += setAccess(node, iterator, PREVIOUS_MEMBER, accessVar);
	traducao += newLine(prevAddr+" = ("+TIPO_PTR_TRAD+")&"+prev);
	traducao += newLine("memcpy("+prevAddr+", "+accessVar+", "+std::to_string(t->size)+")") + "\n";
	
	return traducao;
}

std::string iterator_end (const std::string &iterator, const std::string &result) {
	return newLine(result+" = "+iterator+"==NULL");
}

std::string iterator_pushAfter (CustomType *list, const std::string &listLabel, CustomType *node, const std::string &iterator, const std::string &data) {
	std::string traducao;
	std::string n, iteratorNext, next, prev, check;
	std::string ifLabel, elseLabel;
	Tipo *t = getTipo(node, DATA_MEMBER);
	Tipo *ptr = getTipo(node, NEXT_MEMBER);
	
	n = generateVarLabel();
	iteratorNext = generateVarLabel();
	next = generateVarLabel();
	prev = generateVarLabel();
	check = generateVarLabel();
	
	ifLabel = generateLabel();
	elseLabel = generateLabel();
	
	traducao = ident() + "//PUSH AFTER\n" + newInstanceOf(node, n, false);
	declararLocal(&tipo_ptr, iteratorNext);
	declararLocal(&tipo_ptr, next);
	declararLocal(&tipo_ptr, prev);
	declararLocal(&tipo_bool, check);
	
	//add data to n
	traducao += setAccess(node, n, DATA_MEMBER, next);
	traducao += newLine(prev+" = ("+TIPO_PTR_TRAD+")&"+data);
	traducao += newLine("memcpy("+next+", "+prev+", "+std::to_string(t->size)+")");
	
	//iteratorNext = iterator.next
	traducao += setAccess(node, iterator, NEXT_MEMBER, next);
	traducao += newLine(prev+" = ("+TIPO_PTR_TRAD+")&"+iteratorNext);
	traducao += newLine("memcpy("+prev+", "+next+", "+std::to_string(ptr->size)+")");
	
	//if (iteratorNext != NULL) iterator.next.prev = n
	traducao += iterator_end (iteratorNext, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += setAccess(node, iteratorNext, PREVIOUS_MEMBER, prev);
	traducao += newLine(next+" = ("+TIPO_PTR_TRAD+")&"+n);
	traducao += newLine("memcpy("+prev+", "+next+", "+std::to_string(ptr->size)+")");
	traducao += newLine("goto "+elseLabel);
	
	//else list.last = n
	traducao += ident() + ifLabel + ":\n";
	traducao += setAccess(list, listLabel, LAST_MEMBER, next);
	traducao += newLine(prev+" = ("+TIPO_PTR_TRAD+")&"+n);
	traducao += newLine("memcpy("+next+", "+prev+", "+std::to_string(ptr->size)+")");
	//endif
	traducao += ident() + elseLabel + ":\n\n";
	
	//iterator.next = n
	traducao += setAccess(node, iterator, NEXT_MEMBER, next);
	traducao += newLine(prev+" = ("+TIPO_PTR_TRAD+")&"+n);
	traducao += newLine("memcpy("+next+", "+prev+", "+std::to_string(ptr->size)+")");
	
	return traducao + "\n";
}

std::string push_back (CustomType *list, const std::string &label, const std::string &data) {
	std::string traducao;
	std::string last, ldata, dataAddr;
	std::string check, ifLabel, elseLabel;
	Tipo *t = getTipo(list, TYPE_MEMBER);
	
	last = generateVarLabel();
	ldata = generateVarLabel();
	dataAddr = generateVarLabel();
	check = generateVarLabel();
	
	declararLocal(&tipo_ptr, last);
	declararLocal(&tipo_ptr, ldata);
	declararLocal(&tipo_ptr, dataAddr);
	declararLocal(&tipo_bool, check);
	
	ifLabel = generateLabel();
	elseLabel = generateLabel();
	
	//last = list.last()
	traducao = list_last(list, label, last);
	
	//if (!last.end()) last.push_after(data)
	traducao += iterator_end(last, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += iterator_pushAfter(list, label, nodeType(t), last, data);
	traducao += newLine("goto "+elseLabel);
	
	//else list.first = list.last = newNode(data)
	traducao += ident() + ifLabel + ":\n";
		//newNode
	traducao += newInstanceOf(nodeType(t), last, false);
	traducao += setAccess(nodeType(t), last, DATA_MEMBER, ldata);
	traducao += newLine(dataAddr+" = ("+TIPO_PTR_TRAD+")&"+data);
	traducao += newLine("memcpy("+ldata+", "+dataAddr+", "+std::to_string(t->size)+")");
		//list.first = newNode
	traducao += newLine(ldata+" = ("+TIPO_PTR_TRAD+")&"+last);
	traducao += setAccess(list, label, FIRST_MEMBER, dataAddr);
	traducao += newLine("memcpy("+dataAddr+", "+ldata+", "+std::to_string(tipo_ptr.size)+")");
		//list.last = newNode
	traducao += setAccess(list, label, LAST_MEMBER, dataAddr);
	traducao += newLine("memcpy("+dataAddr+", "+ldata+", "+std::to_string(tipo_ptr.size)+")");
	
	traducao += newLine(elseLabel+":")+"\n";
	
	return traducao;
}
