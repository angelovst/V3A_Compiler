%{
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "helper.h"
#define YYSTYPE atributos

using namespace std;

int yylex(void);
void yyerror(string);

int yyparse();

%}

%token TK_INT TK_FLOAT TK_BOOL TK_CHAR TK_STR
%token TK_IF TK_BLOCO_ABRIR TK_BLOCO_FECHAR TK_ELSE TK_FOR TK_DO TK_WHILE TK_BREAK TK_ALL TK_CONTINUE TK_PRINT
%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_BOOL TK_TIPO_CHAR TK_TIPO_LIST TK_TIPO_STR
%token TK_DOTS TK_2MAIS TK_2MENOS
%token TK_FIM TK_ERROR	TK_ENDL

%start S

%right TK_ATRIB
%left TK_OR TK_AND TK_NOT
%nonassoc TK_IGUAL TK_DIFERENTE
%nonassoc TK_MAIOR TK_MENOR TK_MAIORI TK_MENORI
%left TK_PLUS TK_MINUS
%left TK_MULT TK_DIV TK_MOD
%right TK_2MAIS TK_2MENOS

%%

S 			: COMANDOS ESCOPO_FIM
			{
				cout << "Regra S : COMANDOS ESCOPO_FIM" << endl;	//debug
				cout << "/*Compilador V3A*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(int argc, char **args)\n{\n" << "\t\n" << $2.traducao << $1.traducao << "\n\treturn 0;\n}" << endl;

			}
			;		

BLOCO	: TK_BLOCO_ABRIR COMANDOS ESCOPO_FIM
			{
				cout << "Regra BLOCO : TK_BLOCO_ABRIR COMANDOS ESCOPO_FIM" << endl;	//debug
				empContexto();
				
				$$.traducao = newLine("{\n" + $3.traducao + $2.traducao + "}");
				$$.label = "";
			}
			;
			
ESCOPO_FIM	:	TK_BLOCO_FECHAR
			{
				
				string declar = contextStack.begin()->declar;
				//cout << "declaracoes " << declar << endl;	//debug
				desempContexto();
				$$.label = "";
				$$.traducao = declar;
			}
			|
			{
				string declar = contextStack.begin()->declar;
				//cout << "declaracoes " << declar << endl;	//debug
				desempContexto();
				$$.label = "";
				$$.traducao = declar;			
			}
			;


LOOP_INICIO	:{
				cout << "Regra LOOP_INICIO : vazio" << endl;	//debug
				empLoop();
				empContexto();
				
				$$.traducao = "";
				$$.label = "";
			};
			
LOOP_FIM	:	{
				cout << "Regra LOOP_FIM : vazio" << endl;	//debug
				desempLoop();
				desempContexto();
				
				$$.traducao = "";
				$$.label = "";
			};

COMANDOS	: COMANDO COMANDOS
			{
				cout << "Regra COMANDOS : COMANDO COMANDOS" << endl;	//debug
				$$.traducao = $1.traducao + $2.traducao;
			}
			|
			{
				cout << "Regra COMANDOS : vazio" << endl;
			}	
			;

COMANDO 	: E TK_ENDL
			{
				cout << "Regra COMANDO : E TK_ENDL" << endl;
			}

			| DECLARACAO TK_ENDL
			{
				cout << "Regra COMANDO : DECLARACAO TK_ENDL" << endl;
				$$.traducao = $1.traducao;
			}
			
			| BLOCO
			{
				cout << "Regra COMANDO : BLOCO" << endl;
				$$.traducao = $1.traducao;
			}
			
			| CONTROLE
			{
				cout << "Regra COMANDO : CONTROLE" << endl;
				$$.traducao = $1.traducao;
			}

			| LOOP_ALT TK_ENDL
			{
				cout << "Regra COMANDO : LOOP_ALT TK_ENDL" << endl;
				$$.traducao = $1.traducao;
			}
			| PRINT TK_ENDL
			{
				cout << "Regra COMANDO : PRINT TK_ENDL" << endl;
				$$.traducao = $1.traducao + " << endl;\n";
			}
			;

E 			: E OP_INFIX E {
				cout << "Regra E : E OP_INFIX E" << endl;	//debug
				void *args[4];
				string traducao;
				
				$$.label = generateVarLabel();	//retorno
				if ($2.tipo->retornos != NULL) {	//caso retorno nao seja especificado inferir o tipo
					declararLocal(resolverTipo($1.tipo, $3.tipo), $$.label);
				} else {
					declararLocal((*$2.tipo->retornos)[0], $$.label);
				}	
				$$.traducao = $1.traducao + $3.traducao;
				
				args[0] = &$1;
				args[1] = &$3;
				args[2] = &$$.label;
				args[3] = &$2.tipo->label;
				
				traducao = $2.tipo->traducaoParcial((void*)args);
				if (traducao == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->label + " e " + $3.tipo->label);
				} else if (traducao == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				}	
				
				$$.traducao += traducao;
				
			}
			| '(' TIPO ')' E
			{	
				//cout << "cast executado" << endl;	//debug
				cout << "Regra E : ( TIPO ) E" << endl;	//debug
				$$.label = generateVarLabel();
				declararLocal($2.tipo, $$.label);
				$$.tipo = $2.tipo;
				$$.traducao = $4.traducao + newLine($$.label + " = " + '(' + $2.tipo->label + ')' + $4.label);
			}

			| '(' E ')'
			{
				cout << "Regra E : ( E )" << endl;	//debug
				//cout << "parentizacao feita" << endl;	//debug
				$$.label = $2.label; //generateVarLabel();
				$$.traducao = $2.traducao;// + "\t" + $$.label + " = " + $2.label + ";\n";
			}
			| '-' E
			{
				cout << "Regra E : -E" << endl;	//debug
				//cout << "inversao feita" << endl;	//debug
				$$.label = generateVarLabel();
				$$.traducao = $2.traducao + newLine($$.label + " = " + " - " + $2.label);
			}
			| INCREMENTOS
			{
				cout << "Regra E : INCREMENTOS" << endl;	//debug
			}

			| TK_INT
			{
				cout << "Regra E : TK_INT" << endl;	//debug
				$$.label = generateVarLabel();
				declararLocal(&tipo_int, $$.label);
				$$.traducao = newLine($$.label + " = " + $1.label);
				$$.tipo = &tipo_int;
			}
			| TK_FLOAT
			{
				cout << "Regra E : TK_FLOAT" << endl;	//debug
				$$.label = generateVarLabel();
				declararLocal(&tipo_float, $$.label);
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = &tipo_float;
			}
			| TK_BOOL
			{
				cout << "Regra E : TK_BOOL" << endl;	//debug
				string aux;
				
				if($1.label == BOOL_TRUE) {
					aux = "1";
				}
				else {
					aux = "0";
				}

				$$.label = generateVarLabel();
				declararLocal(&tipo_bool, $$.label);
				$$.traducao = newLine($$.label + " = " + aux);
				$$.tipo = &tipo_bool;

			}
			| TK_CHAR
			{
				cout << "Regra E : TK_CHAR" << endl;	//debug
				$$.label = generateVarLabel();
				declararLocal(&tipo_char, $$.label);
				$$.traducao = newLine($$.label + " = " + $1.label);
				$$.tipo = &tipo_char;
			}
			| TK_ID
			{
				cout << "Regra E : TK_ID" << endl;	//debug
				$$.tipo = NULL;
				$$.label = $1.label;
				$$.traducao = "";
			}
			;
			
DECLARACAO 	: TIPO TK_ID
			{
				//cout << "tipo " << $1.tipo->label << " declarado" << endl;
				cout << "Regra DECLARACAO : TIPO TK_ID" << endl;	//debug
				$$.tipo = $1.tipo;
				if(!declararLocal($1.tipo, $2.label)) {
					yyerror("Variavel ja declarada localmente");
				}	

			}

			| TIPO TK_ID TK_ATRIB E
			{
				cout << "Regra DECLARACAO : TIPO TK_ID TK_ATRIB E" << endl;	//debug
				if(!declararLocal($1.tipo, $2.label)) {
        			yyerror("Variavel ja declarada");	
				}
				string atrib;
				atributos *args[2] = {&$1, &$4};
				
				$$.tipo = $1.tipo;
				atrib = traducaoAtribuicao((void*)args);
				if (atrib == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->label + " e " + $3.tipo->label);
				}
				$$.traducao = atrib;
			}
			;			
			
OP_INFIX	: TK_PLUS
			{
				cout << "Regra OP_INFIX : TK_PLUS" << endl;	//debug
				$$.label = "+";
				$$.tipo = &tipo_arithmetic_operator;
			}
			| TK_MINUS
			{
				cout << "Regra OP_INFIX : TK_MINUS" << endl;	//debug
				$$.label = "-";
				$$.tipo = &tipo_arithmetic_operator;
			}
			| TK_MULT
			{
				cout << "Regra OP_INFIX : TK_MULT" << endl;	//debug
				$$.label = "*";
				$$.tipo = &tipo_arithmetic_operator;
			}
			| TK_DIV {
				cout << "Regra OP_INFIX : TK_DIV" << endl;	//debug
				$$.label = "/";
				$$.tipo = &tipo_arithmetic_operator;
			}
			| TK_MOD {
				cout << "Regra OP_INFIX : TK_MOD" << endl;	//debug
				$$.label = "%";
				$$.tipo = &tipo_arithmetic_operator;
			}
			| TK_AND  {
				cout << "Regra OP_INFIX : TK_AND" << endl;	//debug
				$$.label = "&&";
				$$.tipo = &tipo_logic_operator;
			}
			| TK_OR {
				cout << "Regra OP_INFIX : TK_OR" << endl;	//debug
				$$.label = "||";
				$$.tipo = &tipo_logic_operator;
			}
			| TK_DIFERENTE  {
				cout << "Regra OP_INFIX : TK_DIFERENTE" << endl;	//debug
				$$.label = "!=";
				$$.tipo = &tipo_logic_operator;
			}
			| TK_IGUAL  {
				cout << "Regra OP_INFIX : TK_IGUAL" << endl;	//debug
				$$.label = "==";
				$$.tipo = &tipo_logic_operator;
			}
			| TK_MAIOR {
				cout << "Regra OP_INFIX : TK_MAIOR" << endl;	//debug
				$$.label = ">";
				$$.tipo = &tipo_logic_operator;
			}
			| TK_MENOR  {
				cout << "Regra OP_INFIX : TK_MENOR" << endl;	//debug
				$$.label = "<";
				$$.tipo = &tipo_logic_operator;
			}
			| TK_MAIORI  {
				cout << "Regra OP_INFIX : TK_MAIORI" << endl;	//debug
				$$.label = ">=";
				$$.tipo = &tipo_logic_operator;
			}
			| TK_MENORI  {
				cout << "Regra OP_INFIX : TK_MENORI" << endl;	//debug
				$$.label = "<=";
				$$.tipo = &tipo_logic_operator;
			}
			| TK_ATRIB {
				cout << "Regra OP_INFIX : TK_ATRIB" << endl;	//debug
				$$.label = "=";
				$$.tipo = &tipo_atrib_operator;
			}
			;

INCREMENTOS	: TK_ID SINAL_DUPL
			{
				cout << "Regra INCREMENTOS : TK_ID SINAL_DUPL" << endl;	//debug

				Tipo *tipo = findVar($1.label);
				if (tipo == NULL) yyerror("Variavel " + $1.label + " nao declarada");

				if(tipo != &tipo_int) yyerror("Variavel " + $1.label + " nao pode ser incrementada (tipo diferente de int)");

				string var1 = generateVarLabel();
				string var2 = generateVarLabel();

				declararLocal(&tipo_int, var1);
				declararLocal(&tipo_int, var2);

				$$.label = var2;
				$$.tipo = tipo;
				$$.traducao =	newLine(var2 + " = " + $1.label + ";\n\t" + var1 + " = 1") + 
								newLine(tipo->label + " = " + $1.label + $2.label + var1);
			}
			| SINAL_DUPL TK_ID
			{
				cout << "Regra INCREMENTOS : SINAL_DUPL TK_ID" << endl;	//debug

				Tipo *tipo = findVar($2.label);
				if (tipo == NULL) yyerror("Variavel " + $2.label + " nao declarada");

				if(tipo != &tipo_int) yyerror("Variavel " + $2.label + " nao pode ser incrementada (tipo diferente de int)");

				string var = generateVarLabel();
				declararLocal(&tipo_int, var);

				$$.label = $2.label;
				$$.tipo = tipo;
				$$.traducao = newLine(var + " = 1") + newLine($$.label + " = " + $$.label + " + " + var);

			}
			;
SINAL_DUPL	: TK_2MAIS
			{
				cout << "Regra SINAL_DUPL : TK_2MAIS" << endl;	//debug
				$$.label = " + ";
				$$.traducao = "";
			}
			| TK_2MENOS
			{
				cout << "Regra SINAL_DUPL : TK_2MENOS" << endl;	//debug
				$$.label = " - ";
				$$.traducao = "";
			}
			;
			
CONTROLE	: TK_IF E TK_DOTS BLOCO
			{
				//cout << $2.tipo->label << endl;	//debug
				cout << "Regra CONTROLE : TK_IF E TK_DOTS BLOCO" << endl;	//debug
				if($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);
					
				$$.traducao = $2.traducao + newLine(var + " = !" + $2.label) + newLine("if (" + var + ") goto " + fim);
				$$.traducao += $4.traducao + fim+":\n";
			}
			| TK_IF E TK_DOTS BLOCO CONTROLE_ALT
			{
				cout << "Regra CONTROLE : TK_IF E TK_DOTS BLOCO CONTROLE_ALT" << endl;	//debug

				if($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);

				$$.traducao = $2.traducao + newLine(var + " = !" + $2.label) + newLine("if (" + var + ") goto " + fim);
				$$.traducao += $4.traducao + newLine("goto " + $5.label) + fim + ":\n" + $5.traducao;
				
			}

			| LOOP
			{
				cout << "Regra CONTROLE : LOOP_INICIO LOOP LOOP_FIM" << endl;	//debug
				$$.traducao = $1.traducao;
			}

			;

CONTROLE_ALT: TK_ELSE TK_IF E TK_DOTS BLOCO
			{
				cout << "Regra CONTROLE_ALT : TK_ELSE TK_IF E TK_DOTS BLOCO" << endl;	//debug
				if($3.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);

				$$.label = fim;
				$$.traducao = $3.traducao + newLine(var + " = !" + $3.label) + newLine("if (" + var + ") goto " + fim);
				$$.traducao += $5.traducao + fim + ":\n" + "\n";

			}

			| TK_ELSE TK_IF E TK_DOTS BLOCO CONTROLE_ALT
			{
				cout << "Regra CONTROLE_ALT : TK_ELSE TK_IF E TK_DOTS BLOCO CONTROLE_ALT" << endl;	//debug
				if($3.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do else if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);

				$$.label = $6.label;
				$$.traducao = $3.traducao + newLine(var + " = !" + $3.label) + newLine("if (" + var + ") goto " + fim);
				$$.traducao += $5.traducao + newLine("goto " + $6.label) + fim + ":\n" + $6.traducao + "\n";

			}

			| TK_ELSE TK_DOTS BLOCO
			{
				cout << "Regra CONTROLE_ALT : TK_ELSE TK_DOTS BLOCO" << endl;	//debug
				$$.label = generateLabel();
				$$.traducao = $3.traducao + $$.label + ":\n";

			}


			;

LOOP 		: TK_FOR DECLARACAO ';' E ';' INCREMENTOS TK_DOTS BLOCO
			{
				cout << "Regra LOOP : TK_FOR DECLARACAO ; E ; INCREMENTOS TK_DOTS BLOCO" << endl;	//debug
				if ($4.tipo != &tipo_bool) yyerror("Tipo da expressao DEVE ser bool");

				string var = generateVarLabel();
				loopLabel* loop = getLoop(1);

				declararLocal(&tipo_int, var);

				$$.traducao = $2.traducao + "\n" + ident() + loop->inicio + ":\n" + $4.traducao + newLine(var + " = !" + $4.label);
				$$.traducao += newLine("if (" + var + ") goto " + loop->fim) + $8.traducao + loop->progressao + ":\n\n" + $6.traducao;
				$$.traducao += newLine("goto " + loop->inicio) + loop->fim + ":\n";

			}

			| TK_WHILE E TK_DOTS BLOCO 
			{
				cout << "Regra LOOP : TK_WHILE E TK_DOTS BLOCO" << endl;	//debug
				if ($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do while DEVE ser bool");
				string var = generateVarLabel();
				loopLabel* loop = getLoop(1);
					
				declararLocal(&tipo_int, var);
					
				$$.traducao = loop->inicio + ":\n" + loop->progressao + ":\n" + $2.traducao + newLine(var + " = !" + $2.label);
				$$.traducao += newLine("if (" + var + ") goto " + loop->fim) + $4.traducao + newLine("goto " + loop->inicio) + loop->fim + ":\n";
				
			}

			| TK_DO BLOCO TK_WHILE E TK_ENDL {
				cout << "Regra LOOP : TK_DO BLOCO TK_WHILE E TK_ENDL" << endl;	//debug
				if ($4.tipo != &tipo_bool) yyerror("Tipo da expressao do DO WHILE DEVE ser bool");

				loopLabel* loop = getLoop(1);

				$$.traducao = loop->inicio + ":\n" + loop->progressao + ":\n" + $4.traducao + $2.traducao + newLine("if (" + $4.label + ") goto " + loop->inicio);
				$$.traducao += loop->fim + ":\n";

			}
			;
			
LOOP_ALT	: TK_BREAK
			{
				cout << "Regra LOOP_ALT : TK_BREAK" << endl;	//debug
				loopLabel* loop = getLoop(1);
				
				if (loop == nullptr) yyerror("Break deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->fim);
				
			}
			| TK_BREAK TK_ALL {
				cout << "Regra LOOP_ALT : TK_BREAK TK_ALL" << endl;	//debug
				loopLabel* loop = getOuterLoop();
				
				if (loop == nullptr) yyerror("Break all deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->fim);
			}
			| TK_BREAK '(' TK_INT ')' {
				cout << "Regra LOOP_ALT : TK_BREAK ( TK_INT )" << endl;	//debug
				loopLabel* loop = getLoop(stoi($3.label));
				
				if (loop == nullptr) yyerror("Break com args deve ser usado dentro de um loop\nou\nargumento invalido");

				$$.traducao = "\tgoto " + loop->fim + ";\n";
			}
			| TK_CONTINUE {
				cout << "Regra LOOP_ALT : TK_CONTINUE" << endl;	//debug
				loopLabel* loop = getLoop(1);
				
				if (loop == nullptr) yyerror("Continue deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->progressao);
			}
			| TK_CONTINUE TK_ALL {
				cout << "Regra LOOP_ALT : TK_CONTINUE TK_ALL" << endl;	//debug
				loopLabel* loop = getOuterLoop();
				
				if (loop == nullptr) yyerror("Continue deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->progressao);
			}
			;

PRINT		: TK_PRINT PRINT_ALT
			{
				cout << "Regra PRINT : TK_PRINT PRINT_ALT" << endl;	//debug
				$$.traducao = $2.traducao + "\tcout" + $2.label;
			}
			;
			
PRINT_ALT	: E
			{
				cout << "Regra PRINT_ALT : E" << endl;	//debug
				$$.traducao = $1.traducao;
				$$.label = " << " + $1.label;
			}

			| E ',' PRINT_ALT
			{
				cout << "Regra PRINT_ALT : E , PRINT_ALT" << endl;	//debug
				$$.traducao = $1.traducao + $3.traducao;
				$$.label = " << " + $1.label + $3.label;
			}
			;

TIPO 		: TK_TIPO_INT
			{
				cout << "Regra TIPO : TK_TIPO_INT" << endl;	//debug
				$$.tipo = &tipo_int;
			}
			| TK_TIPO_FLOAT
			{
				cout << "Regra TIPO : TK_TIPO_FLOAT" << endl;	//debug
				$$.tipo = &tipo_float;
			}
			| TK_TIPO_BOOL
			{
				cout << "Regra TIPO : TK_TIPO_BOOL" << endl;	//debug
				$$.tipo = &tipo_bool;
			}
			| TK_TIPO_CHAR
			{
				cout << "Regra TIPO : TK_TIPO_CHAR" << endl;	//debug
				$$.tipo = &tipo_char;
			}
			| TK_TIPO_LIST
			{
				cout << "Regra TIPO : TK_TIPO_LIST" << endl;	//debug
				$$.tipo = &tipo_list;
			}
			;

%%

#include "lex.yy.c"

int main( int argc, char* argv[] )
{
	empContexto();
	cout << "parsing" << endl;	//debug
	yyparse();
	cout << "parsed" << endl;	//debug

	return 0;
}

void yyerror( string MSG )
{
	cout << "Linha " << line << ": " << MSG << endl;
	exit (0);
}
