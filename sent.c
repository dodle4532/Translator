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
#line 1 "sent.y"

  #include <math.h>
  #include <stdio.h>
  #include <stdlib.h> // Для NULL
  #include <string.h>
  #include "lex.h"
  #include "ast.h"
  #include "astHelper.h"
  int yylex (void);
  void yyerror (char *s);
  extern struct ast* ast;
  int num = 1;
  bool isFunc = false;
  enum VALUE_TYPE getValueType(char* val) {
      if (val == NULL) {
        return NULL_TYPE;
      }
      if (!strcmp(val, "bool")) {
          return BOOLEAN_TYPE;
      }
      if (!strcmp(val, "u32") || !strcmp(val, "u64")) {
          return INTEGER_TYPE;
      }
      if (!strcmp(val, "f32")) {
          return FLOAT_TYPE;
      }
      if (!strcmp(val, "str")) {
          return STRING_TYPE;
      }
      return NULL_TYPE;
  }

#line 104 "sent.c"

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

#include "sent.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_WORD = 5,                       /* WORD  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_LET = 7,                        /* LET  */
  YYSYMBOL_U32 = 8,                        /* U32  */
  YYSYMBOL_U64 = 9,                        /* U64  */
  YYSYMBOL_F32 = 10,                       /* F32  */
  YYSYMBOL_STR = 11,                       /* STR  */
  YYSYMBOL_BOOL = 12,                      /* BOOL  */
  YYSYMBOL_TRUE = 13,                      /* TRUE  */
  YYSYMBOL_FALSE = 14,                     /* FALSE  */
  YYSYMBOL_FN = 15,                        /* FN  */
  YYSYMBOL_INT = 16,                       /* INT  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_EQUALS = 21,                    /* EQUALS  */
  YYSYMBOL_NOT_EQUALS = 22,                /* NOT_EQUALS  */
  YYSYMBOL_QUOTE = 23,                     /* QUOTE  */
  YYSYMBOL_IN = 24,                        /* IN  */
  YYSYMBOL_TWO_POINTS = 25,                /* TWO_POINTS  */
  YYSYMBOL_ARROW = 26,                     /* ARROW  */
  YYSYMBOL_RETURN = 27,                    /* RETURN  */
  YYSYMBOL_LESS = 28,                      /* LESS  */
  YYSYMBOL_MORE = 29,                      /* MORE  */
  YYSYMBOL_EQ_LESS = 30,                   /* EQ_LESS  */
  YYSYMBOL_EQ_MORE = 31,                   /* EQ_MORE  */
  YYSYMBOL_32_ = 32,                       /* ';'  */
  YYSYMBOL_33_ = 33,                       /* ':'  */
  YYSYMBOL_34_ = 34,                       /* '='  */
  YYSYMBOL_35_ = 35,                       /* '('  */
  YYSYMBOL_36_ = 36,                       /* ')'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* '{'  */
  YYSYMBOL_39_ = 39,                       /* '}'  */
  YYSYMBOL_40_ = 40,                       /* '+'  */
  YYSYMBOL_41_ = 41,                       /* '-'  */
  YYSYMBOL_42_ = 42,                       /* '*'  */
  YYSYMBOL_43_ = 43,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_input = 45,                     /* input  */
  YYSYMBOL_command = 46,                   /* command  */
  YYSYMBOL_declaration = 47,               /* declaration  */
  YYSYMBOL_init = 48,                      /* init  */
  YYSYMBOL_initialization = 49,            /* initialization  */
  YYSYMBOL_assignment = 50,                /* assignment  */
  YYSYMBOL_type = 51,                      /* type  */
  YYSYMBOL_functionCall = 52,              /* functionCall  */
  YYSYMBOL_value = 53,                     /* value  */
  YYSYMBOL_parametrs = 54,                 /* parametrs  */
  YYSYMBOL_par = 55,                       /* par  */
  YYSYMBOL_val = 56,                       /* val  */
  YYSYMBOL_function = 57,                  /* function  */
  YYSYMBOL_returnArrow = 58,               /* returnArrow  */
  YYSYMBOL_functionImplementation = 59,    /* functionImplementation  */
  YYSYMBOL_returnVal = 60,                 /* returnVal  */
  YYSYMBOL_funcImpl = 61,                  /* funcImpl  */
  YYSYMBOL_brackets_functionImplementation = 62, /* brackets_functionImplementation  */
  YYSYMBOL_if_expression = 63,             /* if_expression  */
  YYSYMBOL_else_expression = 64,           /* else_expression  */
  YYSYMBOL_expression = 65,                /* expression  */
  YYSYMBOL_cmp = 66,                       /* cmp  */
  YYSYMBOL_while_expression = 67,          /* while_expression  */
  YYSYMBOL_for_expression = 68,            /* for_expression  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_second = 70                     /* second  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   105

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
      35,    36,    42,    40,    37,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    32,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    93,    93,    94,    98,    99,   100,   101,   102,   103,
     104,   108,   115,   116,   119,   124,   128,   129,   130,   131,
     132,   136,   141,   142,   144,   152,   154,   162,   163,   167,
     170,   173,   176,   179,   182,   185,   189,   195,   196,   200,
     201,   205,   206,   210,   211,   212,   213,   214,   215,   216,
     221,   225,   232,   233,   237,   241,   242,   243,   244,   245,
     246,   250,   255,   267,   268,   269,   273,   274,   275
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
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "FLOAT", "WORD",
  "STRING", "LET", "U32", "U64", "F32", "STR", "BOOL", "TRUE", "FALSE",
  "FN", "INT", "IF", "ELSE", "FOR", "WHILE", "EQUALS", "NOT_EQUALS",
  "QUOTE", "IN", "TWO_POINTS", "ARROW", "RETURN", "LESS", "MORE",
  "EQ_LESS", "EQ_MORE", "';'", "':'", "'='", "'('", "')'", "','", "'{'",
  "'}'", "'+'", "'-'", "'*'", "'/'", "$accept", "input", "command",
  "declaration", "init", "initialization", "assignment", "type",
  "functionCall", "value", "parametrs", "par", "val", "function",
  "returnArrow", "functionImplementation", "returnVal", "funcImpl",
  "brackets_functionImplementation", "if_expression", "else_expression",
  "expression", "cmp", "while_expression", "for_expression", "expr",
  "second", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-78)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -78,     7,   -78,   -25,     8,    12,    28,    14,    28,   -78,
     -78,   -78,    -7,   -78,   -78,   -78,   -78,    28,    28,     6,
      10,    11,   -78,   -78,    17,   -78,   -78,   -78,   -78,    29,
       9,    21,     9,   -78,   -27,   -78,   -11,    18,    19,   -78,
      53,    50,   -78,   -78,   -78,   -78,   -78,   -78,    28,     1,
      48,    64,   -78,    28,    28,    28,    28,   -78,    28,   -78,
     -78,   -78,   -78,   -78,    34,    36,    35,    33,   -78,    28,
     -78,   -78,    40,    37,     1,   -78,   -78,   -78,     9,   -78,
      49,   -78,   -78,   -78,   -78,   -78,    45,   -78,    53,    52,
      50,    47,   -78,   -78,   -78,   -78,   -78,    77,   -78,   -78,
      53,    43,   -78,   -78,     9,   -78,     1,   -78,    44,   -78
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     3,
       4,     5,     0,     7,     8,     9,    10,     0,    22,     0,
       0,     0,    30,    31,    32,    29,    33,    34,    35,     0,
       0,     0,     0,     6,    68,    15,    65,     0,    23,    14,
       0,    28,    55,    56,    57,    58,    59,    60,     0,     0,
      53,     0,    61,     0,     0,     0,     0,    21,    22,    16,
      17,    18,    19,    20,    13,     0,     0,    25,    54,    42,
      45,    44,     0,     0,    39,    46,    47,    48,     0,    51,
       0,    66,    67,    63,    64,    24,     0,    12,     0,    38,
      28,     0,    41,    43,    50,    40,    52,     0,    11,    27,
       0,     0,    26,    49,     0,    37,     0,    62,     0,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   -78,    81,   -78,    83,    22,   -77,    -1,    27,
      -3,   -78,    -4,   -78,   -78,   -69,   -78,   -78,   -29,    87,
     -78,    82,   -78,    88,    90,   -16,   -18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     9,    70,    86,    71,    19,    64,    28,    37,
      66,    67,    34,    13,   101,    73,    91,    74,    50,    75,
      79,    30,    48,    76,    77,    38,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      12,    35,    29,    52,    29,    95,     3,     2,     4,    17,
      18,    99,     3,    20,     4,    53,    54,    21,     6,    31,
       7,     8,     5,   105,     6,    33,     7,     8,    69,    55,
      56,    22,    23,    24,    25,    81,    82,   108,    39,    83,
      84,    26,    27,    40,    68,    51,    41,    49,    72,    96,
      42,    43,    18,    92,    57,    65,    58,    44,    45,    46,
      47,    59,    60,    61,    62,    63,    78,    80,    17,    88,
      90,    89,    93,    72,    97,   107,    94,    98,   100,   103,
     104,   106,    10,   109,    11,    85,    87,   102,    14,    15,
      32,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    72
};

static const yytype_int8 yycheck[] =
{
       1,    17,     6,    32,     8,    74,     5,     0,     7,    34,
      35,    88,     5,     5,     7,    42,    43,     5,    17,     5,
      19,    20,    15,   100,    17,    32,    19,    20,    27,    40,
      41,     3,     4,     5,     6,    53,    54,   106,    32,    55,
      56,    13,    14,    33,    48,    24,    35,    38,    49,    78,
      21,    22,    35,    69,    36,     5,    37,    28,    29,    30,
      31,     8,     9,    10,    11,    12,    18,     3,    34,    33,
      37,    36,    32,    74,    25,   104,    39,    32,    26,    32,
       3,    38,     1,    39,     1,    58,    64,    90,     1,     1,
       8,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,     0,     5,     7,    15,    17,    19,    20,    46,
      47,    49,    52,    57,    63,    67,    68,    34,    35,    50,
       5,     5,     3,     4,     5,     6,    13,    14,    52,    56,
      65,     5,    65,    32,    56,    69,    70,    53,    69,    32,
      33,    35,    21,    22,    28,    29,    30,    31,    66,    38,
      62,    24,    62,    42,    43,    40,    41,    36,    37,     8,
       9,    10,    11,    12,    51,     5,    54,    55,    56,    27,
      47,    49,    52,    59,    61,    63,    67,    68,    18,    64,
       3,    70,    70,    69,    69,    53,    48,    50,    33,    36,
      37,    60,    69,    32,    39,    59,    62,    25,    32,    51,
      26,    58,    54,    32,     3,    51,    38,    62,    59,    39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    47,    48,    48,    49,    50,    51,    51,    51,    51,
      51,    52,    53,    53,    53,    54,    54,    55,    55,    56,
      56,    56,    56,    56,    56,    56,    57,    58,    58,    59,
      59,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      62,    63,    64,    64,    65,    66,    66,    66,    66,    66,
      66,    67,    68,    69,    69,    69,    70,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     1,     1,     1,
       1,     6,     1,     0,     3,     2,     1,     1,     1,     1,
       1,     4,     0,     1,     3,     1,     3,     3,     0,     1,
       1,     1,     1,     1,     1,     1,     9,     2,     0,     1,
       2,     1,     0,     2,     1,     1,     1,     1,     1,     3,
       3,     4,     2,     0,     3,     1,     1,     1,     1,     1,
       1,     3,     7,     3,     3,     1,     3,     3,     1
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
  case 3: /* input: input command  */
#line 94 "sent.y"
                {}
#line 1232 "sent.c"
    break;

  case 4: /* command: declaration  */
#line 98 "sent.y"
              {push_back_com(ast->declarations, (yyvsp[0].com));}
#line 1238 "sent.c"
    break;

  case 5: /* command: initialization  */
#line 99 "sent.y"
                 {push_back_com(ast->initializations, (yyvsp[0].com));}
#line 1244 "sent.c"
    break;

  case 6: /* command: functionCall ';'  */
#line 100 "sent.y"
                   {push_back_com(ast->functionCalls, (yyvsp[-1].com));}
#line 1250 "sent.c"
    break;

  case 7: /* command: function  */
#line 101 "sent.y"
           {push_back_com(ast->functions, (yyvsp[0].com));}
#line 1256 "sent.c"
    break;

  case 8: /* command: if_expression  */
#line 102 "sent.y"
                {push_back_com(ast->if_expressions, (yyvsp[0].com));}
#line 1262 "sent.c"
    break;

  case 9: /* command: while_expression  */
#line 103 "sent.y"
                   {push_back_com(ast->cycles, (yyvsp[0].com));}
#line 1268 "sent.c"
    break;

  case 10: /* command: for_expression  */
#line 104 "sent.y"
                 {push_back_com(ast->cycles, (yyvsp[0].com));}
#line 1274 "sent.c"
    break;

  case 11: /* declaration: LET WORD ':' type init ';'  */
#line 108 "sent.y"
                             { 
                               struct member_type* mem = createMember((yyvsp[-1]._val), (yyvsp[-4].str));
                               mem->wantedType = getValueType((yyvsp[-2].str));
                               (yyval.com) = createCommand(num++, MEMBER_COM_TYPE, mem); free((yyvsp[-2].str));}
#line 1283 "sent.c"
    break;

  case 12: /* init: assignment  */
#line 115 "sent.y"
             {(yyval._val) = (yyvsp[0]._val);}
#line 1289 "sent.c"
    break;

  case 13: /* init: %empty  */
#line 116 "sent.y"
         {(yyval._val) = createValue(NULL_TYPE, NULL);}
#line 1295 "sent.c"
    break;

  case 14: /* initialization: WORD assignment ';'  */
#line 119 "sent.y"
                      { struct member_type* mem = createMember((yyvsp[-1]._val), (yyvsp[-2].str));
                        (yyval.com) = createCommand(num++, INIT_COM_TYPE, mem);}
#line 1302 "sent.c"
    break;

  case 15: /* assignment: '=' expr  */
#line 124 "sent.y"
           {(yyval._val) = (yyvsp[0]._val);}
#line 1308 "sent.c"
    break;

  case 16: /* type: U32  */
#line 128 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1314 "sent.c"
    break;

  case 17: /* type: U64  */
#line 129 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1320 "sent.c"
    break;

  case 18: /* type: F32  */
#line 130 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1326 "sent.c"
    break;

  case 19: /* type: STR  */
#line 131 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1332 "sent.c"
    break;

  case 20: /* type: BOOL  */
#line 132 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1338 "sent.c"
    break;

  case 21: /* functionCall: WORD '(' value ')'  */
#line 136 "sent.y"
                           { struct func_call_type* f = createFuncCall((yyvsp[-3].str), (yyvsp[-1].valVec));
                             (yyval.com) = createCommand(num++, FUNC_CALL_TYPE, f);}
#line 1345 "sent.c"
    break;

  case 22: /* value: %empty  */
#line 141 "sent.y"
                {(yyval.valVec) = createValueVec();}
#line 1351 "sent.c"
    break;

  case 23: /* value: expr  */
#line 142 "sent.y"
                 {(yyval.valVec) = createValueVec();
                 push_back_val((yyval.valVec), (yyvsp[0]._val));}
#line 1358 "sent.c"
    break;

  case 24: /* value: expr ',' value  */
#line 144 "sent.y"
                 {(yyval.valVec) = createValueVec();
                 push_back_val((yyval.valVec), (yyvsp[-2]._val));
                 for(int i = 0; i < (yyvsp[0].valVec)->size; ++i) {
                  push_back_val((yyval.valVec), (yyvsp[0].valVec)->values[i]);
                 }}
#line 1368 "sent.c"
    break;

  case 25: /* parametrs: par  */
#line 152 "sent.y"
                    {(yyval.membVec) = createMemberVec();
                     if ((yyvsp[0].memb)->value->type != NULL_TYPE) push_back_mem((yyval.membVec), (yyvsp[0].memb));}
#line 1375 "sent.c"
    break;

  case 26: /* parametrs: par ',' parametrs  */
#line 154 "sent.y"
                    {(yyval.membVec) = createMemberVec();
                     push_back_mem((yyval.membVec), (yyvsp[-2].memb));
                     for(int i = 0; i < (yyvsp[0].membVec)->size; ++i) {
                      push_back_mem((yyval.membVec), (yyvsp[0].membVec)->members[i]);
                     }}
#line 1385 "sent.c"
    break;

  case 27: /* par: WORD ':' type  */
#line 162 "sent.y"
                {(yyval.memb) = createMember(createValue(getValueType((yyvsp[0].str)), NULL), (yyvsp[-2].str));}
#line 1391 "sent.c"
    break;

  case 28: /* par: %empty  */
#line 163 "sent.y"
           {(yyval.memb) = createMember(createValue(NULL_TYPE, NULL), NULL);}
#line 1397 "sent.c"
    break;

  case 29: /* val: STRING  */
#line 167 "sent.y"
         { char* str = calloc(64, sizeof(char));
           strcpy(str, (yyvsp[0].str));
           (yyval._val) = createValue(STRING_TYPE, str); free((yyvsp[0].str));}
#line 1405 "sent.c"
    break;

  case 30: /* val: NUM  */
#line 170 "sent.y"
         { int* a = malloc(sizeof(int));
           *a = (yyvsp[0].integer);
           (yyval._val) = createValue(INTEGER_TYPE, a);}
#line 1413 "sent.c"
    break;

  case 31: /* val: FLOAT  */
#line 173 "sent.y"
           { float* a = malloc(sizeof(float));
           *a = (yyvsp[0].fl);
           (yyval._val) = createValue(FLOAT_TYPE, a);}
#line 1421 "sent.c"
    break;

  case 32: /* val: WORD  */
#line 176 "sent.y"
         { char* str = calloc(64, sizeof(char));
           strcpy(str, (yyvsp[0].str));
           (yyval._val) = createValue(OBJECT_TYPE, str); free((yyvsp[0].str));}
#line 1429 "sent.c"
    break;

  case 33: /* val: TRUE  */
#line 179 "sent.y"
         { int* a = malloc(sizeof(int));
           *a = (yyvsp[0].integer);
           (yyval._val) = createValue(BOOLEAN_TYPE, a);}
#line 1437 "sent.c"
    break;

  case 34: /* val: FALSE  */
#line 182 "sent.y"
          { int* a = malloc(sizeof(int));
           *a = (yyvsp[0].integer);
           (yyval._val) = createValue(BOOLEAN_TYPE, a);}
#line 1445 "sent.c"
    break;

  case 35: /* val: functionCall  */
#line 185 "sent.y"
               {(yyval._val) = createValue(FUNC_TYPE, (yyvsp[0].com));}
#line 1451 "sent.c"
    break;

  case 36: /* function: FN WORD '(' parametrs ')' returnArrow '{' functionImplementation '}'  */
#line 189 "sent.y"
                                                                       { isFunc = true;struct func_impl_type* res = createFuncImpl((yyvsp[-7].str), (yyvsp[-5].membVec), (yyvsp[-1].ast_type), 
                                                                             NULL); res->wantedReturnType = getValueType((yyvsp[-3].str)); free((yyvsp[-3].str));
                                                                          (yyval.com) = createCommand(num++, FUNC_IMPL_TYPE, (void*)res);}
#line 1459 "sent.c"
    break;

  case 37: /* returnArrow: ARROW type  */
#line 195 "sent.y"
             {(yyval.str) = (yyvsp[0].str);}
#line 1465 "sent.c"
    break;

  case 38: /* returnArrow: %empty  */
#line 196 "sent.y"
             {(yyval.str) = NULL;}
#line 1471 "sent.c"
    break;

  case 39: /* functionImplementation: funcImpl  */
#line 200 "sent.y"
                                  { (yyval.ast_type) = (yyvsp[0].ast_type);}
#line 1477 "sent.c"
    break;

  case 40: /* functionImplementation: funcImpl functionImplementation  */
#line 201 "sent.y"
                                  { (yyval.ast_type) = mergeAst((yyvsp[-1].ast_type), (yyvsp[0].ast_type));}
#line 1483 "sent.c"
    break;

  case 41: /* returnVal: expr  */
#line 205 "sent.y"
       {(yyval._val) = (yyvsp[0]._val);}
#line 1489 "sent.c"
    break;

  case 42: /* returnVal: %empty  */
#line 206 "sent.y"
         {(yyval._val) = createValue(NULL_TYPE, NULL);}
#line 1495 "sent.c"
    break;

  case 43: /* funcImpl: functionCall ';'  */
#line 210 "sent.y"
                   {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->functionCalls, (yyvsp[-1].com));}
#line 1501 "sent.c"
    break;

  case 44: /* funcImpl: initialization  */
#line 211 "sent.y"
                 {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->initializations, (yyvsp[0].com));}
#line 1507 "sent.c"
    break;

  case 45: /* funcImpl: declaration  */
#line 212 "sent.y"
              {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->declarations, (yyvsp[0].com));}
#line 1513 "sent.c"
    break;

  case 46: /* funcImpl: if_expression  */
#line 213 "sent.y"
                {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->if_expressions, (yyvsp[0].com));}
#line 1519 "sent.c"
    break;

  case 47: /* funcImpl: while_expression  */
#line 214 "sent.y"
                   {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->cycles, (yyvsp[0].com));}
#line 1525 "sent.c"
    break;

  case 48: /* funcImpl: for_expression  */
#line 215 "sent.y"
                 {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->cycles, (yyvsp[0].com));}
#line 1531 "sent.c"
    break;

  case 49: /* funcImpl: RETURN returnVal ';'  */
#line 216 "sent.y"
                       {(yyval.ast_type) = createAst(); char* str = calloc(4, sizeof(char)); sprintf(str, "%d", num);
                        push_back_com((yyval.ast_type)->declarations, createCommand(num++, RETURN_TYPE, createMember((yyvsp[-1]._val), str)));}
#line 1538 "sent.c"
    break;

  case 50: /* brackets_functionImplementation: '{' functionImplementation '}'  */
#line 221 "sent.y"
                                 {(yyval.ast_type) = (yyvsp[-1].ast_type);}
#line 1544 "sent.c"
    break;

  case 51: /* if_expression: IF expression brackets_functionImplementation else_expression  */
#line 225 "sent.y"
                                                                {
                                                                  struct if_expr_type* res = createIfExpr((yyvsp[-2].if_cond), (yyvsp[-1].ast_type), (yyvsp[0].if_expr));
                                                                  (yyval.com) = createCommand(num++, IF_COM_TYPE, (void*)res);
                                                                  }
#line 1553 "sent.c"
    break;

  case 52: /* else_expression: ELSE brackets_functionImplementation  */
#line 232 "sent.y"
                                       {(yyval.if_expr) = createIfExpr(NULL, (yyvsp[0].ast_type), NULL);}
#line 1559 "sent.c"
    break;

  case 53: /* else_expression: %empty  */
#line 233 "sent.y"
         {(yyval.if_expr) = NULL;}
#line 1565 "sent.c"
    break;

  case 54: /* expression: val cmp val  */
#line 237 "sent.y"
              {(yyval.if_cond) = createIfCond((yyvsp[-1].str), (yyvsp[-2]._val), (yyvsp[0]._val));}
#line 1571 "sent.c"
    break;

  case 55: /* cmp: EQUALS  */
#line 241 "sent.y"
         {(yyval.str) = (yyvsp[0].str);}
#line 1577 "sent.c"
    break;

  case 56: /* cmp: NOT_EQUALS  */
#line 242 "sent.y"
             {(yyval.str) = (yyvsp[0].str);}
#line 1583 "sent.c"
    break;

  case 57: /* cmp: LESS  */
#line 243 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1589 "sent.c"
    break;

  case 58: /* cmp: MORE  */
#line 244 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1595 "sent.c"
    break;

  case 59: /* cmp: EQ_LESS  */
#line 245 "sent.y"
          {(yyval.str) = (yyvsp[0].str);}
#line 1601 "sent.c"
    break;

  case 60: /* cmp: EQ_MORE  */
#line 246 "sent.y"
          {(yyval.str) = (yyvsp[0].str);}
#line 1607 "sent.c"
    break;

  case 61: /* while_expression: WHILE expression brackets_functionImplementation  */
#line 250 "sent.y"
                                                   {  struct cycle_type* res = createCycle((yyvsp[-1].if_cond), (yyvsp[0].ast_type), NULL);
                                                      (yyval.com) = createCommand(num++, CYCLE_COM_TYPE, (void*)res);num++;}
#line 1614 "sent.c"
    break;

  case 62: /* for_expression: FOR WORD IN NUM TWO_POINTS NUM brackets_functionImplementation  */
#line 255 "sent.y"
                                                                 {int* a = calloc(16, sizeof(int));*a = (yyvsp[-3].integer);
                                                                  int* b = calloc(16, sizeof(int));*b = (yyvsp[-1].integer);
                                                                  struct cycle_type* res = createCycle(createIfCond(strdup("<="),
                                                                  createValue(OBJECT_TYPE,(yyvsp[-5].str)),createValue(INTEGER_TYPE,b)), (yyvsp[0].ast_type),
                                                                  createMember(createValue(INTEGER_TYPE, a), (yyvsp[-5].str)));
                                                                  char* str = calloc(16, sizeof(char));
                                                                  strcat(str, (yyvsp[-5].str)); strcat(str, "+1");
                                                                  push_back_com(res->body->initializations, createCommand(num++, INIT_COM_TYPE, (struct command_type*)createMember(createValue(OBJECT_TYPE, str), (yyvsp[-5].str))));
                                                                  (yyval.com) = createCommand(num++, CYCLE_COM_TYPE, (void*)res);}
#line 1628 "sent.c"
    break;

  case 63: /* expr: second '+' expr  */
#line 267 "sent.y"
                  {(yyval._val) = getOp((yyvsp[-2]._val), (yyvsp[0]._val), '+'); if ((yyval._val) == NULL) {YYABORT;}}
#line 1634 "sent.c"
    break;

  case 64: /* expr: second '-' expr  */
#line 268 "sent.y"
                  {(yyval._val) = getOp((yyvsp[-2]._val), (yyvsp[0]._val), '-'); if ((yyval._val) == NULL) {YYABORT;}}
#line 1640 "sent.c"
    break;

  case 65: /* expr: second  */
#line 269 "sent.y"
                  {(yyval._val) = (yyvsp[0]._val);}
#line 1646 "sent.c"
    break;

  case 66: /* second: val '*' second  */
#line 273 "sent.y"
                 {(yyval._val) = getOp((yyvsp[-2]._val), (yyvsp[0]._val), '*'); if ((yyval._val) == NULL) {YYABORT;}}
#line 1652 "sent.c"
    break;

  case 67: /* second: val '/' second  */
#line 274 "sent.y"
                 {(yyval._val) = getOp((yyvsp[-2]._val), (yyvsp[0]._val), '/'); if ((yyval._val) == NULL) {YYABORT;}}
#line 1658 "sent.c"
    break;

  case 68: /* second: val  */
#line 275 "sent.y"
                 {(yyval._val) = (yyvsp[0]._val);}
#line 1664 "sent.c"
    break;


#line 1668 "sent.c"

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

#line 278 "sent.y"


void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
  printf("%d\n", num);
}
