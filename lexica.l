%{
#include <string>
#include "helper.h"

%}

ESPACO [ \t]
ALGARISMO [0-9]
LETRA [A-Za-z]
ASCII [ -~]
ASCIIFULL [\0-~]

BOOL ("false"|"true")
DELIM {ESPACO}+
INT {ALGARISMO}+
FLOAT {INT}+("."{INT}+)?
CHAR \'{ASCIIFULL}\'
ID {LETRA}({LETRA}|{INT})*
COMENTARIO "//"{ASCII}*"\n"
COMENTARIO_MULT_LINHA "/*"{ASCIIFULL}*"*/"

%%

"\n"		{ line++; return TK_ENDL; }
";"			{ return TK_ENDL; }

{DELIM} 	{}

"print"		{return TK_PRINT;}

"int"		{return TK_TIPO_INT;}
"float"		{return TK_TIPO_FLOAT;}
"bool"		{return TK_TIPO_BOOL;}
"char"		{return TK_TIPO_CHAR;}
"list"		{return TK_TIPO_LIST;}

"main"		{return TK_MAIN;}
"do"		{return TK_BLOCO_ABRIR;}
"end"		{return TK_BLOCO_FECHAR;}
"if"		{return TK_IF;}
"else"		{return TK_ELSE;}
"for"		{return TK_FOR;}
"stepping"	{return TK_STEPPING;}
"from"		{return TK_FROM;}
"to"		{return TK_TO;}
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
"<-"		{ return TK_ATRIB;}

"~"			{ return TK_NOT;}
"and"		{ return TK_AND;}
"or" 		{ return TK_OR;}
"~="		{ return TK_DIFERENTE;}
"="			{ return TK_IGUAL;}

">" 		{ return TK_MAIOR;}
"<"			{ return TK_MENOR;}
">="		{ return TK_MAIORI;}
"<="		{ return TK_MENORI;}
":"			{ return TK_DOTS;}

[(){}[\];,]	{ return *yytext; }

{INT}			{ yylval.label = yytext; return TK_INT; }
{FLOAT}			{ yylval.label = yytext; return TK_FLOAT; }
{BOOL}			{ yylval.label = yytext; return TK_BOOL; }
{CHAR}			{ yylval.label = yytext; return TK_CHAR;}
{ID}			{ yylval.label = yytext; return TK_ID; }
{COMENTARIO}	{ yylval.label = yytext; return TK_COMENTARIO; }
{COMENTARIO_MULT_LINHA} {yylval.label = yytext; return TK_COMENTARIO_MULT_LINHA; }

.			{ *yytext; }

%%
