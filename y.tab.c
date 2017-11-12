/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sintatica.y" /* yacc.c:339  */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#define YYSTYPE atributos	

using namespace std;

void oi() {
	cout << "oi" << endl;
}

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


#line 141 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_INT = 258,
    TK_FLOAT = 259,
    TK_BOOL = 260,
    TK_CHAR = 261,
    TK_STR = 262,
    TK_IF = 263,
    TK_ELSE = 264,
    TK_FOR = 265,
    TK_DO = 266,
    TK_WHILE = 267,
    TK_BREAK = 268,
    TK_ALL = 269,
    TK_CONTINUE = 270,
    TK_PRINT = 271,
    TK_MAIN = 272,
    TK_ID = 273,
    TK_TIPO_INT = 274,
    TK_TIPO_FLOAT = 275,
    TK_TIPO_BOOL = 276,
    TK_TIPO_CHAR = 277,
    TK_TIPO_STR = 278,
    TK_DOTS = 279,
    TK_2MAIS = 280,
    TK_2MENOS = 281,
    TK_FIM = 282,
    TK_ERROR = 283,
    TK_ATRIB = 284,
    TK_OR = 285,
    TK_AND = 286,
    TK_NOT = 287,
    TK_IGUAL = 288,
    TK_DIFERENTE = 289,
    TK_MAIOR = 290,
    TK_MENOR = 291,
    TK_MAIORI = 292,
    TK_MENORI = 293,
    TK_MOD = 294
  };
#endif
/* Tokens.  */
#define TK_INT 258
#define TK_FLOAT 259
#define TK_BOOL 260
#define TK_CHAR 261
#define TK_STR 262
#define TK_IF 263
#define TK_ELSE 264
#define TK_FOR 265
#define TK_DO 266
#define TK_WHILE 267
#define TK_BREAK 268
#define TK_ALL 269
#define TK_CONTINUE 270
#define TK_PRINT 271
#define TK_MAIN 272
#define TK_ID 273
#define TK_TIPO_INT 274
#define TK_TIPO_FLOAT 275
#define TK_TIPO_BOOL 276
#define TK_TIPO_CHAR 277
#define TK_TIPO_STR 278
#define TK_DOTS 279
#define TK_2MAIS 280
#define TK_2MENOS 281
#define TK_FIM 282
#define TK_ERROR 283
#define TK_ATRIB 284
#define TK_OR 285
#define TK_AND 286
#define TK_NOT 287
#define TK_IGUAL 288
#define TK_DIFERENTE 289
#define TK_MAIOR 290
#define TK_MENOR 291
#define TK_MAIORI 292
#define TK_MENORI 293
#define TK_MOD 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 270 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      44,    45,    41,    39,    49,    40,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,   101,   107,   114,   122,   130,   138,   142,
     146,   149,   154,   159,   164,   168,   175,   237,   299,   361,
     423,   430,   437,   445,   453,   461,   468,   475,   482,   491,
     496,   502,   504,   511,   518,   535,   542,   549,   566,   584,
     600,   604,   609,   624,   643,   650,   668,   687,   698,   715,
     740,   760,   777,   795,   810,   818,   825,   832,   839,   848,
     853,   859,   867,   871,   875,   879,   883
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_INT", "TK_FLOAT", "TK_BOOL",
  "TK_CHAR", "TK_STR", "TK_IF", "TK_ELSE", "TK_FOR", "TK_DO", "TK_WHILE",
  "TK_BREAK", "TK_ALL", "TK_CONTINUE", "TK_PRINT", "TK_MAIN", "TK_ID",
  "TK_TIPO_INT", "TK_TIPO_FLOAT", "TK_TIPO_BOOL", "TK_TIPO_CHAR",
  "TK_TIPO_STR", "TK_DOTS", "TK_2MAIS", "TK_2MENOS", "TK_FIM", "TK_ERROR",
  "TK_ATRIB", "TK_OR", "TK_AND", "TK_NOT", "TK_IGUAL", "TK_DIFERENTE",
  "TK_MAIOR", "TK_MENOR", "TK_MAIORI", "TK_MENORI", "'+'", "'-'", "'*'",
  "'/'", "TK_MOD", "'('", "')'", "'{'", "'}'", "';'", "','", "$accept",
  "S", "MAIN", "ESCOPO_INICIO", "ESCOPO_FIM", "LOOP_INICIO", "LOOP_FIM",
  "BLOCO", "COMANDOS", "COMANDO", "E", "INCREMENTOS", "SINAL_DUPL",
  "CONTROLE", "CONTROLE_ALT", "ATRIBUICAO", "LOOP", "LOOP_ALT", "PRINT",
  "PRINT_ALT", "TIPO", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    43,
      45,    42,    47,   294,    40,    41,   123,   125,    59,    44
};
# endif

#define YYPACT_NINF -54

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

#define YYTABLE_NINF -11

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-11)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -8,   -22,    20,   -13,   -54,   -23,    92,   -54,   -54,   -54,
     -54,   -54,   -54,   146,    -9,    17,   146,   -19,   -54,   -54,
     -54,   -54,   -54,   -54,   -54,   146,   122,    26,    -6,    92,
     163,   -54,    16,   -54,     9,    10,    11,    21,   -14,   182,
     -54,    39,   -54,   143,   -54,   146,   -54,   -24,   262,    -2,
       7,   -54,   146,   -54,   -54,   -54,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   -54,   -54,
     -54,   -54,   -54,    31,   -54,    18,   146,   275,   -54,   146,
      32,    14,    22,    54,   201,   -54,   285,   285,   295,   295,
      43,    43,    43,    43,   -24,   -24,   -54,   -54,   146,    60,
     -54,   -54,   275,   146,    92,   146,   -54,   275,    -5,   -54,
     214,    23,   230,   -54,   146,   -54,   -10,   -54,   -54,   249,
     -54,   -14,    47,   -54,   -54,   -54,    60,   -54,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     6,     2,    32,    33,
      34,    35,    36,     0,    54,    57,     0,    37,    62,    63,
      64,    65,    66,    40,    41,     0,     0,     0,     0,     6,
       0,    31,     0,    13,     0,     0,     0,     0,    37,     0,
      55,     0,    58,    60,    59,     0,    38,    30,     0,     0,
       0,     4,     0,     7,     3,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    11,    39,
      12,    14,    15,    48,     4,     0,     0,    50,    29,     0,
       0,     0,     0,     0,     0,    44,    21,    20,    22,    23,
      24,    25,    26,    27,    16,    19,    17,    18,     0,    42,
      56,    61,    28,     0,     6,     0,     4,    49,     0,    43,
       0,     0,     0,    52,     0,     4,     0,     5,    53,     0,
      47,     0,     0,     8,     4,     4,    45,    51,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   -50,   -27,   -54,
     -12,   -44,   -17,   -54,   -53,    37,   -54,   -54,   -54,     0,
      62
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,    82,   123,    27,    85,    83,    28,    29,
      30,    31,    32,    33,   109,    34,    53,    35,    36,    44,
      37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    39,    55,   114,    43,    40,    23,    24,   121,     1,
      45,    23,    24,    47,    48,    23,    24,    66,    67,   115,
       4,    46,     3,     6,    99,    80,    18,    19,    20,    21,
      22,    42,     5,    77,    69,    41,    50,    51,    52,    73,
      84,    54,    75,    79,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,   113,    70,    71,    72,
      98,    45,   103,   100,    43,   120,   105,   102,   104,   108,
     117,   125,   122,   128,   126,   127,   101,   111,   -11,   -11,
     -11,   -11,    64,    65,    66,    67,   107,    81,    49,     0,
       0,   110,     0,   112,     0,     8,     9,    10,    11,    12,
      13,     0,   119,     0,    46,    14,     0,    15,    16,     0,
      17,    18,    19,    20,    21,    22,     0,    23,    24,     0,
       0,     0,     0,     0,     0,     8,     9,    10,    11,    12,
       0,     0,    25,     0,     0,     0,    26,     0,     0,   -10,
      38,    18,    19,    20,    21,    22,     0,    23,    24,     8,
       9,    10,    11,    12,     0,     0,     0,     0,     0,     0,
       0,     0,    25,     0,    38,     0,    26,     0,     0,     0,
       0,    23,    24,    56,    57,     0,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    25,     0,     0,     0,
      26,     0,    76,    56,    57,     0,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    74,     0,     0,     0,
       0,    68,    56,    57,     0,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,   106,     0,     0,     0,     0,
       0,    56,    57,     0,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    56,    57,     0,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,     0,     0,     0,
      56,    57,   116,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   124,     0,     0,     0,     0,   118,    56,
      57,     0,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    56,    57,     0,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    56,    57,    78,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,   -11,   -11,
      60,    61,    62,    63,    64,    65,    66,    67
};

static const yytype_int8 yycheck[] =
{
      17,    13,    29,     8,    16,    14,    25,    26,    18,    17,
      29,    25,    26,    25,    26,    25,    26,    41,    42,    24,
       0,    38,    44,    46,    74,    18,    19,    20,    21,    22,
      23,    14,    45,    45,    18,    44,    10,    11,    12,    18,
      52,    47,     3,    45,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,   106,    48,    48,    48,
      29,    29,    48,    45,    76,   115,    12,    79,    46,     9,
      47,    24,   116,   126,   124,   125,    76,   104,    35,    36,
      37,    38,    39,    40,    41,    42,    98,    50,    26,    -1,
      -1,   103,    -1,   105,    -1,     3,     4,     5,     6,     7,
       8,    -1,   114,    -1,   121,    13,    -1,    15,    16,    -1,
      18,    19,    20,    21,    22,    23,    -1,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    -1,    47,
      18,    19,    20,    21,    22,    23,    -1,    25,    26,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    18,    -1,    44,    -1,    -1,    -1,
      -1,    25,    26,    30,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    40,    -1,    -1,    -1,
      44,    -1,    49,    30,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    24,    -1,    -1,    -1,
      -1,    48,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      30,    31,    48,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    24,    -1,    -1,    -1,    -1,    48,    30,
      31,    -1,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    30,    31,    45,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    51,    44,     0,    45,    46,    52,     3,     4,
       5,     6,     7,     8,    13,    15,    16,    18,    19,    20,
      21,    22,    23,    25,    26,    40,    44,    55,    58,    59,
      60,    61,    62,    63,    65,    67,    68,    70,    18,    60,
      14,    44,    14,    60,    69,    29,    62,    60,    60,    70,
      10,    11,    12,    66,    47,    58,    30,    31,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    48,    18,
      48,    48,    48,    18,    24,     3,    49,    60,    45,    45,
      18,    65,    53,    57,    60,    56,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    29,    57,
      45,    69,    60,    48,    46,    12,    24,    60,     9,    64,
      60,    58,    60,    57,     8,    24,    48,    47,    48,    60,
      57,    18,    61,    54,    24,    24,    57,    57,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      58,    59,    59,    59,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    64,    64,    64,    65,    65,
      65,    66,    66,    66,    67,    67,    67,    67,    67,    68,
      69,    69,    70,    70,    70,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     0,     0,     0,     0,     5,     2,
       0,     2,     2,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     4,     5,     3,     5,     6,     3,     2,     4,
       3,     8,     4,     5,     1,     2,     4,     1,     2,     2,
       1,     3,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 95 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "/*Compilador V3A*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" << "\t" + varDeclar + "\n" << (yyvsp[0]).traducao << "\treturn 0;\n}" << endl;

			}
#line 1480 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 102 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 107 "sintatica.y" /* yacc.c:1646  */
    {
				empContexto();
				
				(yyval).traducao = "";
				(yyval).label = "";
			}
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 114 "sintatica.y" /* yacc.c:1646  */
    {
				desempContexto();
				
				(yyval).traducao = "";
				(yyval).label = "";
			}
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 122 "sintatica.y" /* yacc.c:1646  */
    {
				empLoop();
				empContexto();
				
				(yyval).traducao = "";
				(yyval).label = "";
			}
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 130 "sintatica.y" /* yacc.c:1646  */
    {
				desempLoop();
				desempContexto();
				
				(yyval).traducao = "";
				(yyval).label = "";
			}
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 138 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-2]).traducao;
			}
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 143 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 146 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = "";}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 150 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 155 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 160 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 1580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 165 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 169 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + " << endl;\n";
			}
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 176 "sintatica.y" /* yacc.c:1646  */
    {
				atributos *id1 = findVar((yyvsp[-2]).label);
				atributos *id2 = findVar((yyvsp[0]).label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = (yyvsp[-2]).label;
					tipo1 = (yyvsp[-2]).tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = (yyvsp[0]).label;
					tipo2 = (yyvsp[0]).tipo;
				}


				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				string aux;
				if(tipo1 == "int" && tipo2 == "float"){

					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + "(float)" + label1 + ";\n";
					aux = generateVar();
					varDeclar += "float " + (yyval).label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + aux + " = " + label2 + " + " + (yyval).label + ";\n";
					(yyval).label = aux;
					(yyval).tipo = "float";

				
				}else if(tipo1 == "float" && tipo2 == "int"){
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + "(float)" + label2 + ";\n";
					aux = generateVar();
					varDeclar += "float " + (yyval).label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + aux + " = " + label1 + " + " + (yyval).label + ";\n";
					(yyval).label = aux;
					(yyval).tipo = "float";
				
				}else if((tipo1 == "int" && tipo2 == "int") || (tipo1 == "float" && tipo2 == "float") ){
					varDeclar += "int " + (yyval).label + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + label1 + " + " + label2 + ";\n";
				}
				else {
					yyerror("Operacao de soma nao contemplada pelo compilador");
				}


				
			}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 238 "sintatica.y" /* yacc.c:1646  */
    {
				atributos *id1 = findVar((yyvsp[-2]).label);
				atributos *id2 = findVar((yyvsp[0]).label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = (yyvsp[-2]).label;
					tipo1 = (yyvsp[-2]).tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = (yyvsp[0]).label;
					tipo2 = (yyvsp[0]).tipo;
				}


				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				string aux;
				if(tipo1 == "int" && tipo2 == "float"){

					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + "(float)" + label1 + ";\n";
					aux = generateVar();
					varDeclar += "float " + (yyval).label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + aux + " = " + label2 + " * " + (yyval).label + ";\n";
					(yyval).label = aux;
					(yyval).tipo = "float";

				
				}else if(tipo1 == "float" && tipo2 == "int"){
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + "(float)" + label2 + ";\n";
					aux = generateVar();
					varDeclar += "float " + (yyval).label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + aux + " = " + label1 + " * " + (yyval).label + ";\n";
					(yyval).label = aux;
					(yyval).tipo = "float";
				
				}else if((tipo1 == "int" && tipo2 == "int") || (tipo1 == "float" && tipo2 == "float") ){
					varDeclar += "int " + (yyval).label + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + label1 + " * " + label2 + ";\n";
				}
				else {
					yyerror("Operacao de mult nao contemplada pelo compilador");
				}


				
			}
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 300 "sintatica.y" /* yacc.c:1646  */
    {
				atributos *id1 = findVar((yyvsp[-2]).label);
				atributos *id2 = findVar((yyvsp[0]).label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = (yyvsp[-2]).label;
					tipo1 = (yyvsp[-2]).tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = (yyvsp[0]).label;
					tipo2 = (yyvsp[0]).tipo;
				}


				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				string aux;
				if(tipo1 == "int" && tipo2 == "float"){

					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + "(float)" + label1 + ";\n";
					aux = generateVar();
					varDeclar += "float " + (yyval).label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + aux + " = " + label2 + " / " + (yyval).label + ";\n";
					(yyval).label = aux;
					(yyval).tipo = "float";

				
				}else if(tipo1 == "float" && tipo2 == "int"){
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + "(float)" + label2 + ";\n";
					aux = generateVar();
					varDeclar += "float " + (yyval).label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + aux + " = " + label1 + " / " + (yyval).label + ";\n";
					(yyval).label = aux;
					(yyval).tipo = "float";
				
				}else if((tipo1 == "int" && tipo2 == "int") || (tipo1 == "float" && tipo2 == "float") ){
					varDeclar += "int " + (yyval).label + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + label1 + " / " + label2 + ";\n";
				}
				else {
					yyerror("Operacao de div nao contemplada pelo compilador");
				}


				
			}
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 362 "sintatica.y" /* yacc.c:1646  */
    {
				atributos *id1 = findVar((yyvsp[-2]).label);
				atributos *id2 = findVar((yyvsp[0]).label);
				string label1;
				string label2;
				string tipo1;
				string tipo2;

				if(id1 != nullptr) {
					label1 = id1->label;
					tipo1 = id1->tipo;
				}
				else {
					label1 = (yyvsp[-2]).label;
					tipo1 = (yyvsp[-2]).tipo;
				}

				if(id2 != nullptr) {
					label2 = id2->label;
					tipo2 = id2->tipo;
				}
				else {
					label2 = (yyvsp[0]).label;
					tipo2 = (yyvsp[0]).tipo;
				}


				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				string aux;
				if(tipo1 == "int" && tipo2 == "float"){

					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + "(float)" + label1 + ";\n";
					aux = generateVar();
					varDeclar += "float " + (yyval).label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + aux + " = " + label2 + " - " + (yyval).label + ";\n";
					(yyval).label = aux;
					(yyval).tipo = "float";

				
				}else if(tipo1 == "float" && tipo2 == "int"){
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + "(float)" + label2 + ";\n";
					aux = generateVar();
					varDeclar += "float " + (yyval).label + ";\n\t";
					varDeclar += "float " + aux + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + aux + " = " + label1 + " - " + (yyval).label + ";\n";
					(yyval).label = aux;
					(yyval).tipo = "float";
				
				}else if((tipo1 == "int" && tipo2 == "int") || (tipo1 == "float" && tipo2 == "float") ){
					varDeclar += "int " + (yyval).label + ";\n\t";
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + label1 + " - " + label2 + ";\n";
				}
				else {
					yyerror("Operacao de sub nao contemplada pelo compilador");
				}


				
			}
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 424 "sintatica.y" /* yacc.c:1646  */
    {	
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-2]).label + " && " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "unsigned char";
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
			}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 431 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-2]).label + " || " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "unsigned char";
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
			}
#line 1882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 438 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-2]).label + " == " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "unsigned char";
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
			}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 446 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-2]).label + " != " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "unsigned char";
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
			}
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 454 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-2]).label + " > " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "unsigned char";
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
			}
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 462 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-2]).label + " < " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "unsigned char";
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
			}
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 469 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-2]).label + " >= " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "unsigned char";
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
			}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 476 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-2]).label + " <= " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "unsigned char";
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
			}
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 483 "sintatica.y" /* yacc.c:1646  */
    {	
				
				(yyval).label = generateVar();
				varDeclar += (yyvsp[-2]).tipo + " " + (yyval).label + ";\n\t";
				(yyval).tipo = (yyvsp[-2]).tipo;
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " =" + '(' + (yyvsp[-2]).tipo + ')' + (yyvsp[0]).label + ";\n";
			}
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 492 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = (yyvsp[-1]).label; //generateVar();
				(yyval).traducao = (yyvsp[-1]).traducao;// + "\t" + $$.label + " = " + $2.label + ";\n";
			}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 497 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + " - " + (yyvsp[0]).label + ";\n";
			}
#line 1978 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 505 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				varDeclar += "int " + (yyval).label + ";\n\t";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "int";
			}
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 512 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				varDeclar += "float " + (yyval).label + ";\n\t";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = "float";
			}
#line 2000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 519 "sintatica.y" /* yacc.c:1646  */
    {
				string aux;
				
				if((yyvsp[0]).label == "true") {
					aux = "1";
				}
				else {
					aux = "0";
				}

				(yyval).label = generateVar();
				varDeclar += "unsigned char " + (yyval).label + ";\n\t";
				(yyval).traducao = "\t" + (yyval).label + " = " + aux + ";\n";
				(yyval).tipo = "unsigned char";

			}
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 536 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				varDeclar += "char " + (yyval).label + ";\n\t";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label +  ";\n";
				(yyval).tipo = "char";
			}
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 543 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateVar();
				varDeclar += "str " + (yyval).label + ";\n\t";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label +  ";\n";
				(yyval).tipo = "str";
			}
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 550 "sintatica.y" /* yacc.c:1646  */
    {
				atributos *id = findVar((yyvsp[0]).label);
				if(id != nullptr) {
					(yyval).tipo = id->tipo;
					(yyval).label = (yyvsp[0]).label;
				}
				else {
				(yyval).label = generateVar();
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ":\n";
				}
			}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 566 "sintatica.y" /* yacc.c:1646  */
    {

				atributos *id = findVar((yyvsp[-1]).label);
				if ( id == nullptr ) yyerror("Variavel " + (yyvsp[-1]).label + " nao declarada para ser incrementada");

				if(id->tipo != "int") yyerror("Variavel " + (yyvsp[-1]).label + " nao pode ser incrementada (tipo diferente de int)");

				string var1 = generateVar();
				string var2 = generateVar();

				varDeclar += "int " + var1 + ";\n\t";
				varDeclar += "int " + var2 + ";\n\t";

				(yyval).label = var2;
				(yyval).tipo = id->tipo;
				(yyval).traducao = "\t" + var2 + " = " + id->label + ";\n\t" + var1 + " = 1;\n\t" + 
								id->label + " = " + id->label + (yyvsp[0]).label + var1 + ";\n";
			}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 584 "sintatica.y" /* yacc.c:1646  */
    {

				atributos *id = findVar((yyvsp[0]).label);
				if ( id == nullptr ) yyerror("Variavel " + (yyvsp[0]).label + " nao declarada para ser incrementada");

				if( id->tipo != "int" ) yyerror("Variavel " + (yyvsp[0]).label + " nao pode ser incrementada (tipo diferente de int)");

				string var = generateVar();
				varDeclar += "int " + var + ";\n\t";

				(yyval).label = id->label;
				(yyval).tipo = id->tipo;
				(yyval).traducao = "\t" + var + " = 1;\n\t" + (yyval).label + " = " + (yyval).label + " + " + var + ";\n";

			}
#line 2102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 600 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = " + ";
				(yyval).traducao = "";
			}
#line 2111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 604 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = " - ";
				(yyval).traducao = "";
			}
#line 2120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 610 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-2]).tipo != "unsigned char") yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVar();
				string fim = generateLabel();

				varDeclar += "int " + var + ";\n\t";
					
					(yyval).traducao = "\n" + (yyvsp[-2]).traducao + 
						"\t" + var + " = !" + (yyvsp[-2]).label + ";\n" +
						"\tif (" + var + ") goto " + fim + ";\n\n" +
						(yyvsp[0]).traducao +
						"\n\t" + fim + ":\n\n";
			}
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 625 "sintatica.y" /* yacc.c:1646  */
    {

				if((yyvsp[-3]).tipo != "unsigned char") yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVar();
				string fim = generateLabel();

				varDeclar += "int " + var + ";\n\t";

				(yyval).traducao = "\n" + (yyvsp[-3]).traducao + 
						"\t" + var + " = !" + (yyvsp[-3]).label + ";\n" +
						"\tif (" + var + ") goto " + fim + ";\n\n" +
						(yyvsp[-1]).traducao +
						"\tgoto " + (yyvsp[0]).label + ";\n\n" +
						"\t" + fim + ":" + (yyvsp[0]).traducao;
				
			}
#line 2161 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 644 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 651 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-2]).tipo != "unsigned char") yyerror("Tipo da expressao do if DEVE ser bool");

				string var = generateVar();
				string fim = generateLabel();

				varDeclar += "int " + var + ";\n\t";

				(yyval).label = fim;
				(yyval).traducao = "\n" + (yyvsp[-2]).traducao + 
						"\t" + var + " = !" + (yyvsp[-2]).label + ";\n\n" +
						"\tif (" + var + ") goto " + fim + ";\n" +
						(yyvsp[0]).traducao +
						"\n\t" + fim + ":\n";

			}
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 669 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-3]).tipo != "unsigned char") yyerror("Tipo da expressao do else if DEVE ser bool");

				string var = generateVar();
				string fim = generateLabel();

				varDeclar += "int " + var + ";\n\t";

				(yyval).label = (yyvsp[0]).label;
				(yyval).traducao = "\n" + (yyvsp[-3]).traducao + 
						"\t" + var + " = !" + (yyvsp[-3]).label + ";\n\n" +
						"\tif (" + var + ") goto " + fim + ";\n" +
						(yyvsp[-1]).traducao +
						"\n\tgoto " + (yyvsp[0]).label + ";\n" +
						"\n\t" + fim + ":" + (yyvsp[0]).traducao;

			}
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 688 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = generateLabel();
				(yyval).traducao = "\n" + (yyvsp[0]).traducao + "\n\t" + (yyval).label + ":\n";

			}
#line 2222 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 699 "sintatica.y" /* yacc.c:1646  */
    {
				std::map<string, atributos> *mapLocal = &varMap.back();

				if(mapLocal->find((yyvsp[0]).label) != mapLocal->end()) {
					yyerror("Variavel ja declarada localmente");
				}
				else {
					(yyval).label = generateVar();
					(yyval).tipo = (yyvsp[-1]).tipo;
					varDeclar += (yyvsp[-1]).traducao + (yyvsp[0]).traducao + (yyval).tipo + " " + (yyval).label + ";\n\t";
					(*mapLocal)[(yyvsp[0]).label] = (yyval);
				}
					

			}
#line 2242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 716 "sintatica.y" /* yacc.c:1646  */
    {	
				std::map<string, atributos> *mapLocal = &varMap.back();
				if(mapLocal->find((yyvsp[-2]).label) != mapLocal->end()) {
        			yyerror("Variavel usada para atribuicao ja declarada");	
				}
				else if( (yyvsp[-3]).tipo == (yyvsp[0]).tipo ){
					if (mapLocal->find((yyvsp[0]).label) != mapLocal->end())	{
						(yyval).label = generateVar();
						(yyval).tipo = (yyvsp[-3]).tipo;
						(yyval).traducao = "\t" + (yyval).label + " = " + (*mapLocal)[(yyvsp[0]).label].label + ";\n";
						varDeclar += (yyvsp[-3]).traducao + (yyvsp[-2]).traducao + (yyval).tipo + " " + (yyval).label + ";\n\t";
						(*mapLocal)[(yyvsp[-2]).label] = (yyval);
					}
					else {
					(yyval).label = (yyvsp[0]).label;
					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
					(yyval).tipo = (yyvsp[-3]).tipo;
					(*mapLocal)[(yyvsp[-2]).label] = (yyval);
					}
				}
				else {
					yyerror("Atribuicao de tipos nao compativeis");
				}
			}
#line 2271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 741 "sintatica.y" /* yacc.c:1646  */
    {
				atributos* atr;
				if ( atr = findVar((yyvsp[-2]).label) ) {
					if(atr->tipo == (yyvsp[0]).tipo) {
						(yyval).traducao = (yyvsp[0]).traducao + "\t" + atr->label + " = " + (yyvsp[0]).label + ";\n";
					}
					else yyerror("atr de tipos incompativeis");
				}
				else {
					std::map<string, atributos> *mapLocal = &varMap.back();
					(yyval).label = (yyvsp[0]).label;
					(yyval).tipo = (yyvsp[0]).tipo;
					(yyval).traducao = (yyvsp[0]).traducao;
					(*mapLocal)[(yyvsp[-2]).label] = (yyval);

				}
			}
#line 2293 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 760 "sintatica.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-4]).tipo != "unsigned char") yyerror("Tipo da expressao do for DEVE ser bool");

				string var = generateVar();
				loopLabel* loop = getLoop(1);

				varDeclar += "int " + var + ";\n\t";

				(yyval).traducao = (yyvsp[-6]).traducao + "\n\t" + loop->inicio + ":\n" + (yyvsp[-4]).traducao + 
						"\t" + var + " = !" + (yyvsp[-4]).label + ";\n" +
						"\tif (" + var + ") goto " + loop->fim + ";\n\n" +
						(yyvsp[0]).traducao + "\t" + loop->progressao + ":\n\n" + (yyvsp[-2]).traducao +
						"\tgoto " + loop->inicio + ";\n\n\t" + 
						loop->fim + ":\n";

			}
#line 2314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 778 "sintatica.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2]).tipo != "unsigned char") yyerror("Tipo da expressao do while DEVE ser bool");

				string var = generateVar();
				loopLabel* loop = getLoop(1);
					
				varDeclar += "int " + var + ";\n\t";
					
				(yyval).traducao = "\t" + loop->inicio + ":\n\t" 
					+ loop->progressao + ":\n" + (yyvsp[-2]).traducao
					+ "\t" + var + " = !" + (yyvsp[-2]).label + ";\n" +
					"\tif (" + var + ") goto " + loop->fim + ";\n" +
					(yyvsp[0]).traducao +
					"\tgoto " + loop->inicio + ";\n\t" + loop->fim + ":\n";
				
			}
#line 2335 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 795 "sintatica.y" /* yacc.c:1646  */
    {

				if ((yyvsp[-1]).tipo != "unsigned char") yyerror("Tipo da expressao do DO WHILE DEVE ser bool");

				loopLabel* loop = getLoop(1);

				(yyval).traducao = "\t" + loop->inicio + ":\n\t" 
						+ loop->progressao + ":\n" + (yyvsp[-1]).traducao 
						+ (yyvsp[-3]).traducao + "\tif (" 
						+ (yyvsp[-1]).label + ") goto " + loop->inicio + ";\n\t"
						+ loop->fim + ":\n";

			}
#line 2353 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 810 "sintatica.y" /* yacc.c:1646  */
    {
				loopLabel* loop = getLoop(1);
				
				if (loop == nullptr) yyerror("Break deve ser usado dentro de um loop");

				(yyval).traducao = "\tgoto " + loop->fim + ";\n";
				
			}
#line 2366 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 818 "sintatica.y" /* yacc.c:1646  */
    {
				loopLabel* loop = getOuterLoop();
				
				if (loop == nullptr) yyerror("Break all deve ser usado dentro de um loop");

				(yyval).traducao = "\tgoto " + loop->fim + ";\n";
			}
#line 2378 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 825 "sintatica.y" /* yacc.c:1646  */
    {
				loopLabel* loop = getLoop(stoi((yyvsp[-1]).label));
				
				if (loop == nullptr) yyerror("Break com args deve ser usado dentro de um loop\nou\nargumento invalido");

				(yyval).traducao = "\tgoto " + loop->fim + ";\n";
			}
#line 2390 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 832 "sintatica.y" /* yacc.c:1646  */
    {
				loopLabel* loop = getLoop(1);
				
				if (loop == nullptr) yyerror("Continue deve ser usado dentro de um loop");

				(yyval).traducao = "\tgoto " + loop->progressao + ";\n";
			}
#line 2402 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 839 "sintatica.y" /* yacc.c:1646  */
    {
				loopLabel* loop = getOuterLoop();
				
				if (loop == nullptr) yyerror("Continue deve ser usado dentro de um loop");

				(yyval).traducao = "\tgoto " + loop->progressao + ";\n";
			}
#line 2414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 849 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao + "\tcout" + (yyvsp[0]).label;
			}
#line 2422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 854 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
				(yyval).label = " << " + (yyvsp[0]).label;
			}
#line 2431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 860 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				(yyval).label = " << " + (yyvsp[-2]).label + (yyvsp[0]).label;
			}
#line 2440 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 868 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "int";
			}
#line 2448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 872 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "float";
			}
#line 2456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 876 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "unsigned char";
			}
#line 2464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 880 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "char";
			}
#line 2472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 883 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "str";
			}
#line 2480 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2484 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 889 "sintatica.y" /* yacc.c:1906  */


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
		cout << loopMap.size() << " " << tamLoop << endl;
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
