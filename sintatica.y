%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#define YYSTYPE atributos

#define TIPO_INT "int"
#define TIPO_FLOAT "float"
#define TIPO_BOOL "unsigend char"
#define TIPO_CHAR "char"
#define TIPO_LIST "list"
#define TIPO_INFIX_OPERATOR "operator inf"

using namespace std;

string generateLabel(){

	static unsigned int i = 0;
	return "TMP" + to_string(i++);
}

typedef struct {
	string traducao;
	size_t size;
} Tipo;
Tipo tipo_int = { TIPO_INT, sizeof(int) };
Tipo tipo_float = { TIPO_FLOAT, sizeof(float) };
Tipo tipo_bool = { TIPO_BOOL, sizeof(unsigned char) };
Tipo tipo_char = { TIPO_CHAR, sizeof(char) };
Tipo tipo_list = { TIPO_LIST, sizeof(size_t)+2*sizeof(void*) };

typedef struct atributos
{
	string label;
	string traducao;
	Tipo tipo;

}atributos;

//DECLARACOES DE FUNCOES

atributos* findVarOnTop(string label);

atributos* findVar(string label);

string findTmpName(string label);

int yylex(void);
void yyerror(string);

//Pilha de variaveis
std::vector<map<string, atributos>> varMap;

//String para declaracao de var
string varDeclar;

bool declaracaoLocal(string &tipo, string &label, struct atributos &atrib){

	std::map<string, atributos> *mapLocal = &varMap.back();

	if(mapLocal->find(label) != mapLocal->end()) return false;

	atrib.label = generateLabel();
	atrib.tipo = tipo;
	(*mapLocal)[label] = atrib;

	cout << atrib.label << endl;
	return true;
}

%}

%token TK_INT TK_FLOAT TK_BOOL TK_CHAR
%token TK_MAIN TK_IF TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_BOOL TK_TIPO_CHAR TK_TIPO_LIST
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
/*
ESCOPO_INICIO: {
				empContexto();
				
				$$.traducao = "";
				$$.label = "";
			};
			
ESCOPO_FIM:	{
				desempContexto();
				
				$$.traducao = "";
				$$.label = "";
			};

BLOCO		: ESCOPO_INICIO '{' COMANDOS '}' ESCOPO_FIM {
				$$.traducao = $3.traducao;
			};
*/
COMANDOS	: COMANDO COMANDOS
			{
				$$.traducao = $1.traducao + $2.traducao;
			}
			|
			;

COMANDO 	: E ';'

			| TIPO TK_ID ';'
			{
				std::map<string, atributos> *mapLocal = &varMap.back();

				if(mapLocal->find($2.label) != mapLocal->end()) {
					yyerror("Variavel ja declarada localmente");
				}
				else {
					$$.label = generateLabel();
					$$.tipo = $1.tipo;
					varDeclar += $1.traducao + $2.traducao + $$.tipo.traducao + " " + $$.label + ";\n\t";
					(*mapLocal)[$2.label] = $$;
				}
					

			}

			| TIPO TK_ID TK_ATRIB E ';'
			{	
				std::map<string, atributos> *mapLocal = &varMap.back();
				if(mapLocal->find($2.label) != mapLocal->end()) {
        			yyerror("Variavel usada para atribuicao ja declarada");	
				}
				else if( $1.tipo.traducao == $4.tipo.traducao ){
					if (mapLocal->find($4.label) != mapLocal->end())	{
						$$.label = generateLabel();
						$$.tipo = $1.tipo;
						$$.traducao = "\t" + $$.label + " = " + (*mapLocal)[$4.label].label + ";\n";
						varDeclar += $1.traducao + $2.traducao + $$.tipo + " " + $$.label + ";\n\t";
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
					if((*mapLocal)[$1.label].tipo.traducao == $3.tipo.traducao) {
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

E 			: E OP_INFIX E {
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao;
				string var1 = $1.label, var2 = $3.label;
				int needsCast = compatibleTypes(&$1.tipo, &$2.tipo);
				
				
				//cast
				if (needsCast) {
					if (needsCast & CAST_1ST) {
						//needs to cast $1 to $3 
						var1 = generateLabel();
						varDeclar += $3.tipo.traducao + ' ' + var1 + "\n\t";
						$$.traducao = $$.traducao + "\t" + var1 + " = " + '(' + $3.tipo.traducao + ')' + $1.label + ";\n";
					} else if (needsCast & CAST_2ND) {
						//needs to cast $3 to $1
						var2 = generateLabel();
						varDeclar += $1.tipo.traducao + ' ' + var2 + "\n\t";
						$$.traducao = $$.traducao + "\t" + var2 + " = " + '(' + $1.tipo.traducao + ')' + $3.label + ";\n";
					} else {
						yyerror("Operacao infixa " + $2.traducao + " invalida para tipos " + $1.tipo.traducao + " e " + $2.tipo.traducao);
					}	
				}
				
				$$.traducao += $$.label + " = " + var1 + $2.traducao + var2 + ";\n";
				
			}
			| '(' TIPO ')' E
			{	
				
				$$.label = generateLabel();
				varDeclar += $2.tipo + " " + $$.label + ";\n\t";
				$$.tipo = $2.tipo;
				$$.traducao = $4.traducao + "\t" + $$.label + " =" + '(' + $2.tipo + ')' + $4.label + ";\n";
			}

			| '(' E ')'
			{
				$$.label = $2.label; //generateLabel();
				$$.traducao = $2.traducao;// + "\t" + $$.label + " = " + $2.label + ";\n";
			}
			| '-' E
			{
				$$.label = generateLabel();
				$$.traducao = $2.traducao + "\t" + $$.label + " = " + " - " + $2.label + ";\n";
			}
			| TK_INT
			{
				$$.label = generateLabel();
				varDeclar += "int " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = TIPO_INT;
			}
			| TK_FLOAT
			{
				$$.label = generateLabel();
				varDeclar += "float " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = TIPO_FLOAT;
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

				$$.label = generateLabel();
				varDeclar += "unsigned char " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + aux + ";\n";
				$$.tipo = TIPO_BOOL;

			}
			| TK_CHAR
			{
				$$.label = generateLabel();
				varDeclar += "char " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label +  ";\n";
				$$.tipo = TIPO_CHAR;
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
				$$.label = generateLabel();
				$$.traducao = "\t" + $$.label + " = " + $1.label + ":\n";
				}
			}
			
			
			;
			
OP_INFIX	: TK_PLUS
			{
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MINUS {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MULT {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_DIV {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MOD {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MINUS  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MULT  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_DIV  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MOD  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_AND  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_OR  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_DIFERENTE  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_IGUAL  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MAIOR  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MENOR  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MAIORI  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			| TK_MENORI  {
				$$.tipo = TK_INFIX_OPERATOR;
			}
			;

TIPO 		: TK_TIPO_INT
			{
				$$.tipo = TIPO_INT;
			}
			| TK_TIPO_FLOAT
			{
				$$.tipo = TIPO_FLOAT;
			}
			| TK_TIPO_BOOL
			{
				$$.tipo = TIPO_BOOL;
			}
			| TK_TIPO_CHAR
			{
				$$.tipo = TIPO_CHAR;
			}
			| TK_TIPO_LIST
			{
				$$.tipo = TIPO_LIST;
			}	
			;

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	map<string, atributos> mapaGlobal;
	varMap.push_back(mapaGlobal);

	yyparse();

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}		

//FUNCOES PARA ENTRADA E SAIDA DE BLOCOS, CONTROLE DO CONTEXTO
void empContexto() {
	map<string, atributos> novoMapa;
	varMap.push_back(novoMapa);
}

void desempContexto() {
	return varMap.pop_back();
}
//FUNCOES DE PROCURA DE VARIAVEL

atributos* findVarOnTop(string label) {
	if (varMap[varMap.size() - 1].count(label)) {
		return &varMap[varMap.size() - 1][label];
	}
	
	return nullptr;
}

atributos* findVar(string label) {
	for (int i = varMap.size() - 1; i >= 0; i--) {
		if (varMap[i].count(label)) {
			return &varMap[i][label];
		}
	}	
	return nullptr;
}
string findTmpName(string label) {
	for (int i = varMap.size() - 1; i >= 0; i--) {
		if (varMap[i].count(label)) {
			return varMap[i][label].label;
		}
	}	
	return "null";
}
