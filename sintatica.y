%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#define YYSTYPE atributos	

using namespace std;

string generateLabel(){

	static unsigned int i = 1;
	return "TMP" + to_string(i++);
}

typedef struct atributos
{
	string label;
	string traducao;
	string tipo;

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
%token TK_MAIN TK_IF TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_BOOL TK_TIPO_CHAR
%token TK_FIM TK_ERROR

%start S

%right TK_ATRIB
%left TK_OR TK_AND TK_NOT
%nonassoc TK_IGUAL TK_DIFERENTE
%nonassoc TK_MAIOR TK_MENOR TK_MAIORI TK_MENORI
%left '+' '-'
%left '*' '/'
%left TK_MOD

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
					varDeclar += $1.traducao + $2.traducao + $$.tipo + " " + $$.label + ";\n\t";
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

E 			: E '+' E
			{

				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao;
				string aux;
				if($1.tipo == "int" && $3.tipo == "float"){

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + $1.label + ";\n";
					aux = generateLabel();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + $3.label + " + " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";

				
				}else if($1.tipo == "float" && $3.tipo == "int"){
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + $3.label + ";\n";
					aux = generateLabel();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + $1.label + " + " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";
				
				}else if(($1.tipo == "int" && $3.tipo == "int") || ($1.tipo == "float" && $3.tipo == "float") ){
					varDeclar += "int " + $$.label + ";\n\t";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + $3.label + ";\n";
				}
				else {
					yyerror("Operacao de soma nao contemplada pelo compilador");
				}


				
			}
			| E '*' E
			{

				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao;
				string aux;

				if($1.tipo == "int" && $3.tipo == "float"){

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + $1.label + ";\n";
					aux = generateLabel();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + $3.label + " * " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";

				
				}else if($1.tipo == "float" && $3.tipo == "int"){
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + $3.label + ";\n";
					aux = generateLabel();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + $1.label + " * " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";
				
				}else if(($1.tipo == "int" && $3.tipo == "int") || ($1.tipo == "float" && $3.tipo == "float") ){
					varDeclar += "int " + $$.label + ";\n\t";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " * " + $3.label + ";\n";
				}
				else {
					yyerror("Operacao de soma nao contemplada pelo compilador");
				}


				
			}
			| E '/' E
			{

				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao;
				string aux;

				if($1.tipo == "int" && $3.tipo == "float"){

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + $1.label + ";\n";
					aux = generateLabel();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + $3.label + " / " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";

				
				}else if($1.tipo == "float" && $3.tipo == "int"){
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + $3.label + ";\n";
					aux = generateLabel();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + $1.label + " / " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";
				
				}else if(($1.tipo == "int" && $3.tipo == "int") || ($1.tipo == "float" && $3.tipo == "float") ){
					varDeclar += "int " + $$.label + ";\n\t";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " / " + $3.label + ";\n";
				}
				else {
					yyerror("Operacao de soma nao contemplada pelo compilador");
				}


				
			}
			| E '-' E
			{

				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao;
				string aux;

				if($1.tipo == "int" && $3.tipo == "float"){

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + $1.label + ";\n";
					aux = generateLabel();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + $3.label + " - " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";

				
				}else if($1.tipo == "float" && $3.tipo == "int"){
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + $3.label + ";\n";
					aux = generateLabel();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + $1.label + " - " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";
				
				}else if(($1.tipo == "int" && $3.tipo == "int") || ($1.tipo == "float" && $3.tipo == "float") ){
					varDeclar += "int " + $$.label + ";\n\t";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " - " + $3.label + ";\n";
				}
				else {
					yyerror("Operacao de soma nao contemplada pelo compilador");
				}


				
			}
			| E TK_AND E
			{	
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " && " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| E TK_OR E
			{
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " || " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| E TK_IGUAL E
			{
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " == " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}

			| E TK_DIFERENTE E
			{
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " != " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}

			| E TK_MAIOR E
			{
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " > " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}

			| E TK_MENOR E
			{
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " < " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| E TK_MAIORI E
			{
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " >= " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| E TK_MENORI E
			{
				$$.label = generateLabel();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " <= " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
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
				$$.tipo = "int";
			}
			| TK_FLOAT
			{
				$$.label = generateLabel();
				varDeclar += "float " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = "float";
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
				$$.tipo = "unsigned char";

			}
			| TK_CHAR
			{
				$$.label = generateLabel();
				varDeclar += "char " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label +  ";\n";
				$$.tipo = "char";
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

TIPO 		: TK_TIPO_INT
			{
				$$.tipo = "int";
			}
			| TK_TIPO_FLOAT
			{
				$$.tipo = "float";
			}
			| TK_TIPO_BOOL
			{
				$$.tipo = "unsigned char";
			}
			| TK_TIPO_CHAR
			{
				$$.tipo = "char";
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