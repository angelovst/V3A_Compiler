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

%%

"\n"		{}

{DELIM} 	{}

"main"		{return TK_MAIN;}

"int"		{return TK_TIPO_INT;}

"float"		{return TK_TIPO_FLOAT;}

"bool"		{return TK_TIPO_BOOL;}

"char"		{return TK_TIPO_CHAR;}

"%"			{return TK_MOD;}

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

[(){}[\];,]	{ return *yytext; }

[+\-*/]		{ return *yytext; }

{INT}		{ yylval.label = yytext; return TK_INT; }
{FLOAT}		{ yylval.label = yytext; return TK_FLOAT; }
{BOOL}		{ yylval.label = yytext; return TK_BOOL; }
{CHAR}		{ yylval.label = yytext; return TK_CHAR;}
{ID}		{ yylval.label = yytext; return TK_ID; }

.			{ *yytext; }

%%
