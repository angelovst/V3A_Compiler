all: helper.h helper.cpp	
		clear
		lex lexica.l
		yacc -d sintatica.y
		g++ -std=c++11 -o glf y.tab.c helper.cpp -lfl

		./glf < exemplo.v3a
		

