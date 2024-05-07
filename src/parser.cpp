/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #define YYDEBUG 1
    #include "AST.hpp"
    #include <iostream>
    #include <string>
    extern int yylex(void);
    extern BaseAST* Root; 

    void yyerror(char *s)
    {
        extern int yylineno;	// defined and maintained in lex
        extern char *yytext;	// defined and maintained in lex
        int len=strlen(yytext);
        int i;
        char buf[512]={0};
        for (i=0;i<len;++i)
        {
            sprintf(buf,"%s%d ",buf,yytext[i]);
        }
        fprintf(stderr, "ERROR: %s at symbol '%s' on line %d\n", s, buf, yylineno);
    }

#line 94 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LPAREN = 3,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 4,                     /* RPAREN  */
  YYSYMBOL_LBRACKET = 5,                   /* LBRACKET  */
  YYSYMBOL_RBRACKET = 6,                   /* RBRACKET  */
  YYSYMBOL_LBRACE = 7,                     /* LBRACE  */
  YYSYMBOL_RBRACE = 8,                     /* RBRACE  */
  YYSYMBOL_COMMA = 9,                      /* COMMA  */
  YYSYMBOL_SEMI = 10,                      /* SEMI  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_NEQ = 12,                       /* NEQ  */
  YYSYMBOL_LT = 13,                        /* LT  */
  YYSYMBOL_LEQ = 14,                       /* LEQ  */
  YYSYMBOL_GT = 15,                        /* GT  */
  YYSYMBOL_GEQ = 16,                       /* GEQ  */
  YYSYMBOL_ADD = 17,                       /* ADD  */
  YYSYMBOL_SUB = 18,                       /* SUB  */
  YYSYMBOL_MUL = 19,                       /* MUL  */
  YYSYMBOL_DIV = 20,                       /* DIV  */
  YYSYMBOL_MOD = 21,                       /* MOD  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_BAND = 25,                      /* BAND  */
  YYSYMBOL_BOR = 26,                       /* BOR  */
  YYSYMBOL_BXOR = 27,                      /* BXOR  */
  YYSYMBOL_ASSIGN = 28,                    /* ASSIGN  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_COLON = 30,                     /* COLON  */
  YYSYMBOL_QUES = 31,                      /* QUES  */
  YYSYMBOL_ELLIPSES = 32,                  /* ELLIPSES  */
  YYSYMBOL_PTR = 33,                       /* PTR  */
  YYSYMBOL_INT = 34,                       /* INT  */
  YYSYMBOL_SHORT = 35,                     /* SHORT  */
  YYSYMBOL_CHAR = 36,                      /* CHAR  */
  YYSYMBOL_VOID = 37,                      /* VOID  */
  YYSYMBOL_DOUBLE = 38,                    /* DOUBLE  */
  YYSYMBOL_BOOL = 39,                      /* BOOL  */
  YYSYMBOL_RETURN = 40,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 41,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 42,                     /* BREAK  */
  YYSYMBOL_IF = 43,                        /* IF  */
  YYSYMBOL_ELSE = 44,                      /* ELSE  */
  YYSYMBOL_FOR = 45,                       /* FOR  */
  YYSYMBOL_WHILE = 46,                     /* WHILE  */
  YYSYMBOL_TRUE = 47,                      /* TRUE  */
  YYSYMBOL_FALSE = 48,                     /* FALSE  */
  YYSYMBOL_STATIC = 49,                    /* STATIC  */
  YYSYMBOL_CONST = 50,                     /* CONST  */
  YYSYMBOL_IDENTIFIER = 51,                /* IDENTIFIER  */
  YYSYMBOL_CONST_INT = 52,                 /* CONST_INT  */
  YYSYMBOL_CONST_CHAR = 53,                /* CONST_CHAR  */
  YYSYMBOL_CONST_STR = 54,                 /* CONST_STR  */
  YYSYMBOL_CONST_DOUBLE = 55,              /* CONST_DOUBLE  */
  YYSYMBOL_CONST_FLOAT = 56,               /* CONST_FLOAT  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_Program = 58,                   /* Program  */
  YYSYMBOL_CompUnit = 59,                  /* CompUnit  */
  YYSYMBOL_Decl = 60,                      /* Decl  */
  YYSYMBOL_Btype = 61,                     /* Btype  */
  YYSYMBOL_VarDecl = 62,                   /* VarDecl  */
  YYSYMBOL_VarList = 63,                   /* VarList  */
  YYSYMBOL_VarDef = 64,                    /* VarDef  */
  YYSYMBOL_ArrDef = 65,                    /* ArrDef  */
  YYSYMBOL_ConstExp = 66,                  /* ConstExp  */
  YYSYMBOL_InitVal = 67,                   /* InitVal  */
  YYSYMBOL_FuncDef = 68,                   /* FuncDef  */
  YYSYMBOL_FuncType = 69,                  /* FuncType  */
  YYSYMBOL_ArgList = 70,                   /* ArgList  */
  YYSYMBOL__ArgList = 71,                  /* _ArgList  */
  YYSYMBOL_Arg = 72,                       /* Arg  */
  YYSYMBOL_PtrType = 73,                   /* PtrType  */
  YYSYMBOL_Block = 74,                     /* Block  */
  YYSYMBOL_BlockItem_ = 75,                /* BlockItem_  */
  YYSYMBOL_BlockItem = 76,                 /* BlockItem  */
  YYSYMBOL_Stmt = 77,                      /* Stmt  */
  YYSYMBOL_Stmt_ = 78,                     /* Stmt_  */
  YYSYMBOL_IfStmt = 79,                    /* IfStmt  */
  YYSYMBOL_ForStmt = 80,                   /* ForStmt  */
  YYSYMBOL_WhileStmt = 81,                 /* WhileStmt  */
  YYSYMBOL_BreakStmt = 82,                 /* BreakStmt  */
  YYSYMBOL_ContinueStmt = 83,              /* ContinueStmt  */
  YYSYMBOL_ReturnStmt = 84,                /* ReturnStmt  */
  YYSYMBOL_LVal = 85,                      /* LVal  */
  YYSYMBOL_ArrVal = 86,                    /* ArrVal  */
  YYSYMBOL_Exp = 87,                       /* Exp  */
  YYSYMBOL_PrimaryExp = 88,                /* PrimaryExp  */
  YYSYMBOL_Constant = 89,                  /* Constant  */
  YYSYMBOL_ExpList = 90,                   /* ExpList  */
  YYSYMBOL__ExpList = 91                   /* _ExpList  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   510

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   311


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   122,   122,   126,   127,   128,   133,   138,   139,   140,
     141,   142,   143,   149,   150,   154,   155,   160,   161,   165,
     166,   170,   174,   180,   181,   186,   187,   188,   195,   196,
     197,   198,   199,   203,   204,   208,   209,   210,   211,   214,
     219,   223,   224,   229,   230,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   254,   255,   258,   259,   263,   264,
     268,   272,   276,   280,   281,   287,   288,   292,   293,   297,
     298,   299,   300,   301,   303,   304,   305,   306,   307,   309,
     310,   311,   312,   313,   314,   316,   317,   319,   320,   321,
     323,   328,   329,   330,   335,   336,   337,   338,   342,   343,
     344,   348,   349
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "COMMA", "SEMI", "EQ", "NEQ",
  "LT", "LEQ", "GT", "GEQ", "ADD", "SUB", "MUL", "DIV", "MOD", "AND", "OR",
  "NOT", "BAND", "BOR", "BXOR", "ASSIGN", "DOT", "COLON", "QUES",
  "ELLIPSES", "PTR", "INT", "SHORT", "CHAR", "VOID", "DOUBLE", "BOOL",
  "RETURN", "CONTINUE", "BREAK", "IF", "ELSE", "FOR", "WHILE", "TRUE",
  "FALSE", "STATIC", "CONST", "IDENTIFIER", "CONST_INT", "CONST_CHAR",
  "CONST_STR", "CONST_DOUBLE", "CONST_FLOAT", "$accept", "Program",
  "CompUnit", "Decl", "Btype", "VarDecl", "VarList", "VarDef", "ArrDef",
  "ConstExp", "InitVal", "FuncDef", "FuncType", "ArgList", "_ArgList",
  "Arg", "PtrType", "Block", "BlockItem_", "BlockItem", "Stmt", "Stmt_",
  "IfStmt", "ForStmt", "WhileStmt", "BreakStmt", "ContinueStmt",
  "ReturnStmt", "LVal", "ArrVal", "Exp", "PrimaryExp", "Constant",
  "ExpList", "_ExpList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-147)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-103)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -147,     8,   -20,  -147,  -147,  -147,  -147,   103,  -147,   -29,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,   -14,  -147,    15,
      -3,  -147,    37,   188,    14,    22,  -147,   -28,    56,    57,
      58,    17,   188,   188,   188,   188,    26,    35,  -147,  -147,
    -147,  -147,  -147,  -147,   423,  -147,  -147,    39,  -147,    41,
    -147,  -147,  -147,    23,    64,  -147,   256,   423,   423,   423,
      92,  -147,   188,   106,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
    -147,   108,    84,  -147,  -147,  -147,  -147,  -147,   109,  -147,
     333,   111,   113,   188,   238,   238,    88,    88,    88,    88,
      38,    38,  -147,  -147,  -147,   457,   440,   489,    68,   474,
    -147,   126,  -147,   188,   314,  -147,  -147,    10,   107,   114,
     124,   128,   132,  -147,  -147,  -147,  -147,   135,  -147,  -147,
    -147,  -147,  -147,  -147,   118,   423,   352,  -147,  -147,   370,
    -147,  -147,   188,   211,   188,  -147,   188,  -147,   276,   188,
     137,   296,   423,   179,   388,   188,   141,   105,   188,   406,
    -147,   179,   148,   188,  -147,   141,   149,  -147,   141,  -147
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     2,     1,    25,    27,    26,     0,     4,     0,
       8,     9,    10,     7,    11,    12,     3,     0,     6,     0,
      17,    16,    32,     0,     0,     0,    31,    38,     0,     0,
      30,    37,     0,     0,     0,     0,     0,    65,    94,    95,
      96,    97,    18,    92,    22,    69,    93,     0,    14,     0,
      13,    39,    35,     0,     0,    36,     0,    70,    71,    72,
      65,    73,   100,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     0,    17,    15,    42,    23,    24,    29,    28,    91,
      99,     0,     0,     0,    79,    80,    81,    82,    83,    84,
      74,    75,    76,    77,    78,    85,    86,    87,    88,    89,
      19,     0,    90,     0,     0,    40,    53,     0,     0,     0,
       0,     0,     0,    43,    46,    41,    44,     0,    47,    48,
      49,    50,    51,    52,    92,    55,    98,    67,    63,     0,
      62,    61,     0,     0,     0,    45,     0,    64,     0,     0,
       0,     0,    54,     0,     0,     0,     0,    57,     0,     0,
      60,     0,     0,     0,    56,     0,     0,    59,     0,    58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,  -147,  -147,    43,   -18,    12,  -147,   110,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,   102,  -147,   -52,  -147,  -147,
    -146,  -137,  -147,  -147,  -147,  -147,  -147,  -147,   -33,  -147,
     -23,  -147,  -147,  -147,  -147
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    16,    17,    18,    25,    21,    24,    81,
      42,     8,     9,    28,    29,    30,    31,   124,   111,   125,
     126,   127,   128,   129,   130,   131,   132,   133,    43,    63,
     135,    45,    46,    91,    92
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,    86,   -20,    61,    27,    51,   150,   157,     3,    56,
      57,    58,    59,    32,     4,   164,     5,     6,    22,    47,
     138,   162,    19,    52,    48,    23,   166,    33,    34,     7,
      84,    49,    50,    85,    35,    36,    27,    20,    62,    90,
     -68,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    72,    73,    74,
      53,    37,    38,    39,    40,    41,    54,   -34,    55,    26,
     114,    10,    11,    12,    13,    14,    15,    60,   134,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     136,    80,    82,    77,   139,    79,    87,   -68,    10,    11,
      12,    13,    14,    15,   160,    70,    71,    72,    73,    74,
     134,    93,    23,   167,   110,   112,   169,   140,   -33,   148,
     134,   151,   113,   152,   141,   134,   154,   142,   134,    32,
     134,   143,   159,    84,   115,   144,   116,    10,    11,    12,
      13,    14,    15,    33,    34,   145,   146,   155,    84,   161,
      35,    36,   165,   168,   123,   149,    88,     0,     0,    83,
      10,    11,    12,    13,    14,    15,   117,   118,   119,   120,
       0,   121,   122,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    32,     0,     0,     0,    84,     0,     0,   116,
       0,    32,     0,     0,     0,     0,    33,    34,     0,     0,
       0,     0,     0,    35,    36,    33,    34,     0,     0,     0,
       0,     0,    35,    36,    32,     0,     0,     0,     0,   117,
     118,   119,   120,     0,   121,   122,     0,     0,    33,    34,
      37,    38,    39,    40,    41,    35,    36,     0,     0,    37,
      38,    39,    40,    41,     0,    10,    11,    12,    13,    14,
      15,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      89,     0,    37,    38,    39,    40,    41,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     153,    77,    78,    79,     0,     0,     0,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     156,    77,    78,    79,     0,     0,     0,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     137,    77,    78,    79,     0,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,     0,    77,
      78,    79,  -102,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     0,    77,    78,
      79,  -101,     0,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,     0,    77,    78,    79,
     147,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,     0,    77,    78,    79,   158,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,     0,    77,    78,    79,   163,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
       0,    77,    78,    79,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     0,    77,    78,
      79,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,     0,     0,    77,    78,    79,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,     0,
       0,     0,    77,    78,    79,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     0,     0,     0,    77,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74
};

static const yytype_int16 yycheck[] =
{
      23,    53,     5,    36,    22,    33,   143,   153,     0,    32,
      33,    34,    35,     3,    34,   161,    36,    37,     3,     5,
      10,   158,    51,    51,    10,    28,   163,    17,    18,    49,
       7,     9,    10,    10,    24,    25,    54,    51,     3,    62,
       5,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    19,    20,    21,
       4,    51,    52,    53,    54,    55,     9,     9,    51,    32,
      93,    34,    35,    36,    37,    38,    39,    51,   111,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
     113,    52,    51,    25,   117,    27,    32,     5,    34,    35,
      36,    37,    38,    39,   156,    17,    18,    19,    20,    21,
     143,     5,    28,   165,     6,     4,   168,    10,     9,   142,
     153,   144,     9,   146,    10,   158,   149,     3,   161,     3,
     163,     3,   155,     7,     8,     3,    10,    34,    35,    36,
      37,    38,    39,    17,    18,    10,    28,    10,     7,    44,
      24,    25,     4,     4,   111,   143,    54,    -1,    -1,    49,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,     3,    -1,    -1,    -1,     7,    -1,    -1,    10,
      -1,     3,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      -1,    -1,    -1,    24,    25,    17,    18,    -1,    -1,    -1,
      -1,    -1,    24,    25,     3,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    45,    46,    -1,    -1,    17,    18,
      51,    52,    53,    54,    55,    24,    25,    -1,    -1,    51,
      52,    53,    54,    55,    -1,    34,    35,    36,    37,    38,
      39,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       4,    -1,    51,    52,    53,    54,    55,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       4,    25,    26,    27,    -1,    -1,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       4,    25,    26,    27,    -1,    -1,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       6,    25,    26,    27,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    25,
      26,    27,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    25,    26,
      27,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    25,    26,    27,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    25,    26,    27,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    25,    26,    27,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    25,    26,    27,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    25,    26,
      27,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    25,    26,    27,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    25,    26,    27,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    25,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    58,    59,     0,    34,    36,    37,    49,    68,    69,
      34,    35,    36,    37,    38,    39,    60,    61,    62,    51,
      51,    64,     3,    28,    65,    63,    32,    61,    70,    71,
      72,    73,     3,    17,    18,    24,    25,    51,    52,    53,
      54,    55,    67,    85,    87,    88,    89,     5,    10,     9,
      10,    33,    51,     4,     9,    51,    87,    87,    87,    87,
      51,    85,     3,    86,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    25,    26,    27,
      52,    66,    51,    64,     7,    10,    74,    32,    72,     4,
      87,    90,    91,     5,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
       6,    75,     4,     9,    87,     8,    10,    40,    41,    42,
      43,    45,    46,    60,    74,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    87,    87,     6,    10,    87,
      10,    10,     3,     3,     3,    10,    28,    10,    87,    62,
      78,    87,    87,     4,    87,    10,     4,    77,    10,    87,
      74,    44,    78,    10,    77,     4,    78,    74,     4,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    59,    59,    60,    61,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    67,    68,    68,    69,    69,    69,    70,    70,
      70,    70,    70,    71,    71,    72,    72,    72,    72,    73,
      74,    75,    75,    76,    76,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    78,    78,    79,    79,    80,    80,
      81,    82,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    88,    88,    88,    89,    89,    89,    89,    90,    90,
      90,    91,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     2,     0,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     3,     0,     1,     3,     4,
       0,     1,     1,     6,     6,     1,     1,     1,     3,     3,
       1,     1,     0,     3,     1,     2,     2,     1,     1,     2,
       3,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     7,     5,     9,     8,
       5,     2,     2,     2,     3,     1,     2,     4,     0,     1,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* Program: CompUnit  */
#line 122 "parser.y"
                                                                                                            { (yyval.astVal) = new Program((CompUnits*)(yyvsp[0].compUnits)); Root = (yyval.astVal);}
#line 1362 "parser.cpp"
    break;

  case 3: /* CompUnit: CompUnit STATIC Decl  */
#line 126 "parser.y"
                                                                    { (yyval.compUnits) = (CompUnits*)(yyvsp[-2].compUnits); (yyval.compUnits)->push_back((CompUnit*)(yyvsp[0].astVal)); }
#line 1368 "parser.cpp"
    break;

  case 4: /* CompUnit: CompUnit FuncDef  */
#line 127 "parser.y"
                                                                                            { (yyval.compUnits) = (CompUnits*)(yyvsp[-1].compUnits); (yyval.compUnits)->push_back((CompUnit*)(yyvsp[0].astVal)); }
#line 1374 "parser.cpp"
    break;

  case 5: /* CompUnit: %empty  */
#line 128 "parser.y"
                                                                                                            { (yyval.compUnits) = new CompUnits(); }
#line 1380 "parser.cpp"
    break;

  case 6: /* Decl: VarDecl  */
#line 133 "parser.y"
                                                            { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1386 "parser.cpp"
    break;

  case 7: /* Btype: VOID  */
#line 138 "parser.y"
                                                            { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1392 "parser.cpp"
    break;

  case 8: /* Btype: INT  */
#line 139 "parser.y"
                                                            { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1398 "parser.cpp"
    break;

  case 9: /* Btype: SHORT  */
#line 140 "parser.y"
                                                            { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1404 "parser.cpp"
    break;

  case 10: /* Btype: CHAR  */
#line 141 "parser.y"
                                                            { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1410 "parser.cpp"
    break;

  case 11: /* Btype: DOUBLE  */
#line 142 "parser.y"
                                                                                        { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1416 "parser.cpp"
    break;

  case 12: /* Btype: BOOL  */
#line 143 "parser.y"
                                                            { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1422 "parser.cpp"
    break;

  case 13: /* VarDecl: Btype VarDef VarList SEMI  */
#line 149 "parser.y"
                                                            { (yyval.astVal) = new VarDecl(*(yyvsp[-3].strVal), (VarDef*)(yyvsp[-2].astVal));}
#line 1428 "parser.cpp"
    break;

  case 14: /* VarDecl: Btype IDENTIFIER ArrDef SEMI  */
#line 150 "parser.y"
                                                                                { (yyval.astVal) = new ArrDef(*(yyvsp[-3].strVal), *(yyvsp[-2].strVal), (Exprs*)(yyvsp[-1].exprs)); }
#line 1434 "parser.cpp"
    break;

  case 16: /* VarList: %empty  */
#line 155 "parser.y"
                                                            { ; }
#line 1440 "parser.cpp"
    break;

  case 17: /* VarDef: IDENTIFIER  */
#line 160 "parser.y"
                                                            { (yyval.astVal) = new VarDef(*(yyvsp[0].strVal));}
#line 1446 "parser.cpp"
    break;

  case 18: /* VarDef: IDENTIFIER ASSIGN InitVal  */
#line 161 "parser.y"
                                                            { (yyval.astVal) = new VarDef(*(yyvsp[-2].strVal), (Expr*)(yyvsp[0].astVal));}
#line 1452 "parser.cpp"
    break;

  case 19: /* ArrDef: ArrDef LBRACKET ConstExp RBRACKET  */
#line 165 "parser.y"
                                                                        { (yyval.exprs) = (Exprs*)(yyvsp[-3].exprs); (yyval.exprs)->push_back((Expr*)(yyvsp[-1].astVal)); }
#line 1458 "parser.cpp"
    break;

  case 20: /* ArrDef: %empty  */
#line 166 "parser.y"
                                                                                                                { (yyval.exprs) = new Exprs(); }
#line 1464 "parser.cpp"
    break;

  case 21: /* ConstExp: CONST_INT  */
#line 170 "parser.y"
                                                                                            { (yyval.astVal) = new Constant((yyvsp[0].intVal)); }
#line 1470 "parser.cpp"
    break;

  case 22: /* InitVal: Exp  */
#line 174 "parser.y"
                                                            { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1476 "parser.cpp"
    break;

  case 23: /* FuncDef: FuncType IDENTIFIER LPAREN ArgList RPAREN SEMI  */
#line 180 "parser.y"
                                                            { (yyval.astVal) = new FuncDef(*(yyvsp[-5].strVal), *(yyvsp[-4].strVal), (ArgList*)(yyvsp[-2].argList)); }
#line 1482 "parser.cpp"
    break;

  case 24: /* FuncDef: FuncType IDENTIFIER LPAREN ArgList RPAREN Block  */
#line 181 "parser.y"
                                                            { (yyval.astVal) = new FuncDef(*(yyvsp[-5].strVal), *(yyvsp[-4].strVal), (ArgList*)(yyvsp[-2].argList), (Block*)(yyvsp[0].astVal)); }
#line 1488 "parser.cpp"
    break;

  case 25: /* FuncType: INT  */
#line 186 "parser.y"
                                                            { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1494 "parser.cpp"
    break;

  case 26: /* FuncType: VOID  */
#line 187 "parser.y"
                                                            { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1500 "parser.cpp"
    break;

  case 27: /* FuncType: CHAR  */
#line 188 "parser.y"
                                                            { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1506 "parser.cpp"
    break;

  case 28: /* ArgList: _ArgList COMMA Arg  */
#line 195 "parser.y"
                                                                                                { (yyval.argList) = (yyvsp[-2].argList); (yyval.argList)->push_back((yyvsp[0].argVal));   }
#line 1512 "parser.cpp"
    break;

  case 29: /* ArgList: _ArgList COMMA ELLIPSES  */
#line 196 "parser.y"
                                                                                                { (yyval.argList) = (yyvsp[-2].argList); (yyval.argList)->SetVarArg();   }
#line 1518 "parser.cpp"
    break;

  case 30: /* ArgList: Arg  */
#line 197 "parser.y"
                                                                                                                { (yyval.argList) = new ArgList(); (yyval.argList)->push_back((yyvsp[0].argVal));   }
#line 1524 "parser.cpp"
    break;

  case 31: /* ArgList: ELLIPSES  */
#line 198 "parser.y"
                                                                                                                { (yyval.argList) = new ArgList(); (yyval.argList)->SetVarArg();   }
#line 1530 "parser.cpp"
    break;

  case 32: /* ArgList: %empty  */
#line 199 "parser.y"
                                                                                                                        { (yyval.argList) = new ArgList(); }
#line 1536 "parser.cpp"
    break;

  case 33: /* _ArgList: _ArgList COMMA Arg  */
#line 203 "parser.y"
                                                                                                { (yyval.argList) = (yyvsp[-2].argList); (yyval.argList)->push_back((yyvsp[0].argVal));   }
#line 1542 "parser.cpp"
    break;

  case 34: /* _ArgList: Arg  */
#line 204 "parser.y"
                                                                                                                { (yyval.argList) = new ArgList(); (yyval.argList)->push_back((yyvsp[0].argVal));   }
#line 1548 "parser.cpp"
    break;

  case 35: /* Arg: Btype IDENTIFIER  */
#line 208 "parser.y"
                                                                                                { (yyval.argVal) = new Arg(*(yyvsp[-1].strVal), *(yyvsp[0].strVal));   }
#line 1554 "parser.cpp"
    break;

  case 36: /* Arg: PtrType IDENTIFIER  */
#line 209 "parser.y"
                                                                                        { (yyval.argVal) = new Arg((yyvsp[-1].ptrType), *(yyvsp[0].strVal));   }
#line 1560 "parser.cpp"
    break;

  case 37: /* Arg: PtrType  */
#line 210 "parser.y"
                                                                                            { (yyval.argVal) = new Arg((yyvsp[0].ptrType));   }
#line 1566 "parser.cpp"
    break;

  case 38: /* Arg: Btype  */
#line 211 "parser.y"
                                                            { (yyval.argVal) = new Arg(*(yyvsp[0].strVal));   }
#line 1572 "parser.cpp"
    break;

  case 39: /* PtrType: Btype PTR  */
#line 214 "parser.y"
                                                            { (yyval.ptrType) = new PointerType(*(yyvsp[-1].strVal)); }
#line 1578 "parser.cpp"
    break;

  case 40: /* Block: LBRACE BlockItem_ RBRACE  */
#line 219 "parser.y"
                                                            { (yyval.astVal) = new Block((Stmts*)(yyvsp[-1].stmts));}
#line 1584 "parser.cpp"
    break;

  case 41: /* BlockItem_: BlockItem_ BlockItem  */
#line 223 "parser.y"
                                                                                { (yyval.stmts) = (Stmts*)(yyvsp[-1].stmts); if ((yyvsp[0].astVal) != NULL) (yyval.stmts)->push_back((Stmt*)(yyvsp[0].astVal)); }
#line 1590 "parser.cpp"
    break;

  case 42: /* BlockItem_: %empty  */
#line 224 "parser.y"
                                                                                                    { (yyval.stmts) = new Stmts(); }
#line 1596 "parser.cpp"
    break;

  case 43: /* BlockItem: Decl  */
#line 229 "parser.y"
                                                            { (yyval.astVal) = (yyvsp[0].astVal);}
#line 1602 "parser.cpp"
    break;

  case 44: /* BlockItem: Stmt  */
#line 230 "parser.y"
                                                                                                    { (yyval.astVal) = (yyvsp[0].astVal);}
#line 1608 "parser.cpp"
    break;

  case 45: /* Stmt: Stmt_ SEMI  */
#line 243 "parser.y"
                                                                                                        {  (yyval.astVal) = (yyvsp[-1].astVal);   }
#line 1614 "parser.cpp"
    break;

  case 46: /* Stmt: Block  */
#line 244 "parser.y"
                                                                                                                {  (yyval.astVal) = (yyvsp[0].astVal);   }
#line 1620 "parser.cpp"
    break;

  case 47: /* Stmt: IfStmt  */
#line 245 "parser.y"
                                                                                                        {  (yyval.astVal) = (yyvsp[0].astVal);   }
#line 1626 "parser.cpp"
    break;

  case 48: /* Stmt: ForStmt  */
#line 246 "parser.y"
                                                                                                        {  (yyval.astVal) = (yyvsp[0].astVal);   }
#line 1632 "parser.cpp"
    break;

  case 49: /* Stmt: WhileStmt  */
#line 247 "parser.y"
                                                                                                        {  (yyval.astVal) = (yyvsp[0].astVal);   }
#line 1638 "parser.cpp"
    break;

  case 50: /* Stmt: BreakStmt  */
#line 248 "parser.y"
                                                                                                        {  (yyval.astVal) = (yyvsp[0].astVal);   }
#line 1644 "parser.cpp"
    break;

  case 51: /* Stmt: ContinueStmt  */
#line 249 "parser.y"
                                                                                                        {  (yyval.astVal) = (yyvsp[0].astVal);   }
#line 1650 "parser.cpp"
    break;

  case 52: /* Stmt: ReturnStmt  */
#line 250 "parser.y"
                                                                                                        {  (yyval.astVal) = (yyvsp[0].astVal);   }
#line 1656 "parser.cpp"
    break;

  case 53: /* Stmt: SEMI  */
#line 251 "parser.y"
                                                                                                                {  (yyval.astVal) = NULL;   }
#line 1662 "parser.cpp"
    break;

  case 54: /* Stmt_: LVal ASSIGN Exp  */
#line 254 "parser.y"
                                                            { (yyval.astVal) = new Assign((LeftVal*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal)); }
#line 1668 "parser.cpp"
    break;

  case 55: /* Stmt_: Exp  */
#line 255 "parser.y"
                                                            { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1674 "parser.cpp"
    break;

  case 56: /* IfStmt: IF LPAREN Exp RPAREN Stmt ELSE Stmt  */
#line 258 "parser.y"
                                                                            {  (yyval.astVal) = new IfStmt((Expr*)(yyvsp[-4].astVal), (Stmt*)(yyvsp[-2].astVal), (Stmt*)(yyvsp[0].astVal));   }
#line 1680 "parser.cpp"
    break;

  case 57: /* IfStmt: IF LPAREN Exp RPAREN Stmt  */
#line 259 "parser.y"
                                                                                {  (yyval.astVal) = new IfStmt((Expr*)(yyvsp[-2].astVal), (Stmt*)(yyvsp[0].astVal));   }
#line 1686 "parser.cpp"
    break;

  case 58: /* ForStmt: FOR LPAREN Stmt_ SEMI Exp SEMI Stmt_ RPAREN Block  */
#line 263 "parser.y"
                                                                {  (yyval.astVal) = new ForStmt((Stmt*)(yyvsp[-6].astVal), (Expr*)(yyvsp[-4].astVal), (Stmt*)(yyvsp[-2].astVal), (Stmt*)(yyvsp[0].astVal));   }
#line 1692 "parser.cpp"
    break;

  case 59: /* ForStmt: FOR LPAREN VarDecl Exp SEMI Stmt_ RPAREN Block  */
#line 264 "parser.y"
                                                            {  (yyval.astVal) = new ForStmt((Stmt*)(yyvsp[-5].astVal), (Expr*)(yyvsp[-4].astVal), (Stmt*)(yyvsp[-2].astVal), (Stmt*)(yyvsp[0].astVal));   }
#line 1698 "parser.cpp"
    break;

  case 60: /* WhileStmt: WHILE LPAREN Exp RPAREN Block  */
#line 268 "parser.y"
                                                                                {  (yyval.astVal) = new WhileStmt((Expr*)(yyvsp[-2].astVal), (Stmt*)(yyvsp[0].astVal));   }
#line 1704 "parser.cpp"
    break;

  case 61: /* BreakStmt: BREAK SEMI  */
#line 272 "parser.y"
                                                                                                        {  (yyval.astVal) = new BreakStmt();   }
#line 1710 "parser.cpp"
    break;

  case 62: /* ContinueStmt: CONTINUE SEMI  */
#line 276 "parser.y"
                                                                                                        {  (yyval.astVal) = new ContinueStmt();   }
#line 1716 "parser.cpp"
    break;

  case 63: /* ReturnStmt: RETURN SEMI  */
#line 280 "parser.y"
                                                                                                        {  (yyval.astVal) = new ReturnStmt();   }
#line 1722 "parser.cpp"
    break;

  case 64: /* ReturnStmt: RETURN Exp SEMI  */
#line 281 "parser.y"
                                                                                                        {  (yyval.astVal) = new ReturnStmt((Expr*)(yyvsp[-1].astVal));   }
#line 1728 "parser.cpp"
    break;

  case 65: /* LVal: IDENTIFIER  */
#line 287 "parser.y"
                                                                                            { (yyval.astVal) = new LeftVal(*(yyvsp[0].strVal)); }
#line 1734 "parser.cpp"
    break;

  case 66: /* LVal: IDENTIFIER ArrVal  */
#line 288 "parser.y"
                                                                                    { (yyval.astVal) = new ArrVal(*(yyvsp[-1].strVal), (Exprs*)(yyvsp[0].exprs)); }
#line 1740 "parser.cpp"
    break;

  case 67: /* ArrVal: ArrVal LBRACKET Exp RBRACKET  */
#line 292 "parser.y"
                                                                    { (yyval.exprs) = (Exprs*)(yyvsp[-3].exprs); (yyval.exprs)->push_back((Expr*)(yyvsp[-1].astVal)); }
#line 1746 "parser.cpp"
    break;

  case 68: /* ArrVal: %empty  */
#line 293 "parser.y"
                                                                                                    { (yyval.exprs) = new Exprs(); }
#line 1752 "parser.cpp"
    break;

  case 69: /* Exp: PrimaryExp  */
#line 297 "parser.y"
                                                                                    { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1758 "parser.cpp"
    break;

  case 70: /* Exp: ADD Exp  */
#line 298 "parser.y"
                                                                            { (yyval.astVal) = new UnaryPlus((Expr*)(yyvsp[0].astVal)); }
#line 1764 "parser.cpp"
    break;

  case 71: /* Exp: SUB Exp  */
#line 299 "parser.y"
                                                                            { (yyval.astVal) = new UnaryMinus((Expr*)(yyvsp[0].astVal)); }
#line 1770 "parser.cpp"
    break;

  case 72: /* Exp: NOT Exp  */
#line 300 "parser.y"
                                                                                    { (yyval.astVal) = new LogicNot((Expr*)(yyvsp[0].astVal)); }
#line 1776 "parser.cpp"
    break;

  case 73: /* Exp: BAND LVal  */
#line 301 "parser.y"
                                                                        { (yyval.astVal) = new AddressOf((LeftVal*)(yyvsp[0].astVal)); }
#line 1782 "parser.cpp"
    break;

  case 74: /* Exp: Exp ADD Exp  */
#line 303 "parser.y"
                                                                                    { (yyval.astVal) = new Addition((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1788 "parser.cpp"
    break;

  case 75: /* Exp: Exp SUB Exp  */
#line 304 "parser.y"
                                                                                    { (yyval.astVal) = new Subtraction((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1794 "parser.cpp"
    break;

  case 76: /* Exp: Exp MUL Exp  */
#line 305 "parser.y"
                                                                                    { (yyval.astVal) = new Multiplication((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1800 "parser.cpp"
    break;

  case 77: /* Exp: Exp DIV Exp  */
#line 306 "parser.y"
                                                                                    { (yyval.astVal) = new Division((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1806 "parser.cpp"
    break;

  case 78: /* Exp: Exp MOD Exp  */
#line 307 "parser.y"
                                                                                    { (yyval.astVal) = new Modulo((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1812 "parser.cpp"
    break;

  case 79: /* Exp: Exp EQ Exp  */
#line 309 "parser.y"
                                                                                    { (yyval.astVal) = new LogicEQ((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1818 "parser.cpp"
    break;

  case 80: /* Exp: Exp NEQ Exp  */
#line 310 "parser.y"
                                                                                    { (yyval.astVal) = new LogicNEQ((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1824 "parser.cpp"
    break;

  case 81: /* Exp: Exp LT Exp  */
#line 311 "parser.y"
                                                                                    { (yyval.astVal) = new LogicLT((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1830 "parser.cpp"
    break;

  case 82: /* Exp: Exp LEQ Exp  */
#line 312 "parser.y"
                                                                                    { (yyval.astVal) = new LogicLEQ((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1836 "parser.cpp"
    break;

  case 83: /* Exp: Exp GT Exp  */
#line 313 "parser.y"
                                                                                    { (yyval.astVal) = new LogicGT((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1842 "parser.cpp"
    break;

  case 84: /* Exp: Exp GEQ Exp  */
#line 314 "parser.y"
                                                                                    { (yyval.astVal) = new LogicGEQ((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1848 "parser.cpp"
    break;

  case 85: /* Exp: Exp AND Exp  */
#line 316 "parser.y"
                                                                                    { (yyval.astVal) = new LogicAND((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1854 "parser.cpp"
    break;

  case 86: /* Exp: Exp OR Exp  */
#line 317 "parser.y"
                                                                                    { (yyval.astVal) = new LogicOR((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1860 "parser.cpp"
    break;

  case 87: /* Exp: Exp BAND Exp  */
#line 319 "parser.y"
                                                            { (yyval.astVal) = new BitwiseAND((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1866 "parser.cpp"
    break;

  case 88: /* Exp: Exp BOR Exp  */
#line 320 "parser.y"
                                                            { (yyval.astVal) = new BitwiseOR((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1872 "parser.cpp"
    break;

  case 89: /* Exp: Exp BXOR Exp  */
#line 321 "parser.y"
                                                            { (yyval.astVal) = new BitwiseXOR((Expr*)(yyvsp[-2].astVal), (Expr*)(yyvsp[0].astVal));}
#line 1878 "parser.cpp"
    break;

  case 90: /* Exp: IDENTIFIER LPAREN ExpList RPAREN  */
#line 323 "parser.y"
                                                            { (yyval.astVal) = new FuncCall(*(yyvsp[-3].strVal), (ExprList*)(yyvsp[-1].exprList));   }
#line 1884 "parser.cpp"
    break;

  case 91: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 328 "parser.y"
                                                                            { (yyval.astVal) = (yyvsp[-1].astVal); }
#line 1890 "parser.cpp"
    break;

  case 92: /* PrimaryExp: LVal  */
#line 329 "parser.y"
                                                                                            { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1896 "parser.cpp"
    break;

  case 93: /* PrimaryExp: Constant  */
#line 330 "parser.y"
                                                                                    { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1902 "parser.cpp"
    break;

  case 94: /* Constant: CONST_INT  */
#line 335 "parser.y"
                                                                                    { (yyval.astVal) = new Constant((yyvsp[0].intVal)); }
#line 1908 "parser.cpp"
    break;

  case 95: /* Constant: CONST_CHAR  */
#line 336 "parser.y"
                                                                                    { (yyval.astVal) = new Constant((yyvsp[0].charVal)); }
#line 1914 "parser.cpp"
    break;

  case 96: /* Constant: CONST_STR  */
#line 337 "parser.y"
                                                            { (yyval.astVal) = new StringType(*(yyvsp[0].strVal)); }
#line 1920 "parser.cpp"
    break;

  case 97: /* Constant: CONST_DOUBLE  */
#line 338 "parser.y"
                                                                                    { std::cout << (yyvsp[0].douVal) << std::endl;  (yyval.astVal) = new Constant((yyvsp[0].douVal)); }
#line 1926 "parser.cpp"
    break;

  case 98: /* ExpList: _ExpList COMMA Exp  */
#line 342 "parser.y"
                                                                                        { (yyval.exprList) = (yyvsp[-2].exprList); (yyval.exprList)->push_back((Expr*)(yyvsp[0].astVal));   }
#line 1932 "parser.cpp"
    break;

  case 99: /* ExpList: Exp  */
#line 343 "parser.y"
                                                                                    { (yyval.exprList) = new ExprList(); (yyval.exprList)->push_back((Expr*)(yyvsp[0].astVal));   }
#line 1938 "parser.cpp"
    break;

  case 100: /* ExpList: %empty  */
#line 344 "parser.y"
                                                                                                                    { (yyval.exprList) = new ExprList();   }
#line 1944 "parser.cpp"
    break;

  case 101: /* _ExpList: _ExpList COMMA Exp  */
#line 348 "parser.y"
                                                                                            { (yyval.exprList) = (yyvsp[-2].exprList); (yyval.exprList)->push_back((Expr*)(yyvsp[0].astVal));   }
#line 1950 "parser.cpp"
    break;

  case 102: /* _ExpList: Exp  */
#line 349 "parser.y"
                                                                                    { (yyval.exprList) = new ExprList(); (yyval.exprList)->push_back((Expr*)(yyvsp[0].astVal));   }
#line 1956 "parser.cpp"
    break;


#line 1960 "parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 352 "parser.y"

