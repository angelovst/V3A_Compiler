%{
#include <string>

%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]

BOOL ("false"|"true")
DELIM {ESPACO}+
INT {DIGITO}+
FLOAT {INT}+("."{INT}+)?
CHAR \'({LETRA}|{INT})\'
ID {LETRA}({LETRA}|{INT})*
STRING \"([^\"\n]|\\\")*\"

%%

"\n"		{}

{DELIM} 	{}

"print"		{return TK_PRINT;}

"int"		{return TK_TIPO_INT;}
"float"		{return TK_TIPO_FLOAT;}
"bool"		{return TK_TIPO_BOOL;}
"char"		{return TK_TIPO_CHAR;}
"list"		{return TK_TIPO_LIST;}
"string"	{return TK_TIPO_STR;}

"main"		{return TK_MAIN;}
"{"			{return TK_BLOCO_ABRIR;}
"}"			{return TK_BLOCO_FECHAR;}
"if"		{return TK_IF;}
"else"		{return TK_ELSE;}
"for"		{return TK_FOR;}
"do"		{return TK_DO;}
"while"		{return TK_WHILE;}
"break"		{return TK_BREAK;}
"continue"	{return TK_CONTINUE;}
"all"		{return TK_ALL;}


"+"			{return TK_PLUS;}
"++"		{return TK_2MAIS;}
"--"		{return TK_2MENOS;}
"-"			{return TK_MINUS;}
"*"			{return TK_MULT;}
"/"			{return TK_DIV;}
"%"			{return TK_MOD;}

"~"			{ return TK_NOT;}
"and"		{ return TK_AND;}
"or" 		{ return TK_OR;}
"~="		{ return TK_DIFERENTE;}
"<-"		{ return TK_ATRIB;}
"="			{ return TK_IGUAL;}

"!"			{ return TK_NOT;}
"&&"		{ return TK_AND;}
"||" 		{ return TK_OR;}
"!="		{ return TK_DIFERENTE;}
"="			{ return TK_ATRIB;}
"=="		{ return TK_IGUAL;}
">" 		{ return TK_MAIOR;}
"<"			{ return TK_MENOR;}
">="		{ return TK_MAIORI;}
"<="		{ return TK_MENORI;}
":"			{ return TK_DOTS;}

[(){}[\];,]	{ return *yytext; }

{INT}		{ yylval.label = yytext; return TK_TIPO_INT; }
{FLOAT}		{ yylval.label = yytext; return TK_TIPO_FLOAT; }
{BOOL}		{ yylval.label = yytext; return TK_TIPO_BOOL; }
{CHAR}		{ yylval.label = yytext; return TK_TIPO_CHAR;}
{ID}		{ yylval.label = yytext; return TK_ID; }
{STRING}	{ yylval.label = yytext; return TK_STR;}

.			{ *yytext; }

%%
