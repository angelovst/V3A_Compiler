#include "list.h"
#include "helper.h"
#include <iostream>

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
	traducao += newInstanceOf (&customTypes[ct.tipo.id], label, false);
	contextStack.begin()->garbageCollect += delete_list(&customTypes[ct.tipo.id], label);
	contextStack.begin()->garbageCollect += newLine("free("+label+")");
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

std::string iterator_pushBefore (CustomType *list, const std::string &listLabel, CustomType *node, const std::string &iterator, const std::string &data) {
	std::string traducao;
	std::string n, iteratorPrev, check;
	std::string ifLabel, elseLabel;
	Tipo *t = getTipo(node, NODE_DATA_MEMBER);
	Tipo *ptr = getTipo(node, NEXT_MEMBER);
	
	n = generateVarLabel();
	iteratorPrev = generateVarLabel();
	check = generateVarLabel();
	
	ifLabel = generateLabel();
	elseLabel = generateLabel();
	
	traducao = iterator_inbounds(iterator, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += "\t" + newLine("std::cout << \"Erro: tentativa de push antes de iterador out of bounds\" << std::endl");
	traducao += "\t" + newLine("return 1");
	
	traducao += ident() + ifLabel + ":\n" + newInstanceOf(node, n, false);
	declararLocal(&tipo_ptr, iteratorPrev);
	declararLocal(&tipo_bool, check);
	
	ifLabel = generateLabel();
	
	//add data to n
	traducao += attrTo(node, n, NODE_DATA_MEMBER, data);
	
	//iteratorPrev = iterator.previous
	traducao += retrieveFrom(node, iterator, PREVIOUS_MEMBER, iteratorPrev);
	
	//n.previous = iteratorPrev
	traducao += attrTo(node, n, PREVIOUS_MEMBER, iteratorPrev);
	//n.next = iterator
	traducao += attrTo(node, n, NEXT_MEMBER, iterator);
	
	//if (iteratorPrev != NULL) iterator.prev.next = n
	traducao += iterator_end (iteratorPrev, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += attrTo(node, iteratorPrev, NEXT_MEMBER, n);
	traducao += newLine("goto "+elseLabel);
	
	//else list.first = n
	traducao += ident() + ifLabel + ":\n";
	traducao += attrTo(list, listLabel, FIRST_MEMBER, n);
	//endif
	traducao += ident() + elseLabel + ":\n\n";
	
	//iterator.previous = n
	traducao += attrTo(node, iterator, PREVIOUS_MEMBER, n);
	
	return traducao + "\n";
}

std::string iterator_remove (CustomType *list, const std::string &listLabel, CustomType *node, const std::string &iterator, const std::string &removed) {
	std::string traducao = "";
	std::string prev, next, check;
	std::string ifLabel, elseLabel, ifL2, elseL2;
	
	prev = generateVarLabel();
	next = generateVarLabel();
	check = generateVarLabel();
	declararLocal(&tipo_ptr, prev);
	declararLocal(&tipo_ptr, next);
	declararLocal(&tipo_bool, check);
	
	//removed = iterator.content
	traducao += retrieveFrom(node, iterator, NODE_DATA_MEMBER, removed);
	
	//next = iterator.next; prev = iterator.previous
	traducao += retrieveFrom(node, iterator, NEXT_MEMBER, next);
	traducao += retrieveFrom(node, iterator, PREVIOUS_MEMBER, prev);
	//if (next == prev)
	ifLabel = generateLabel();
	elseLabel = generateLabel();
	traducao += newLine(check+" = "+next+"!="+prev);
	traducao += newLine("if ("+check+") goto "+ifLabel);
		//list.first = null; list.last = null
	traducao += "\t" + attrTo(list, listLabel, FIRST_MEMBER, NULL_VAR);
	traducao += "\t" + attrTo(list, listLabel, LAST_MEMBER, NULL_VAR);
	traducao += newLine("goto "+elseLabel);
	//else
	traducao += ident() + ifLabel + ":\n";
		//if (next == NULL) list.last = prev
	ifL2 = generateLabel();
	elseL2 = generateLabel();
	traducao += newLine(check+" = "+next+"!=NULL");
	traducao += newLine("if ("+check+") goto "+ifL2);
	traducao += "\t"+ attrTo(list, listLabel, LAST_MEMBER, prev);
	traducao += newLine("goto "+elseL2);
		//else next.previous = prev
	traducao += ident() + ifL2 + ":\n";
	traducao += attrTo(node, next, PREVIOUS_MEMBER, prev);
	traducao += newLine(elseL2+":");
		//if (prev == NULL) list.first = next
	ifL2 = generateLabel();
	elseL2 = generateLabel();
	traducao += newLine(check+" = "+prev+"!=NULL");
	traducao += newLine("if ("+check+") goto "+ifL2);
	traducao += "\t"+ attrTo(list, listLabel, FIRST_MEMBER, next);
	traducao += newLine("goto "+elseL2);
		//else previous.next = next
	traducao += ident() + ifL2 + ":\n";
	traducao += attrTo(node, prev, NEXT_MEMBER, next);
	traducao += newLine(elseL2+":");
	
	traducao += newLine(elseLabel+":");
	
	//free iterator
	traducao += newLine("free("+iterator+")");
	
	return traducao;
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

std::string push_front (CustomType *list, const std::string &label, const std::string &data) {
	std::string traducao;
	std::string first, n;
	std::string check, ifLabel, elseLabel;
	Tipo *t = getTipo(list, TYPE_MEMBER);
	
	first = generateVarLabel();
	check = generateVarLabel();
	n = generateVarLabel();
	
	declararLocal(&tipo_ptr, first);
	declararLocal(&tipo_bool, check);
	
	ifLabel = generateLabel();
	elseLabel = generateLabel();
	
	//first = list.first()
	traducao = retrieveFrom(list, label, FIRST_MEMBER, first);
	
	//if (!first.end()) first.push_before(data)
	traducao += iterator_end(first, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += iterator_pushBefore(list, label, nodeType(t), first, data);
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

std::string pop_back (CustomType *list, const std::string &label, const std::string &removed) {
	std::string traducao;
	std::string last, n;
	std::string check, ifLabel;
	Tipo *t = getTipo(list, TYPE_MEMBER);
	
	last = generateVarLabel();
	check = generateVarLabel();
	
	declararLocal(&tipo_ptr, last);
	declararLocal(&tipo_bool, check);
	
	ifLabel = generateLabel();
	
	//last = list.last()
	traducao = retrieveFrom(list, label, LAST_MEMBER, last);
	
	//if (!last.end()) remove(last)
	traducao += iterator_end(last, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += iterator_remove(list, label, nodeType(t), last, removed);
	traducao += newLine(ifLabel + ":");
	
	return traducao;
}

std::string pop_front (CustomType *list, const std::string &label, const std::string &removed) {
	std::string traducao;
	std::string first;
	std::string check, ifLabel;
	Tipo *t = getTipo(list, TYPE_MEMBER);
	
	first = generateVarLabel();
	check = generateVarLabel();
	
	declararLocal(&tipo_ptr, first);
	declararLocal(&tipo_bool, check);
	
	ifLabel = generateLabel();
	
	//first = list.first()
	traducao = retrieveFrom(list, label, FIRST_MEMBER, first);
	
	//if (!last.end()) remove(first)
	traducao += iterator_end(first, check);
	traducao += newLine("if ("+check+") goto "+ifLabel);
	traducao += iterator_remove(list, label, nodeType(t), first, removed);
	traducao += newLine(ifLabel + ":");
	
	return traducao;
}

std::string delete_list (CustomType *list, const std::string &label) {
	std::string traducao = "";
	std::string deleting, next, check;
	std::string loopEnd, loopBegin;
	Tipo *t = getTipo(list, TYPE_MEMBER);
	CustomType *node = nodeType(t);
	
	deleting = generateVarLabel();
	next = generateVarLabel();
	check = generateVarLabel();
	declararLocal(&tipo_ptr, deleting);
	declararLocal(&tipo_ptr, next);
	declararLocal(&tipo_bool, check);
	
	//deleting = list.first
	traducao += retrieveFrom(list, label, FIRST_MEMBER, deleting);
	//if deleting.end goto loopEnd
	loopEnd = generateLabel();
	loopBegin = generateLabel();
	traducao += ident() + loopBegin + ":\n";
	traducao += iterator_end(deleting, check);
	traducao += newLine("if ("+check+") goto "+loopEnd);
		//next = deleting.next
	traducao += retrieveFrom(node, deleting, NEXT_MEMBER, next);
		//free(deleting)
	traducao += newLine("free("+deleting+")");
		//deleting = next
	traducao += newLine(deleting+" = "+next);
	traducao += newLine("goto "+loopBegin);
	
	traducao += newLine(loopEnd+":");
	
	return traducao;
}
