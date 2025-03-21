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
  enum VALUE_TYPE getValueType(char* val) {
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
  int getIntRes(int l, int r, const char* op) {
    if (!strcmp(op, "+")) {
      return l + r;
    }
    if (!strcmp(op, "-")) {
      return l - r;
    }
    if (!strcmp(op, "*")) {
      return l * r;
    }
    if (!strcmp(op, "/")) {
      return l / r;
    }
  }
  float getFloatRes(float l, float r, const char* op) {
    if (!strcmp(op, "+")) {
      return l + r;
    }
    if (!strcmp(op, "-")) {
      return l - r;
    }
    if (!strcmp(op, "*")) {
      return l * r;
    }
    if (!strcmp(op, "/")) {
      return l / r;
    }
  }
  struct value_type* getOp(struct value_type* left, struct value_type* right, const char* op) {
    struct value_type* val = calloc(1, sizeof(struct value_type));
    if (left->type == INTEGER_TYPE && right->type == INTEGER_TYPE) {
      val->type = INTEGER_TYPE;
      int* a = malloc(sizeof(int));
      *a = getIntRes(*(int*)left->data, *(int*)right->data, op);
      val->data = a;
      if (left->data != NULL) {
        free(left->data);
      }
      free(left);
      if (right->data != NULL) {
        free(right->data);
      }
      free(right);
      return val;
    }
    if (left->type == FLOAT_TYPE && right->type == FLOAT_TYPE) {
      val->type = FLOAT_TYPE;
      float* a = malloc(sizeof(float));
      *a = getFloatRes(*(float*)left->data, *(float*)right->data, op);
      val->data = a;
      if (left->data != NULL) {
        free(left->data);
      }
      free(left);
      if (right->data != NULL) {
        free(right->data);
      }
      free(right);
      return val;
    }
    if (strcmp(op, "+")) {
      free(val);
      return NULL;
    }
    if (left->type == BOOLEAN_TYPE || right->type == BOOLEAN_TYPE || left->type == NULL_TYPE || right->type == NULL_TYPE) {
      free(val); return NULL;
    }
    if (left->type == OBJECT_TYPE || right->type == OBJECT_TYPE) {
      char* l1;
      char* l2;
      if (left->type == INTEGER_TYPE) {
        l1 = calloc(32,sizeof(char));
        sprintf(l1, "%d", *(int*)left->data);
        free(left->data);
        left->data = NULL;
      }
      else {
        l1 = (char*)left->data;
      }
      if (right->type == INTEGER_TYPE) {
        l2 = calloc(32,sizeof(char));
        sprintf(l2, "%d", *(int*)right->data);
        free(right->data);
        right->data = NULL;
      }
      else {
        l2 = (char*)right->data;
      }
      val->type = OBJECT_TYPE;
      strcat(l1, "+"); strcat(l1, l2);
      val->data = l1;
      free(l2);
      return val;
    }
    if (left->type == STRING_TYPE && left->type == STRING_TYPE && op == "+") {
        strcat((char*) left->data, (char*)right->data);
        val->type = STRING_TYPE;
        val->data = strdup((char*)left->data);
        free(right->data);
        free(right);
        free(left->data);
        free(left);
        return val;
    }
    if (left->data != NULL) {
      free(left->data);
    }
    free(left);
    if (right->data != NULL) {
      free(right->data);
    }
    free(right);
    free(val);
    return NULL;
  }

#line 215 "sent.c"

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
  YYSYMBOL_WORD = 4,                       /* WORD  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_LET = 6,                        /* LET  */
  YYSYMBOL_U32 = 7,                        /* U32  */
  YYSYMBOL_U64 = 8,                        /* U64  */
  YYSYMBOL_F32 = 9,                        /* F32  */
  YYSYMBOL_STR = 10,                       /* STR  */
  YYSYMBOL_BOOL = 11,                      /* BOOL  */
  YYSYMBOL_TRUE = 12,                      /* TRUE  */
  YYSYMBOL_FALSE = 13,                     /* FALSE  */
  YYSYMBOL_FN = 14,                        /* FN  */
  YYSYMBOL_INT = 15,                       /* INT  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_EQUALS = 20,                    /* EQUALS  */
  YYSYMBOL_NOT_EQUALS = 21,                /* NOT_EQUALS  */
  YYSYMBOL_QUOTE = 22,                     /* QUOTE  */
  YYSYMBOL_IN = 23,                        /* IN  */
  YYSYMBOL_TWO_POINTS = 24,                /* TWO_POINTS  */
  YYSYMBOL_RETURN = 25,                    /* RETURN  */
  YYSYMBOL_LESS = 26,                      /* LESS  */
  YYSYMBOL_MORE = 27,                      /* MORE  */
  YYSYMBOL_EQ_LESS = 28,                   /* EQ_LESS  */
  YYSYMBOL_EQ_MORE = 29,                   /* EQ_MORE  */
  YYSYMBOL_30_ = 30,                       /* ':'  */
  YYSYMBOL_31_ = 31,                       /* ';'  */
  YYSYMBOL_32_ = 32,                       /* '='  */
  YYSYMBOL_33_ = 33,                       /* '('  */
  YYSYMBOL_34_ = 34,                       /* ')'  */
  YYSYMBOL_35_ = 35,                       /* ','  */
  YYSYMBOL_36_ = 36,                       /* '{'  */
  YYSYMBOL_37_ = 37,                       /* '}'  */
  YYSYMBOL_38_ = 38,                       /* '+'  */
  YYSYMBOL_39_ = 39,                       /* '-'  */
  YYSYMBOL_40_ = 40,                       /* '*'  */
  YYSYMBOL_41_ = 41,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_input = 43,                     /* input  */
  YYSYMBOL_command = 44,                   /* command  */
  YYSYMBOL_declaration = 45,               /* declaration  */
  YYSYMBOL_init = 46,                      /* init  */
  YYSYMBOL_initialization = 47,            /* initialization  */
  YYSYMBOL_assignment = 48,                /* assignment  */
  YYSYMBOL_type = 49,                      /* type  */
  YYSYMBOL_functionCall = 50,              /* functionCall  */
  YYSYMBOL_value = 51,                     /* value  */
  YYSYMBOL_parametrs = 52,                 /* parametrs  */
  YYSYMBOL_par = 53,                       /* par  */
  YYSYMBOL_val = 54,                       /* val  */
  YYSYMBOL_function = 55,                  /* function  */
  YYSYMBOL_functionImplementation = 56,    /* functionImplementation  */
  YYSYMBOL_ret = 57,                       /* ret  */
  YYSYMBOL_returnVal = 58,                 /* returnVal  */
  YYSYMBOL_funcImpl = 59,                  /* funcImpl  */
  YYSYMBOL_brackets_functionImplementation = 60, /* brackets_functionImplementation  */
  YYSYMBOL_if_expression = 61,             /* if_expression  */
  YYSYMBOL_else_expression = 62,           /* else_expression  */
  YYSYMBOL_expression = 63,                /* expression  */
  YYSYMBOL_cmp = 64,                       /* cmp  */
  YYSYMBOL_while_expression = 65,          /* while_expression  */
  YYSYMBOL_for_expression = 66,            /* for_expression  */
  YYSYMBOL_expr = 67,                      /* expr  */
  YYSYMBOL_second = 68                     /* second  */
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
#define YYLAST   82

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  103

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


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
      33,    34,    40,    38,    35,    39,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    30,    31,
       2,    32,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   201,   201,   202,   206,   207,   208,   209,   210,   211,
     212,   216,   227,   228,   231,   236,   240,   241,   242,   243,
     244,   248,   253,   254,   256,   264,   266,   274,   275,   279,
     282,   285,   288,   291,   297,   302,   303,   307,   308,   312,
     313,   317,   318,   319,   320,   321,   325,   329,   336,   337,
     341,   345,   346,   347,   348,   349,   350,   354,   359,   369,
     370,   371,   375,   376,   377
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
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "WORD",
  "STRING", "LET", "U32", "U64", "F32", "STR", "BOOL", "TRUE", "FALSE",
  "FN", "INT", "IF", "ELSE", "FOR", "WHILE", "EQUALS", "NOT_EQUALS",
  "QUOTE", "IN", "TWO_POINTS", "RETURN", "LESS", "MORE", "EQ_LESS",
  "EQ_MORE", "':'", "';'", "'='", "'('", "')'", "','", "'{'", "'}'", "'+'",
  "'-'", "'*'", "'/'", "$accept", "input", "command", "declaration",
  "init", "initialization", "assignment", "type", "functionCall", "value",
  "parametrs", "par", "val", "function", "functionImplementation", "ret",
  "returnVal", "funcImpl", "brackets_functionImplementation",
  "if_expression", "else_expression", "expression", "cmp",
  "while_expression", "for_expression", "expr", "second", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -69,    11,   -69,   -23,     3,     8,    29,    10,    29,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,    29,    29,    -3,
     -14,    -7,   -69,   -69,   -69,   -69,   -69,    18,     1,    25,
       1,   -21,   -69,   -16,    22,    -4,   -69,    44,    44,   -69,
     -69,   -69,   -69,   -69,   -69,    29,     2,    40,    55,   -69,
      29,    29,    29,    29,    28,    29,   -69,   -69,   -69,   -69,
     -69,    30,    56,    27,    31,   -69,   -69,   -69,   -69,    26,
       2,   -69,   -69,     1,   -69,    41,   -69,   -69,   -69,   -69,
     -69,   -69,    36,   -69,   -69,    32,    44,   -69,   -69,   -69,
      66,   -69,     2,   -69,     1,    45,   -69,    29,    34,    42,
     -69,   -69,   -69
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     3,
       4,     5,     6,     7,     8,     9,    10,     0,    22,     0,
       0,     0,    30,    31,    29,    32,    33,     0,     0,     0,
       0,    64,    15,    61,     0,    23,    14,     0,    28,    51,
      52,    53,    54,    55,    56,     0,     0,    49,     0,    57,
       0,     0,     0,     0,     0,    22,    16,    17,    18,    19,
      20,    13,     0,     0,    25,    50,    43,    42,    41,     0,
      35,    44,    45,     0,    47,     0,    62,    63,    59,    60,
      21,    24,     0,    12,    27,     0,    28,    46,    36,    48,
       0,    11,     0,    26,     0,    38,    58,    40,     0,     0,
      39,    34,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   -69,    71,   -69,    73,    14,    39,    76,    23,
      -6,   -69,    -5,   -69,   -68,   -69,   -69,   -69,   -30,    78,
     -69,    74,   -69,    80,   -69,   -48,   -15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     9,    66,    82,    67,    19,    62,    68,    34,
      63,    64,    31,    13,    69,    98,    99,    70,    47,    71,
      74,    28,    45,    72,    16,    32,    33
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      49,    27,    88,    27,    78,    79,     3,    20,     4,    17,
      18,     2,    21,    35,    29,     3,    37,     4,     6,    50,
      51,     8,    52,    53,    95,     5,    38,     6,    36,     7,
       8,    55,    22,    23,    24,    76,    77,    46,    39,    40,
      65,    25,    26,    89,    41,    42,    43,    44,    48,   100,
      35,    56,    57,    58,    59,    60,    54,    73,    75,    80,
      84,    85,    17,    87,    96,    90,    86,    91,    92,    94,
      97,   101,    10,   102,    11,    83,    61,    12,    81,    14,
      93,    15,    30
};

static const yytype_int8 yycheck[] =
{
      30,     6,    70,     8,    52,    53,     4,     4,     6,    32,
      33,     0,     4,    18,     4,     4,    30,     6,    16,    40,
      41,    19,    38,    39,    92,    14,    33,    16,    31,    18,
      19,    35,     3,     4,     5,    50,    51,    36,    20,    21,
      45,    12,    13,    73,    26,    27,    28,    29,    23,    97,
      55,     7,     8,     9,    10,    11,    34,    17,     3,    31,
       4,    34,    32,    37,    94,    24,    35,    31,    36,     3,
      25,    37,     1,    31,     1,    61,    37,     1,    55,     1,
      86,     1,     8
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,     0,     4,     6,    14,    16,    18,    19,    44,
      45,    47,    50,    55,    61,    65,    66,    32,    33,    48,
       4,     4,     3,     4,     5,    12,    13,    54,    63,     4,
      63,    54,    67,    68,    51,    54,    31,    30,    33,    20,
      21,    26,    27,    28,    29,    64,    36,    60,    23,    60,
      40,    41,    38,    39,    34,    35,     7,     8,     9,    10,
      11,    49,    49,    52,    53,    54,    45,    47,    50,    56,
      59,    61,    65,    17,    62,     3,    68,    68,    67,    67,
      31,    51,    46,    48,     4,    34,    35,    37,    56,    60,
      24,    31,    36,    52,     3,    56,    60,    25,    57,    58,
      67,    37,    31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    44,    44,    44,    44,
      44,    45,    46,    46,    47,    48,    49,    49,    49,    49,
      49,    50,    51,    51,    51,    52,    52,    53,    53,    54,
      54,    54,    54,    54,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    59,    59,    59,    60,    61,    62,    62,
      63,    64,    64,    64,    64,    64,    64,    65,    66,    67,
      67,    67,    68,    68,    68
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     6,     1,     0,     3,     2,     1,     1,     1,     1,
       1,     5,     0,     1,     3,     1,     3,     2,     0,     1,
       1,     1,     1,     1,     9,     1,     2,     3,     0,     1,
       0,     1,     1,     1,     1,     1,     3,     4,     2,     0,
       3,     1,     1,     1,     1,     1,     1,     3,     7,     3,
       3,     1,     3,     3,     1
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
#line 202 "sent.y"
                {num++;}
#line 1336 "sent.c"
    break;

  case 4: /* command: declaration  */
#line 206 "sent.y"
              {push_back_com(ast->declarations, (yyvsp[0].com));}
#line 1342 "sent.c"
    break;

  case 5: /* command: initialization  */
#line 207 "sent.y"
                 {push_back_com(ast->initializations, (yyvsp[0].com));}
#line 1348 "sent.c"
    break;

  case 6: /* command: functionCall  */
#line 208 "sent.y"
               {push_back_com(ast->functionCalls, (yyvsp[0].com));}
#line 1354 "sent.c"
    break;

  case 7: /* command: function  */
#line 209 "sent.y"
           {push_back_com(ast->functions, (yyvsp[0].com));}
#line 1360 "sent.c"
    break;

  case 8: /* command: if_expression  */
#line 210 "sent.y"
                {push_back_com(ast->if_expressions, (yyvsp[0].com));}
#line 1366 "sent.c"
    break;

  case 9: /* command: while_expression  */
#line 211 "sent.y"
                   {push_back_com(ast->cycles, (yyvsp[0].com));}
#line 1372 "sent.c"
    break;

  case 10: /* command: for_expression  */
#line 212 "sent.y"
                 {push_back_com(ast->cycles, (yyvsp[0].com));}
#line 1378 "sent.c"
    break;

  case 11: /* declaration: LET WORD ':' type init ';'  */
#line 216 "sent.y"
                             { if ((yyvsp[-1]._val)->type != OBJECT_TYPE) {
                                 if ((yyvsp[-1]._val)->type != getValueType((yyvsp[-2].str))) {
                                  printf("Incorrect type for %s\n", (yyvsp[-4].str));
                                  YYABORT;
                                 }                           
                               }
                               struct member_type* mem = createMember(createValue(getValueType((yyvsp[-2].str)), (yyvsp[-1]._val)->data), (yyvsp[-4].str));
                               (yyval.com) = createCommand(num, mem); free((yyvsp[-2].str));}
#line 1391 "sent.c"
    break;

  case 12: /* init: assignment  */
#line 227 "sent.y"
             {(yyval._val) = (yyvsp[0]._val);}
#line 1397 "sent.c"
    break;

  case 13: /* init: %empty  */
#line 228 "sent.y"
         {(yyval._val) = createValue(NULL_TYPE, NULL);}
#line 1403 "sent.c"
    break;

  case 14: /* initialization: WORD assignment ';'  */
#line 231 "sent.y"
                      { struct member_type* mem = createMember((yyvsp[-1]._val), (yyvsp[-2].str));
                        (yyval.com) = createCommand(num, mem);}
#line 1410 "sent.c"
    break;

  case 15: /* assignment: '=' expr  */
#line 236 "sent.y"
           {(yyval._val) = (yyvsp[0]._val);}
#line 1416 "sent.c"
    break;

  case 16: /* type: U32  */
#line 240 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1422 "sent.c"
    break;

  case 17: /* type: U64  */
#line 241 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1428 "sent.c"
    break;

  case 18: /* type: F32  */
#line 242 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1434 "sent.c"
    break;

  case 19: /* type: STR  */
#line 243 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1440 "sent.c"
    break;

  case 20: /* type: BOOL  */
#line 244 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1446 "sent.c"
    break;

  case 21: /* functionCall: WORD '(' value ')' ';'  */
#line 248 "sent.y"
                         { struct func_call_type* f = createFuncCall((yyvsp[-4].str), (yyvsp[-2].valVec));
                           (yyval.com) = createCommand(num, f);}
#line 1453 "sent.c"
    break;

  case 22: /* value: %empty  */
#line 253 "sent.y"
                {(yyval.valVec) = createValueVec();}
#line 1459 "sent.c"
    break;

  case 23: /* value: val  */
#line 254 "sent.y"
                {(yyval.valVec) = createValueVec();
                 push_back_val((yyval.valVec), (yyvsp[0]._val));}
#line 1466 "sent.c"
    break;

  case 24: /* value: val ',' value  */
#line 256 "sent.y"
                {(yyval.valVec) = createValueVec();
                 push_back_val((yyval.valVec), (yyvsp[-2]._val));
                 for(int i = 0; i < (yyvsp[0].valVec)->size; ++i) {
                  push_back_val((yyval.valVec), (yyvsp[0].valVec)->values[i]);
                 }}
#line 1476 "sent.c"
    break;

  case 25: /* parametrs: par  */
#line 264 "sent.y"
                    {(yyval.membVec) = createMemberVec();
                     push_back_mem((yyval.membVec), (yyvsp[0].memb));}
#line 1483 "sent.c"
    break;

  case 26: /* parametrs: par ',' parametrs  */
#line 266 "sent.y"
                    {(yyval.membVec) = createMemberVec();
                     push_back_mem((yyval.membVec), (yyvsp[-2].memb));
                     for(int i = 0; i < (yyvsp[0].membVec)->size; ++i) {
                      push_back_mem((yyval.membVec), (yyvsp[0].membVec)->members[i]);
                     }}
#line 1493 "sent.c"
    break;

  case 27: /* par: type WORD  */
#line 274 "sent.y"
            {(yyval.memb) = createMember(createValue(getValueType((yyvsp[-1].str)), NULL), (yyvsp[0].str));}
#line 1499 "sent.c"
    break;

  case 28: /* par: %empty  */
#line 275 "sent.y"
           {(yyval.memb) = createMember(createValue(NULL_TYPE, NULL), NULL);}
#line 1505 "sent.c"
    break;

  case 29: /* val: STRING  */
#line 279 "sent.y"
         { char* str = calloc(64, sizeof(char));
           strcpy(str, (yyvsp[0].str));
           (yyval._val) = createValue(STRING_TYPE, str); free((yyvsp[0].str));}
#line 1513 "sent.c"
    break;

  case 30: /* val: NUM  */
#line 282 "sent.y"
         { int* a = malloc(sizeof(int));
           *a = (yyvsp[0].integer);
           (yyval._val) = createValue(INTEGER_TYPE, a);}
#line 1521 "sent.c"
    break;

  case 31: /* val: WORD  */
#line 285 "sent.y"
         { char* str = calloc(64, sizeof(char));
           strcpy(str, (yyvsp[0].str));
           (yyval._val) = createValue(OBJECT_TYPE, str); free((yyvsp[0].str));}
#line 1529 "sent.c"
    break;

  case 32: /* val: TRUE  */
#line 288 "sent.y"
         { int* a = malloc(sizeof(int));
           *a = (yyvsp[0].integer);
           (yyval._val) = createValue(BOOLEAN_TYPE, a);}
#line 1537 "sent.c"
    break;

  case 33: /* val: FALSE  */
#line 291 "sent.y"
          { int* a = malloc(sizeof(int));
           *a = (yyvsp[0].integer);
           (yyval._val) = createValue(BOOLEAN_TYPE, a);}
#line 1545 "sent.c"
    break;

  case 34: /* function: FN WORD '(' parametrs ')' '{' functionImplementation ret '}'  */
#line 297 "sent.y"
                                                               { struct func_impl_type* res = createFuncImpl((yyvsp[-7].str), (yyvsp[-5].membVec), (yyvsp[-2].ast_type), (yyvsp[-1]._val));
                                                                          (yyval.com) = createCommand(num, (void*)res);}
#line 1552 "sent.c"
    break;

  case 35: /* functionImplementation: funcImpl  */
#line 302 "sent.y"
                                  { (yyval.ast_type) = (yyvsp[0].ast_type);}
#line 1558 "sent.c"
    break;

  case 36: /* functionImplementation: funcImpl functionImplementation  */
#line 303 "sent.y"
                                  { (yyval.ast_type) = fullMergeAst((yyvsp[-1].ast_type), (yyvsp[0].ast_type));}
#line 1564 "sent.c"
    break;

  case 37: /* ret: RETURN returnVal ';'  */
#line 307 "sent.y"
                       {(yyval._val) = (yyvsp[-1]._val);}
#line 1570 "sent.c"
    break;

  case 38: /* ret: %empty  */
#line 308 "sent.y"
         {(yyval._val) = createValue(NULL_TYPE, NULL);}
#line 1576 "sent.c"
    break;

  case 39: /* returnVal: expr  */
#line 312 "sent.y"
       {(yyval._val) = (yyvsp[0]._val);}
#line 1582 "sent.c"
    break;

  case 40: /* returnVal: %empty  */
#line 313 "sent.y"
         {(yyval._val) = createValue(NULL_TYPE, NULL);}
#line 1588 "sent.c"
    break;

  case 41: /* funcImpl: functionCall  */
#line 317 "sent.y"
               {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->functionCalls, (yyvsp[0].com));}
#line 1594 "sent.c"
    break;

  case 42: /* funcImpl: initialization  */
#line 318 "sent.y"
                 {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->initializations, (yyvsp[0].com));}
#line 1600 "sent.c"
    break;

  case 43: /* funcImpl: declaration  */
#line 319 "sent.y"
              {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->declarations, (yyvsp[0].com));}
#line 1606 "sent.c"
    break;

  case 44: /* funcImpl: if_expression  */
#line 320 "sent.y"
                {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->if_expressions, (yyvsp[0].com));}
#line 1612 "sent.c"
    break;

  case 45: /* funcImpl: while_expression  */
#line 321 "sent.y"
                   {(yyval.ast_type) = createAst(); push_back_com((yyval.ast_type)->cycles, (yyvsp[0].com));}
#line 1618 "sent.c"
    break;

  case 46: /* brackets_functionImplementation: '{' functionImplementation '}'  */
#line 325 "sent.y"
                                 {(yyval.ast_type) = (yyvsp[-1].ast_type);}
#line 1624 "sent.c"
    break;

  case 47: /* if_expression: IF expression brackets_functionImplementation else_expression  */
#line 329 "sent.y"
                                                                {
                                                                  struct if_expr_type* res = createIfExpr((yyvsp[-2].if_cond), (yyvsp[-1].ast_type), (yyvsp[0].if_expr));
                                                                  (yyval.com) = createCommand(num, (void*)res);
                                                                  }
#line 1633 "sent.c"
    break;

  case 48: /* else_expression: ELSE brackets_functionImplementation  */
#line 336 "sent.y"
                                       {(yyval.if_expr) = createIfExpr(NULL, (yyvsp[0].ast_type), NULL);}
#line 1639 "sent.c"
    break;

  case 49: /* else_expression: %empty  */
#line 337 "sent.y"
         {(yyval.if_expr) = NULL;}
#line 1645 "sent.c"
    break;

  case 50: /* expression: val cmp val  */
#line 341 "sent.y"
              {(yyval.if_cond) = createIfCond((yyvsp[-1].str), (yyvsp[-2]._val), (yyvsp[0]._val));}
#line 1651 "sent.c"
    break;

  case 51: /* cmp: EQUALS  */
#line 345 "sent.y"
         {(yyval.str) = (yyvsp[0].str);}
#line 1657 "sent.c"
    break;

  case 52: /* cmp: NOT_EQUALS  */
#line 346 "sent.y"
             {(yyval.str) = (yyvsp[0].str);}
#line 1663 "sent.c"
    break;

  case 53: /* cmp: LESS  */
#line 347 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1669 "sent.c"
    break;

  case 54: /* cmp: MORE  */
#line 348 "sent.y"
       {(yyval.str) = (yyvsp[0].str);}
#line 1675 "sent.c"
    break;

  case 55: /* cmp: EQ_LESS  */
#line 349 "sent.y"
          {(yyval.str) = (yyvsp[0].str);}
#line 1681 "sent.c"
    break;

  case 56: /* cmp: EQ_MORE  */
#line 350 "sent.y"
          {(yyval.str) = (yyvsp[0].str);}
#line 1687 "sent.c"
    break;

  case 57: /* while_expression: WHILE expression brackets_functionImplementation  */
#line 354 "sent.y"
                                                   {  struct cycle_type* res = createCycle((yyvsp[-1].if_cond), (yyvsp[0].ast_type));
                                                      (yyval.com) = createCommand(num, (void*)res);}
#line 1694 "sent.c"
    break;

  case 58: /* for_expression: FOR WORD IN NUM TWO_POINTS NUM brackets_functionImplementation  */
#line 359 "sent.y"
                                                                 {int* a = calloc(16, sizeof(int));*a = (yyvsp[-3].integer);
                                                                  int* b = calloc(16, sizeof(int));*b = (yyvsp[-1].integer);
                                                                  push_back_com(ast->declarations, 
                                                                  createCommand(num, (struct command_type*)createMember(createValue(INTEGER_TYPE,a),(yyvsp[-5].str))));
                                                                  struct cycle_type* res = createCycle(createIfCond(strdup("<="),
                                                                  createValue(OBJECT_TYPE,(yyvsp[-5].str)),createValue(INTEGER_TYPE,b)), (yyvsp[0].ast_type));num++;
                                                                  (yyval.com) = createCommand(num, (void*)res);}
#line 1706 "sent.c"
    break;

  case 59: /* expr: second '+' expr  */
#line 369 "sent.y"
                  {(yyval._val) = getOp((yyvsp[-2]._val), (yyvsp[0]._val), "+"); if ((yyval._val) == NULL) {YYABORT;}}
#line 1712 "sent.c"
    break;

  case 60: /* expr: second '-' expr  */
#line 370 "sent.y"
                  {(yyval._val) = getOp((yyvsp[-2]._val), (yyvsp[0]._val), "-"); if ((yyval._val) == NULL) {YYABORT;}}
#line 1718 "sent.c"
    break;

  case 61: /* expr: second  */
#line 371 "sent.y"
                  {(yyval._val) = (yyvsp[0]._val);}
#line 1724 "sent.c"
    break;

  case 62: /* second: val '*' second  */
#line 375 "sent.y"
                 {(yyval._val) = getOp((yyvsp[-2]._val), (yyvsp[0]._val), "*"); if ((yyval._val) == NULL) {YYABORT;}}
#line 1730 "sent.c"
    break;

  case 63: /* second: val '/' second  */
#line 376 "sent.y"
                 {(yyval._val) = getOp((yyvsp[-2]._val), (yyvsp[0]._val), "/"); if ((yyval._val) == NULL) {YYABORT;}}
#line 1736 "sent.c"
    break;

  case 64: /* second: val  */
#line 377 "sent.y"
                 {(yyval._val) = (yyvsp[0]._val);}
#line 1742 "sent.c"
    break;


#line 1746 "sent.c"

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

#line 380 "sent.y"


void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}
