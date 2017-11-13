CC = g++ -std=c++11
OBJS = helper.o list.o

all: $(OBJS)
		lex lexica.l
		yacc -d sintatica.y
		$(CC) -std=c++11 -o glf y.tab.c $(OBJS) -lfl
		
%.o: %.c
	$(CC) -c $^
		
clean:
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f glf
	rm -f *.o
	rm -f lex.yy.c
