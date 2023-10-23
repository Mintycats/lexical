/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "syntax.y"


    #include<stdio.h>
    #include<string.h>
    #include<stdarg.h>
    #include<ctype.h>
    #include "lex.yy.c"

    /* declared funcion */
    int yylex(void);
    void yyerror(char*);
    int PrintError(char , int , char*);
    int isNewError(int);
    void ErrorPrinter(char, char*);//used in yyerror

    /* declared tree node */
    enum Nodetype {
        Expression,//a sentance
        Noval,//don't have val
        Val//have val
    };
    enum ValType {
        StringType,
        IntType,
        FloatType,
        NoneType
    };
    struct Node {
        enum Nodetype type;//type of node
        enum ValType valtype;//type of val
        char name[32];
        int lineno;//use for print
        union {//union of value
            int intval;
            float floatval;
            char strval[32];
        };
        struct Node* leftchild;
        struct Node* rightbrother;
    };

    /* declared tree funcion */
    struct Node* MakeNode(char* nodename, enum Nodetype type, int lineno);
    void PrintTree(struct Node* rootnode, int spaceNum);
    void MakeTree(struct Node* father, struct Node* child);
    void TearsDown(struct Node* rootnode);
    
    /* declared global value */
    int hasError = 0;
    int lastErrorLine = 0;
    struct Node* Root = NULL;

    struct Node* debugger = NULL;
    struct Node* debugger2 = NULL;

    /* defined operation*/
    #define MAKE_NODE_EXP(nodeName, nodeLink, nodeLocation) \
            nodeLink = MakeNode(nodeName, Expression, nodeLocation.first_line); \
            nodeLink->valtype = NoneType;

#line 131 "syntax.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
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
    INT = 258,
    FLOAT = 259,
    ID = 260,
    TYPE = 261,
    PLUS = 262,
    MINUS = 263,
    STAR = 264,
    DIV = 265,
    SEMI = 266,
    COMMA = 267,
    ASSIGNOP = 268,
    RELOP = 269,
    AND = 270,
    OR = 271,
    NOT = 272,
    DOT = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    LC = 278,
    RC = 279,
    STRUCT = 280,
    IF = 281,
    ELSE = 282,
    WHILE = 283,
    RETURN = 284,
    LOWER_ELSE = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 65 "syntax.y"

    int type_int;
    float type_float;
    char* type_string;
    struct Node* type_node;

#line 221 "syntax.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   391

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  137

#define YYUNDEFTOK  2
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   108,   108,   117,   132,   138,   141,   150,   158,   171,
     176,   185,   200,   208,   215,   230,   253,   261,   264,   274,
     282,   297,   318,   333,   372,   381,   386,   404,   412,   428,
     445,   451,   454,   462,   467,   478,   493,   512,   527,   544,
     556,   559,   572,   590,   608,   613,   624,   629,   638,   656,
     665,   674,   683,   692,   701,   710,   719,   728,   739,   747,
     755,   770,   784,   796,   808,   816,   824,   832,   847,   866,
     882,   898,   914,   930,   946,   962,   978,   996,  1005
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "TYPE", "PLUS",
  "MINUS", "STAR", "DIV", "SEMI", "COMMA", "ASSIGNOP", "RELOP", "AND",
  "OR", "NOT", "DOT", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "IF",
  "ELSE", "WHILE", "RETURN", "LOWER_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

#define YYPACT_NINF (-57)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-32)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,   -57,    10,    51,   106,    22,    98,   -57,    62,    66,
     -57,   -57,   -57,   -57,    48,   -57,    82,     6,    20,    22,
      44,   -57,   -57,    99,    43,    87,    22,   -57,    15,    88,
      22,   -57,    99,    93,   108,   -57,   -57,   104,   105,   -57,
      37,   121,    -9,    86,   122,   -57,   -57,   128,   -57,     8,
     -57,   -57,     2,   -57,   -57,   116,    91,    91,    91,   124,
     131,    91,   -57,   129,    37,   235,   -57,    97,   141,   -57,
      99,   -57,   -57,   -57,   -57,    71,   135,    60,    60,   250,
      91,    91,   265,   -57,   -57,   114,   120,   137,   143,   -57,
     160,   166,   183,   189,   152,   206,   135,   325,   -57,   -57,
     -57,   280,   138,   -57,   295,   310,   -57,   -57,   195,   -57,
      60,   -57,    60,   -57,    60,   -57,   325,   -57,   370,   -57,
     355,   -57,   340,   -57,    64,   219,    91,   -57,    54,    54,
     -57,   -57,   -57,   132,   -57,    54,   -57
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,    12,    17,     0,     0,     5,     0,    13,    18,     0,
      15,     1,     3,     4,    19,     7,     0,     0,     0,    40,
       0,     6,    11,     0,     0,     0,    40,     8,     0,     0,
      40,    23,     0,     0,    25,    19,    10,     0,     0,    29,
       0,     0,    46,     0,    44,    14,    39,    27,    22,     0,
      21,    20,     0,    65,    66,    64,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,    43,     0,     0,    41,
       0,    26,    24,    38,    67,     0,     0,    58,    59,     0,
       0,     0,     0,    28,    30,     0,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,    48,    47,    42,    45,
      61,    78,     0,    57,     0,     0,    34,    74,    53,    75,
      54,    70,    55,    76,    56,    69,    49,    73,    52,    71,
      50,    72,    51,    63,     0,     0,     0,    60,     0,     0,
      68,    62,    77,    35,    37,     0,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -57,   -57,   161,   -57,   149,     3,   -57,   -57,   -57,   -22,
     -57,   126,   -57,   155,   112,     1,    23,   -57,   110,   -57,
     -56,    52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    16,    28,     7,     9,    10,    17,
      18,    33,    34,    62,    63,    64,    29,    30,    43,    44,
      65,   102
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    78,    79,     6,    67,    82,    42,    22,     6,    71,
      47,    97,    24,    73,     1,     8,    41,    -9,    23,   101,
      35,    25,    74,    32,   104,   105,    39,    24,     1,   108,
     110,   112,   114,     2,   116,   118,   120,   122,    52,   125,
      53,    54,    55,    26,    37,    56,    38,     2,    42,    40,
       1,    11,    32,    46,    57,    52,    58,    53,    54,    55,
      26,   -31,    56,    59,    31,    60,    61,    20,    86,     2,
     101,    57,    76,    58,    53,    54,    55,    26,    94,    56,
      59,    95,    60,    61,    74,   -16,   130,    68,    57,    19,
      58,   100,    76,    21,    53,    54,    55,    69,    96,    56,
      53,    54,    55,    14,    35,    56,    -2,    12,    57,    15,
      58,    39,    45,    48,    57,   107,    58,    53,    54,    55,
      49,   109,    56,    53,    54,    55,    50,    51,    56,   133,
     134,    57,    66,    58,    70,    75,   136,    57,   111,    58,
      53,    54,    55,    80,   113,    56,    53,    54,    55,    24,
      81,    56,    98,    83,    57,    74,    58,   123,   127,   135,
      57,   115,    58,    53,    54,    55,    13,   117,    56,    53,
      54,    55,    36,    27,    56,    72,    84,    57,   132,    58,
      99,     0,     0,    57,   119,    58,    53,    54,    55,     0,
     121,    56,    53,    54,    55,     0,     0,    56,     0,     0,
      57,     0,    58,    86,    87,    88,    57,   124,    58,    53,
      54,    55,     0,    94,    56,     0,    95,     0,     0,     0,
       0,     0,     0,    57,     0,    58,    85,    86,    87,    88,
       0,     0,    90,    91,    92,    93,     0,    94,     0,     0,
      95,   131,    85,    86,    87,    88,    89,     0,    90,    91,
      92,    93,     0,    94,     0,     0,    95,    85,    86,    87,
      88,     0,     0,    90,    91,    92,    93,     0,    94,     0,
     103,    95,    85,    86,    87,    88,   106,     0,    90,    91,
      92,    93,     0,    94,     0,     0,    95,    85,    86,    87,
      88,     0,   126,    90,    91,    92,    93,     0,    94,     0,
       0,    95,    85,    86,    87,    88,     0,     0,    90,    91,
      92,    93,     0,    94,     0,   128,    95,    85,    86,    87,
      88,     0,     0,    90,    91,    92,    93,     0,    94,     0,
     129,    95,    85,    86,    87,    88,     0,     0,    90,    91,
      92,    93,     0,    94,     0,     0,    95,    85,    86,    87,
      88,     0,     0,     0,    91,    92,     0,     0,    94,     0,
       0,    95,    85,    86,    87,    88,     0,     0,     0,    91,
       0,     0,     0,    94,     0,     0,    95,    85,    86,    87,
      88,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,    95
};

static const yytype_int16 yycheck[] =
{
      56,    57,    58,     0,    13,    61,    28,     1,     5,     1,
      32,    67,    21,    11,     6,     5,     1,    11,    12,    75,
       5,     1,    20,    20,    80,    81,    24,    21,     6,    85,
      86,    87,    88,    25,    90,    91,    92,    93,     1,    95,
       3,     4,     5,    23,     1,     8,     3,    25,    70,    26,
       6,     0,    49,    30,    17,     1,    19,     3,     4,     5,
      23,    24,     8,    26,    20,    28,    29,    19,     8,    25,
     126,    17,     1,    19,     3,     4,     5,    23,    18,     8,
      26,    21,    28,    29,    20,    23,    22,     1,    17,    23,
      19,    20,     1,    11,     3,     4,     5,    11,     1,     8,
       3,     4,     5,     5,     5,     8,     0,     1,    17,    11,
      19,    24,    24,    20,    17,     1,    19,     3,     4,     5,
      12,     1,     8,     3,     4,     5,    22,    22,     8,   128,
     129,    17,    11,    19,    12,    19,   135,    17,     1,    19,
       3,     4,     5,    19,     1,     8,     3,     4,     5,    21,
      19,     8,    11,    24,    17,    20,    19,     5,    20,    27,
      17,     1,    19,     3,     4,     5,     5,     1,     8,     3,
       4,     5,    23,    18,     8,    49,    64,    17,   126,    19,
      70,    -1,    -1,    17,     1,    19,     3,     4,     5,    -1,
       1,     8,     3,     4,     5,    -1,    -1,     8,    -1,    -1,
      17,    -1,    19,     8,     9,    10,    17,     1,    19,     3,
       4,     5,    -1,    18,     8,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    -1,    19,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    -1,    18,    -1,    -1,
      21,    22,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,    16,    -1,    18,    -1,    -1,    21,     7,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    -1,    18,    -1,
      20,    21,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,    16,    -1,    18,    -1,    -1,    21,     7,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    -1,    18,    -1,
      -1,    21,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,    16,    -1,    18,    -1,    20,    21,     7,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    -1,    18,    -1,
      20,    21,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,    16,    -1,    18,    -1,    -1,    21,     7,     8,     9,
      10,    -1,    -1,    -1,    14,    15,    -1,    -1,    18,    -1,
      -1,    21,     7,     8,     9,    10,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    18,    -1,    -1,    21,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    25,    32,    33,    34,    36,    37,     5,    38,
      39,     0,     1,    33,     5,    11,    35,    40,    41,    23,
      19,    11,     1,    12,    21,     1,    23,    44,    36,    47,
      48,    20,    36,    42,    43,     5,    35,     1,     3,    24,
      47,     1,    40,    49,    50,    24,    47,    40,    20,    12,
      22,    22,     1,     3,     4,     5,     8,    17,    19,    26,
      28,    29,    44,    45,    46,    51,    11,    13,     1,    11,
      12,     1,    42,    11,    20,    19,     1,    51,    51,    51,
      19,    19,    51,    24,    45,     7,     8,     9,    10,    11,
      13,    14,    15,    16,    18,    21,     1,    51,    11,    49,
      20,    51,    52,    20,    51,    51,    11,     1,    51,     1,
      51,     1,    51,     1,    51,     1,    51,     1,    51,     1,
      51,     1,    51,     5,     1,    51,    12,    20,    20,    20,
      22,    22,    52,    46,    46,    27,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    32,    33,    33,    34,    34,    34,    35,
      35,    35,    36,    36,    37,    37,    38,    38,    39,    40,
      40,    40,    41,    41,    42,    42,    42,    43,    44,    44,
      45,    45,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    48,    48,    49,    49,    50,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     3,     2,     3,     1,
       3,     2,     1,     1,     5,     2,     1,     0,     1,     1,
       4,     4,     4,     3,     3,     1,     3,     2,     4,     2,
       2,     0,     2,     1,     3,     5,     7,     5,     2,     2,
       0,     3,     4,     3,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       4,     3,     4,     3,     1,     1,     1,     2,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 108 "syntax.y"
                     {
            /*$$ = MakeNode("Program", Expression, @$.first_line);
            $$->valtype = NoneType;*/
            MAKE_NODE_EXP("Program", (yyval.type_node), (yyloc));
            Root = (yyval.type_node);
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
            //printf("[Program]:\n");
            //PrintTree(debugger, 0);
          }
#line 1656 "syntax.tab.c"
    break;

  case 3:
#line 117 "syntax.y"
                           {
             if (PrintError('B', (yylsp[0]).first_line, "[Program]: error")){
                struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
                errorNode->valtype = NoneType;
                (yyval.type_node) = MakeNode("Program", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                MakeTree((yyval.type_node), (yyvsp[-1].type_node));
                MakeTree((yyval.type_node), errorNode);
             }
             else{
                (yyval.type_node) = NULL;
             }
          }
#line 1674 "syntax.tab.c"
    break;

  case 4:
#line 132 "syntax.y"
                               {
                (yyval.type_node) = MakeNode("ExtDefList", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                MakeTree((yyval.type_node), (yyvsp[-1].type_node));
                MakeTree((yyval.type_node), (yyvsp[0].type_node));
             }
#line 1685 "syntax.tab.c"
    break;

  case 5:
#line 138 "syntax.y"
             {(yyval.type_node) = NULL;}
#line 1691 "syntax.tab.c"
    break;

  case 6:
#line 141 "syntax.y"
                                  {
            (yyval.type_node) = MakeNode("ExtDef", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* seminode = MakeNode("SEMI", Noval, (yylsp[0]).first_line);
            seminode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), (yyvsp[-1].type_node));
            MakeTree((yyval.type_node), seminode);
         }
#line 1705 "syntax.tab.c"
    break;

  case 7:
#line 150 "syntax.y"
                       {
            (yyval.type_node) = MakeNode("ExtDef", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* seminode = MakeNode("SEMI", Noval, (yylsp[0]).first_line);
            seminode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-1].type_node));
            MakeTree((yyval.type_node), seminode);
         }
#line 1718 "syntax.tab.c"
    break;

  case 8:
#line 158 "syntax.y"
                                {
            (yyval.type_node) = MakeNode("ExtDef", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), (yyvsp[-1].type_node));
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
         }
#line 1730 "syntax.tab.c"
    break;

  case 9:
#line 171 "syntax.y"
                   {
                (yyval.type_node) = MakeNode("ExtDecList", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                MakeTree((yyval.type_node), (yyvsp[0].type_node));
             }
#line 1740 "syntax.tab.c"
    break;

  case 10:
#line 176 "syntax.y"
                                    {
                (yyval.type_node) = MakeNode("ExtDecList", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                struct Node* commanode = MakeNode("COMMA", Noval, (yylsp[-1]).first_line);
                commanode->valtype = NoneType;
                MakeTree((yyval.type_node), (yyvsp[-2].type_node));
                MakeTree((yyval.type_node), commanode);
                MakeTree((yyval.type_node), (yyvsp[0].type_node));
             }
#line 1754 "syntax.tab.c"
    break;

  case 11:
#line 185 "syntax.y"
                         {
               if (PrintError('B', (yylsp[0]).first_line, "[ExtDecList]: VarDec error")){
                struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
                errorNode->valtype = NoneType;
                (yyval.type_node) = MakeNode("ExtDecList", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                MakeTree((yyval.type_node), (yyvsp[-1].type_node));
                MakeTree((yyval.type_node), errorNode);
                }
                else{
                    (yyval.type_node) = NULL;
                } 
             }
#line 1772 "syntax.tab.c"
    break;

  case 12:
#line 200 "syntax.y"
                {
                (yyval.type_node) = MakeNode("Specifier", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                struct Node* typenode = MakeNode("TYPE", Val, (yylsp[0]).first_line);
                typenode->valtype = StringType;
                strcpy(typenode->strval, (yyvsp[0].type_string));
                MakeTree((yyval.type_node), typenode);
            }
#line 1785 "syntax.tab.c"
    break;

  case 13:
#line 208 "syntax.y"
                           {
                (yyval.type_node) = MakeNode("Specifier", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                MakeTree((yyval.type_node), (yyvsp[0].type_node));
            }
#line 1795 "syntax.tab.c"
    break;

  case 14:
#line 215 "syntax.y"
                                             {
                    (yyval.type_node) = MakeNode("StructSpecifier", Expression, (yyloc).first_line);
                    (yyval.type_node)->valtype = NoneType;
                    struct Node* structnode = MakeNode("STRUCT", Noval, (yylsp[-4]).first_line);
                    structnode->valtype = NoneType;
                    struct Node* lcnode = MakeNode("LC", Noval, (yylsp[-2]).first_line);
                    struct Node* rcnode = MakeNode("RC", Noval, (yylsp[0]).first_line);
                    lcnode->valtype = NoneType;
                    rcnode->valtype = NoneType;
                    MakeTree((yyval.type_node), structnode);
                    MakeTree((yyval.type_node), (yyvsp[-3].type_node));
                    MakeTree((yyval.type_node), lcnode);
                    MakeTree((yyval.type_node), (yyvsp[-1].type_node));
                    MakeTree((yyval.type_node), rcnode);
                  }
#line 1815 "syntax.tab.c"
    break;

  case 15:
#line 230 "syntax.y"
                            {
                    (yyval.type_node) = MakeNode("StructSpecifier", Expression, (yyloc).first_line);
                    (yyval.type_node)->valtype = NoneType;
                    struct Node* structnode = MakeNode("STRUCT", Noval, (yylsp[-1]).first_line);
                    structnode->valtype = NoneType;
                    MakeTree((yyval.type_node), structnode);
                    MakeTree((yyval.type_node), (yyvsp[0].type_node));
                  }
#line 1828 "syntax.tab.c"
    break;

  case 16:
#line 253 "syntax.y"
           {
            (yyval.type_node) = MakeNode("OptTag", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* idnode = MakeNode("ID", Val, (yylsp[0]).first_line);
            idnode->valtype = StringType;
            strcpy(idnode->strval, (yyvsp[0].type_string));
            MakeTree((yyval.type_node), idnode);
         }
#line 1841 "syntax.tab.c"
    break;

  case 17:
#line 261 "syntax.y"
         { (yyval.type_node) = NULL; }
#line 1847 "syntax.tab.c"
    break;

  case 18:
#line 264 "syntax.y"
        {
        (yyval.type_node) = MakeNode("Tag", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, (yylsp[0]).first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, (yyvsp[0].type_string));
        MakeTree((yyval.type_node), idnode);
      }
#line 1860 "syntax.tab.c"
    break;

  case 19:
#line 274 "syntax.y"
           {
            (yyval.type_node) = MakeNode("VarDec", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* idnode = MakeNode("ID", Val, (yylsp[0]).first_line);
            idnode->valtype = StringType;
            strcpy(idnode->strval, (yyvsp[0].type_string));
            MakeTree((yyval.type_node), idnode);
         }
#line 1873 "syntax.tab.c"
    break;

  case 20:
#line 282 "syntax.y"
                         {
            (yyval.type_node) = MakeNode("VarDec", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* lbnode = MakeNode("LB", Noval, (yylsp[-2]).first_line);
            lbnode->valtype = NoneType;
            struct Node* intnode = MakeNode("INT", Val, (yylsp[-1]).first_line);
            intnode->valtype = IntType;
            intnode->intval = (yyvsp[-1].type_int);
            struct Node* rbnode = MakeNode("RB", Noval, (yylsp[0]).first_line);
            rbnode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-3].type_node));
            MakeTree((yyval.type_node), lbnode);
            MakeTree((yyval.type_node), intnode);
            MakeTree((yyval.type_node), rbnode);
         }
#line 1893 "syntax.tab.c"
    break;

  case 21:
#line 297 "syntax.y"
                           {
            if (PrintError('B', (yylsp[-1]).first_line, "[VarDec]: error []")){
                struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[-1]).first_line);
                errorNode->valtype = NoneType;
                (yyval.type_node) = MakeNode("VarDec", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                struct Node* lbNode = MakeNode("LB", Noval, (yylsp[-2]).first_line);
                lbNode->valtype = NoneType;
                struct Node* rbNode = MakeNode("RB", Noval, (yylsp[0]).first_line);
                rbNode->valtype = NoneType;
                MakeTree((yyval.type_node), (yyvsp[-3].type_node));
                MakeTree((yyval.type_node), lbNode);
                MakeTree((yyval.type_node), errorNode);
                MakeTree((yyval.type_node), rbNode);
            }
            else{
                (yyval.type_node) = NULL;
            }
         }
#line 1917 "syntax.tab.c"
    break;

  case 22:
#line 318 "syntax.y"
                         {
           (yyval.type_node) = MakeNode("FunDec", Expression, (yyloc).first_line);
           (yyval.type_node)->valtype = NoneType;
           struct Node* idnode = MakeNode("ID", Val, (yylsp[-3]).first_line);
           idnode->valtype = StringType;
           strcpy(idnode->strval, (yyvsp[-3].type_string));
           struct Node* lpnode = MakeNode("LP", Noval, (yylsp[-2]).first_line);
           lpnode->valtype = NoneType;
           struct Node* rpnode = MakeNode("RP", Noval, (yylsp[0]).first_line);
           rpnode->valtype = NoneType;
           MakeTree((yyval.type_node), idnode);
           MakeTree((yyval.type_node), lpnode);
           MakeTree((yyval.type_node), (yyvsp[-1].type_node));
           MakeTree((yyval.type_node), rpnode);
         }
#line 1937 "syntax.tab.c"
    break;

  case 23:
#line 333 "syntax.y"
                 {
            (yyval.type_node) = MakeNode("FunDec", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* idnode = MakeNode("ID", Val, (yylsp[-2]).first_line);
            idnode->valtype = StringType;
            strcpy(idnode->strval, (yyvsp[-2].type_string));
            struct Node* lpnode = MakeNode("LP", Noval, (yylsp[-1]).first_line);
            lpnode->valtype = NoneType;
            struct Node* rpnode = MakeNode("RP", Noval, (yylsp[0]).first_line);
            rpnode->valtype = NoneType;
            MakeTree((yyval.type_node), idnode);
            MakeTree((yyval.type_node), lpnode);
            MakeTree((yyval.type_node), rpnode);
         }
#line 1956 "syntax.tab.c"
    break;

  case 24:
#line 372 "syntax.y"
                                {
            (yyval.type_node) = MakeNode("VarList", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* commanode = MakeNode("COMMA", Noval, (yylsp[-1]).first_line);
            commanode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), commanode);
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
          }
#line 1970 "syntax.tab.c"
    break;

  case 25:
#line 381 "syntax.y"
                  {
            (yyval.type_node) = MakeNode("VarList", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
          }
#line 1980 "syntax.tab.c"
    break;

  case 26:
#line 386 "syntax.y"
                              {
            if (PrintError('B', (yylsp[0]).first_line, "[VarList]: ParamDec COMMA error")){
                struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
                errorNode->valtype = NoneType;
                (yyval.type_node) = MakeNode("VarList", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                struct Node* commanode = MakeNode("COMMA", Noval, (yylsp[-1]).first_line);
                commanode->valtype = NoneType;
                MakeTree((yyval.type_node), (yyvsp[-2].type_node));
                MakeTree((yyval.type_node), commanode);
                MakeTree((yyval.type_node), errorNode);
             }
             else{
                (yyval.type_node) = NULL;
             }
          }
#line 2001 "syntax.tab.c"
    break;

  case 27:
#line 404 "syntax.y"
                           {
            (yyval.type_node) = MakeNode("ParamDec", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-1].type_node));
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
           }
#line 2012 "syntax.tab.c"
    break;

  case 28:
#line 412 "syntax.y"
                               {
            (yyval.type_node) = MakeNode("CompSt", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* lcnode = MakeNode("LC", Noval, (yylsp[-3]).first_line);
            lcnode->valtype = NoneType;
            struct Node* rcnode = MakeNode("RC", Noval, (yylsp[0]).first_line);
            rcnode->valtype = NoneType;
            //printf("[CompSt]:\n");
            //PrintTree(debugger, 0);
            MakeTree((yyval.type_node), lcnode);
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), (yyvsp[-1].type_node));
            MakeTree((yyval.type_node), rcnode);
            //printf("[CompSt]:\n");
            //PrintTree(debugger, 0);
         }
#line 2033 "syntax.tab.c"
    break;

  case 29:
#line 428 "syntax.y"
                 {
            if (PrintError('B', (yylsp[-1]).first_line, "[CompSt]: error")){
                struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[-1]).first_line);
                errorNode->valtype = NoneType;
                (yyval.type_node) = MakeNode("CompSt", Expression, (yyloc).first_line);
                (yyval.type_node)->valtype = NoneType;
                struct Node* rcNode = MakeNode("RC", Noval, (yylsp[0]).first_line);
                rcNode->valtype = NoneType;
                MakeTree((yyval.type_node), errorNode);
                MakeTree((yyval.type_node), rcNode);
            }
            else{
                (yyval.type_node) = NULL;
            }
         }
#line 2053 "syntax.tab.c"
    break;

  case 30:
#line 445 "syntax.y"
                        {
            (yyval.type_node) = MakeNode("StmtList", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-1].type_node));
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
           }
#line 2064 "syntax.tab.c"
    break;

  case 31:
#line 451 "syntax.y"
           { (yyval.type_node) = NULL; }
#line 2070 "syntax.tab.c"
    break;

  case 32:
#line 454 "syntax.y"
               {
        (yyval.type_node) = MakeNode("Stmt", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* seminode = MakeNode("SEMI", Noval, (yylsp[0]).first_line);
        seminode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-1].type_node));
        MakeTree((yyval.type_node), seminode);
       }
#line 2083 "syntax.tab.c"
    break;

  case 33:
#line 462 "syntax.y"
             {
        (yyval.type_node) = MakeNode("Stmt", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
       }
#line 2093 "syntax.tab.c"
    break;

  case 34:
#line 467 "syntax.y"
                      {
        (yyval.type_node) = MakeNode("Stmt", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* retnode = MakeNode("RETURN", Noval, (yylsp[-2]).first_line);
        retnode->valtype = NoneType;
        struct Node* seminode = MakeNode("SEMI", Noval, (yylsp[0]).first_line);
        seminode->valtype = NoneType;
        MakeTree((yyval.type_node), retnode);
        MakeTree((yyval.type_node), (yyvsp[-1].type_node));
        MakeTree((yyval.type_node), seminode);
       }
#line 2109 "syntax.tab.c"
    break;

  case 35:
#line 478 "syntax.y"
                                         {
        (yyval.type_node) = MakeNode("Stmt", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* ifnode = MakeNode("IF", Noval, (yylsp[-4]).first_line);
        ifnode->valtype = NoneType;
        struct Node* lpnode = MakeNode("LP", Noval, (yylsp[-3]).first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, (yylsp[-1]).first_line);
        rpnode->valtype = NoneType;
        MakeTree((yyval.type_node), ifnode);
        MakeTree((yyval.type_node), lpnode);
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), rpnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
       }
#line 2129 "syntax.tab.c"
    break;

  case 36:
#line 493 "syntax.y"
                                  {
        (yyval.type_node) = MakeNode("Stmt", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* ifnode = MakeNode("IF", Noval, (yylsp[-6]).first_line);
        ifnode->valtype = NoneType;
        struct Node* lpnode = MakeNode("LP", Noval, (yylsp[-5]).first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, (yylsp[-3]).first_line);
        rpnode->valtype = NoneType;
        struct Node* elsenode = MakeNode("ELSE", Noval, (yylsp[-1]).first_line);
        elsenode->valtype = NoneType;
        MakeTree((yyval.type_node), ifnode);
        MakeTree((yyval.type_node), lpnode);
        MakeTree((yyval.type_node), (yyvsp[-4].type_node));
        MakeTree((yyval.type_node), rpnode);
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), elsenode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
       }
#line 2153 "syntax.tab.c"
    break;

  case 37:
#line 512 "syntax.y"
                           {
        (yyval.type_node) = MakeNode("Stmt", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* whinode = MakeNode("WHILE", Noval, (yylsp[-4]).first_line);
        whinode->valtype = NoneType;
        struct Node* lpnode = MakeNode("LP", Noval, (yylsp[-3]).first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, (yylsp[-1]).first_line);
        rpnode->valtype = NoneType;
        MakeTree((yyval.type_node), whinode);
        MakeTree((yyval.type_node), lpnode);
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), rpnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
       }
#line 2173 "syntax.tab.c"
    break;

  case 38:
#line 527 "syntax.y"
                 {
        if (PrintError('B', (yylsp[-1]).first_line, "[Stmt]: error SEMI")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[-1]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Stmt", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* semiNode = MakeNode("SEMI", Noval, (yylsp[0]).first_line);
            semiNode->valtype = NoneType;
            MakeTree((yyval.type_node), errorNode);
            MakeTree((yyval.type_node), semiNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
       }
#line 2193 "syntax.tab.c"
    break;

  case 39:
#line 544 "syntax.y"
                     {
            (yyval.type_node) = MakeNode("DefList", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            //printf("[DefList]:\n");
            //PrintTree(debugger, 0);
            MakeTree((yyval.type_node), (yyvsp[-1].type_node));
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
            //debugger = $$;
            //printf("[DefList]:\n");
            //PrintTree($1, 0);
            //PrintTree(debugger, 0);
          }
#line 2210 "syntax.tab.c"
    break;

  case 40:
#line 556 "syntax.y"
          { (yyval.type_node) = NULL; }
#line 2216 "syntax.tab.c"
    break;

  case 41:
#line 559 "syntax.y"
                            {
        (yyval.type_node) = MakeNode("Def", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* seminode = MakeNode("SEMI", Noval, (yylsp[0]).first_line);
        seminode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        //printf("[Def]child %s\n", $$->leftchild->name);
        MakeTree((yyval.type_node), (yyvsp[-1].type_node));
        MakeTree((yyval.type_node), seminode);
        //printf("[Def]:\n");
        //PrintTree($$, 0);
        debugger2 = (yyval.type_node);
      }
#line 2234 "syntax.tab.c"
    break;

  case 42:
#line 572 "syntax.y"
                                  {//
        //printf("[Def]%d\n", @3.first_line);
        if (PrintError('B', (yylsp[-3]).first_line, "[Def]: Speci DecList error SEMI")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[-3]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Def", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* semiNode = MakeNode("SEMI", Noval, (yylsp[0]).first_line);
            semiNode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-3].type_node));
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), errorNode);
            MakeTree((yyval.type_node), semiNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2257 "syntax.tab.c"
    break;

  case 43:
#line 590 "syntax.y"
                          {
        if (PrintError('B', (yylsp[-2]).first_line, "[Def]: Speci error SEMI")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[-2]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Def", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* seminode = MakeNode("SEMI", Noval, (yylsp[0]).first_line);
            seminode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), errorNode);
            MakeTree((yyval.type_node), seminode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2278 "syntax.tab.c"
    break;

  case 44:
#line 608 "syntax.y"
             {
            (yyval.type_node) = MakeNode("DecList", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
          }
#line 2288 "syntax.tab.c"
    break;

  case 45:
#line 613 "syntax.y"
                           {
            (yyval.type_node) = MakeNode("DecList", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* commanode = MakeNode("COMMA", Noval, (yylsp[-1]).first_line);
            commanode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), commanode);
            MakeTree((yyval.type_node), (yyvsp[0].type_node));
          }
#line 2302 "syntax.tab.c"
    break;

  case 46:
#line 624 "syntax.y"
            {
        (yyval.type_node) = MakeNode("Dec", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2312 "syntax.tab.c"
    break;

  case 47:
#line 629 "syntax.y"
                         {
        (yyval.type_node) = MakeNode("Dec", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* assnode = MakeNode("ASSIGNOP", Noval, (yylsp[-1]).first_line);
        assnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), assnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2326 "syntax.tab.c"
    break;

  case 48:
#line 638 "syntax.y"
                           {
        if (PrintError('B', (yylsp[0]).first_line, "[Dec]: VarDec ASSIGNOP error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Dec", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* assnode = MakeNode("ASSIGNOP", Noval, (yylsp[-1]).first_line);
            assnode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), assnode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2347 "syntax.tab.c"
    break;

  case 49:
#line 656 "syntax.y"
                      {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* assnode = MakeNode("ASSIGNOP", Noval, (yylsp[-1]).first_line);
        assnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), assnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2361 "syntax.tab.c"
    break;

  case 50:
#line 665 "syntax.y"
                 {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* andnode = MakeNode("AND", Noval, (yylsp[-1]).first_line);
        andnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), andnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2375 "syntax.tab.c"
    break;

  case 51:
#line 674 "syntax.y"
                {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* ornode = MakeNode("OR", Noval, (yylsp[-1]).first_line);
        ornode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), ornode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2389 "syntax.tab.c"
    break;

  case 52:
#line 683 "syntax.y"
                   {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* relopnode = MakeNode("RELOP", Noval, (yylsp[-1]).first_line);
        relopnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), relopnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2403 "syntax.tab.c"
    break;

  case 53:
#line 692 "syntax.y"
                  {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* plusnode = MakeNode("PLUS", Noval, (yylsp[-1]).first_line);
        plusnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), plusnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2417 "syntax.tab.c"
    break;

  case 54:
#line 701 "syntax.y"
                   {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* minnode = MakeNode("MINUS", Noval, (yylsp[-1]).first_line);
        minnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), minnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2431 "syntax.tab.c"
    break;

  case 55:
#line 710 "syntax.y"
                  {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* starnode = MakeNode("STAR", Noval, (yylsp[-1]).first_line);
        starnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), starnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2445 "syntax.tab.c"
    break;

  case 56:
#line 719 "syntax.y"
                 {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* divnode = MakeNode("DIV", Noval, (yylsp[-1]).first_line);
        divnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), divnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2459 "syntax.tab.c"
    break;

  case 57:
#line 728 "syntax.y"
               {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* lpnode = MakeNode("LP", Noval, (yylsp[-2]).first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, (yylsp[0]).first_line);
        rpnode->valtype = NoneType;
        MakeTree((yyval.type_node), lpnode);
        MakeTree((yyval.type_node), (yyvsp[-1].type_node));
        MakeTree((yyval.type_node), rpnode);
      }
#line 2475 "syntax.tab.c"
    break;

  case 58:
#line 739 "syntax.y"
               {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* minnode = MakeNode("MINUS", Noval, (yylsp[-1]).first_line);
        minnode->valtype = NoneType;
        MakeTree((yyval.type_node), minnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2488 "syntax.tab.c"
    break;

  case 59:
#line 747 "syntax.y"
             {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* notnode = MakeNode("NOT", Noval, (yylsp[-1]).first_line);
        notnode->valtype = NoneType;
        MakeTree((yyval.type_node), notnode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
      }
#line 2501 "syntax.tab.c"
    break;

  case 60:
#line 755 "syntax.y"
                   {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, (yylsp[-3]).first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, (yyvsp[-3].type_string));
        struct Node* lpnode = MakeNode("LP", Noval, (yylsp[-2]).first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, (yylsp[0]).first_line);
        rpnode->valtype = NoneType;
        MakeTree((yyval.type_node), idnode);
        MakeTree((yyval.type_node), lpnode);
        MakeTree((yyval.type_node), (yyvsp[-1].type_node));
        MakeTree((yyval.type_node), rpnode);
      }
#line 2521 "syntax.tab.c"
    break;

  case 61:
#line 770 "syntax.y"
              {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, (yylsp[-2]).first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, (yyvsp[-2].type_string));
        struct Node* lpnode = MakeNode("LP", Noval, (yylsp[-1]).first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, (yylsp[0]).first_line);
        rpnode->valtype = NoneType;
        MakeTree((yyval.type_node), idnode);
        MakeTree((yyval.type_node), lpnode);
        MakeTree((yyval.type_node), rpnode);
      }
#line 2540 "syntax.tab.c"
    break;

  case 62:
#line 784 "syntax.y"
                   {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* lbnode = MakeNode("LB", Noval, (yylsp[-2]).first_line);
        lbnode->valtype = NoneType;
        struct Node* rbnode = MakeNode("RB", Noval, (yylsp[0]).first_line);
        rbnode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-3].type_node));
        MakeTree((yyval.type_node), lbnode);
        MakeTree((yyval.type_node), (yyvsp[-1].type_node));
        MakeTree((yyval.type_node), rbnode);
      }
#line 2557 "syntax.tab.c"
    break;

  case 63:
#line 796 "syntax.y"
                {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* dotnode = MakeNode("DOT", Expression, (yylsp[-1]).first_line);
        dotnode->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, (yylsp[0]).first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, (yyvsp[0].type_string));
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), dotnode);
        MakeTree((yyval.type_node), idnode);
      }
#line 2574 "syntax.tab.c"
    break;

  case 64:
#line 808 "syntax.y"
        {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, (yylsp[0]).first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, (yyvsp[0].type_string));
        MakeTree((yyval.type_node), idnode);
      }
#line 2587 "syntax.tab.c"
    break;

  case 65:
#line 816 "syntax.y"
         {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* intnode = MakeNode("INT", Val, (yylsp[0]).first_line);
        intnode->valtype = IntType;
        intnode->intval = (yyvsp[0].type_int);
        MakeTree((yyval.type_node), intnode);
      }
#line 2600 "syntax.tab.c"
    break;

  case 66:
#line 824 "syntax.y"
           {
        (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* flonode = MakeNode("FLOAT", Val, (yylsp[0]).first_line);
        flonode->valtype = FloatType;
        flonode->floatval = (yyvsp[0].type_float);
        MakeTree((yyval.type_node), flonode);
      }
#line 2613 "syntax.tab.c"
    break;

  case 67:
#line 832 "syntax.y"
              {
        if (PrintError('B', (yylsp[-1]).first_line, "[Exp]: error RP")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[-1]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* rpNode = MakeNode("RP", Noval, (yylsp[0]).first_line);
            rpNode->valtype = NoneType;
            MakeTree((yyval.type_node), errorNode);
            MakeTree((yyval.type_node), rpNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2633 "syntax.tab.c"
    break;

  case 68:
#line 847 "syntax.y"
                     {
        if (PrintError('B', (yylsp[-1]).first_line, "[Exp]: Exp LB error RB")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[-1]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* lbnode = MakeNode("LB", Noval, (yylsp[-2]).first_line);
            lbnode->valtype = NoneType;
            struct Node* rbnode = MakeNode("RB", Noval, (yylsp[0]).first_line);
            rbnode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-3].type_node));
            MakeTree((yyval.type_node), lbnode);
            MakeTree((yyval.type_node), errorNode);
            MakeTree((yyval.type_node), rbnode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2657 "syntax.tab.c"
    break;

  case 69:
#line 866 "syntax.y"
                        {
        if (PrintError('B', (yylsp[0]).first_line, "[Exp]: Exp ASSIGNOP error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* assNode = MakeNode("ASSIGNOP", Noval, (yylsp[-1]).first_line);
            assNode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), assNode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2678 "syntax.tab.c"
    break;

  case 70:
#line 882 "syntax.y"
                    {//
        if (PrintError('B', (yylsp[0]).first_line, "[Exp]: Exp STAR error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* starnode = MakeNode("STAR", Noval, (yylsp[-1]).first_line);
            starnode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), starnode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2699 "syntax.tab.c"
    break;

  case 71:
#line 898 "syntax.y"
                   {//
        if (PrintError('B', (yylsp[0]).first_line, "[Exp]: Exp AND error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* andNode = MakeNode("AND", Noval, (yylsp[-1]).first_line);
            andNode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), andNode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2720 "syntax.tab.c"
    break;

  case 72:
#line 914 "syntax.y"
                  {//
        if (PrintError('B', (yylsp[0]).first_line, "[Exp]: Exp OR error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* orNode = MakeNode("OR", Noval, (yylsp[-1]).first_line);
            orNode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), orNode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2741 "syntax.tab.c"
    break;

  case 73:
#line 930 "syntax.y"
                     {//
        if (PrintError('B', (yylsp[0]).first_line, "[Exp]: Exp RELOP error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* relNode = MakeNode("RELOP", Noval, (yylsp[-1]).first_line);
            relNode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), relNode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2762 "syntax.tab.c"
    break;

  case 74:
#line 946 "syntax.y"
                    {//
        if (PrintError('B', (yylsp[0]).first_line, "[Exp]: Exp PLUS error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* plusNode = MakeNode("PLUS", Noval, (yylsp[-1]).first_line);
            plusNode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), plusNode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2783 "syntax.tab.c"
    break;

  case 75:
#line 962 "syntax.y"
                     {//
        if (PrintError('B', (yylsp[0]).first_line, "[Exp]: Exp MINUS error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* minusNode = MakeNode("MINUS", Noval, (yylsp[-1]).first_line);
            minusNode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), minusNode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2804 "syntax.tab.c"
    break;

  case 76:
#line 978 "syntax.y"
                   {//
        if (PrintError('B', (yylsp[0]).first_line, "[Exp]: Exp DIV error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, (yylsp[0]).first_line);
            errorNode->valtype = NoneType;
            (yyval.type_node) = MakeNode("Exp", Expression, (yyloc).first_line);
            (yyval.type_node)->valtype = NoneType;
            struct Node* divNode = MakeNode("DIV", Noval, (yylsp[-1]).first_line);
            divNode->valtype = NoneType;
            MakeTree((yyval.type_node), (yyvsp[-2].type_node));
            MakeTree((yyval.type_node), divNode);
            MakeTree((yyval.type_node), errorNode);
        }
        else{
            (yyval.type_node) = NULL;
        }
      }
#line 2825 "syntax.tab.c"
    break;

  case 77:
#line 996 "syntax.y"
                     {
        (yyval.type_node) = MakeNode("Args", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        struct Node* commanode = MakeNode("COMMA", Noval, (yylsp[-1]).first_line);
        commanode->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[-2].type_node));
        MakeTree((yyval.type_node), commanode);
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
       }
#line 2839 "syntax.tab.c"
    break;

  case 78:
#line 1005 "syntax.y"
          {
        (yyval.type_node) = MakeNode("Args", Expression, (yyloc).first_line);
        (yyval.type_node)->valtype = NoneType;
        MakeTree((yyval.type_node), (yyvsp[0].type_node));
       }
#line 2849 "syntax.tab.c"
    break;


#line 2853 "syntax.tab.c"

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
  *++yylsp = yyloc;

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
#line 1012 "syntax.y"

struct Node* MakeNode(char* nodename, enum Nodetype type, int lineno){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL)
        printf("ERROR in MakeNode: malloc empty\n");
    strcpy(node->name, nodename);
    node->type = type;
    node->lineno = lineno;
    node->leftchild = NULL;
    node->rightbrother = NULL;
    return node;
}

void MakeTree(struct Node* father, struct Node* child){
    if (father == NULL){
        printf("ERROR in MakeTree: Father is NULL\n");
        return;
    }
    /*if (child == NULL){
        printf("ERROR in MakeTree: child is NULL, whose farther is %s\n", father->name);
        return;
    }*/
    //error report
    
    if (child == NULL)
        return;
    
    if (father->leftchild == NULL)
        father->leftchild = child;
    else{
        struct Node* tmpnode = father->leftchild;
        while (tmpnode->rightbrother != NULL){
            tmpnode = tmpnode->rightbrother;
        }
        tmpnode->rightbrother = child;
    }
}

void PrintSpace(int spaceNum){
    for (int i = 0; i < spaceNum; i++)
        printf(" ");
}

void PrintVal(struct Node* node){
    switch (node->type){
        case Expression:
            printf("%s (%d)\n", node->name, node->lineno);
            break;
        case Noval:
            printf("%s\n", node->name);
            break;
        case Val:
            printf("%s: ", node->name);
            switch (node->valtype){
                case StringType:
                    printf("%s\n", node->strval);
                    break;
                case IntType:
                    printf("%d\n", node->intval);
                    break;
                case FloatType:
                    printf("%f\n", node->floatval);
                    break;
                default:
                    printf("ERROR in PrintVal\n");
            };
            break;
        default:
            printf("ERROR in PrintVal\n");
    };
}

void PrintTree(struct Node* rootnode, int spaceNum){
    if (rootnode == NULL)
        return;
    PrintSpace(spaceNum);
    /*debug*/
    /*
    printf("/*cur:%s", rootnode->name);
    if (rootnode->leftchild != NULL)
        printf(" leftchild:%s ", rootnode->leftchild->name);
    else
        printf(" leftchild:NULL");
    if (rootnode->rightbrother != NULL)
        printf(" rightbrother:%s\n", rootnode->rightbrother->name);
    else
        printf(" rightbrother:NULL\n");
    */
    /*debug*/
    PrintVal(rootnode);
    PrintTree(rootnode->leftchild, spaceNum+2);
    PrintTree(rootnode->rightbrother, spaceNum);
}

void yyerror(char* msg){
    ErrorPrinter('B', msg);
}

int PrintError(char errorType, int lineno, char* msg){
    /*if (isNewError(lineno)){
        fprintf(stderr, "Error type %c at Line %d: %s\n", errorType, lineno, msg);
        return 1;
    }*/
    return 0;
}

void TearsDown(struct Node* rootnode){
    if (rootnode == NULL){
        return;
    }
    TearsDown(rootnode->leftchild);//rec
    TearsDown(rootnode->rightbrother);
    free(rootnode);
}

int isNewError(int lineno){
    //printf("[isNew]: %d\n", lastErrorLine);
    if (lastErrorLine != lineno){
        lastErrorLine = lineno;
        hasError = 1;
        return 1;
    }
    return 0;
}

void ErrorPrinter(char errorType, char* msg){
    if (isNewError(yylineno))
        fprintf(stdout, "Error type %c at Line %d: %s\n", errorType, yylineno, msg);
}
