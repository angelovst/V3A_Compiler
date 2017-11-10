CC = g++ -std=c++11
OBJS = y.tab.o helper.o

all: $(OBJS)	
		clear
		lex lexica.l
		yacc -d sintatica.y
		$(CC) -std=c++11 -o glf $(OBJS) -lfl

		./glf < exemplo.v3a
		
*.o: *.c
	$(CC) -c $<
