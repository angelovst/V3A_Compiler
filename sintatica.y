%{
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "helper.h"
#define YYSTYPE atributos

%}

%token TK_INT TK_FLOAT TK_BOOL TK_CHAR
%token TK_MAIN TK_ID tK_IF TK_ELSE TK_FOR TK_DO TK_WHILE TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_BOOL TK_TIPO_CHAR TK_TIPO_LIST
%token TK_FIM TK_ERROR

%start S

%right TK_ATRIB
%left TK_OR TK_AND TK_NOT
%nonassoc TK_IGUAL TK_DIFERENTE
%nonassoc TK_MAIOR TK_MENOR TK_MAIORI TK_MENORI
%left TK_PLUS TK_MINUS
%left TK_MULT TK_DIV TK_MOD

%%

S 			: TK_MAIN '(' ')' MAIN
			{
				cout << "/*Compilador V3A*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" << "\t" + varDeclar + "\n" << $4.traducao << "\treturn 0;\n}" << endl;

			}
			;

MAIN		: '{' COMANDOS '}'
			{
				$$.traducao = $2.traducao;
			}
			;

ESCOPO_INICIO: {
				cout << "contexto empilhado" << endl;	//debug
				empContexto();
				
				$$.traducao = "";
				$$.label = "";
			};
			
ESCOPO_FIM	:	{
				cout << "contexto desempilhado" << endl;	//debug
				desempContexto();
				
				$$.traducao = "";
				$$.label = "";
			};


LOOP_INICIO	:{
				empLoop();
				empContexto();
				
				$$.traducao = "";
				$$.label = "";
			};
			
LOOP_FIM	:	{
				desempLoop();
				desempContexto();
				
				$$.traducao = "";
				$$.label = "";
			};

BLOCO		: ESCOPO_INICIO '{' COMANDOS '}' ESCOPO_FIM {
				$$.traducao = $3.traducao;
			};

COMANDOS	: COMANDO COMANDOS
			{
				cout << "comando traduzido" << endl;	//debug
				$$.traducao = $1.traducao + $2.traducao;
			}
			| {$$.traducao = "";}
			;

COMANDO 	: E ';'

			| TIPO TK_ID ';'
			{
				cout << "variavel declarada" << endl;	//debug
				std::map<string, atributos> *mapLocal = &varMap.back();

				if(mapLocal->find($2.label) != mapLocal->end()) {
					yyerror("Variavel ja declarada localmente");
				}
				else {
					$$.label = generateVarLabel();
					$$.tipo = $1.tipo;
					varDeclar += $1.traducao + $2.traducao + $$.tipo->label + " " + $$.label + ";\n\t";
					(*mapLocal)[$2.label] = $$;
				}
					

			}

			| TIPO TK_ID TK_ATRIB E ';'
			{	
				cout << "variavel declarada com atribuicao" << endl;	//debug
				std::map<string, atributos> *mapLocal = &varMap.back();
				if(mapLocal->find($2.label) != mapLocal->end()) {
        			yyerror("Variavel usada para atribuicao ja declarada");	
				}
				else if( $1.tipo->label == $4.tipo->label ){
					if (mapLocal->find($4.label) != mapLocal->end())	{
						$$.label = generateVarLabel();
						$$.tipo = $1.tipo;
						$$.traducao = "\t" + $$.label + " = " + (*mapLocal)[$4.label].label + ";\n";
						varDeclar += $1.traducao + $2.traducao + $$.tipo->label + " " + $$.label + ";\n\t";
						(*mapLocal)[$2.label] = $$;
					}
					else {
					$$.label = $4.label;
					$$.traducao = $1.traducao + $2.traducao + $4.traducao;
					$$.tipo = $1.tipo;
					(*mapLocal)[$2.label] = $$;
					}
				}
				else {
					yyerror("Atribuicao de tipos nao compativeis");
				}
			}
			| TK_ID TK_ATRIB E ';'
			{
				cout << "variavel atribuida" << endl;	//debug
				std::map<string, atributos> *mapLocal = &varMap.back();
				
				if(mapLocal->find($1.label) != mapLocal->end()) {
					if((*mapLocal)[$1.label].tipo->label == $3.tipo->label) {
						$$.traducao = $3.traducao + "\t" + (*mapLocal)[$1.label].label + " = " + $3.label + ";\n";
					}
					else {
						yyerror("Tipos nao compativeis");
					}
				}
				else {
					$$.label = $3.label;
					$$.tipo = $3.tipo;
					$$.traducao = $3.traducao;
					(*mapLocal)[$1.label] = $$;

				}
			}
			
			| ATRIBUICAO
			
			| CONTROLE

			;

E 			: E OP_INFIX E {
				cout << "operacao infixa executada" << endl;	//debug
				$$.label = generateVarLabel();
				$$.traducao = $1.traducao + $3.traducao;
				string var1, var2;
				string cast = implicitCast (&$1, &$2, &var1, &var2);
				
				$$.traducao += $$.label + " = " + var1 + $2.traducao + var2 + ";\n";
				
			}
			| '(' TIPO ')' E
			{	
				cout << "cast executado" << endl;	//debug
				$$.label = generateVarLabel();
				varDeclar += $2.tipo->label + " " + $$.label + ";\n\t";
				$$.tipo = $2.tipo;
				$$.traducao = $4.traducao + "\t" + $$.label + " =" + '(' + $2.tipo->label + ')' + $4.label + ";\n";
			}

			| '(' E ')'
			{
				cout << "parentizacao feita" << endl;	//debug
				$$.label = $2.label; //generateVarLabel();
				$$.traducao = $2.traducao;// + "\t" + $$.label + " = " + $2.label + ";\n";
			}
			| '-' E
			{
				cout << "inversao feita" << endl;	//debug
				$$.label = generateVarLabel();
				$$.traducao = $2.traducao + "\t" + $$.label + " = " + " - " + $2.label + ";\n";
			}
			| TK_INT
			{
				$$.label = generateVarLabel();
				varDeclar += "int " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = &tipo_int;
			}
			| TK_FLOAT
			{
				$$.label = generateVarLabel();
				varDeclar += "float " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = &tipo_float;
			}
			| TK_BOOL
			{
				string aux;
				
				if($1.label == "true") {
					aux = "1";
				}
				else {
					aux = "0";
				}

				$$.label = generateVarLabel();
				varDeclar += "unsigned char " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + aux + ";\n";
				$$.tipo = &tipo_bool;

			}
			| TK_CHAR
			{
				$$.label = generateVarLabel();
				varDeclar += "char " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label +  ";\n";
				$$.tipo = &tipo_char;
			}
			| TK_ID
			{
				atributos *id = findVar($1.label);
				if(id != nullptr) {
					$$.tipo = id->tipo;
					$$.label = $1.label;
				}
				/*if(varMap.find($1.label) != varMap.end()) {
        			$$.tipo = varMap[$1.label].tipo;
        			$$.label = varMap[$1.label].label;
				}*/
				else {
					$$.label = generateVarLabel();
					$$.traducao = "\t" + $$.label + " = " + $1.label + ":\n";
				}
			}
			
			
			;
			
OP_INFIX	: TK_PLUS
			{
				$$.label = "+";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_MINUS {
				$$.label = "-";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_MULT {
				$$.label = "*";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_DIV {
				$$.label = "/";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_MOD {
				$$.label = "%";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_AND  {
				$$.label = "&&";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_OR {
				$$.label = "||";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_DIFERENTE  {
				$$.label = "!=";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_IGUAL  {
				$$.label = "==";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_MAIOR {
				$$.label = ">";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_MENOR  {
				$$.label = "<";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_MAIORI  {
				$$.label = ">=";
				$$.tipo = &tipo_inf_operator;
			}
			| TK_MENORI  {
				$$.label = "<=";
				$$.tipo = &tipo_inf_operator;
			}
			;
			
CONTROLE	: TK_IF E TK_DOTS BLOCO
			{
				if($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLoopLabel();

				varDeclar += "int " + var + ";\n\t";
					
					$$.traducao = "\n" + $2.traducao + 
						"\t" + var + " = !" + $2.label + ";\n" +
						"\tif (" + var + ") goto " + fim + ";\n\n" +
						$4.traducao +
						"\n\t" + fim + ":\n\n";
			}
			| TK_IF E TK_DOTS BLOCO CONTROLE_ALT
			{

				if($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLoopLabel();

				varDeclar += "int " + var + ";\n\t";

				$$.traducao = "\n" + $2.traducao + 
						"\t" + var + " = !" + $2.label + ";\n" +
						"\tif (" + var + ") goto " + fim + ";\n\n" +
						$4.traducao +
						"\tgoto " + $5.label + ";\n\n" +
						"\t" + fim + ":" + $5.traducao;
				
			}

			| LOOP_INICIO LOOP LOOP_FIM
			{
				$$.traducao = $2.traducao;
			}

			;

CONTROLE_ALT: TK_ELSE TK_IF E TK_DOTS BLOCO
			{
				if($3.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLoopLabel();

				varDeclar += "int " + var + ";\n\t";

				$$.label = fim;
				$$.traducao = "\n" + $3.traducao + 
						"\t" + var + " = !" + $3.label + ";\n\n" +
						"\tif (" + var + ") goto " + fim + ";\n" +
						$5.traducao +
						"\n\t" + fim + ":\n";

			}

			| TK_ELSE TK_IF E TK_DOTS BLOCO CONTROLE_ALT
			{
				if($3.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do else if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLoopLabel();

				varDeclar += "int " + var + ";\n\t";

				$$.label = $6.label;
				$$.traducao = "\n" + $3.traducao + 
						"\t" + var + " = !" + $3.label + ";\n\n" +
						"\tif (" + var + ") goto " + fim + ";\n" +
						$5.traducao +
						"\n\tgoto " + $6.label + ";\n" +
						"\n\t" + fim + ":" + $6.traducao;

			}

			| TK_ELSE TK_DOTS BLOCO
			{
				$$.label = generateLoopLabel();
				$$.traducao = "\n" + $3.traducao + "\n\t" + $$.label + ":\n";

			}


			;


ATRIBUICAO 	: TIPO TK_ID ';'
			{
				std::map<string, atributos> *mapLocal = &varMap.back();

				if(mapLocal->find($2.label) != mapLocal->end()) {
					yyerror("Variavel ja declarada localmente");
				}
				else {
					$$.label = generateVarLabel();
					$$.tipo = $1.tipo;
					varDeclar += $1.traducao + $2.traducao + $$.tipo->label + " " + $$.label + ";\n\t";
					(*mapLocal)[$2.label] = $$;
				}
					

			}

			| TIPO TK_ID TK_ATRIB E ';'
			{	
				std::map<string, atributos> *mapLocal = &varMap.back();
				if(mapLocal->find($2.label) != mapLocal->end()) {
        			yyerror("Variavel usada para atribuicao ja declarada");	
				}
				else if( $1.tipo == $4.tipo ){
					if (mapLocal->find($4.label) != mapLocal->end())	{
						$$.label = generateVarLabel();
						$$.tipo = $1.tipo;
						$$.traducao = "\t" + $$.label + " = " + (*mapLocal)[$4.label].label + ";\n";
						varDeclar += $1.traducao + $2.traducao + $$.tipo->label + " " + $$.label + ";\n\t";
						(*mapLocal)[$2.label] = $$;
					}
					else {
					$$.label = $4.label;
					$$.traducao = $1.traducao + $2.traducao + $4.traducao;
					$$.tipo = $1.tipo;
					(*mapLocal)[$2.label] = $$;
					}
				}
				else {
					yyerror("Atribuicao de tipos nao compativeis");
				}
			}
			| TK_ID TK_ATRIB E ';'
			{
				std::map<string, atributos> *mapLocal = &varMap.back();
				
				if(mapLocal->find($1.label) != mapLocal->end()) {
					if((*mapLocal)[$1.label].tipo == $3.tipo) {
						$$.traducao = $3.traducao + "\t" + (*mapLocal)[$1.label].label + " = " + $3.label + ";\n";
					}
					else {
						yyerror("Tipos nao compativeis");
					}
				}
				else {
					$$.label = $3.label;
					$$.tipo = $3.tipo;
					$$.traducao = $3.traducao;
					(*mapLocal)[$1.label] = $$;

				}
			}
			;

LOOP 		: TK_WHILE E TK_DOTS BLOCO 
			{
				if ($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do while DEVE ser bool");

				string var = generateVarLabel();
				loopLabel* loop = getLoop();
					
				varDeclar += "int " + var + ";\n\t";
					
				$$.traducao = "\t" + loop->inicio + ":\n\t" 
					+ loop->progressao + ":\n" + $2.traducao
					+ "\t" + var + " = !" + $2.label + ";\n" +
					"\tif (" + var + ") goto " + loop->fim + ";\n" +
					$4.traducao +
					"\tgoto " + loop->inicio + ";\n\t" + loop->fim + ":\n";
				
			}
			;

TIPO 		: TK_TIPO_INT
			{
				$$.tipo = &tipo_int;
			}
			| TK_TIPO_FLOAT
			{
				$$.tipo = &tipo_float;
			}
			| TK_TIPO_BOOL
			{
				$$.tipo = &tipo_bool;
			}
			| TK_TIPO_CHAR
			{
				$$.tipo = &tipo_char;
			}
			| TK_TIPO_LIST
			{
				$$.tipo = &tipo_list;
			}	
			;

%%

#include "lex.yy.c"

using namespace std;

int yylex(void);
void yyerror(string);

int yyparse();

int main( int argc, char* argv[] )
{
	map<string, atributos> mapaGlobal;
	varMap.push_back(mapaGlobal);

	cout << "parsing" << endl;	//debug
	yyparse();
	cout << "parsed" << endl;	//debug

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}
