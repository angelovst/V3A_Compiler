#include "list.h"
#include "helper.h"

CustomType* nodeType (Tipo *tipo, const std::string &nullVar) {
	Tipo t = *tipo;
	t.id |= GROUP_STRUCT|GROUP_PTR;
	t.trad = TIPO_PTR_TRAD;
	t.size = sizeof(char*);
	
	if (customTypes.count(t.id) == 0) {
		CustomType add = newCustomType();
		std::string null;
		
		addVar(&add, tipo, NODE_DATA_MEMBER, "");
		addVar(&add, &t, NEXT_MEMBER, nullVar);
		addVar(&add, &t, PREVIOUS_MEMBER, nullVar);
		
		customTypes[t.id] = add;
		createCustomType(&add, std::to_string(t.id));
		
		//std::cout << "node=" << std::hex << t.id << std::endl;	//debug
	}
	//std::cout << "nothing to declare" << std::endl;	//debug
	return &customTypes[t.id];
}

std::string newList (Tipo *tipo, std::string &label) {
	CustomType ct = newCustomType();
	std::string traducao, nullVar;
	Tipo t = *tipo;
	
	t.id |= GROUP_STRUCT|GROUP_PTR;
	t.trad = TIPO_PTR_TRAD;
	t.size = sizeof(char*);
	
	nullVar = generateVarLabel();
	declararLocal(&tipo_ptr, nullVar);
	
	traducao = newLine(nullVar+" = NULL");
	
	addVar(&ct, &t, FIRST_MEMBER, nullVar);
	addVar(&ct, &t, LAST_MEMBER, nullVar);
	addVar(&ct, tipo, TYPE_MEMBER, "");
	
	ct.tipo.size -= tipo->size;
	
	if (!createCustomType(&ct, label)) {
		return VAR_ALREADY_DECLARED;
	}
	traducao += newInstanceOf (&customTypes[ct.tipo.id], label, true);
	return traducao;
}

std::string iterator_end (const std::string &iterator, const std::string &result) {
	return newLine(result+" = "+iterator+"==NULL");
}

std::string iterator_pushAfter (CustomType *list, const std::string &listLabel, CustomType *node, const std::string &iterator, const std::string &data) {
	std::string traducao;
	std::string n, iteratorNext, next, prev, check;
	std::string ifLabel, elseLabel;
	Tipo *t = getTipo(node, NODE_DATA_MEMBER);
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
	traducao += setAccess(node, n, NODE_DATA_MEMBER, next);
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
	std::string last, ldata, dataAddr, n;
	std::string check, ifLabel, elseLabel;
	std::string nullVar;
	std::string iterator;
	Tipo *t = getTipo(list, TYPE_MEMBER);
	Tipo *ptr = newPtr(t);
	
	last = generateVarLabel();
	ldata = generateVarLabel();
	dataAddr = generateVarLabel();
	check = generateVarLabel();
	n = generateVarLabel();
	nullVar = generateVarLabel();
	iterator = generateVarLabel();
	
	declararLocal(&tipo_ptr, last);
	declararLocal(&tipo_ptr, ldata);
	declararLocal(&tipo_ptr, dataAddr);
	declararLocal(&tipo_bool, check);
	declararLocal(&tipo_ptr, nullVar);
	declararLocal(&tipo_ptr, iterator);
	
	ifLabel = generateLabel();
	elseLabel = generateLabel();
	
	//last = list.last()
	traducao = setAccess(list, label, LAST_MEMBER, last);
	
	//if (!last.end()) last.push_after(data)
	traducao += newLine(ldata+" = ("+TIPO_PTR_TRAD+")&"+iterator);
	traducao += newLine("memcpy("+ldata+", "+last+", "+std::to_string(tipo_ptr.size)+")");
	traducao += newLine(nullVar+" = NULL");
	traducao += iterator_end(iterator, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += iterator_pushAfter(list, label, nodeType(t, nullVar), last, data);
	traducao += newLine("goto "+elseLabel);
	
	//else list.first = list.last = newNode(data)
	traducao += ident() + ifLabel + ":\n";
		//newNode
	traducao += ident() + "//new node\n";
	traducao += newInstanceOf(nodeType(t, nullVar), n, false);
	traducao += setAccess(nodeType(t, nullVar), n, NODE_DATA_MEMBER, ldata);
	traducao += newLine(dataAddr+" = ("+TIPO_PTR_TRAD+")&"+data);
	traducao += newLine("memcpy("+ldata+", "+dataAddr+", "+std::to_string(t->size)+")");
		//list.first = newNode
	traducao += newLine(ldata+" = ("+TIPO_PTR_TRAD+")&"+n);
	traducao += setAccess(list, label, FIRST_MEMBER, dataAddr);
	traducao += newLine("memcpy("+dataAddr+", "+ldata+", "+std::to_string(tipo_ptr.size)+")");
		//list.last = newNode
	traducao += setAccess(list, label, LAST_MEMBER, dataAddr);
	traducao += newLine("memcpy("+dataAddr+", "+ldata+", "+std::to_string(tipo_ptr.size)+")");
	
	traducao += newLine(elseLabel+":")+"\n";
	
	return traducao;
}
