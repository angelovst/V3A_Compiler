%{
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "struct.h"
#include "matrix.h"
#include "list.h"
#define YYSTYPE atributos
#define OUTPUT_INTERMEDIARIO "-i"
using namespace std;
int yylex(void);
void yyerror(string);

int yyparse (void);

fstream output;
FILE *input;

CustomType constructingType;

%}

%token TK_INT TK_FLOAT TK_BOOL TK_CHAR TK_LIST
%token TK_IF TK_BLOCO_ABRIR TK_BLOCO_FECHAR TK_ELSE TK_FOR TK_STEPPING TK_FROM TK_TO TK_REPEAT TK_UNTIL TK_WHILE TK_BREAK TK_ALL TK_CONTINUE TK_PRINT TK_SWITCH TK_CASE TK_DEFAULT
%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_BOOL TK_TIPO_CHAR TK_TIPO_MATRIX TK_TIPO_VECTOR TK_TIPO_LIST TK_TIPO_STR
%token TK_COMENTARIO TK_COMENTARIO_MULT_LINHA
%token TK_STRUCT TK_HAS TK_MEMBER_ACCESS
%token TK_OPEN_MEMBER TK_CLOSE_MEMBER
%token TK_PUSH
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
%right TK_OPEN_MEMBER TK_MEMBER_ACCESS

%%

S 			: COMANDOS
			{
				cout << "Regra S : COMANDOS" << endl;	//debug
				string globalDeclar = contextStack.begin()->declar;
				string globalGarbageCollect = contextStack.begin()->garbageCollect;
				output << "/*Compilador V3A*/\n" << "#include <iostream>\n#include<cstring>\n#include<stdlib.h>\n\nusing namespace std; \n\nint main(int argc, char **args)\n{\n" << "\t\n" << globalDeclar << "\n" << $1.traducao << "\n" << globalGarbageCollect << "\n\treturn 0;\n}" << endl;

			}
			;		

BLOCO	: ESCOPO_INICIO COMANDOS ESCOPO_FIM
		{
			cout << "Regra BLOCO : COMANDOS" << endl;	//debug
			
			//$$.traducao = "";
			$$.traducao = $1.traducao + contextStack.begin()->declar + "\n" + $2.traducao + "\n" + contextStack.begin()->garbageCollect;
			
			desempContexto();
			$$.traducao += ident() + "}";
			$$.label = "";
		}
		;
			
ESCOPO_INICIO	:	TK_BLOCO_ABRIR TK_DOTS
				{
					cout << "Regra ESCOPO_INICIO : TK_BLOCO_ABRIR" << endl;	//debug
					$$.traducao = ident() + "{\n";
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
				cout << "Regra COMANDOS : vazio" << endl;	//debug
			}	
			;

COMANDO 	: E
			{
				cout << "Regra COMANDO : " << $1.label << endl;	//debug
				$$.traducao = $1.traducao;
			}

			| DECLARACAO
			{
				cout << "Regra COMANDO : DECLARACAO" << endl;	//debug
				$$.traducao = $1.traducao;
			}
			
			| DECLARACAO_STRUCT
			{
				cout << "Regra COMANDO : DECLARACAO_STRUCT" << endl;	//debug
				$$.traducao = $1.traducao;
			}
			
			| BLOCO
			{
				cout << "Regra COMANDO : ESCOPO_INICIO BLOCO ESCOPO_FIM" << endl;	//debug
				$$.traducao = $1.traducao;
			}
			
			| CONTROLE
			{
				cout << "Regra COMANDO : CONTROLE" << endl;	//debug
				$$.traducao = $1.traducao;
			}

			| LOOP_ALT TK_ENDL
			{
				cout << "Regra COMANDO : LOOP_ALT TK_ENDL" << endl;	//debug
				$$.traducao = $1.traducao;
			}
			| PRINT
			{
				cout << "Regra COMANDO : PRINT" << endl;	//debug
				$$.traducao = $1.traducao;
			}
			| TK_COMENTARIO
			{
				cout << "Regra COMANDO : TK_COMENTARIO" << endl;	//debug
				$$.traducao = $1.label;
			}
			| TK_COMENTARIO_MULT_LINHA
			{
				cout << "Regra COMANDO : TK_COMENTARIO_MULT_LINHA" << endl;	//debug
				$$.traducao = $1.label + "\n";
			}
			| TK_ENDL
			{
				//cout << "Regra COMANDO : TK_ENDL" << endl;	//debug
			}
			| TK_ID TK_PUSH E
			{
				cout << "Regra COMANDO : TK_ID TK_PUSH E" << endl;	//debug
				CustomType *t = &customTypes[customTypesIds[$1.label]];
				Tipo *dataT;
				std::string data;
				if (t == NULL) {
					yyerror($1.label + " nao declarado ou nao e uma lista");
				}
				dataT = getTipo(t, TYPE_MEMBER);
				if (dataT == NULL) {
					yyerror($1.label + " nao e uma lista");
				}
				
				if ((getGroup($3.tipo)&getGroup(dataT)) != getGroup($3.tipo) || resolverTipo(dataT, $3.tipo) != dataT) {
					yyerror("Nao foi possivel converter " + $3.tipo->trad + " para " + dataT->trad);
				}
				
				$$.tipo = dataT;
				$$.traducao = $3.traducao + implicitCast(&$$, &$3, &$$.label, &data);
				$$.traducao += push_back(t, $1.label, data);
			}
			;			

E 			: E TK_ATRIB E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_PLUS E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_MINUS E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_MULT E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_DIV E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_AND E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_OR E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_DIFERENTE E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_IGUAL E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_MAIOR E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_MENOR E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_MAIORI E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| E TK_MENORI E {

				cout << "Regra E : " << $1.label << " " << $2.label << " " << $3.label << endl;	//debug				
				atributos atrib;
				string retorno = traducaoOperadores($1, $2, $3, &atrib);

				if (retorno == INVALID_CAST) {
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $3.tipo->trad);
				} else if (retorno == VAR_ALREADY_DECLARED) {
					yyerror("Variavel com nome " + $1.label + " ja declarada anteriormente");
				} else if (retorno == VAR_UNDECLARED) {
					yyerror("Variavel nao declarada");
				}

				$$ = atrib;
			}
			| '(' TIPO ')' E
			{	
				//cout << "cast executado" << endl;	//debug
				cout << "Regra E : ( TIPO ) E" << endl;	//debug
				$$.label = generateVarLabel();
				declararLocal($2.tipo, $$.label);
				$$.tipo = $2.tipo;
				$$.traducao = $4.traducao + newLine($$.label + " = " + '(' + $2.tipo->trad + ')' + $4.label);
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
			
			| TK_ID TK_MEMBER_ACCESS TK_ID
			{
				cout << "Regra E : " << $1.label << "'s " << $3.label << endl;	//debug
				$1.tipo = findVar($1.label);
				if ($1.tipo == NULL) {
					yyerror($1.label + " nao declarada anteriormente");
				}
				if (!belongsTo($1.tipo, GROUP_STRUCT)) {
					yyerror($1.label + " nao e um struct");
				}
				
				CustomType &type = customTypes[$1.tipo->id];
				Tipo *tipo = getTipo(&type, $3.label);
				
				//if (belongsTo(tipo, GROUP_PTR)) cout << "is pointer" << endl;	//debug
				
				if (tipo == NULL) {
					yyerror($3.label + " nao pertence ao struct");
				}
				
				$$.label = generateVarLabel();
				$$.tipo = tipo;
				declararLocal(&tipo_ptr, $$.label);
				
				$$.traducao = setAccess(&type, $1.label, $3.label, $$.label);
			}
			| TK_ID TK_OPEN_MEMBER E TK_CLOSE_MEMBER TK_OPEN_MEMBER E TK_CLOSE_MEMBER
			{
				cout << "Regra E : TK_ID TK_OPEN_MEMBER E TK_CLOSE_MEMBER TK_OPEN_MEMBER E TK_CLOSE_MEMBER" << endl;	//debug
				$1.tipo = findVar($1.label);
				if ($1.tipo == NULL) {
					yyerror($1.label + " nao declarada anteriormente");
				}
				if (!belongsTo($1.tipo, GROUP_STRUCT)) {
					cout << "here" << endl;
					yyerror($1.label + " nao e uma matriz");
				}
				if (!belongsTo($3.tipo, GROUP_NUMBER) || resolverTipo(&tipo_int, $3.tipo) != &tipo_int || !belongsTo($6.tipo, GROUP_NUMBER) || resolverTipo(&tipo_int, $6.tipo) != &tipo_int) {
					yyerror("Argumento de indice da matrix deve ser do tipo int");
				}
				
				std::string tdr;
				std::string c1, c2;
				CustomType &type = customTypes[$1.tipo->id];
				Tipo *tipo = getTipo(&type, DATA_MEMBER);
				
				$$.traducao = $3.traducao + $6.traducao;
				
				$$.tipo = &tipo_int;
				$$.traducao += implicitCast(&$$, &$3, &$$.label, &c1);
				$$.traducao += implicitCast(&$$, &$6, &$$.label, &c2);
				
				if (tipo == NULL) {
					yyerror($1.label + " nao e uma matriz");
				}
				
				$$.label = generateVarLabel();
				$$.tipo = tipo;
				declararLocal(&tipo_ptr, $$.label);
				
				$$.traducao += setIndexAccess(&type, $1.label, $3.label, $6.label, $$.label);
				
			}
			| TK_ID TK_OPEN_MEMBER E TK_CLOSE_MEMBER
			{
				cout << "Regra E : TK_ID TK_OPEN_MEMBER E TK_CLOSE_MEMBER TK_OPEN_MEMBER E TK_CLOSE_MEMBER" << endl;	//debug
				$1.tipo = findVar($1.label);
				if ($1.tipo == NULL) {
					yyerror($1.label + " nao declarada anteriormente");
				}
				if (!belongsTo($1.tipo, GROUP_STRUCT)) {
					cout << "here" << endl;
					yyerror($1.label + " nao e uma matriz");
				}
				if (!belongsTo($3.tipo, GROUP_NUMBER) || resolverTipo(&tipo_int, $3.tipo) != &tipo_int) {
					yyerror("Argumento de indice da matrix deve ser do tipo int");
				}
				
				std::string tdr;
				std::string c1, colum;
				CustomType &type = customTypes[$1.tipo->id];
				Tipo *tipo = getTipo(&type, DATA_MEMBER);
				
				$$.traducao = $3.traducao;
				
				$$.tipo = &tipo_int;
				$$.traducao += implicitCast(&$$, &$3, &$$.label, &c1);
				
				if (tipo == NULL) {
					yyerror($1.label + " nao e uma matriz");
				}
				
				$$.label = generateVarLabel();
				$$.tipo = tipo;
				declararLocal(&tipo_ptr, $$.label);
				
				colum = generateVarLabel();
				declararLocal(&tipo_int, colum);
				
				$$.traducao += newLine(colum + " = 0");
				
				$$.traducao += setIndexAccess(&type, $1.label, $3.label, colum, $$.label);
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
				//cout << "tipo " << $1.tipo->trad << " declarado" << endl;
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
					yyerror("Operacao invalida com tipos " + $1.tipo->trad + " e " + $4.tipo->trad);
				}
				$$.traducao = $1.traducao + $4.traducao + atrib;
			}
			
			| TIPO TK_TIPO_MATRIX TK_ID TK_OPEN_MEMBER E TK_CLOSE_MEMBER TK_OPEN_MEMBER E TK_CLOSE_MEMBER
			{
				cout << "Regra DECLARACAO : TIPO TK_TIPO_MATRIX TK_ID TK_OPEN_MEMBER E TK_CLOSE_MEMBER TK_OPEN_MEMBER E TK_CLOSE_MEMBER" << endl;	//debug
				if (!belongsTo($5.tipo, GROUP_NUMBER) || resolverTipo(&tipo_int, $5.tipo) != &tipo_int || !belongsTo($8.tipo, GROUP_NUMBER) || resolverTipo(&tipo_int, $8.tipo) != &tipo_int) {
					yyerror("Argumento de dimensao da matrix deve ser do tipo int");
				}
				
				std::string tdr;
				std::string c1, c2;
				
				$$.traducao = $5.traducao + $8.traducao;
				
				$$.tipo = &tipo_int;
				$$.traducao += implicitCast(&$$, &$5, &$$.label, &c1);
				$$.traducao += implicitCast(&$$, &$8, &$$.label, &c2);
				
				tdr = newMatrix($1.tipo, $3.label, c1, c2);
				if (tdr == VAR_ALREADY_DECLARED) {
					yyerror($3.label + " ja declarada anteriormente");
				}
				
				$$.traducao += tdr;
				
			}
			| TIPO TK_TIPO_VECTOR TK_ID TK_OPEN_MEMBER E TK_CLOSE_MEMBER
			{
				cout << "Regra DECLARACAO : TIPO TK_TIPO_MATRIX TK_ID TK_OPEN_MEMBER E TK_CLOSE_MEMBER TK_OPEN_MEMBER E TK_CLOSE_MEMBER" << endl;	//debug
				if (!belongsTo($5.tipo, GROUP_NUMBER) || resolverTipo(&tipo_int, $5.tipo) != &tipo_int) {
					yyerror("Argumento de dimensao do vetor deve ser do tipo int");
				}
				
				std::string tdr;
				std::string c1, colum;
				
				$$.traducao = $5.traducao;
				
				$$.tipo = &tipo_int;
				$$.traducao += implicitCast(&$$, &$5, &$$.label, &c1);
				
				colum = generateVarLabel();
				declararLocal(&tipo_int, colum);
				
				$$.traducao += newLine(colum + " = 1");
				
				tdr = newMatrix($1.tipo, $3.label, c1, colum);
				if (tdr == VAR_ALREADY_DECLARED) {
					yyerror($3.label + " ja declarada anteriormente");
				}
				
				$$.traducao += tdr;
			}
			| TIPO TK_TIPO_LIST TK_ID
			{
				cout << "Regra DECLARACAO : TIPO TK_TIPO_LIST TK_ID" << endl;	//debug
				if (findVar($3.label) != NULL) {
					yyerror("Variavel " + $3.label + " ja declarada anteriormente");
				}
				$$.traducao = newList($1.tipo, $3.label);
			}
			
			| TK_ID TK_ID
			{
				cout << "Regra DECLARACAO : TK_ID TK_ID" <<endl;	//debug
				if (customTypesIds.count($1.label) == 0) {
					yyerror($1.label + " nao nomeia um tipo");
				}
				CustomType &c = customTypes[customTypesIds[$1.label]];
				$$.traducao = newInstanceOf(&c, $2.label, true);
				if ($$.traducao == VAR_ALREADY_DECLARED) {
					yyerror($2.label +" ja declarada anteriormente");
				}
			}
			;
			
STRUCT	: TK_STRUCT
		{
			cout << "Regra STRUCT : TK_STRUCT" << endl;	//debug
			constructingType = newCustomType();
		}
		;
			
DECLARACAO_STRUCT	: STRUCT TK_ID TK_HAS TK_DOTS MEMBROS_STRUCT TK_BLOCO_FECHAR
					{
						cout << "Regra DECLARACAO_STRUCT : TK_STRUCT TK_ID TK_HAS MEMBROS_STRUCT" << endl;	//debug
						if (!createCustomType(&constructingType, $2.label)) {
							yyerror("Tipo " + $2.label + " ja declarado anteriormente");
						}
						$$.traducao = $5.traducao;
					}
					;
					
MEMBROS_STRUCT	:	MEMBRO_STRUCT MEMBROS_STRUCT
				{
					cout << "Regra MEMBROS_STRUCT : MEMBRO_STRUCT MEMBROS_STRUCT" << endl;	//debug
					$$.traducao = $1.traducao + $2.traducao;
				}
				|
				{
					cout << "Regra MEMBROS_STRUCT : vazio" << endl;	//debug
				}
				;
				
MEMBRO_STRUCT	: TIPO TK_ID
				{
					cout << "Regra MEMBRO_STRUCT : TIPO TK_ID" << endl;	//debug
					if (!addVar(&constructingType, $1.tipo, $2.label, "")) {
						yyerror("Variavel " + $2.label + " ja declarada no struct");
					}			
				}
				| TIPO TK_ID TK_ATRIB E
				{
					cout << "Regra MEMBRO_STRUCT : TIPO TK_ID TK_ATRIB E" << endl;	//debug
					if (!belongsTo($4.tipo, getGroup($1.tipo)) || resolverTipo($1.tipo, $4.tipo) != $1.tipo) {
						yyerror("Nao e possivel converter tipo " + $4.tipo->trad + " para " + $1.tipo->trad);
					}
					
					std::string tmp;
					$$.tipo = $1.tipo;
					
					$$.traducao = $4.traducao + implicitCast(&$$, &$4, &$$.label, &tmp);
					
					//cout << tmp << endl;	//debug
					
					if (!addVar(&constructingType, $1.tipo, $2.label, tmp)) {
						yyerror("Variavel " + $2.label + " ja declarada no struct");
					}	
				}
				| TK_ENDL
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
				$$.traducao =	newLine(var2 + " = " + $1.label) + newLine(var1 + " = 1") + 
								newLine($1.label + " = " + $1.label + $2.label + var1);
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
				//cout << $2.tipo->trad << endl;	//debug
				cout << "Regra CONTROLE : TK_IF E BLOCO" << endl;	//debug
				if($2.tipo != &tipo_bool) yyerror("Tipo da expressao DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);
				
				$$.traducao = "\n" + $2.traducao + newLine(var + " = !" + $2.label) + newLine("if (" + var + ") goto " + fim) + $3.traducao + newLine(fim+":");
			}
			| TK_IF E BLOCO CONTROLE_ALT
			{
				cout << "Regra CONTROLE : TK_IF E BLOCO CONTROLE_ALT" << endl;	//debug

				if($2.tipo != &tipo_bool) yyerror("Tipo da expressao DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);

				$$.traducao = "\n" + $2.traducao + newLine(var + " = !" + $2.label) + newLine("if (" + var + ") goto " + fim);
				$$.traducao += $3.traducao + newLine("goto " + $4.label) + newLine(fim+":") + $4.traducao;
				
			}

			| LOOP
			{
				cout << "Regra CONTROLE : LOOP_INICIO LOOP LOOP_FIM" << endl;	//debug
				$$.traducao = $1.traducao;
			}
			| TK_SWITCH CASE_VAR TK_DOTS TK_ENDL SWITCH_ALT
			{
				cout << "Regra CONTROLE : TK_SWITCH TK_ID TK_DOTS SWITCH_ALT" << endl;  //debug

				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);

				$$.traducao = $5.traducao;
				varSwitch.pop_front();
			}
			;
CASE_VAR	: TK_ID
			{
				cout << "Regra CASE_VAR : TK_ID" << endl;
				$1.tipo = findVar($1.label);
				if ($1.tipo == NULL) {
					yyerror($1.label + " nao declarada anteriormente");
				}
				varSwitch.push_front($1);

			}

SWITCH_ALT	: CASE SWITCH_ALT
			{
				cout << "Regra SWITCH_ALT : CASE SWITCH_ALT" << endl;

				$$.traducao = $1.traducao + $2.traducao;
			}
			| CASE
			{
				cout << "Regra SWITCH_ALT : CASE" << endl;
				$$.traducao = $1.traducao;
			}
			| TK_DEFAULT BLOCO
			{
				cout << "Regra SWITCH_ALT : Tk_DEFAULT BLOCO" << endl;

				$$.traducao = $2.traducao + "\n";
			}
			;

CASE		: TK_CASE E BLOCO
			{
				cout << "Regra CASE : TK_CASE E BLOCO" << endl;
				if(varSwitch.front().tipo != $2.tipo) {
					yyerror("Comparacao de tipos diferentes");
				}
				string var = generateVarLabel();
				string fim = generateLabel();

				declararLocal(&tipo_int, var);

				$$.traducao = "\n" + $2.traducao + newLine(var + " = " + $2.label + " != " + varSwitch.front().label) + newLine("if (" + var + ") goto " + fim) + $3.traducao + newLine(fim+":");;
				$$.tipo = $2.tipo;
			}
			;

CONTROLE_ALT: TK_ELSE CONTROLE
			{
				cout << "Regra CONTROLE_ALT : TK_ELSE CONTROLE" << endl;	//debug
				$$.label = generateLabel();
				$$.traducao = $2.traducao + newLine($$.label+":"); 
			}
			| TK_ELSE BLOCO
			{
				cout << "Regra CONTROLE_ALT : TK_ELSE BLOCO" << endl;	//debug
				$$.label = generateLabel();
				$$.traducao = $2.traducao + newLine($$.label + ":");
			}
			;
			
DECLARACAO_NUMERO	: TK_ID
					{
						cout << "Regra DECLARACAO : TK_ID" << endl;
						$$.tipo = findVar($1.label);
						if ($$.tipo == NULL) {
							$$.tipo = &tipo_int;
							declararLocal($$.tipo, $1.label);
						} else if (!belongsTo($1.tipo, GROUP_NUMBER)) {
							yyerror($1.label + " era esperado armazenar numero");
						}
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
		
REPEAT	: TK_REPEAT TK_DOTS
		{
			cout << "Regra REPEAT : TK_UNTIL" << endl;
			empLoop();
			$$.traducao = "\n" + ident() + "//REPEAT UNTIL LOOP\n" + ident() + "{\n";
			empContexto();
		}

LOOP 		: FOR DECLARACAO_NUMERO TK_FROM E TK_TO E BLOCO
			{
				cout << "Regra LOOP : FOR DECLARACAO_NUMERO TK_FROM E TK_TO E BLOCO" << endl;	//debug
				if (!belongsTo($4.tipo, GROUP_NUMBER)) yyerror("Expressao do limite inferior deve retornar numero");
				if (!belongsTo($6.tipo, GROUP_NUMBER)) yyerror("Expressao do limite superior deve retornar numero");
				
				Tipo *i, *final;
				atributos *castTo;
				string iLabel;
				string limitInf, limitSup; 
				string check;
				string inc;
				string prevValue;
				string checkIncElse = generateLabel();
				string checkIncEnd = generateLabel();
				string checkBiggerElse = generateLabel();
				string checkBiggerEnd = generateLabel();
				
				//cout << "declaring vars" << endl;	//debug;
				final = resolverTipo($2.tipo, $4.tipo);
				castTo = (final == $2.tipo) ? &$2 : &$4;
				final = resolverTipo(final, $4.tipo);
				castTo = (final == $4.tipo) ? &$4 : castTo;
				final = resolverTipo(final, $6.tipo);
				castTo = (final == $6.tipo) ? &$6 : castTo;
				
				
				check = generateVarLabel();
				declararLocal(&tipo_bool, check);
				inc = generateVarLabel();
				declararLocal(final, inc);
				prevValue = generateVarLabel();
				declararLocal(final, prevValue);
				
				LoopLabel* loop = getLoop(0);
				
				$$.traducao = $4.traducao + $6.traducao;
				
				//cout << "casting vars" << endl;	//debug
				//escrever casts caso necessarios
				$$.traducao += implicitCast(castTo, &$2, &castTo->label, &iLabel);
				$$.traducao += implicitCast(castTo, &$4, &castTo->label, &limitInf);
				$$.traducao += implicitCast(castTo, &$6, &castTo->label, &limitSup);
				//cout << "counting var casted" << endl;	//debug
				
				//cout << "checking increment" << endl;	//debug
				//checar se incremento deve ser positivo ou negativo
				$$.traducao += ident() + "//checar variavel de incremento\n" + newLine(check + " = " + limitInf + "<" + limitSup);
				$$.traducao += newLine("if (" + check + ") goto " + checkIncElse);
				//incremento negatvo caso limitInf > limitSup
				$$.traducao += "\t" + newLine(inc + " = " + "-1");
				$$.traducao += "\t" + newLine("goto " + checkIncEnd);
				//incremento positivo caso limitInf < limitSup
				$$.traducao += ident() + checkIncElse + ":\n";
				$$.traducao += "\t" + newLine(inc + " = " + "1");
				$$.traducao += ident() + checkIncEnd + ":\n\n";
				
				//cout << "translating loop" << endl;	//debug
				$$.traducao += newLine(iLabel + " = " + limitInf);	//inicializar variavel de contagem
				//escrever bloco
				$$.traducao += ident() + "//laco de repeticao\n" + newLine(loop->inicio+":") + newLine(prevValue + " = " + iLabel);
				
				//checar se verificacao deve ser >= ou <=
				$$.traducao += ident() + "//checar variavel de incremento\n" + newLine(check + " = " + limitInf + "<" + limitSup);
				$$.traducao += newLine("if (" + check + ") goto " + checkBiggerElse);
				//verificar <= caso limitInf > limitSup
				$$.traducao += "\t" + newLine(check + " = " + iLabel + "<=" + limitSup);
				$$.traducao += "\t" + newLine("goto " + checkBiggerEnd);
				//verificar >= caso limitInf < limitSup
				$$.traducao += ident() + checkBiggerElse + ":\n";
				$$.traducao += "\t" + newLine(check + " = " + iLabel + ">=" + limitSup);
				$$.traducao += ident() + checkBiggerEnd + ":\n\n";
				
				$$.traducao += newLine("if (" + check + ") goto " + loop->fim) + $7.traducao + loop->progressao+":\n";
				//incrementar variavel de contagem
				$$.traducao += newLine(iLabel + " = " + prevValue + "+" + inc);
				$$.traducao += newLine("goto " + loop->inicio);
				
				$$.traducao = $1.traducao + contextStack.begin()->declar + "\n" + $$.traducao;
				desempLoop();
				desempContexto();
				$$.traducao += ident() + "}\n" + newLine(loop->fim+":");
				//cout << "loop translated" << endl;	//debug

			}
			| FOR DECLARACAO_NUMERO TK_STEPPING E TK_FROM E TK_TO E BLOCO
			{
				cout << "Regra LOOP : FOR DECLARACAO_NUMERO TK_STEPPING E TK_FROM E TK_TO E BLOCO" << endl;	//debug
				if (!belongsTo($4.tipo, GROUP_NUMBER)) yyerror("Expressao do step deve retornar numero");
				if (!belongsTo($6.tipo, GROUP_NUMBER)) yyerror("Expressao do limite inferior deve retornar numero");
				if (!belongsTo($8.tipo, GROUP_NUMBER)) yyerror("Expressao do limite superior deve retornar numero");
				
				Tipo *i, *final;
				atributos *castTo;
				string iLabel;
				string inc, limitInf, limitSup; 
				string check = generateVarLabel();
				string prevValue = generateVarLabel();
				string checkBiggerElse = generateLabel();
				string checkBiggerEnd = generateLabel();
				
				//cout << "declaring vars" << endl;	//debug;
				final = resolverTipo($4.tipo, $6.tipo);
				castTo = (final == $4.tipo) ? &$4 : &$6;
				final = resolverTipo(final, $8.tipo);
				castTo = (final == $8.tipo) ? &$8 : castTo;
				final = resolverTipo(final, $2.tipo);
				castTo = (final == $2.tipo) ? &$2 : castTo;

				declararLocal(&tipo_bool, check);
				declararLocal(final, prevValue);
				
				LoopLabel* loop = getLoop(0);
				
				$$.traducao = $4.traducao + $6.traducao + $8.traducao;
				
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
				$$.traducao += ident() + "//laco de repeticao\n" + newLine(loop->inicio+":") + newLine(prevValue + " = " + iLabel);
				
				//checar se verificacao deve ser >= ou <=
				$$.traducao += ident() + "//checar variavel de incremento\n" + newLine(check + " = " + limitInf + "<" + limitSup);
				$$.traducao += newLine("if (" + check + ") goto " + checkBiggerElse);
				//verificar <= caso limitInf > limitSup
				$$.traducao += "\t" + newLine(check + " = " + iLabel + "<=" + limitSup);
				$$.traducao += "\t" + newLine("goto " + checkBiggerEnd);
				//verificar >= caso limitInf < limitSup
				$$.traducao += ident() + checkBiggerElse + ":\n";
				$$.traducao += "\t" + newLine(check + " = " + iLabel + ">=" + limitSup);
				$$.traducao += ident() + checkBiggerEnd + ":\n\n";
				
				$$.traducao += newLine("if (" + check + ") goto " + loop->fim) + $9.traducao + loop->progressao+":\n";
				//incrementar variavel de contagem
				$$.traducao += newLine(iLabel + " = " + prevValue + "+" + inc);
				$$.traducao += newLine("goto " + loop->inicio);
				
				$$.traducao = $1.traducao + contextStack.begin()->declar + "\n" + $$.traducao;
				desempLoop();
				desempContexto();
				$$.traducao += ident() + "}\n" + newLine(loop->fim+":");
				//cout << "loop translated" << endl;	//debug

			} 

			| WHILE E BLOCO 
			{
				cout << "Regra LOOP : TK_WHILE E BLOCO" << endl;	//debug
				if ($2.tipo != &tipo_bool) yyerror("Tipo da expressao do while DEVE ser bool");
				string var = generateVarLabel();
				LoopLabel* loop = getLoop(0);
					
				declararLocal(&tipo_bool, var);
				
				$$.traducao = $1.traducao + contextStack.begin()->declar + "\n";
				$$.traducao += newLine(loop->inicio+":") + $2.traducao + newLine(var + " = !" + $2.label);
				$$.traducao += newLine("if (" + var + ") goto " + loop->fim) + $3.traducao + newLine("goto " + loop->inicio) + ident() + newLine(loop->fim+":");
				desempLoop();
				desempContexto();
				$$.traducao += ident() + "}\n";
				
			}
			| REPEAT COMANDOS TK_UNTIL E TK_ENDL
			{
				cout << "Regra LOOP : REPEAT COMANDOS TK_UNTIL E TK_ENDL" << endl;	//debug
				if ($4.tipo != &tipo_bool) yyerror("Tipo da expressao do repeat DEVE ser bool");
				
				LoopLabel* loop = getLoop(0);
				
				$$.traducao = $1.traducao + contextStack.begin()->declar + "\n";
				$$.traducao += newLine(loop->inicio+":") + newLine(loop->progressao+":") + $2.traducao + "\n" + $4.traducao;
				$$.traducao += newLine("if (" + $4.label + ") goto " + loop->fim);
				$$.traducao += newLine("goto " + loop->inicio);
				desempLoop();
				desempContexto();
				$$.traducao += ident() + "} " + loop->fim + ":;\n";
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
				LoopLabel* loop = getLoop(stoi($3.label) - 1);
				
				if (loop == NULL) yyerror("Break com deve ser usado dentro de um loop\n\tou\n\tArgumento Invalido");

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
				if (!belongsTo($1.tipo, GROUP_PTR)) {
					$$.label = " << " + $1.label + " << std::endl";
				} else {
					std::string var;
					Tipo t = nonPtr($1.tipo);
					$$.tipo = &t;
					$$.traducao += implicitCast(&$$, &$1, &$$.label, &var);
					$$.label = " << " + var + " << std::endl";
				}
			}

			| E ',' PRINT_ALT
			{
				cout << "Regra PRINT_ALT : E , PRINT_ALT" << endl;	//debug
				if (findVar($1.label) == NULL) {
					yyerror("Variavel " + $1.label + " nao declarada");
				}
				$$.traducao = $1.traducao + $3.traducao;
				if (!belongsTo($1.tipo, GROUP_PTR)) {
					$$.label = " << " + $1.label + " << \" \" " + $3.label;
				} else {
					std::string var;
					Tipo t = nonPtr($1.tipo);
					$$.tipo = &t;
					$$.traducao += implicitCast(&$$, &$1, &$$.label, &var);
					$$.label = " << " + var + " << \" \" " + $3.label;
				}
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
		string echo = "echo " + compile + "\n";
		system(echo.c_str());	//debug
		system(compile.c_str());
		remove(outputFileName.c_str());	
	}
	//limpar retorno e argumentos de funcoes
	delete(tipo_logic_operator.retornos);
	return 0;
	
}

void yyerror( string MSG ) {
	cout << "Linha " << line << ": " << MSG << endl;
	closeFiles();
	exit (0);
}
