%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#define YYSTYPE atributos

using namespace std;

string generateVar() {

	static unsigned int i = 1;
	return "TMP" + to_string(i++);
}

string generateLabel() {

	static unsigned int i = 1;
	return "label_" + to_string(i++);
}

typedef struct atributos {

	string label;
	string traducao;
	string tipo;
	string tamanho;
}atributos;

typedef struct loopLabel {

	string inicio;		
	string progressao;
	string fim;
}loopLabel;

//DECLARACOES DE FUNCOES

void empContexto();

void desempContexto();

atributos* findVarOnTop(string label);

atributos* findVar(string label);

string findTmpName(string label);

void empLoop();

void desempLoop();

loopLabel* getLoop(int tamLoop);

loopLabel* getOuterLoop();

int yylex(void);
void yyerror(string);

//Pilha de variaveis
std::vector<map<string, atributos>> varMap;

//Pilha de labels de loop
std::vector<loopLabel> loopMap;

//String para declaracao de var
string varDeclar;

%}

%token TK_INT TK_FLOAT TK_BOOL TK_CHAR TK_STR TK_IF TK_ELSE TK_FOR TK_DO TK_WHILE TK_BREAK TK_ALL TK_CONTINUE TK_PRINT
%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_BOOL TK_TIPO_CHAR TK_TIPO_STR
%token TK_DOTS TK_2MAIS TK_2MENOS
%token TK_FIM TK_ERROR

%start S

%right TK_ATRIB
%left TK_OR TK_AND TK_NOT
%nonassoc TK_IGUAL TK_DIFERENTE
%nonassoc TK_MAIOR TK_MENOR TK_MAIORI TK_MENORI
%left '+' '-'
%left '*' '/'
%left TK_MOD
%right TK_2MAIS TK_2MENOS

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
				empContexto();
				
				$$.traducao = "";
				$$.label = "";
			};
			
ESCOPO_FIM	:	{
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
				$$.traducao = $1.traducao + $2.traducao;
			}
			| {$$.traducao = "";}
			;

COMANDO 	: E ';'
			{
				$$.traducao = $1.traducao;
			}

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

E 			: E '+' E
			{
				atributos *id1 = findVar($1.label);
				atributos *id2 = findVar($3.label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = $1.label;
					tipo1 = $1.tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = $3.label;
					tipo2 = $3.tipo;
				}


				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao;
				string aux;
				if(tipo1 == "int" && tipo2 == "float"){

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + label1 + ";\n";
					aux = generateVar();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + label2 + " + " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";

				
				}else if(tipo1 == "float" && tipo2 == "int"){
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + label2 + ";\n";
					aux = generateVar();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + label1 + " + " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";
				
				}else if((tipo1 == "int" && tipo2 == "int") || (tipo1 == "float" && tipo2 == "float") ){
					varDeclar += "int " + $$.label + ";\n\t";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + label1 + " + " + label2 + ";\n";
				}
				else {
					yyerror("Operacao de soma nao contemplada pelo compilador");
				}


				
			}
			| E '*' E
			{
				atributos *id1 = findVar($1.label);
				atributos *id2 = findVar($3.label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = $1.label;
					tipo1 = $1.tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = $3.label;
					tipo2 = $3.tipo;
				}


				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao;
				string aux;
				if(tipo1 == "int" && tipo2 == "float"){

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + label1 + ";\n";
					aux = generateVar();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + label2 + " * " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";

				
				}else if(tipo1 == "float" && tipo2 == "int"){
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + label2 + ";\n";
					aux = generateVar();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + label1 + " * " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";
				
				}else if((tipo1 == "int" && tipo2 == "int") || (tipo1 == "float" && tipo2 == "float") ){
					varDeclar += "int " + $$.label + ";\n\t";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + label1 + " * " + label2 + ";\n";
				}
				else {
					yyerror("Operacao de mult nao contemplada pelo compilador");
				}


				
			}
			| E '/' E
			{
				atributos *id1 = findVar($1.label);
				atributos *id2 = findVar($3.label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = $1.label;
					tipo1 = $1.tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = $3.label;
					tipo2 = $3.tipo;
				}


				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao;
				string aux;
				if(tipo1 == "int" && tipo2 == "float"){

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + label1 + ";\n";
					aux = generateVar();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + label2 + " / " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";

				
				}else if(tipo1 == "float" && tipo2 == "int"){
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + label2 + ";\n";
					aux = generateVar();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + label1 + " / " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";
				
				}else if((tipo1 == "int" && tipo2 == "int") || (tipo1 == "float" && tipo2 == "float") ){
					varDeclar += "int " + $$.label + ";\n\t";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + label1 + " / " + label2 + ";\n";
				}
				else {
					yyerror("Operacao de div nao contemplada pelo compilador");
				}


				
			}
			| E '-' E
			{
				atributos *id1 = findVar($1.label);
				atributos *id2 = findVar($3.label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = $1.label;
					tipo1 = $1.tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = $3.label;
					tipo2 = $3.tipo;
				}


				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao;
				string aux;
				if(tipo1 == "int" && tipo2 == "float"){

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + label1 + ";\n";
					aux = generateVar();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + label2 + " - " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";

				
				}else if(tipo1 == "float" && tipo2 == "int"){
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + "(float)" + label2 + ";\n";
					aux = generateVar();
					varDeclar += "float " + $$.label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					$$.traducao = $$.traducao + "\t" + aux + " = " + label1 + " - " + $$.label + ";\n";
					$$.label = aux;
					$$.tipo = "float";
				
				}else if((tipo1 == "int" && tipo2 == "int") || (tipo1 == "float" && tipo2 == "float") ){
					varDeclar += "int " + $$.label + ";\n\t";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + label1 + " - " + label2 + ";\n";
				}
				else {
					yyerror("Operacao de sub nao contemplada pelo compilador");
				}


				
			}
			| E TK_AND E
			{	
				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " && " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| E TK_OR E
			{
				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " || " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| E TK_IGUAL E
			{
				atributos *id1 = findVar($1.label);
				atributos *id2 = findVar($3.label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = $1.label;
					tipo1 = $1.tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = $3.label;
					tipo2 = $3.tipo;
				}

				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + label1 + " == " + label2 + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}

			| E TK_DIFERENTE E
			{
				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " != " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}

			| E TK_MAIOR E
			{
				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " > " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}

			| E TK_MENOR E
			{
				atributos *id1 = findVar($1.label);
				atributos *id2 = findVar($3.label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = $1.label;
					tipo1 = $1.tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = $3.label;
					tipo2 = $3.tipo;
				}

				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + label1 + " < " + label2 + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| E TK_MAIORI E
			{
				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " >= " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| E TK_MENORI E
			{
				$$.label = generateVar();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " <= " + $3.label + ";\n";
				$$.tipo = "unsigned char";
				varDeclar += "unsigned char " + $$.label + ";\n\t";
			}
			| '(' TIPO ')' E
			{	
				
				$$.label = generateVar();
				varDeclar += $2.tipo + " " + $$.label + ";\n\t";
				$$.tipo = $2.tipo;
				$$.traducao = $4.traducao + "\t" + $$.label + " =" + '(' + $2.tipo + ')' + $4.label + ";\n";
			}

			| '(' E ')'
			{
				$$.label = $2.label; //generateVar();
				$$.traducao = $2.traducao;// + "\t" + $$.label + " = " + $2.label + ";\n";
			}
			| '-' E
			{
				$$.label = generateVar();
				$$.traducao = $2.traducao + "\t" + $$.label + " = " + " - " + $2.label + ";\n";
			}

			| INCREMENTOS

			| TK_INT
			{
				$$.label = generateVar();
				varDeclar += "int " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = "int";
			}
			| TK_FLOAT
			{
				$$.label = generateVar();
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

				$$.label = generateVar();
				varDeclar += "unsigned char " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + aux + ";\n";
				$$.tipo = "unsigned char";

			}
			| TK_CHAR
			{
				$$.label = generateVar();
				varDeclar += "char " + $$.label + ";\n\t";
				$$.traducao = "\t" + $$.label + " = " + $1.label +  ";\n";
				$$.tipo = "char";
			}
			| TK_STR
			{
				$$.tamanho = to_string($1.label.size() - 1);
				$$.label = generateVar();
				varDeclar += "char[" + $$.tamanho + "] " + $$.label + ";\n\t";
				$$.traducao = "\tstrcpy(" + $$.label + ", " + $1.label + ");\n";
				$$.tipo = "char ";
			}
			| TK_ID
			{
				atributos *id = findVar($1.label);
				if(id != nullptr) {
					$$.tipo = id->tipo;
					$$.label = $1.label;
				}
				else {
				$$.label = generateVar();
				$$.traducao = "\t" + $$.label + " = " + $1.label + ":\n";
				}
			}

			
			
			;

INCREMENTOS	: TK_ID SINAL_DUPL {

				atributos *id = findVar($1.label);
				if ( id == nullptr ) yyerror("Variavel " + $1.label + " nao declarada para ser incrementada");

				if(id->tipo != "int") yyerror("Variavel " + $1.label + " nao pode ser incrementada (tipo diferente de int)");

				string var1 = generateVar();
				string var2 = generateVar();

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

				if( id->tipo != "int" ) yyerror("Variavel " + $2.label + " nao pode ser incrementada (tipo diferente de int)");

				string var = generateVar();
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
				if($2.tipo != "unsigned char") yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVar();
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

				if($2.tipo != "unsigned char") yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVar();
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
				if($3.tipo != "unsigned char") yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVar();
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
				if($3.tipo != "unsigned char") yyerror("Tipo da expressao do else if DEVE ser bool");

				string var = generateVar();
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
				else if ( $1.tipo == "char ") {
					$$.label = generateVar();
					$$.tipo = $1.tipo;
					varDeclar += $1.traducao + $2.traducao + $$.tipo + $$.label + "[200];\n\t";
					(*mapLocal)[$2.label] = $$;
				}
				else {
					$$.label = generateVar();
					$$.tipo = $1.tipo;
					varDeclar += $1.traducao + $2.traducao + $$.tipo + " " + $$.label + ";\n\t";
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
						$$.label = generateVar();
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
			| TK_ID TK_ATRIB E
			{
				atributos* atr;
				if ( atr = findVar($1.label) ) {
					if(atr->tipo == $3.tipo) {
						if($3.tipo == "char ") {
							if($3.tamanho <= atr->tamanho ) {								
								$$.traducao = $3.traducao + "\t" + "strcpy(" + atr->label + ", " + $3.label + ");\n";
							}
							else {
								
								string var = generateVar();
								varDeclar += "char[" + $3.tamanho + "] " + var + ";\n\t";
								
								atr->label = var;

								$$.traducao = $3.traducao + "\t" + "strcpy(" + atr->label + ", " + $3.label + ");\n";;

							}
						}
						else { 
							$$.traducao = $3.traducao + "\t" + atr->label + " = " + $3.label + ";\n";
						}
					}
					else yyerror("atr de tipos incompativeis");
				}
				else {
					std::map<string, atributos> *mapLocal = &varMap.back();
					$$.label = $3.label;
					$$.tipo = $3.tipo;
					$$.traducao = $3.traducao;
					$$.tamanho = $3.tamanho;
					(*mapLocal)[$1.label] = $$;

				}
			}
			;

LOOP 		: TK_FOR ATRIBUICAO ';' E ';' INCREMENTOS TK_DOTS BLOCO {
				if ($4.tipo != "unsigned char") yyerror("Tipo da expressao do for DEVE ser bool");

				string var = generateVar();
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
				if ($2.tipo != "unsigned char") yyerror("Tipo da expressao do while DEVE ser bool");

				string var = generateVar();
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

				if ($4.tipo != "unsigned char") yyerror("Tipo da expressao do DO WHILE DEVE ser bool");

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
			| TK_TIPO_STR
			{
				$$.tipo = "char ";
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
	map<string, atributos> mapa;
	varMap.push_back(mapa);
}

void desempContexto() {
	return varMap.pop_back();
}
//FUNCOES PARA CONTROLE DOS BLOCOS DE LOOP
void empLoop() {
	string inicio = generateLabel();
	string progressao = generateLabel();
	string fim = generateLabel();
	loopLabel novo = {inicio, progressao, fim};
	loopMap.push_back(novo);
}

void desempLoop() {
	return loopMap.pop_back();
}

loopLabel* getLoop(int tamLoop) {
	if (loopMap.size() && tamLoop <= loopMap.size() && tamLoop > 0) {
		//cout << loopMap.size() << " " << tamLoop << endl;
		return &loopMap[loopMap.size() - tamLoop];
	} else {
		return nullptr;
	}
}

loopLabel* getOuterLoop() {
	if (loopMap.size()) {
		return &loopMap[0];
	} else {
		return nullptr;
	}
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