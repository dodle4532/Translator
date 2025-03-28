/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SENT_TAB_H_INCLUDED
# define YY_YY_SENT_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUM = 258,                     /* NUM  */
    WORD = 259,                    /* WORD  */
    STRING = 260,                  /* STRING  */
    LET = 261,                     /* LET  */
    U32 = 262,                     /* U32  */
    U64 = 263,                     /* U64  */
    F32 = 264,                     /* F32  */
    STR = 265,                     /* STR  */
    BOOL = 266,                    /* BOOL  */
    TRUE = 267,                    /* TRUE  */
    FALSE = 268,                   /* FALSE  */
    FN = 269,                      /* FN  */
    INT = 270,                     /* INT  */
    IF = 271,                      /* IF  */
    ELSE = 272,                    /* ELSE  */
    FOR = 273,                     /* FOR  */
    WHILE = 274,                   /* WHILE  */
    EQUALS = 275,                  /* EQUALS  */
    NOT_EQUALS = 276,              /* NOT_EQUALS  */
    QUOTE = 277,                   /* QUOTE  */
    IN = 278,                      /* IN  */
    TWO_POINTS = 279,              /* TWO_POINTS  */
    RETURN = 280,                  /* RETURN  */
    LESS = 281,                    /* LESS  */
    MORE = 282,                    /* MORE  */
    EQ_LESS = 283,                 /* EQ_LESS  */
    EQ_MORE = 284                  /* EQ_MORE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "sent.y"

    char* str;
    int integer;
    struct member_type* memb;
    struct value_type* _val;
    struct value_vec* valVec;
    struct member_vec* membVec;
    struct command_type* com;
    struct ast* ast_type;
    struct if_cond_type* if_cond;
    struct if_expr_type* if_expr;

#line 106 "sent.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SENT_TAB_H_INCLUDED  */
