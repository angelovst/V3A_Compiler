/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
