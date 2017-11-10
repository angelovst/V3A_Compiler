/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "sintatica.y"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "helper.h"
#define YYSTYPE atributos

#line 29 "y.tab.c"

#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define TK_INT 257
#define TK_FLOAT 258
#define TK_BOOL 259
#define TK_CHAR 260
#define TK_MAIN 261
#define TK_ID 262
#define tK_IF 263
#define TK_ELSE 264
#define TK_FOR 265
#define TK_DO 266
#define TK_WHILE 267
#define TK_TIPO_INT 268
#define TK_TIPO_FLOAT 269
#define TK_TIPO_BOOL 270
#define TK_TIPO_CHAR 271
#define TK_TIPO_LIST 272
#define TK_FIM 273
#define TK_ERROR 274
#define TK_ATRIB 275
#define TK_OR 276
#define TK_AND 277
#define TK_NOT 278
#define TK_IGUAL 279
#define TK_DIFERENTE 280
#define TK_MAIOR 281
#define TK_MENOR 282
#define TK_MAIORI 283
#define TK_MENORI 284
#define TK_PLUS 285
#define TK_MINUS 286
#define TK_MULT 287
#define TK_DIV 288
#define TK_MOD 289
#define TK_IF 290
#define TK_DOTS 291
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    3,    4,    5,    6,    7,    2,    2,    8,
    8,    8,    8,    8,    8,    9,    9,    9,    9,    9,
    9,    9,    9,    9,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   12,   12,   12,
   14,   14,   14,   11,   11,   11,   15,   10,   10,   10,
   10,   10,
};
static const YYINT yylen[] = {                            2,
    4,    3,    0,    0,    0,    0,    5,    2,    0,    2,
    3,    5,    4,    1,    1,    3,    4,    3,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    4,    5,    3,
    5,    6,    3,    3,    5,    4,    4,    1,    1,    1,
    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    1,   20,   21,   22,   23,
    0,   48,   49,   50,   51,   52,    0,    0,    0,    0,
    0,    0,    0,    0,   14,   15,    0,   24,    0,    0,
    0,    0,    2,    0,    6,    8,   31,   30,   33,   32,
   34,   35,   36,   37,   25,   26,   27,   28,   29,   10,
    0,    0,    0,   18,    0,    3,    0,   40,    0,    0,
   11,   13,    0,    0,    0,    3,    0,    0,    0,   39,
   47,   12,    0,    0,    3,    4,    0,   43,    7,    3,
    0,   42,
};
static const YYINT yydgoto[] = {                          2,
    6,   20,   64,   79,   21,   58,   65,   22,   23,   24,
   25,   26,   51,   70,   35,
};
static const YYINT yysindex[] = {                      -255,
  -29,    0,  -28, -111,   -1,    0,    0,    0,    0,    0,
 -261,    0,    0,    0,    0,    0,   33,  105,  105, -110,
 -249,   -1,   30, -243,    0,    0,  105,    0,   -4,  -14,
 -112, -189,    0,  105,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  105,  -52,   44,    0,  105,    0, -161,    0, -112,  105,
    0,    0, -112,  -94, -234,    0,   58,   -1, -282,    0,
    0,    0,  -93,  105,    0,    0, -128,    0,    0,    0,
 -234,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0, -124,    0,    0,    0,    0,    0,
   72,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -124,    0,    0,    0,    0,    0,    0,    0,    0,
  -39,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -37,    0,
    0,    0,  -31,    0,  -40,    0,    0, -124,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -24,    0,
};
static const YYINT yygindex[] = {                         0,
    0,  -19,    0,    0,    0,    0,  -49,    0,    6,   17,
    0,    0,    0,  -46,    0,
};
#define YYTABLESIZE 367
static const YYINT yytable[] = {                         38,
    9,   19,   36,   16,   38,    1,   61,   74,   75,   17,
    3,    5,    4,   27,   33,   41,   71,   34,   52,   19,
   41,   16,   29,   31,   32,   78,   55,   17,   68,   69,
   81,   76,   53,   30,   82,    0,   54,    0,   17,   57,
    0,    0,    0,   18,    0,    0,    0,    0,   73,    0,
    0,    0,    0,    0,    0,    0,   59,    0,    0,    0,
   63,    0,    0,    0,    0,   67,    0,    0,    0,    0,
    0,    0,   17,    0,    0,    0,    0,   18,    0,   77,
    0,    0,    0,    0,   38,    0,   37,   38,   50,   39,
   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,
   41,   56,   62,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   37,   38,   72,   39,   40,   41,
   42,   43,   44,   45,   46,   47,   48,   49,    0,   66,
   24,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    5,    0,   17,    0,    0,   37,   38,   18,
   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,
   49,    0,   80,   37,   38,    0,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   38,   38,   38,   38,
    0,   38,   60,    0,    0,    0,   38,   38,   38,   38,
   38,   38,   41,   41,   41,   41,    0,   41,    0,    0,
    0,    0,   41,   41,   41,   41,   41,   41,    0,   38,
    0,   19,    0,   16,    0,    7,    8,    9,   10,   17,
   11,    0,    0,    0,    0,   41,   12,   13,   14,   15,
   16,   37,   38,    0,   39,   40,   41,   42,   43,   44,
   45,   46,   47,   48,   49,    0,    0,    0,   19,    7,
    8,    9,   10,    0,   28,    0,    0,    0,    0,    0,
   12,   13,   14,   15,   16,   37,   38,    0,   39,   40,
   41,   42,   43,   44,   45,   46,   47,   48,   49,   37,
   38,    0,   39,   40,   41,   42,   43,   44,   45,   46,
   47,   48,   49,   37,   38,    0,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   24,   24,    0,
   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,
   24,    7,    8,    9,   10,    0,   28,
};
static const YYINT yycheck[] = {                         40,
  125,   41,   22,   41,   45,  261,   59,  290,  291,   41,
   40,  123,   41,  275,  125,   40,   66,  267,  262,   59,
   45,   59,   17,   18,   19,   75,   41,   59,  123,  264,
   80,  125,   27,   17,   81,   -1,   41,   -1,   40,   34,
   -1,   -1,   -1,   45,   -1,   -1,   -1,   -1,   68,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   51,   -1,   -1,   -1,
   55,   -1,   -1,   -1,   -1,   60,   -1,   -1,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   -1,   -1,   45,   -1,   74,
   -1,   -1,   -1,   -1,  125,   -1,  276,  277,   59,  279,
  280,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  125,  291,   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  276,  277,   59,  279,  280,  281,
  282,  283,  284,  285,  286,  287,  288,  289,   -1,  291,
   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  267,   -1,   40,   -1,   -1,  276,  277,   45,
  279,  280,  281,  282,  283,  284,  285,  286,  287,  288,
  289,   -1,  291,  276,  277,   -1,  279,  280,  281,  282,
  283,  284,  285,  286,  287,  288,  289,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
   -1,  262,  275,   -1,   -1,   -1,  267,  268,  269,  270,
  271,  272,  257,  258,  259,  260,   -1,  262,   -1,   -1,
   -1,   -1,  267,  268,  269,  270,  271,  272,   -1,  290,
   -1,  291,   -1,  291,   -1,  257,  258,  259,  260,  291,
  262,   -1,   -1,   -1,   -1,  290,  268,  269,  270,  271,
  272,  276,  277,   -1,  279,  280,  281,  282,  283,  284,
  285,  286,  287,  288,  289,   -1,   -1,   -1,  290,  257,
  258,  259,  260,   -1,  262,   -1,   -1,   -1,   -1,   -1,
  268,  269,  270,  271,  272,  276,  277,   -1,  279,  280,
  281,  282,  283,  284,  285,  286,  287,  288,  289,  276,
  277,   -1,  279,  280,  281,  282,  283,  284,  285,  286,
  287,  288,  289,  276,  277,   -1,  279,  280,  281,  282,
  283,  284,  285,  286,  287,  288,  289,  276,  277,   -1,
  279,  280,  281,  282,  283,  284,  285,  286,  287,  288,
  289,  257,  258,  259,  260,   -1,  262,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 291
#define YYUNDFTOKEN 309
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,0,"'-'",0,0,0,0,0,0,0,0,0,0,0,0,0,"';'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TK_INT",
"TK_FLOAT","TK_BOOL","TK_CHAR","TK_MAIN","TK_ID","tK_IF","TK_ELSE","TK_FOR",
"TK_DO","TK_WHILE","TK_TIPO_INT","TK_TIPO_FLOAT","TK_TIPO_BOOL","TK_TIPO_CHAR",
"TK_TIPO_LIST","TK_FIM","TK_ERROR","TK_ATRIB","TK_OR","TK_AND","TK_NOT",
"TK_IGUAL","TK_DIFERENTE","TK_MAIOR","TK_MENOR","TK_MAIORI","TK_MENORI",
"TK_PLUS","TK_MINUS","TK_MULT","TK_DIV","TK_MOD","TK_IF","TK_DOTS",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : S",
"S : TK_MAIN '(' ')' MAIN",
"MAIN : '{' COMANDOS '}'",
"ESCOPO_INICIO :",
"ESCOPO_FIM :",
"LOOP_INICIO :",
"LOOP_FIM :",
"BLOCO : ESCOPO_INICIO '{' COMANDOS '}' ESCOPO_FIM",
"COMANDOS : COMANDO COMANDOS",
"COMANDOS :",
"COMANDO : E ';'",
"COMANDO : TIPO TK_ID ';'",
"COMANDO : TIPO TK_ID TK_ATRIB E ';'",
"COMANDO : TK_ID TK_ATRIB E ';'",
"COMANDO : ATRIBUICAO",
"COMANDO : CONTROLE",
"E : E OP_INFIX E",
"E : '(' TIPO ')' E",
"E : '(' E ')'",
"E : '-' E",
"E : TK_INT",
"E : TK_FLOAT",
"E : TK_BOOL",
"E : TK_CHAR",
"E : TK_ID",
"OP_INFIX : TK_PLUS",
"OP_INFIX : TK_MINUS",
"OP_INFIX : TK_MULT",
"OP_INFIX : TK_DIV",
"OP_INFIX : TK_MOD",
"OP_INFIX : TK_AND",
"OP_INFIX : TK_OR",
"OP_INFIX : TK_DIFERENTE",
"OP_INFIX : TK_IGUAL",
"OP_INFIX : TK_MAIOR",
"OP_INFIX : TK_MENOR",
"OP_INFIX : TK_MAIORI",
"OP_INFIX : TK_MENORI",
"CONTROLE : TK_IF E TK_DOTS BLOCO",
"CONTROLE : TK_IF E TK_DOTS BLOCO CONTROLE_ALT",
"CONTROLE : LOOP_INICIO LOOP LOOP_FIM",
"CONTROLE_ALT : TK_ELSE TK_IF E TK_DOTS BLOCO",
"CONTROLE_ALT : TK_ELSE TK_IF E TK_DOTS BLOCO CONTROLE_ALT",
"CONTROLE_ALT : TK_ELSE TK_DOTS BLOCO",
"ATRIBUICAO : TIPO TK_ID ';'",
"ATRIBUICAO : TIPO TK_ID TK_ATRIB E ';'",
"ATRIBUICAO : TK_ID TK_ATRIB E ';'",
"LOOP : TK_WHILE E TK_DOTS BLOCO",
"TIPO : TK_TIPO_INT",
"TIPO : TK_TIPO_FLOAT",
"TIPO : TK_TIPO_BOOL",
"TIPO : TK_TIPO_CHAR",
"TIPO : TK_TIPO_LIST",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 496 "sintatica.y"

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
#line 384 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 27 "sintatica.y"
	{
				cout << "/*Compilador V3A*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" << "\t" + varDeclar + "\n" << yystack.l_mark[0].traducao << "\treturn 0;\n}" << endl;

			}
break;
case 2:
#line 34 "sintatica.y"
	{
				yyval.traducao = yystack.l_mark[-1].traducao;
			}
break;
case 3:
#line 39 "sintatica.y"
	{
				cout << "contexto empilhado" << endl;	/*debug*/
				empContexto();
				
				yyval.traducao = "";
				yyval.label = "";
			}
break;
case 4:
#line 47 "sintatica.y"
	{
				cout << "contexto desempilhado" << endl;	/*debug*/
				desempContexto();
				
				yyval.traducao = "";
				yyval.label = "";
			}
break;
case 5:
#line 56 "sintatica.y"
	{
				empLoop();
				empContexto();
				
				yyval.traducao = "";
				yyval.label = "";
			}
break;
case 6:
#line 64 "sintatica.y"
	{
				desempLoop();
				desempContexto();
				
				yyval.traducao = "";
				yyval.label = "";
			}
break;
case 7:
#line 72 "sintatica.y"
	{
				yyval.traducao = yystack.l_mark[-2].traducao;
			}
break;
case 8:
#line 77 "sintatica.y"
	{
				cout << "comando traduzido" << endl;	/*debug*/
				yyval.traducao = yystack.l_mark[-1].traducao + yystack.l_mark[0].traducao;
			}
break;
case 9:
#line 81 "sintatica.y"
	{yyval.traducao = "";}
break;
case 11:
#line 87 "sintatica.y"
	{
				cout << "variavel declarada" << endl;	/*debug*/
				std::map<string, atributos> *mapLocal = &varMap.back();

				if(mapLocal->find(yystack.l_mark[-1].label) != mapLocal->end()) {
					yyerror("Variavel ja declarada localmente");
				}
				else {
					yyval.label = generateVarLabel();
					yyval.tipo = yystack.l_mark[-2].tipo;
					varDeclar += yystack.l_mark[-2].traducao + yystack.l_mark[-1].traducao + yyval.tipo->label + " " + yyval.label + ";\n\t";
					(*mapLocal)[yystack.l_mark[-1].label] = yyval;
				}
					

			}
break;
case 12:
#line 105 "sintatica.y"
	{	
				cout << "variavel declarada com atribuicao" << endl;	/*debug*/
				std::map<string, atributos> *mapLocal = &varMap.back();
				if(mapLocal->find(yystack.l_mark[-3].label) != mapLocal->end()) {
        			yyerror("Variavel usada para atribuicao ja declarada");	
				}
				else if( yystack.l_mark[-4].tipo->label == yystack.l_mark[-1].tipo->label ){
					if (mapLocal->find(yystack.l_mark[-1].label) != mapLocal->end())	{
						yyval.label = generateVarLabel();
						yyval.tipo = yystack.l_mark[-4].tipo;
						yyval.traducao = "\t" + yyval.label + " = " + (*mapLocal)[yystack.l_mark[-1].label].label + ";\n";
						varDeclar += yystack.l_mark[-4].traducao + yystack.l_mark[-3].traducao + yyval.tipo->label + " " + yyval.label + ";\n\t";
						(*mapLocal)[yystack.l_mark[-3].label] = yyval;
					}
					else {
					yyval.label = yystack.l_mark[-1].label;
					yyval.traducao = yystack.l_mark[-4].traducao + yystack.l_mark[-3].traducao + yystack.l_mark[-1].traducao;
					yyval.tipo = yystack.l_mark[-4].tipo;
					(*mapLocal)[yystack.l_mark[-3].label] = yyval;
					}
				}
				else {
					yyerror("Atribuicao de tipos nao compativeis");
				}
			}
break;
case 13:
#line 131 "sintatica.y"
	{
				cout << "variavel atribuida" << endl;	/*debug*/
				std::map<string, atributos> *mapLocal = &varMap.back();
				
				if(mapLocal->find(yystack.l_mark[-3].label) != mapLocal->end()) {
					if((*mapLocal)[yystack.l_mark[-3].label].tipo->label == yystack.l_mark[-1].tipo->label) {
						yyval.traducao = yystack.l_mark[-1].traducao + "\t" + (*mapLocal)[yystack.l_mark[-3].label].label + " = " + yystack.l_mark[-1].label + ";\n";
					}
					else {
						yyerror("Tipos nao compativeis");
					}
				}
				else {
					yyval.label = yystack.l_mark[-1].label;
					yyval.tipo = yystack.l_mark[-1].tipo;
					yyval.traducao = yystack.l_mark[-1].traducao;
					(*mapLocal)[yystack.l_mark[-3].label] = yyval;

				}
			}
break;
case 16:
#line 158 "sintatica.y"
	{
				cout << "operacao infixa executada" << endl;	/*debug*/
				yyval.label = generateVarLabel();
				yyval.traducao = yystack.l_mark[-2].traducao + yystack.l_mark[0].traducao;
				string var1, var2;
				string cast = implicitCast (&yystack.l_mark[-2], &yystack.l_mark[-1], &var1, &var2);
				
				yyval.traducao += yyval.label + " = " + var1 + yystack.l_mark[-1].traducao + var2 + ";\n";
				
			}
break;
case 17:
#line 169 "sintatica.y"
	{	
				cout << "cast executado" << endl;	/*debug*/
				yyval.label = generateVarLabel();
				varDeclar += yystack.l_mark[-2].tipo->label + " " + yyval.label + ";\n\t";
				yyval.tipo = yystack.l_mark[-2].tipo;
				yyval.traducao = yystack.l_mark[0].traducao + "\t" + yyval.label + " =" + '(' + yystack.l_mark[-2].tipo->label + ')' + yystack.l_mark[0].label + ";\n";
			}
break;
case 18:
#line 178 "sintatica.y"
	{
				cout << "parentizacao feita" << endl;	/*debug*/
				yyval.label = yystack.l_mark[-1].label; /*generateVarLabel();*/
				yyval.traducao = yystack.l_mark[-1].traducao;/* + "\t" + $$.label + " = " + $2.label + ";\n";*/
			}
break;
case 19:
#line 184 "sintatica.y"
	{
				cout << "inversao feita" << endl;	/*debug*/
				yyval.label = generateVarLabel();
				yyval.traducao = yystack.l_mark[0].traducao + "\t" + yyval.label + " = " + " - " + yystack.l_mark[0].label + ";\n";
			}
break;
case 20:
#line 190 "sintatica.y"
	{
				yyval.label = generateVarLabel();
				varDeclar += "int " + yyval.label + ";\n\t";
				yyval.traducao = "\t" + yyval.label + " = " + yystack.l_mark[0].label + ";\n";
				yyval.tipo = &tipo_int;
			}
break;
case 21:
#line 197 "sintatica.y"
	{
				yyval.label = generateVarLabel();
				varDeclar += "float " + yyval.label + ";\n\t";
				yyval.traducao = "\t" + yyval.label + " = " + yystack.l_mark[0].label + ";\n";
				yyval.tipo = &tipo_float;
			}
break;
case 22:
#line 204 "sintatica.y"
	{
				string aux;
				
				if(yystack.l_mark[0].label == "true") {
					aux = "1";
				}
				else {
					aux = "0";
				}

				yyval.label = generateVarLabel();
				varDeclar += "unsigned char " + yyval.label + ";\n\t";
				yyval.traducao = "\t" + yyval.label + " = " + aux + ";\n";
				yyval.tipo = &tipo_bool;

			}
break;
case 23:
#line 221 "sintatica.y"
	{
				yyval.label = generateVarLabel();
				varDeclar += "char " + yyval.label + ";\n\t";
				yyval.traducao = "\t" + yyval.label + " = " + yystack.l_mark[0].label +  ";\n";
				yyval.tipo = &tipo_char;
			}
break;
case 24:
#line 228 "sintatica.y"
	{
				atributos *id = findVar(yystack.l_mark[0].label);
				if(id != nullptr) {
					yyval.tipo = id->tipo;
					yyval.label = yystack.l_mark[0].label;
				}
				/*if(varMap.find($1.label) != varMap.end()) {
        			$$.tipo = varMap[$1.label].tipo;
        			$$.label = varMap[$1.label].label;
				}*/
				else {
					yyval.label = generateVarLabel();
					yyval.traducao = "\t" + yyval.label + " = " + yystack.l_mark[0].label + ":\n";
				}
			}
break;
case 25:
#line 248 "sintatica.y"
	{
				yyval.label = "+";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 26:
#line 252 "sintatica.y"
	{
				yyval.label = "-";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 27:
#line 256 "sintatica.y"
	{
				yyval.label = "*";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 28:
#line 260 "sintatica.y"
	{
				yyval.label = "/";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 29:
#line 264 "sintatica.y"
	{
				yyval.label = "%";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 30:
#line 268 "sintatica.y"
	{
				yyval.label = "&&";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 31:
#line 272 "sintatica.y"
	{
				yyval.label = "||";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 32:
#line 276 "sintatica.y"
	{
				yyval.label = "!=";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 33:
#line 280 "sintatica.y"
	{
				yyval.label = "==";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 34:
#line 284 "sintatica.y"
	{
				yyval.label = ">";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 35:
#line 288 "sintatica.y"
	{
				yyval.label = "<";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 36:
#line 292 "sintatica.y"
	{
				yyval.label = ">=";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 37:
#line 296 "sintatica.y"
	{
				yyval.label = "<=";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 38:
#line 303 "sintatica.y"
	{
				if(yystack.l_mark[-2].tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLoopLabel();

				varDeclar += "int " + var + ";\n\t";
					
					yyval.traducao = "\n" + yystack.l_mark[-2].traducao + 
						"\t" + var + " = !" + yystack.l_mark[-2].label + ";\n" +
						"\tif (" + var + ") goto " + fim + ";\n\n" +
						yystack.l_mark[0].traducao +
						"\n\t" + fim + ":\n\n";
			}
break;
case 39:
#line 318 "sintatica.y"
	{

				if(yystack.l_mark[-3].tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLoopLabel();

				varDeclar += "int " + var + ";\n\t";

				yyval.traducao = "\n" + yystack.l_mark[-3].traducao + 
						"\t" + var + " = !" + yystack.l_mark[-3].label + ";\n" +
						"\tif (" + var + ") goto " + fim + ";\n\n" +
						yystack.l_mark[-1].traducao +
						"\tgoto " + yystack.l_mark[0].label + ";\n\n" +
						"\t" + fim + ":" + yystack.l_mark[0].traducao;
				
			}
break;
case 40:
#line 337 "sintatica.y"
	{
				yyval.traducao = yystack.l_mark[-1].traducao;
			}
break;
case 41:
#line 344 "sintatica.y"
	{
				if(yystack.l_mark[-2].tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLoopLabel();

				varDeclar += "int " + var + ";\n\t";

				yyval.label = fim;
				yyval.traducao = "\n" + yystack.l_mark[-2].traducao + 
						"\t" + var + " = !" + yystack.l_mark[-2].label + ";\n\n" +
						"\tif (" + var + ") goto " + fim + ";\n" +
						yystack.l_mark[0].traducao +
						"\n\t" + fim + ":\n";

			}
break;
case 42:
#line 362 "sintatica.y"
	{
				if(yystack.l_mark[-3].tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do else if DEVE ser bool");

				string var = generateVarLabel();
				string fim = generateLoopLabel();

				varDeclar += "int " + var + ";\n\t";

				yyval.label = yystack.l_mark[0].label;
				yyval.traducao = "\n" + yystack.l_mark[-3].traducao + 
						"\t" + var + " = !" + yystack.l_mark[-3].label + ";\n\n" +
						"\tif (" + var + ") goto " + fim + ";\n" +
						yystack.l_mark[-1].traducao +
						"\n\tgoto " + yystack.l_mark[0].label + ";\n" +
						"\n\t" + fim + ":" + yystack.l_mark[0].traducao;

			}
break;
case 43:
#line 381 "sintatica.y"
	{
				yyval.label = generateLoopLabel();
				yyval.traducao = "\n" + yystack.l_mark[0].traducao + "\n\t" + yyval.label + ":\n";

			}
break;
case 44:
#line 392 "sintatica.y"
	{
				std::map<string, atributos> *mapLocal = &varMap.back();

				if(mapLocal->find(yystack.l_mark[-1].label) != mapLocal->end()) {
					yyerror("Variavel ja declarada localmente");
				}
				else {
					yyval.label = generateVarLabel();
					yyval.tipo = yystack.l_mark[-2].tipo;
					varDeclar += yystack.l_mark[-2].traducao + yystack.l_mark[-1].traducao + yyval.tipo->label + " " + yyval.label + ";\n\t";
					(*mapLocal)[yystack.l_mark[-1].label] = yyval;
				}
					

			}
break;
case 45:
#line 409 "sintatica.y"
	{	
				std::map<string, atributos> *mapLocal = &varMap.back();
				if(mapLocal->find(yystack.l_mark[-3].label) != mapLocal->end()) {
        			yyerror("Variavel usada para atribuicao ja declarada");	
				}
				else if( yystack.l_mark[-4].tipo == yystack.l_mark[-1].tipo ){
					if (mapLocal->find(yystack.l_mark[-1].label) != mapLocal->end())	{
						yyval.label = generateVarLabel();
						yyval.tipo = yystack.l_mark[-4].tipo;
						yyval.traducao = "\t" + yyval.label + " = " + (*mapLocal)[yystack.l_mark[-1].label].label + ";\n";
						varDeclar += yystack.l_mark[-4].traducao + yystack.l_mark[-3].traducao + yyval.tipo->label + " " + yyval.label + ";\n\t";
						(*mapLocal)[yystack.l_mark[-3].label] = yyval;
					}
					else {
					yyval.label = yystack.l_mark[-1].label;
					yyval.traducao = yystack.l_mark[-4].traducao + yystack.l_mark[-3].traducao + yystack.l_mark[-1].traducao;
					yyval.tipo = yystack.l_mark[-4].tipo;
					(*mapLocal)[yystack.l_mark[-3].label] = yyval;
					}
				}
				else {
					yyerror("Atribuicao de tipos nao compativeis");
				}
			}
break;
case 46:
#line 434 "sintatica.y"
	{
				std::map<string, atributos> *mapLocal = &varMap.back();
				
				if(mapLocal->find(yystack.l_mark[-3].label) != mapLocal->end()) {
					if((*mapLocal)[yystack.l_mark[-3].label].tipo == yystack.l_mark[-1].tipo) {
						yyval.traducao = yystack.l_mark[-1].traducao + "\t" + (*mapLocal)[yystack.l_mark[-3].label].label + " = " + yystack.l_mark[-1].label + ";\n";
					}
					else {
						yyerror("Tipos nao compativeis");
					}
				}
				else {
					yyval.label = yystack.l_mark[-1].label;
					yyval.tipo = yystack.l_mark[-1].tipo;
					yyval.traducao = yystack.l_mark[-1].traducao;
					(*mapLocal)[yystack.l_mark[-3].label] = yyval;

				}
			}
break;
case 47:
#line 456 "sintatica.y"
	{
				if (yystack.l_mark[-2].tipo->label != TIPO_BOOL) yyerror("Tipo da expressao do while DEVE ser bool");

				string var = generateVarLabel();
				loopLabel* loop = getLoop();
					
				varDeclar += "int " + var + ";\n\t";
					
				yyval.traducao = "\t" + loop->inicio + ":\n\t" 
					+ loop->progressao + ":\n" + yystack.l_mark[-2].traducao
					+ "\t" + var + " = !" + yystack.l_mark[-2].label + ";\n" +
					"\tif (" + var + ") goto " + loop->fim + ";\n" +
					yystack.l_mark[0].traducao +
					"\tgoto " + loop->inicio + ";\n\t" + loop->fim + ":\n";
				
			}
break;
case 48:
#line 474 "sintatica.y"
	{
				yyval.tipo = &tipo_int;
			}
break;
case 49:
#line 478 "sintatica.y"
	{
				yyval.tipo = &tipo_float;
			}
break;
case 50:
#line 482 "sintatica.y"
	{
				yyval.tipo = &tipo_bool;
			}
break;
case 51:
#line 486 "sintatica.y"
	{
				yyval.tipo = &tipo_char;
			}
break;
case 52:
#line 490 "sintatica.y"
	{
				yyval.tipo = &tipo_list;
			}
break;
#line 1126 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
