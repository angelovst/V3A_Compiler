#include "list.h"
#include "helper.h"

CustomType* nodeType (Tipo *tipo) {
	Tipo t = *tipo;
	t.id |= GROUP_STRUCT|GROUP_PTR;
	t.trad = TIPO_PTR_TRAD;
	t.size = sizeof(char*);
	
	if (customTypes.count(t.id) == 0) {
		CustomType add = newCustomType();
		
		addVar(&add, tipo, NODE_DATA_MEMBER, "");
		addVar(&add, &t, NEXT_MEMBER, NULL_VAR);
		addVar(&add, &t, PREVIOUS_MEMBER, NULL_VAR);
		
		customTypes[t.id] = add;
		createCustomType(&add, std::to_string(t.id));
		
		//std::cout << "node=" << std::hex << t.id << std::endl;	//debug
	}
	//std::cout << "nothing to declare" << std::endl;	//debug
	return &customTypes[t.id];
}

std::string newList (Tipo *tipo, std::string &label) {
	CustomType ct = newCustomType();
	std::string traducao;
	Tipo t = *tipo;
	
	t.id |= GROUP_STRUCT|GROUP_PTR;
	t.trad = TIPO_PTR_TRAD;
	t.size = sizeof(char*);
	
	addVar(&ct, &t, FIRST_MEMBER, NULL_VAR);
	addVar(&ct, &t, LAST_MEMBER, NULL_VAR);
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
std::string iterator_inbounds (const std::string &iterator, const std::string &result) {
	return newLine(result+" = "+iterator+"!=NULL");
}

std::string iterator_pushAfter (CustomType *list, const std::string &listLabel, CustomType *node, const std::string &iterator, const std::string &data) {
	std::string traducao;
	std::string n, iteratorNext, check;
	std::string ifLabel, elseLabel;
	Tipo *t = getTipo(node, NODE_DATA_MEMBER);
	Tipo *ptr = getTipo(node, NEXT_MEMBER);
	
	n = generateVarLabel();
	iteratorNext = generateVarLabel();
	check = generateVarLabel();
	
	ifLabel = generateLabel();
	elseLabel = generateLabel();
	
	traducao = iterator_inbounds(iterator, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += "\t" + newLine("std::cout << \"Erro: tentativa de push apos iterador out of bounds\" << std::endl");
	traducao += "\t" + newLine("return 1");
	
	traducao += ident() + ifLabel + ":\n" + newInstanceOf(node, n, false);
	declararLocal(&tipo_ptr, iteratorNext);
	declararLocal(&tipo_bool, check);
	
	ifLabel = generateLabel();
	
	//add data to n
	traducao += attrTo(node, n, NODE_DATA_MEMBER, data);
	
	//iteratorNext = iterator.next
	traducao += retrieveFrom(node, iterator, NEXT_MEMBER, iteratorNext);
	
	//n.previous = iterator
	traducao += attrTo(node, n, PREVIOUS_MEMBER, iterator);
	//n.next = iteratorNext
	traducao += attrTo(node, n, NEXT_MEMBER, iteratorNext);
	
	//if (iteratorNext != NULL) iterator.next.prev = n
	traducao += iterator_end (iteratorNext, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += attrTo(node, iteratorNext, PREVIOUS_MEMBER, n);
	traducao += newLine("goto "+elseLabel);
	
	//else list.last = n
	traducao += ident() + ifLabel + ":\n";
	traducao += attrTo(list, listLabel, LAST_MEMBER, n);
	//endif
	traducao += ident() + elseLabel + ":\n\n";
	
	//iterator.next = n
	traducao += attrTo(node, iterator, NEXT_MEMBER, n);
	
	return traducao + "\n";
}

std::string push_back (CustomType *list, const std::string &label, const std::string &data) {
	std::string traducao;
	std::string last, n;
	std::string check, ifLabel, elseLabel;
	Tipo *t = getTipo(list, TYPE_MEMBER);
	
	last = generateVarLabel();
	check = generateVarLabel();
	n = generateVarLabel();
	
	declararLocal(&tipo_ptr, last);
	declararLocal(&tipo_bool, check);
	
	ifLabel = generateLabel();
	elseLabel = generateLabel();
	
	//last = list.last()
	traducao = retrieveFrom(list, label, LAST_MEMBER, last);
	
	//if (!last.end()) last.push_after(data)
	traducao += iterator_end(last, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += iterator_pushAfter(list, label, nodeType(t), last, data);
	traducao += newLine("goto "+elseLabel);
	
	//else list.first = list.last = newNode(data)
	traducao += ident() + ifLabel + ":\n";
		//newNode
	traducao += ident() + "//new node\n";
	traducao += newInstanceOf(nodeType(t), n, false);
	traducao += attrTo(nodeType(t), n, NODE_DATA_MEMBER, data);
		//list.first = newNode
	traducao += attrTo(list, label, FIRST_MEMBER, n);
		//list.last = newNode
	traducao += attrTo(list, label, LAST_MEMBER, n);
	
	traducao += newLine(elseLabel+":")+"\n";
	
	return traducao;
}
