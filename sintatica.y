%{
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#define YYSTYPE atributos
#define OUTPUT_INTERMEDIARIO "-i"

using namespace std;

int yylex(void);
void yyerror(string);

int yyparse (void);

fstream output;
FILE *input;

%}

%token TK_INT TK_FLOAT TK_BOOL TK_CHAR TK_STR
%token TK_IF TK_BLOCO_ABRIR TK_BLOCO_FECHAR TK_ELSE TK_FOR TK_STEPPING TK_FROM TK_TO TK_DO TK_WHILE TK_BREAK TK_ALL TK_CONTINUE TK_PRINT
%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_BOOL TK_TIPO_CHAR TK_TIPO_LIST TK_TIPO_STR
%token TK_DOTS
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

S 			: COMANDOS
			{
				cout << "Regra S : COMANDOS" << endl;	//debug
				string globalDeclar = contextStack.begin()->declar;
				output << "/*Compilador V3A*/\n" << "#include <iostream>\n#include<stdlib.h>\n\nint main(int argc, char **args)\n{\n" << "\t\n" << globalDeclar << "\n" << $1.traducao << "\n\treturn 0;\n}" << endl;

			}
			;		

BLOCO	: ESCOPO_INICIO COMANDOS ESCOPO_FIM
		{
			cout << "Regra BLOCO : COMANDOS" << endl;	//debug
			string declar = contextStack.begin()->declar;
			desempContexto();
			
			//$$.traducao = "";
			$$.traducao = ident() + "{\n" + declar + "\n" + $2.traducao + ident() + "}";
			$$.label = "";
		}
		;
			
ESCOPO_INICIO	:	TK_BLOCO_ABRIR TK_DOTS
				{
					cout << "Regra ESCOPO_INICIO : TK_BLOCO_ABRIR" << endl;	//debug
					empContexto();
				}
				;
			
ESCOPO_FIM	:	TK_BLOCO_FECHAR
			{
				cout << "Regra ESCOPO_FIM : TK_BLOCO_FECHAR" << endl;	//debug
			}
			|
			;

COMANDOS	: COMANDO COMANDOS
			{
				cout << "Regra COMANDOS : COMANDO COMANDOS" << endl;	//debug
				$$.traducao = $1.traducao + $2.traducao;
			}
			|
			{
				$$.traducao = "";
				cout << "Regra COMANDOS : vazio" << endl;
			}	
			;

COMANDO 	: E
			{
				cout << "Regra COMANDO : " << $1.label << endl;
				$$.traducao = $1.traducao;
			}

			| DECLARACAO
			{
				cout << "Regra COMANDO : DECLARACAO" << endl;
				$$.traducao = $1.traducao;
			}
			
			| BLOCO
			{
				cout << "Regra COMANDO : ESCOPO_INICIO BLOCO ESCOPO_FIM" << endl;
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
			| PRINT
			{
				cout << "Regra COMANDO : PRINT" << endl;
				$$.traducao = $1.traducao;
			}
			| TK_ENDL
			;

E 			: E OP_INFIX E {
				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug
				void *args[4];
				string traducao;
				
				$$.label = generateVarLabel();	//retorno
				if ($2.tipo->retornos == NULL) {	//caso retorno nao seja especificado inferir o tipo
					$$.tipo = resolverTipo($1.tipo, $3.tipo);
				} else {
					$$.tipo = (*$2.tipo->retornos)[0];
				}
				declararLocal($$.tipo, $$.label);
				$$.traducao = $1.traducao + $3.traducao;
				
				args[0] = &$1;
				args[1] = &$3;
				args[2] = &$$.label;
				args[3] = &$2.label;
				
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
				cout << "Regra E : " << $1.label << endl;	//debug
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
				cout << "Regra E : " << $1.label << endl;	//debug
				$$.tipo = findVar($1.label);
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
				void *args[3] = {&$2, &$4, NULL};
				
				$$.tipo = $1.tipo;
				$2.tipo = $1.tipo;
				atrib = traducaoAtribuicao((void*)args);
				if (atrib == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->label + " e " + $4.tipo->label);
				}
				$$.traducao = $1.traducao + $4.traducao + atrib;
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
			
CONTROLE	: TK_IF E BLOCO
			{
				//cout << $2.tipo->label << endl;	//debug
				cout << "Regra CONTROLE : TK_IF E BLOCO" << endl;	//debug
				if($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);
				
				$$.traducao = "\n" + $2.traducao + newLine(var + " = !" + $2.label) + newLine("if (" + var + ") goto " + fim) + $3.traducao + ident() + fim+":\n";
			}
			| TK_IF E BLOCO CONTROLE_ALT
			{
				cout << "Regra CONTROLE : TK_IF E BLOCO CONTROLE_ALT" << endl;	//debug

				if($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);

				$$.traducao = "\n" + $2.traducao + newLine(var + " = !" + $2.label) + newLine("if (" + var + ") goto " + fim);
				$$.traducao += $3.traducao + newLine("goto " + $4.label) + ident() + fim + ":\n" + $4.traducao;
				
			}

			| LOOP
			{
				cout << "Regra CONTROLE : LOOP_INICIO LOOP LOOP_FIM" << endl;	//debug
				$$.traducao = $1.traducao;
			}
			;

CONTROLE_ALT: TK_ELSE CONTROLE
			{
				cout << "Regra CONTROLE_ALT : TK_ELSE CONTROLE" << endl;	//debug
				$$.label = generateLabel();
				$$.traducao = $2.traducao + ident() + $$.label + ":\n"; 
			}
			| TK_ELSE BLOCO
			{
				cout << "Regra CONTROLE_ALT : TK_ELSE BLOCO" << endl;	//debug
				$$.label = generateLabel();
				$$.traducao = $2.traducao + $$.label + ":\n";
			}
			;
			
FOR	: TK_FOR
	{
		cout << "Regra FOR : TK_FOR" << endl;	//debug
		empLoop();
		$$.traducao = "\n" + ident() + "//FOR LOOP\n" + ident() + "{\n";
		empContexto();	//separar expressoes dentro da declaracao do for do resto
	}
	;

WHILE	: TK_WHILE
		{
			cout << "Regra WHILE : TK_WHILE" << endl;	//debug
			empLoop();
			$$.traducao = "\n" + ident() + "//WHILE LOOP\n" + ident() + "{\n";
			empContexto();	//separar expressoes dentro da declaracao do for do resto
		}
		;

LOOP 		: FOR TK_ID TK_FROM E TK_TO E BLOCO
			{
				cout << "Regra LOOP : TK_ID TK_FROM E TK_TO E BLOCO" << endl;	//debug
				if (!isNumero($4.tipo)) yyerror("Expressao do limite inferior deve retornar numero");
				if (!isNumero($6.tipo)) yyerror("Expressao do limite superior deve retornar numero");
				
				Tipo *i, *final;
				atributos *castTo;
				string iLabel;
				string limitInf, limitSup; 
				string check = generateVarLabel();
				string inc = generateVarLabel();
				string prevValue = generateVarLabel();
				string checkElse = generateLabel();
				string checkEnd = generateLabel();
				
				//cout << "declaring vars" << endl;	//debug;
				final = resolverTipo($4.tipo, $6.tipo);
				castTo = (final == $4.tipo) ? &$4 : &$6;
				
				i = findVar($2.label);
				if (i == NULL) {
					$2.tipo = final;
					declararLocal($2.tipo, $2.label);
				} else if (!isNumero(i)) {
					yyerror("Variavel " + $2.label + " deve armazenar numero");
				} else {
					$2.tipo = i;
					final = resolverTipo(final, $2.tipo);
					castTo = (final == $2.tipo) ? &$2 : castTo;
				}
				declararLocal(&tipo_bool, check);
				declararLocal(final, inc);
				declararLocal(final, prevValue);
				
				LoopLabel* loop = getLoop(0);
				
				$$.traducao = $1.traducao + contextStack.begin()->declar + "\n";
				$$.traducao += $4.traducao + $6.traducao;
				
				//cout << "casting vars" << endl;	//debug
				//escrever casts caso necessarios
				$$.traducao += implicitCast(castTo, &$2, &castTo->label, &iLabel);
				$$.traducao += implicitCast(castTo, &$4, &castTo->label, &limitInf);
				$$.traducao += implicitCast(castTo, &$6, &castTo->label, &limitSup);
				//cout << "counting var casted" << endl;	//debug
				
				//cout << "checking increment" << endl;	//debug
				//checar se incremento deve ser positivo ou negativo
				$$.traducao += ident() + "//checar variavel de incremento\n" + newLine(check + " = " + limitInf + "<" + limitSup);
				$$.traducao += newLine("if (" + check + ") goto " + checkElse);
				//incremento negatvo caso limitInf > limitSup
				$$.traducao += "\t" + newLine(inc + " = " + "-1");
				$$.traducao += "\t" + newLine("goto " + checkEnd);
				//incremento positivo caso limitInf < limitSup
				$$.traducao += ident() + checkElse + ":\n";
				$$.traducao += "\t" + newLine(inc + " = " + "1");
				$$.traducao += ident() + checkEnd + ":\n\n";
				
				//cout << "translating loop" << endl;	//debug
				$$.traducao += newLine(iLabel + " = " + limitInf);	//inicializar variavel de contagem
				//escrever bloco
				$$.traducao += ident() + "//laco de repeticao\n" + ident() + loop->inicio + ":\n" + newLine(prevValue + " = " + iLabel);
				$$.traducao += newLine(check + " = " + iLabel + ">=" + limitSup);
				$$.traducao += newLine("if (" + check + ") goto " + loop->fim) + $7.traducao + loop->progressao + ":\n";
				//incrementar variavel de contagem
				$$.traducao += newLine(iLabel + " = " + prevValue + "+" + inc);
				$$.traducao += newLine("goto " + loop->inicio) + ident() + loop->fim + ":\n";
				
				desempLoop();
				desempContexto();
				$$.traducao += ident() + "}\n";
				//cout << "loop translated" << endl;	//debug

			}
			| FOR TK_ID TK_STEPPING E TK_FROM E TK_TO E BLOCO
			{
				cout << "Regra LOOP : TK_ID TK_STEPPING E TK_FROM E TK_TO E BLOCO" << endl;	//debug
				if (!isNumero($4.tipo)) yyerror("Expressao do step deve retornar numero");
				if (!isNumero($6.tipo)) yyerror("Expressao do limite inferior deve retornar numero");
				if (!isNumero($8.tipo)) yyerror("Expressao do limite superior deve retornar numero");
				
				Tipo *i, *final;
				atributos *castTo;
				string iLabel;
				string limitInf, limitSup; 
				string check = generateVarLabel();
				string inc = generateVarLabel();
				string prevValue = generateVarLabel();
				
				//cout << "declaring vars" << endl;	//debug;
				final = resolverTipo($4.tipo, $6.tipo);
				castTo = (final == $4.tipo) ? &$4 : &$6;
				final = resolverTipo(final, $8.tipo);
				castTo = (final == $8.tipo) ? &$8 : castTo;
				
				i = findVar($2.label);
				if (i == NULL) {
					$2.tipo = final;
					declararLocal($2.tipo, $2.label);
				} else if (!isNumero(i)) {
					yyerror("Variavel " + $2.label + " deve armazenar numero");
				} else {
					$2.tipo = i;
					final = resolverTipo(final, $2.tipo);
					castTo = (final == $2.tipo) ? &$2 : castTo;
				}
				declararLocal(&tipo_bool, check);
				declararLocal(final, inc);
				declararLocal(final, prevValue);
				
				LoopLabel* loop = getLoop(0);
				
				$$.traducao = $1.traducao + contextStack.begin()->declar + "\n";
				$$.traducao += $4.traducao + $6.traducao + $8.traducao;
				
				//cout << "casting vars" << endl;	//debug
				//escrever casts caso necessarios
				$$.traducao += implicitCast(castTo, &$2, &castTo->label, &iLabel);
				$$.traducao += implicitCast(castTo, &$4, &castTo->label, &inc);
				$$.traducao += implicitCast(castTo, &$6, &castTo->label, &limitInf);
				$$.traducao += implicitCast(castTo, &$8, &castTo->label, &limitSup);
				//cout << "counting var casted" << endl;	//debug
				
				//cout << "translating loop" << endl;	//debug
				$$.traducao += newLine(iLabel + " = " + limitInf);	//inicializar variavel de contagem
				//escrever bloco
				$$.traducao += ident() + "//laco de repeticao\n" + ident() + loop->inicio + ":\n" + newLine(prevValue + " = " + iLabel);
				$$.traducao += newLine(check + " = " + iLabel + ">=" + limitSup);
				$$.traducao += newLine("if (" + check + ") goto " + loop->fim) + $9.traducao + loop->progressao + ":\n";
				//incrementar variavel de contagem
				$$.traducao += newLine(iLabel + " = " + prevValue + "+" + inc);
				$$.traducao += newLine("goto " + loop->inicio) + ident() + loop->fim + ":\n";
				
				desempLoop();
				desempContexto();
				$$.traducao += ident() + "}\n";
				//cout << "loop translated" << endl;	//debug

			} 

			| WHILE E BLOCO 
			{
				cout << "Regra LOOP : TK_WHILE E BLOCO" << endl;	//debug
				if ($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do while DEVE ser bool");
				string var = generateVarLabel();
				LoopLabel* loop = getLoop(0);
					
				declararLocal(&tipo_bool, var);
				
				$$.traducao = $1.traducao + contextStack.begin()->declar + "\n";
				$$.traducao += ident() + loop->inicio + ":\n" + $2.traducao + newLine(var + " = !" + $2.label);
				$$.traducao += newLine("if (" + var + ") goto " + loop->fim) + $3.traducao + newLine("goto " + loop->inicio) + ident() + loop->fim + ":\n";
				desempLoop();
				desempContexto();
				$$.traducao += ident() + "}\n";
				
			}

			| BLOCO TK_WHILE E TK_ENDL {
				cout << "Regra LOOP : TK_DO BLOCO TK_WHILE E TK_ENDL" << endl;	//debug
				if ($4.tipo != &tipo_bool) yyerror("Tipo da expressao do DO WHILE DEVE ser bool");

				LoopLabel* loop = getLoop(0);

				$$.traducao = loop->inicio + ":\n" + loop->progressao + ":\n" + $3.traducao + $1.traducao + newLine("if (" + $3.label + ") goto " + loop->inicio);
				$$.traducao += loop->fim + ":\n";
				desempLoop();

			}
			;
			
LOOP_ALT	: TK_BREAK
			{
				cout << "Regra LOOP_ALT : TK_BREAK" << endl;	//debug
				LoopLabel* loop = getLoop(0);
				
				if (loop == nullptr) yyerror("Break deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->fim);
				
			}
			| TK_BREAK TK_ALL {
				cout << "Regra LOOP_ALT : TK_BREAK TK_ALL" << endl;	//debug
				LoopLabel* loop = getOuterLoop();
				
				if (loop == nullptr) yyerror("Break all deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->fim);
			}
			| TK_BREAK '(' TK_INT ')' {
				cout << "Regra LOOP_ALT : TK_BREAK ( TK_INT )" << endl;	//debug
				LoopLabel* loop = getLoop(stoi($3.label));
				
				if (loop == NULL) yyerror("Break com deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->fim);
			}
			| TK_CONTINUE {
				cout << "Regra LOOP_ALT : TK_CONTINUE" << endl;	//debug
				LoopLabel* loop = getLoop(0);
				
				if (loop == NULL) yyerror("Continue deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->progressao);
			}
			| TK_CONTINUE TK_ALL {
				cout << "Regra LOOP_ALT : TK_CONTINUE TK_ALL" << endl;	//debug
				LoopLabel* loop = getOuterLoop();
				
				if (loop == NULL) yyerror("Continue deve ser usado dentro de um loop");

				$$.traducao = newLine("goto " + loop->progressao);
			}
			;

PRINT		: TK_PRINT PRINT_ALT
			{
				cout << "Regra PRINT : TK_PRINT PRINT_ALT" << endl;	//debug
				$$.traducao = $2.traducao + newLine("std::cout" + $2.label);
			}
			;
			
PRINT_ALT	: E	TK_ENDL
			{
				cout << "Regra PRINT_ALT : E TK_ENDL" << endl;	//debug
				if (findVar($1.label) == NULL) {
					yyerror("Variavel " + $1.label + " nao declarada");
				}
				$$.traducao = $1.traducao;
				$$.label = " << " + $1.label + " << std::endl";
			}

			| E ',' PRINT_ALT
			{
				cout << "Regra PRINT_ALT : E , PRINT_ALT" << endl;	//debug
				if (findVar($1.label) == NULL) {
					yyerror("Variavel " + $1.label + " nao declarada");
				}
				$$.traducao = $1.traducao + $3.traducao;
				$$.label = " << " + $1.label + " << \" \"" + $3.label;
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

void closeFiles (void) {
	fclose(input);
	output.close();
}

int main (int argc, char **args) {
	string inputFileName, outputFileName, outputCompiled;

	if (argc < 3) {
		cout << "Especifique os arquivos de entrada e saida" << endl;
		return 1;
	}
	
	if (string(args[1]) == OUTPUT_INTERMEDIARIO) {
		inputFileName = args[2];
		outputFileName = string(args[3]) + ".c";
	} else {
		inputFileName = args[1];
		outputCompiled = args[2];
		outputFileName = outputCompiled + ".c";
	}
	
	input = fopen(inputFileName.c_str(), "r");
	if (input == NULL) {
		cout << "Arquivo \"" << inputFileName << "\" nao pode ser aberto. Certifique-se de que o arquivo existe" << endl;
		return 2;
	}
	yyin = input;
	
	output.open(outputFileName, fstream::out | fstream::trunc);
	if (output.fail()) {
		fclose(input);
		cout << "Arquivo \"" << outputFileName << "\" nao pode ser aberto" << endl;
		return 3;
	}
	
	empContexto();
	//cout << "parsing" << endl;	//debug
	yyparse();
	//cout << "parsed" << endl;	//debug
	desempContexto();
	
	closeFiles();
	if (string(args[1]) != OUTPUT_INTERMEDIARIO) {
		string compile = "g++ -std=c++11 " + outputFileName + " -o " + outputCompiled;
		//system("stty -echo");
		system(compile.c_str());
		//system("stty echo");
		remove(outputFileName.c_str());	
	}	
	return 0;
	
}

void yyerror( string MSG ) {
	cout << "Linha " << line << ": " << MSG << endl;
	closeFiles();
	exit (0);
}
