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
CHAR \'(({ASCIIFULL})|(\\{ASCIIFULL}))\'
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
"matrix"	{return TK_TIPO_MATRIX;}
"vector"	{return TK_TIPO_VECTOR;}
"list"		{return TK_TIPO_LIST;}

"type"		{return TK_STRUCT;}
"has"		{return TK_HAS;}
"'s"		{return TK_MEMBER_ACCESS;}

"main"		{return TK_MAIN;}
"do"		{return TK_BLOCO_ABRIR;}
"end"		{return TK_BLOCO_FECHAR;}
"if"		{return TK_IF;}
"else"		{return TK_ELSE;}
"for"		{return TK_FOR;}
"stepping"	{return TK_STEPPING;}
"from"		{return TK_FROM;}
"to"		{return TK_TO;}
"while"		{return TK_WHILE;}
"repeat"	{return TK_REPEAT;}
"until"		{return TK_UNTIL;}
"break"		{return TK_BREAK;}
"continue"	{return TK_CONTINUE;}
"all"		{return TK_ALL;}
"switch"	{return TK_SWITCH;}
"case"		{return TK_CASE;}
"default"	{return TK_DEFAULT;}


"+"			{ yylval.label = yytext; yylval.tipo = &tipo_arithmetic_operator;return TK_PLUS;}
"-"			{ yylval.label = yytext; yylval.tipo = &tipo_arithmetic_operator;return TK_MINUS;}
"*"			{ yylval.label = yytext; yylval.tipo = &tipo_arithmetic_operator;return TK_MULT;}
"/"			{ yylval.label = yytext; yylval.tipo = &tipo_arithmetic_operator;return TK_DIV;}
"%"			{ yylval.label = yytext; yylval.tipo = &tipo_arithmetic_operator;return TK_MOD;}
"<-"		{ yylval.label = "="; yylval.tipo = &tipo_atrib_operator;return TK_ATRIB;}
"++"		{ return TK_2MAIS; }
"--"		{ return TK_2MENOS; }

"~"			{ yylval.label = "!" ; return TK_NOT;}
"and"		{ yylval.label = "&" ; yylval.tipo = &tipo_logic_operator; return TK_AND;}
"or" 		{ yylval.label = "|" ; yylval.tipo = &tipo_logic_operator; return TK_OR;}
"~="		{ yylval.label = "!=" ; yylval.tipo = &tipo_logic_operator; return TK_DIFERENTE;}
"="			{ yylval.label = "==" ; yylval.tipo = &tipo_logic_operator; return TK_IGUAL;}

">" 		{ yylval.label = yytext ; yylval.tipo = &tipo_logic_operator; return TK_MAIOR;}
"<"			{ yylval.label = yytext ; yylval.tipo = &tipo_logic_operator; return TK_MENOR;}
">="		{ yylval.label = yytext ; yylval.tipo = &tipo_logic_operator; return TK_MAIORI;}
"<="		{ yylval.label = yytext ; yylval.tipo = &tipo_logic_operator; return TK_MENORI;}
":"			{ return TK_DOTS;}

"["	{ return TK_OPEN_MEMBER; }
"]" { return TK_CLOSE_MEMBER; }

"push"		{ return TK_PUSH; }

[(){}[\];,]		{ return *yytext; }

{INT}			{ yylval.label = yytext; return TK_INT; }
{FLOAT}			{ yylval.label = yytext; return TK_FLOAT; }
{BOOL}			{ yylval.label = yytext; return TK_BOOL; }
{CHAR}			{ yylval.label = yytext; return TK_CHAR;}
{ID}			{ yylval.label = yytext; return TK_ID; }
{COMENTARIO}	{ yylval.label = yytext; return TK_COMENTARIO; }
{COMENTARIO_MULT_LINHA} {yylval.label = yytext; return TK_COMENTARIO_MULT_LINHA; }

.			{ *yytext; }

%%
