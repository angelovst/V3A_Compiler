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
%token TK_FIM TK_ERROR

%start S

%right TK_ATRIB
%left TK_OR TK_AND TK_NOT
%nonassoc TK_IGUAL TK_DIFERENTE
%nonassoc TK_MAIOR TK_MENOR TK_MAIORI TK_MENORI
%left TK_PLUS TK_MINUS
%left TK_MULT TK_DIV TK_MOD
%right TK_2MAIS TK_2MENOS

%%

S 			: TK_MAIN '(' ')' MAIN
			{
				cout << "/*Compilador V3A*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" << "\t" + varDeclar + "\n" << $4.traducao << "\treturn 0;\n}" << endl;

			}
			;

MAIN		: TK_BLOCO_ABRIR COMANDOS TK_BLOCO_FECHAR
			{
				$$.traducao = $2.traducao;
			}
			;

ESCOPO_INICIO: {
				//cout << "contexto empilhado" << endl;	//debug
				empContexto();
				
				$$.traducao = "";
				$$.label = "";
			};
			
ESCOPO_FIM	:	{
				//cout << "contexto desempilhado" << endl;	//debug
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

BLOCO		: ESCOPO_INICIO TK_BLOCO_ABRIR COMANDOS TK_BLOCO_FECHAR ESCOPO_FIM {
				$$.traducao = $3.traducao;
			};

COMANDOS	: COMANDO COMANDOS
			{
				//cout << "comando traduzido" << endl;	//debug
				$$.traducao = $1.traducao + $2.traducao;
			}
			| {$$.traducao = "";}
			;

COMANDO 	: E ';'

			| ATRIBUICAO ';'
			{
				$$.traducao = $1.traducao;
			}
			
			| CONTROLE
			{
				$$.traducao = $1.traducao;
			}

			| LOOP_ALT ';'
			{
				$$.traducao = $1.traducao;
			}
			| PRINT ';'
			{
				$$.traducao = $1.traducao + " << endl;\n";
			}
			;

E 			: E OP_INFIX E {
				//cout << "operacao infixa executada" << endl;	//debug
				$$.label = generateVarLabel();
				varDeclar += $$.tipo->label + " " + $$.label + ";\n\t";
				$$.traducao = $1.traducao + $3.traducao;
				string args[3];
				string var1, var2;
				string cast = implicitCast (&$1, &$3, &var1, &var2);
				
				if (cast == INVALID_CAST) {
					yyerror("Impossivel converter " + $1.tipo->label + " e " + $3.tipo->label);
				}
				
				args[0] = var1;
				args[1] = $2.label;
				args[2] = var2;
				$$.traducao += cast + "\t" + $$.label + " = " + $2.tipo->traducaoParcial((void*)args) + ";\n";
				
			}
			| '(' TIPO ')' E
			{	
				//cout << "cast executado" << endl;	//debug
				$$.label = generateVarLabel();
				varDeclar += $2.tipo->label + " " + $$.label + ";\n\t";
				$$.tipo = $2.tipo;
				$$.traducao = $4.traducao + "\t" + $$.label + " =" + '(' + $2.tipo->label + ')' + $4.label + ";\n";
			}

			| '(' E ')'
			{
				//cout << "parentizacao feita" << endl;	//debug
				$$.label = $2.label; //generateVarLabel();
				$$.traducao = $2.traducao;// + "\t" + $$.label + " = " + $2.label + ";\n";
			}
			| '-' E
			{
				//cout << "inversao feita" << endl;	//debug
				$$.label = generateVarLabel();
				$$.traducao = $2.traducao + "\t" + $$.label + " = " + " - " + $2.label + ";\n";
			}
			| INCREMENTOS

			| TK_TIPO_INT
			{
				$$.label = generateVarLabel();
				varDeclar += "int " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = &tipo_int;
			}
			| TK_TIPO_FLOAT
			{
				$$.label = generateVarLabel();
				varDeclar += "float " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = &tipo_float;
			}
			| TK_TIPO_BOOL
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
			| TK_TIPO_CHAR
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

INCREMENTOS	: TK_ID SINAL_DUPL {

				atributos *id = findVar($1.label);
				if ( id == nullptr ) yyerror("Variavel " + $1.label + " nao declarada para ser incrementada");

				if(id->tipo != &tipo_int) yyerror("Variavel " + $1.label + " nao pode ser incrementada (tipo diferente de int)");

				string var1 = generateVarLabel();
				string var2 = generateVarLabel();

				varDeclar += "int " + var1 + ";\n\t";
				varDeclar += "int " + var2 + ";\n\t";

				$$.label = var2;
				$$.tipo = id->tipo;
				$$.traducao = "\t" + var2 + " = " + id->label + ";\n\t" + var1 + " = 1;\n\t" + 
								id->label + " = " + id->label + $2.label + var1 + ";\n";
			}
			| SINAL_DUPL TK_ID {

				atributos *id = findVar($2.label);
				if ( id == nullptr ) yyerror("Variavel " + $2.label + " nao declarada para ser incrementada");

				if( id->tipo != &tipo_int ) yyerror("Variavel " + $2.label + " nao pode ser incrementada (tipo diferente de int)");

				string var = generateVarLabel();
				varDeclar += "int " + var + ";\n\t";

				$$.label = id->label;
				$$.tipo = id->tipo;
				$$.traducao = "\t" + var + " = 1;\n\t" + $$.label + " = " + $$.label + " + " + var + ";\n";

			}
			;
SINAL_DUPL	: TK_2MAIS {
				$$.label = " + ";
				$$.traducao = "";
			}
			| TK_2MENOS {
				$$.label = " - ";
				$$.traducao = "";
			}
			;
			
CONTROLE	: TK_IF E TK_DOTS BLOCO
			{
				cout << $2.tipo->label << endl;
				if($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

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
				string fim = generateLabel();

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
				string fim = generateLabel();

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
				string fim = generateLabel();

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
				$$.label = generateLabel();
				$$.traducao = "\n" + $3.traducao + "\n\t" + $$.label + ":\n";

			}


			;


ATRIBUICAO 	: TIPO TK_ID
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

			| TIPO TK_ID TK_ATRIB E
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
			| TK_ID TK_ATRIB E
			{
				atributos* atr;
				if ( atr = findVar($1.label) ) {
					if(atr->tipo == $3.tipo) {
						$$.traducao = $3.traducao + "\t" + atr->label + " = " + $3.label + ";\n";
					}
					else yyerror("atr de tipos incompativeis");
				}
				else {
					std::map<string, atributos> *mapLocal = &varMap.back();
					$$.label = $3.label;
					$$.tipo = $3.tipo;
					$$.traducao = $3.traducao;
					(*mapLocal)[$1.label] = $$;

				}
			}
			;

LOOP 		: TK_FOR ATRIBUICAO ';' E ';' INCREMENTOS TK_DOTS BLOCO {
				if ($4.tipo != &tipo_bool) yyerror("Tipo da expressao do for DEVE ser bool");

				string var = generateVarLabel();
				loopLabel* loop = getLoop(1);

				varDeclar += "int " + var + ";\n\t";

				$$.traducao = $2.traducao + "\n\t" + loop->inicio + ":\n" + $4.traducao + 
						"\t" + var + " = !" + $4.label + ";\n" +
						"\tif (" + var + ") goto " + loop->fim + ";\n\n" +
						$8.traducao + "\t" + loop->progressao + ":\n\n" + $6.traducao +
						"\tgoto " + loop->inicio + ";\n\n\t" + 
						loop->fim + ":\n";

			}

			|TK_WHILE E TK_DOTS BLOCO 
			{
				if ($2.tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do while DEVE ser bool");
				string var = generateVarLabel();
				loopLabel* loop = getLoop(1);
					
				varDeclar += "int " + var + ";\n\t";
					
				$$.traducao = "\t" + loop->inicio + ":\n\t" 
					+ loop->progressao + ":\n" + $2.traducao
					+ "\t" + var + " = !" + $2.label + ";\n" +
					"\tif (" + var + ") goto " + loop->fim + ";\n" +
					$4.traducao +
					"\tgoto " + loop->inicio + ";\n\t" + loop->fim + ":\n";
				
			}

			| TK_DO BLOCO TK_WHILE E ';' {

				if ($4.tipo != &tipo_bool) yyerror("Tipo da expressao do DO WHILE DEVE ser bool");

				loopLabel* loop = getLoop(1);

				$$.traducao = "\t" + loop->inicio + ":\n\t" 
						+ loop->progressao + ":\n" + $4.traducao 
						+ $2.traducao + "\tif (" 
						+ $4.label + ") goto " + loop->inicio + ";\n\t"
						+ loop->fim + ":\n";

			}

			;
LOOP_ALT	: TK_BREAK {
				loopLabel* loop = getLoop(1);
				
				if (loop == nullptr) yyerror("Break deve ser usado dentro de um loop");

				$$.traducao = "\tgoto " + loop->fim + ";\n";
				
			}
			| TK_BREAK TK_ALL {
				loopLabel* loop = getOuterLoop();
				
				if (loop == nullptr) yyerror("Break all deve ser usado dentro de um loop");

				$$.traducao = "\tgoto " + loop->fim + ";\n";
			}
			| TK_BREAK '(' TK_INT ')' {
				loopLabel* loop = getLoop(stoi($3.label));
				
				if (loop == nullptr) yyerror("Break com args deve ser usado dentro de um loop\nou\nargumento invalido");

				$$.traducao = "\tgoto " + loop->fim + ";\n";
			}
			| TK_CONTINUE {
				loopLabel* loop = getLoop(1);
				
				if (loop == nullptr) yyerror("Continue deve ser usado dentro de um loop");

				$$.traducao = "\tgoto " + loop->progressao + ";\n";
			}
			| TK_CONTINUE TK_ALL {
				loopLabel* loop = getOuterLoop();
				
				if (loop == nullptr) yyerror("Continue deve ser usado dentro de um loop");

				$$.traducao = "\tgoto " + loop->progressao + ";\n";
			}
			;

PRINT		: TK_PRINT PRINT_ALT
			{
				$$.traducao = $2.traducao + "\tcout" + $2.label;
			}
			;
PRINT_ALT	: E
			{
				string label;
				atributos* atr;
				if ( atr = findVar($1.label) ) label = atr->label;
				else label = $1.label;
				$$.traducao = $1.traducao;
				$$.label = " << " + label;
			}

			| E ',' PRINT_ALT
			{
				string label;
				atributos* atr;
				if ( atr = findVar($1.label) ) label = atr->label;
				else label = $1.label;
				$$.traducao = $1.traducao + $3.traducao;
				$$.label = " << " + label + $3.label;
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
