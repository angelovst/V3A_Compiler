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
#define TK_IF 262
#define TK_ID 263
#define TK_TIPO_INT 264
#define TK_TIPO_FLOAT 265
#define TK_TIPO_BOOL 266
#define TK_TIPO_CHAR 267
#define TK_TIPO_LIST 268
#define TK_FIM 269
#define TK_ERROR 270
#define TK_ATRIB 271
#define TK_OR 272
#define TK_AND 273
#define TK_NOT 274
#define TK_IGUAL 275
#define TK_DIFERENTE 276
#define TK_MAIOR 277
#define TK_MENOR 278
#define TK_MAIORI 279
#define TK_MENORI 280
#define TK_PLUS 281
#define TK_MINUS 282
#define TK_MULT 283
#define TK_DIV 284
#define TK_MOD 285
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    2,    2,    3,    3,    3,    3,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    5,    5,    5,    5,    5,
};
static const YYINT yylen[] = {                            2,
    4,    3,    2,    0,    2,    3,    5,    4,    3,    4,
    3,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    1,   13,   14,   15,   16,
    0,   31,   32,   33,   34,   35,    0,    0,    0,    0,
    0,    0,    0,   17,    0,    0,    0,    2,    3,   24,
   23,   26,   25,   27,   28,   29,   30,   18,   19,   20,
   21,   22,    5,    0,    0,    0,   11,    0,    0,    0,
    6,    8,    0,    0,    7,
};
static const YYINT yydgoto[] = {                          2,
    6,   19,   20,   21,   22,   44,
};
static const YYINT yysindex[] = {                      -251,
  -29,    0,  -28, -111,  -39,    0,    0,    0,    0,    0,
 -257,    0,    0,    0,    0,    0,  -12,   56, -110,  -39,
  -15, -247,   56,    0,  -41,  -24, -230,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   56,  -57,   -1,    0,   56, -230,   56,
    0,    0, -230,   13,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0, -107,    0,    0,    0,    0,    0,
   27,    0,    0,    0,    0,    0,    0,    0,    0, -107,
    0,    0,    0,    0,    0,    0,  -36,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -34,    0,
    0,    0,  -33,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,    1,    0,  -14,    2,    0,
};
#define YYTABLESIZE 319
static const YYINT yytable[] = {                         47,
   17,   51,   25,   27,   12,   18,    9,   10,   46,    1,
    3,    5,    4,   23,   28,   45,   48,    4,   26,    0,
   29,    0,   12,    0,    9,   10,    0,   17,    0,   49,
    0,    0,   18,   53,    0,   54,    0,    0,    0,    0,
    0,   30,   31,   43,   32,   33,   34,   35,   36,   37,
   38,   39,   40,   41,   42,    0,    0,   52,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   55,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   17,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   17,    0,    0,    0,    0,
   18,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   50,    0,    0,    0,    7,    8,    9,
   10,    0,    0,   11,   12,   13,   14,   15,   16,    0,
   30,   31,    0,   32,   33,   34,   35,   36,   37,   38,
   39,   40,   41,   42,    7,    8,    9,   10,    0,    0,
   24,   12,   13,   14,   15,   16,   30,   31,    0,   32,
   33,   34,   35,   36,   37,   38,   39,   40,   41,   42,
   30,   31,    0,   32,   33,   34,   35,   36,   37,   38,
   39,   40,   41,   42,   30,   31,    0,   32,   33,   34,
   35,   36,   37,   38,   39,   40,   41,   42,   17,   17,
    0,   17,   17,   17,   17,   17,   17,   17,   17,   17,
   17,   17,    7,    8,    9,   10,    0,    0,   24,
};
static const YYINT yycheck[] = {                         41,
   40,   59,   17,   18,   41,   45,   41,   41,   23,  261,
   40,  123,   41,  271,  125,  263,   41,  125,   17,   -1,
   20,   -1,   59,   -1,   59,   59,   -1,   40,   -1,   44,
   -1,   -1,   45,   48,   -1,   50,   -1,   -1,   -1,   -1,
   -1,  272,  273,   59,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,   -1,   -1,   59,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   40,   -1,   -1,   -1,   -1,
   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  271,   -1,   -1,   -1,  257,  258,  259,
  260,   -1,   -1,  263,  264,  265,  266,  267,  268,   -1,
  272,  273,   -1,  275,  276,  277,  278,  279,  280,  281,
  282,  283,  284,  285,  257,  258,  259,  260,   -1,   -1,
  263,  264,  265,  266,  267,  268,  272,  273,   -1,  275,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
  272,  273,   -1,  275,  276,  277,  278,  279,  280,  281,
  282,  283,  284,  285,  272,  273,   -1,  275,  276,  277,
  278,  279,  280,  281,  282,  283,  284,  285,  272,  273,
   -1,  275,  276,  277,  278,  279,  280,  281,  282,  283,
  284,  285,  257,  258,  259,  260,   -1,   -1,  263,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 285
#define YYUNDFTOKEN 294
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
"TK_FLOAT","TK_BOOL","TK_CHAR","TK_MAIN","TK_IF","TK_ID","TK_TIPO_INT",
"TK_TIPO_FLOAT","TK_TIPO_BOOL","TK_TIPO_CHAR","TK_TIPO_LIST","TK_FIM",
"TK_ERROR","TK_ATRIB","TK_OR","TK_AND","TK_NOT","TK_IGUAL","TK_DIFERENTE",
"TK_MAIOR","TK_MENOR","TK_MAIORI","TK_MENORI","TK_PLUS","TK_MINUS","TK_MULT",
"TK_DIV","TK_MOD",0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : S",
"S : TK_MAIN '(' ')' MAIN",
"MAIN : '{' COMANDOS '}'",
"COMANDOS : COMANDO COMANDOS",
"COMANDOS :",
"COMANDO : E ';'",
"COMANDO : TIPO TK_ID ';'",
"COMANDO : TIPO TK_ID TK_ATRIB E ';'",
"COMANDO : TK_ID TK_ATRIB E ';'",
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
#line 301 "sintatica.y"

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
#line 335 "y.tab.c"

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
#line 33 "sintatica.y"
	{
				yyval.traducao = yystack.l_mark[-1].traducao;
			}
break;
case 3:
#line 57 "sintatica.y"
	{
				yyval.traducao = yystack.l_mark[-1].traducao + yystack.l_mark[0].traducao;
			}
break;
case 6:
#line 66 "sintatica.y"
	{
				std::map<string, atributos> *mapLocal = &varMap.back();

				if(mapLocal->find(yystack.l_mark[-1].label) != mapLocal->end()) {
					yyerror("Variavel ja declarada localmente");
				}
				else {
					yyval.label = generateLabel();
					yyval.tipo = yystack.l_mark[-2].tipo;
					varDeclar += yystack.l_mark[-2].traducao + yystack.l_mark[-1].traducao + yyval.tipo->label + " " + yyval.label + ";\n\t";
					(*mapLocal)[yystack.l_mark[-1].label] = yyval;
				}
					

			}
break;
case 7:
#line 83 "sintatica.y"
	{	
				std::map<string, atributos> *mapLocal = &varMap.back();
				if(mapLocal->find(yystack.l_mark[-3].label) != mapLocal->end()) {
        			yyerror("Variavel usada para atribuicao ja declarada");	
				}
				else if( yystack.l_mark[-4].tipo->label == yystack.l_mark[-1].tipo->label ){
					if (mapLocal->find(yystack.l_mark[-1].label) != mapLocal->end())	{
						yyval.label = generateLabel();
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
case 8:
#line 108 "sintatica.y"
	{
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
case 9:
#line 130 "sintatica.y"
	{
				yyval.label = generateLabel();
				yyval.traducao = yystack.l_mark[-2].traducao + yystack.l_mark[0].traducao;
				string var1, var2;
				string cast = implicitCast (&yystack.l_mark[-2], &yystack.l_mark[-1], &var1, &var2);
				
				/*cast*/
				if (cast == INVALID_CAST) {
					yyerror("Operacao infixa " + yystack.l_mark[-1].label + " invalida para tipos " + yystack.l_mark[-2].tipo->label + " e " + yystack.l_mark[-1].tipo->label);	
				} else {
					yyval.traducao += "\t" + cast;
				}
				
				yyval.traducao += yyval.label + " = " + var1 + yystack.l_mark[-1].traducao + var2 + ";\n";
				
			}
break;
case 10:
#line 147 "sintatica.y"
	{	
				
				yyval.label = generateLabel();
				varDeclar += yystack.l_mark[-2].tipo->label + " " + yyval.label + ";\n\t";
				yyval.tipo = yystack.l_mark[-2].tipo;
				yyval.traducao = yystack.l_mark[0].traducao + "\t" + yyval.label + " =" + '(' + yystack.l_mark[-2].tipo->label + ')' + yystack.l_mark[0].label + ";\n";
			}
break;
case 11:
#line 156 "sintatica.y"
	{
				yyval.label = yystack.l_mark[-1].label; /*generateLabel();*/
				yyval.traducao = yystack.l_mark[-1].traducao;/* + "\t" + $$.label + " = " + $2.label + ";\n";*/
			}
break;
case 12:
#line 161 "sintatica.y"
	{
				yyval.label = generateLabel();
				yyval.traducao = yystack.l_mark[0].traducao + "\t" + yyval.label + " = " + " - " + yystack.l_mark[0].label + ";\n";
			}
break;
case 13:
#line 166 "sintatica.y"
	{
				yyval.label = generateLabel();
				varDeclar += "int " + yyval.label + ";\n\t";
				yyval.traducao = "\t" + yyval.label + " = " + yystack.l_mark[0].label + ";\n";
				yyval.tipo = &tipo_int;
			}
break;
case 14:
#line 173 "sintatica.y"
	{
				yyval.label = generateLabel();
				varDeclar += "float " + yyval.label + ";\n\t";
				yyval.traducao = "\t" + yyval.label + " = " + yystack.l_mark[0].label + ";\n";
				yyval.tipo = &tipo_float;
			}
break;
case 15:
#line 180 "sintatica.y"
	{
				string aux;
				
				if(yystack.l_mark[0].label == "true") {
					aux = "1";
				}
				else {
					aux = "0";
				}

				yyval.label = generateLabel();
				varDeclar += "unsigned char " + yyval.label + ";\n\t";
				yyval.traducao = "\t" + yyval.label + " = " + aux + ";\n";
				yyval.tipo = &tipo_bool;

			}
break;
case 16:
#line 197 "sintatica.y"
	{
				yyval.label = generateLabel();
				varDeclar += "char " + yyval.label + ";\n\t";
				yyval.traducao = "\t" + yyval.label + " = " + yystack.l_mark[0].label +  ";\n";
				yyval.tipo = &tipo_char;
			}
break;
case 17:
#line 204 "sintatica.y"
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
					yyval.label = generateLabel();
					yyval.traducao = "\t" + yyval.label + " = " + yystack.l_mark[0].label + ":\n";
				}
			}
break;
case 18:
#line 224 "sintatica.y"
	{
				yyval.label = "+";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 19:
#line 228 "sintatica.y"
	{
				yyval.label = "-";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 20:
#line 232 "sintatica.y"
	{
				yyval.label = "*";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 21:
#line 236 "sintatica.y"
	{
				yyval.label = "/";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 22:
#line 240 "sintatica.y"
	{
				yyval.label = "%";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 23:
#line 244 "sintatica.y"
	{
				yyval.label = "&&";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 24:
#line 248 "sintatica.y"
	{
				yyval.label = "||";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 25:
#line 252 "sintatica.y"
	{
				yyval.label = "!=";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 26:
#line 256 "sintatica.y"
	{
				yyval.label = "==";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 27:
#line 260 "sintatica.y"
	{
				yyval.label = ">";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 28:
#line 264 "sintatica.y"
	{
				yyval.label = "<";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 29:
#line 268 "sintatica.y"
	{
				yyval.label = ">=";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 30:
#line 272 "sintatica.y"
	{
				yyval.label = "<=";
				yyval.tipo = &tipo_inf_operator;
			}
break;
case 31:
#line 279 "sintatica.y"
	{
				yyval.tipo = &tipo_int;
			}
break;
case 32:
#line 283 "sintatica.y"
	{
				yyval.tipo = &tipo_float;
			}
break;
case 33:
#line 287 "sintatica.y"
	{
				yyval.tipo = &tipo_bool;
			}
break;
case 34:
#line 291 "sintatica.y"
	{
				yyval.tipo = &tipo_char;
			}
break;
case 35:
#line 295 "sintatica.y"
	{
				yyval.tipo = &tipo_list;
			}
break;
#line 850 "y.tab.c"
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
