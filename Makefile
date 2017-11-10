CC = g++ -std=c++11

all:
		lex lexica.l
		yacc -d sintatica.y
		$(CC) -std=c++11 -o glf y.tab.c helper.c $(OBJS) -lfl

		./glf < exemplo.v3a
