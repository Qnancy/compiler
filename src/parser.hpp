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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    LPAREN = 258,                  /* LPAREN  */
    RPAREN = 259,                  /* RPAREN  */
    LBRACKET = 260,                /* LBRACKET  */
    RBRACKET = 261,                /* RBRACKET  */
    LBRACE = 262,                  /* LBRACE  */
    RBRACE = 263,                  /* RBRACE  */
    COMMA = 264,                   /* COMMA  */
    SEMI = 265,                    /* SEMI  */
    EQ = 266,                      /* EQ  */
    NEQ = 267,                     /* NEQ  */
    LT = 268,                      /* LT  */
    LEQ = 269,                     /* LEQ  */
    GT = 270,                      /* GT  */
    GEQ = 271,                     /* GEQ  */
    ADD = 272,                     /* ADD  */
    SUB = 273,                     /* SUB  */
    MUL = 274,                     /* MUL  */
    DIV = 275,                     /* DIV  */
    MOD = 276,                     /* MOD  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    NOT = 279,                     /* NOT  */
    BAND = 280,                    /* BAND  */
    BOR = 281,                     /* BOR  */
    BXOR = 282,                    /* BXOR  */
    ASSIGN = 283,                  /* ASSIGN  */
    DOT = 284,                     /* DOT  */
    COLON = 285,                   /* COLON  */
    QUES = 286,                    /* QUES  */
    ELLIPSES = 287,                /* ELLIPSES  */
    PTR = 288,                     /* PTR  */
    INT = 289,                     /* INT  */
    SHORT = 290,                   /* SHORT  */
    CHAR = 291,                    /* CHAR  */
    VOID = 292,                    /* VOID  */
    DOUBLE = 293,                  /* DOUBLE  */
    BOOL = 294,                    /* BOOL  */
    RETURN = 295,                  /* RETURN  */
    CONTINUE = 296,                /* CONTINUE  */
    BREAK = 297,                   /* BREAK  */
    IF = 298,                      /* IF  */
    ELSE = 299,                    /* ELSE  */
    FOR = 300,                     /* FOR  */
    WHILE = 301,                   /* WHILE  */
    TRUE = 302,                    /* TRUE  */
    FALSE = 303,                   /* FALSE  */
    STATIC = 304,                  /* STATIC  */
    CONST = 305,                   /* CONST  */
    IDENTIFIER = 306,              /* IDENTIFIER  */
    CONST_INT = 307,               /* CONST_INT  */
    CONST_CHAR = 308,              /* CONST_CHAR  */
    CONST_STR = 309,               /* CONST_STR  */
    CONST_DOUBLE = 310,            /* CONST_DOUBLE  */
    CONST_FLOAT = 311              /* CONST_FLOAT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "parser.y"

    int intVal;
    double douVal;
	char charVal;
    std::string* strVal;
    BaseAST *astVal;
	CompUnits *compUnits;
	Stmts *stmts;
	Exprs *exprs;
    Arg *argVal;
    ArgList *argList;
    ExprList *exprList;
    Expr *expVal;
    PointerType *ptrType;

#line 136 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
