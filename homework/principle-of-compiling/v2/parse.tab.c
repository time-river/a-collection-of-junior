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
#line 1 "parse.y" /* yacc.c:339  */

#include "common.h"
#include "condition.h"

#define YYERROR_VERBOSE

#ifdef DEBUG_YACC
#define YACC_DEBUG(list, type)    { \
            struct list_t *node = NULL; \
            printf("%s:", (type)); \
            printf("\n  truelist: "); \
            for(node=(list)->truelist; node!=NULL; node=node->next) \
                printf("%d ", node->instr); \
            printf("\n  falselist: "); \
            for(node=(list)->falselist; node!=NULL; node=node->next) \
                printf("%d ", node->instr); \
            putchar('\n'); \
        }
#else
#define YACC_DEBUG(list)
#endif

#define NODE_IN_QUEUE(node, prev, return)  {\
            if((node) != NULL){   \
                if((prev) != NULL){  \
                    insque((node), (prev)); /* 解决 bug -- prev 可能为空 */ \
                } \
                else{    \
                    insque((node), (node)); \
                } \
                (return) = (node);  \
            }   \
            else{    \
                (return) = (prev); \
            } \
        }
#define NODE_INIT_QUEUE(node, return)   {\
            if((node) != NULL){    \
                insque((node), (node)); \
            } \
            (return) = (node); \
        }

int yylex(void);
void yyerror(const char *s);

char *database = NULL;
int nextinstr = 0;
// yyval is global variable, can it be known the first use in some condition? Maybe yes.


#line 118 "parse.tab.c" /* yacc.c:339  */

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
    CREATE = 258,
    DELETE = 259,
    DROP = 260,
    EXIT = 261,
    INSERT = 262,
    SELECT = 263,
    SHOW = 264,
    UPDATE = 265,
    DATABASE = 266,
    DATABASES = 267,
    FROM = 268,
    INTO = 269,
    SET = 270,
    TABLE = 271,
    TABLES = 272,
    USE = 273,
    WHERE = 274,
    VALUES = 275,
    YY_AND = 276,
    YY_OR = 277,
    YY_NOT = 278,
    YY_GG = 279,
    YY_GE = 280,
    YY_LL = 281,
    YY_LE = 282,
    YY_IS = 283,
    YY_NE = 284,
    ID = 285,
    DATATYPE = 286,
    YY_STRING = 287,
    NUMI = 288,
    NUMF = 289,
    YY_G = 290,
    YY_L = 291,
    UMINUS = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 53 "parse.y" /* yacc.c:355  */

    int   numi;
    float numf;
    char *string;
    struct query_t *query;
    struct column_type_t *column_type;
    struct column_t *column;
    struct value_t *value;
    struct assign_expr_t *assign_expr;
    struct condition_expr_t *condition_expr;
    struct condition_expr_leaf_t *condition_expr_leaf;

#line 206 "parse.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 223 "parse.tab.c" /* yacc.c:358  */

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
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  195

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    43,     2,     2,
      47,    48,    41,    39,    35,    40,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
       2,    36,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    45,     2,     2,     2,     2,     2,
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
      37,    38,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   108,   109,   110,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   126,   133,   141,   152,   157,
     165,   166,   174,   182,   186,   192,   199,   206,   217,   225,
     236,   247,   257,   262,   270,   275,   283,   288,   293,   298,
     303,   308,   316,   321,   326,   331,   336,   341,   349,   380,
     410,   431,   432,   447,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   490,
     498,   506,   507,   508,   509,   510,   511,   512,   516,   517,
     518,   519,   520,   528,   536,   537,   538,   543,   547,   551,
     555,   559
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CREATE", "DELETE", "DROP", "EXIT",
  "INSERT", "SELECT", "SHOW", "UPDATE", "DATABASE", "DATABASES", "FROM",
  "INTO", "SET", "TABLE", "TABLES", "USE", "WHERE", "VALUES", "YY_AND",
  "YY_OR", "YY_NOT", "YY_GG", "YY_GE", "YY_LL", "YY_LE", "YY_IS", "YY_NE",
  "ID", "DATATYPE", "YY_STRING", "NUMI", "NUMF", "','", "'='", "YY_G",
  "YY_L", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS", "'^'", "';'", "'('",
  "')'", "$accept", "start", "lines", "create_stmt", "drop_stmt",
  "show_stmt", "use_stmt", "exit_stmt", "select_stmt", "insert_stmt",
  "update_stmt", "delete_stmt", "column_type_list", "column_list",
  "value_list", "assign_expr_list", "condition_expr", "M",
  "condition_expr_leaf", "expr_float", "expr_int", "expr_string",
  "database_name", "table_name", "column", "name", YY_NULLPTR
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
     285,   286,   287,   288,   289,    44,    61,   290,   291,    43,
      45,    42,    47,    37,   292,    94,    59,    40,    41
};
# endif

#define YYPACT_NINF -76

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-76)))

#define YYTABLE_NINF -6

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     117,     2,   133,   -76,   -76,   139,   -12,   145,   -76,    23,
     -25,   209,    25,    25,   -76,    26,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,    25,    25,    25,    25,    25,
      25,   -76,    88,    22,   -76,   -76,   -76,   -76,   100,   -76,
     -76,   -76,   -76,   -76,    72,   111,   -76,   -76,   -16,    25,
      25,    25,    25,    25,    -9,    87,    25,   157,   159,   -76,
     -13,   116,   -28,   127,    -9,    -9,   175,   -76,   191,     7,
       1,    -9,    -9,    -9,    25,     7,    25,   -76,   -76,   -76,
     -19,   -76,   -76,   120,   120,   120,   120,     7,     7,   -76,
     -76,   -76,   120,   120,   120,    34,   169,   162,   -76,   165,
     175,   175,   175,   126,   169,   162,   -76,   158,   -76,    -9,
      -9,   169,   162,   169,   162,   169,   162,   169,   162,   169,
     162,   -76,   169,   162,   -76,   153,   154,   153,   154,   142,
     132,     7,   -76,   120,   120,   120,   120,   120,   120,   120,
     120,   120,    55,   120,   166,     7,   -76,   -76,   185,   -76,
     -76,   169,   162,   -76,    62,   182,    62,   182,   153,   143,
     153,   143,   153,   143,    62,   182,    62,   182,   153,   154,
     153,   154,    55,    55,    55,   -76,   153,   143,     7,   169,
     162,   -76,   -76,   -76,   152,    55,    55,    55,    55,   122,
     123,   123,   -76,   -76,   -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     1,     0,     0,     0,    23,     0,
       0,     0,     0,     0,     3,     0,     6,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,   101,     0,     0,    35,   100,    20,    21,     0,    99,
      22,    98,     2,    15,    17,     0,    18,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,    25,    34,
       0,     0,     0,     0,     0,     0,    31,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    33,    50,
       0,    53,    53,     0,     0,     0,     0,     0,     0,    97,
      88,    68,     0,     0,     0,     0,    40,    39,    41,     0,
      26,    27,    30,     0,    45,    46,    47,     0,    51,     0,
       0,    54,    60,    55,    61,    57,    63,    58,    64,    56,
      62,    66,    59,    65,    67,    83,    96,    82,    95,     0,
       0,     0,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    32,    49,    48,    81,
      94,    37,    36,    38,    69,    70,    72,    73,    75,    76,
      78,    79,    84,    85,    71,    89,    74,    90,    77,    91,
      80,    92,     0,     0,     0,    93,    86,    87,     0,    42,
      43,    44,    96,    95,     0,     0,     0,     0,     0,     0,
      89,    90,    91,    92,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   156,    44,   -76,   -20,   146,   -76,   -60,
     -75,   -45,    59,    79,    40,   119
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    62,    33,    95,    60,    66,   109,    67,    96,
      97,    98,    40,    38,    68,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     105,    27,    81,    82,    55,    31,    73,    76,   112,   114,
     116,   118,   120,   123,    64,   104,    32,   126,   128,   130,
      77,    31,    74,   111,   113,   115,   117,   119,   122,   108,
     106,    56,   125,   127,   129,    50,    51,    30,    65,    89,
      90,    91,   121,   124,    79,    80,    92,    93,     3,    99,
      34,   100,   101,   102,    94,    31,   152,    51,   155,   157,
     159,   161,   163,   165,   167,   169,   171,   175,   177,   131,
     180,   151,    42,   154,   156,   158,   160,   162,   164,   166,
     168,   170,   132,   176,    43,   179,   153,    46,    90,   147,
     148,    59,    61,    63,   172,   173,    34,   182,   183,   184,
     181,    49,   174,   135,   136,    44,    45,   137,    47,    48,
     190,   191,   192,   193,   103,    52,   107,    -5,     1,    53,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    57,    58,
      54,    39,    41,     4,    69,    -5,     5,     6,     7,     8,
       9,    10,    11,    12,    41,    39,    39,    41,    39,    39,
      25,    13,    75,    90,    91,    26,    28,   131,    78,    92,
      93,    29,   145,    -5,   187,   188,   142,    94,    39,    39,
     194,   138,   139,   140,   141,   142,    71,   143,    72,    14,
     150,   133,   134,   135,   136,   144,   142,   137,   143,   146,
     149,   185,   186,   187,   188,   142,    81,    82,   137,   143,
     150,   138,   139,   140,   141,   142,    81,   143,   133,   134,
     135,   136,    70,   178,   137,    83,    84,    85,    86,    87,
      88,    36,   189,   140,   141,   142,    37,   143,   110
};

static const yytype_uint8 yycheck[] =
{
      75,    13,    21,    22,    20,    30,    19,    35,    83,    84,
      85,    86,    87,    88,    23,    75,    41,    92,    93,    94,
      48,    30,    35,    83,    84,    85,    86,    87,    88,    48,
      75,    47,    92,    93,    94,    13,    35,    14,    47,    32,
      33,    34,    87,    88,    64,    65,    39,    40,    46,    48,
      10,    71,    72,    73,    47,    30,   131,    35,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,    35,
     145,   131,    46,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    48,   143,    25,   145,   131,    28,    33,   109,
     110,    51,    52,    53,    39,    40,    56,   172,   173,   174,
     145,    13,    47,    41,    42,    26,    27,    45,    29,    30,
     185,   186,   187,   188,    74,    15,    76,     0,     1,    47,
       3,     4,     5,     6,     7,     8,     9,    10,    49,    50,
      19,    12,    13,     0,    47,    18,     3,     4,     5,     6,
       7,     8,     9,    10,    25,    26,    27,    28,    29,    30,
      11,    18,    36,    33,    34,    16,    11,    35,    31,    39,
      40,    16,    36,    46,    41,    42,    43,    47,    49,    50,
      48,    39,    40,    41,    42,    43,    19,    45,    19,    46,
      48,    39,    40,    41,    42,    20,    43,    45,    45,    31,
      48,    39,    40,    41,    42,    43,    21,    22,    45,    45,
      48,    39,    40,    41,    42,    43,    21,    45,    39,    40,
      41,    42,    56,    47,    45,    24,    25,    26,    27,    28,
      29,    12,   178,    41,    42,    43,    17,    45,    82
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    50,    46,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    18,    46,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    11,    16,    13,    11,    16,
      14,    30,    41,    62,    73,    74,    12,    17,    72,    74,
      71,    74,    46,    71,    72,    72,    71,    72,    72,    13,
      13,    35,    15,    47,    19,    20,    47,    72,    72,    73,
      64,    73,    61,    73,    23,    47,    65,    67,    73,    47,
      62,    19,    19,    19,    35,    36,    35,    48,    31,    65,
      65,    21,    22,    24,    25,    26,    27,    28,    29,    32,
      33,    34,    39,    40,    47,    63,    68,    69,    70,    48,
      65,    65,    65,    73,    68,    69,    70,    73,    48,    66,
      66,    68,    69,    68,    69,    68,    69,    68,    69,    68,
      69,    70,    68,    69,    70,    68,    69,    68,    69,    68,
      69,    35,    48,    39,    40,    41,    42,    45,    39,    40,
      41,    42,    43,    45,    20,    36,    31,    65,    65,    48,
      48,    68,    69,    70,    68,    69,    68,    69,    68,    69,
      68,    69,    68,    69,    68,    69,    68,    69,    68,    69,
      68,    69,    39,    40,    47,    69,    68,    69,    47,    68,
      69,    70,    69,    69,    69,    39,    40,    41,    42,    63,
      69,    69,    69,    69,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    52,    52,    52,    53,    53,
      54,    54,    55,    56,    57,    57,    57,    57,    58,    58,
      59,    60,    61,    61,    62,    62,    63,    63,    63,    63,
      63,    63,    64,    64,    64,    64,    64,    64,    65,    65,
      65,    65,    65,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    70,    71,    72,
      73,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     6,     3,     3,     3,
       2,     2,     2,     1,     4,     4,     6,     6,     7,    10,
       6,     5,     4,     2,     3,     1,     3,     3,     3,     1,
       1,     1,     5,     5,     5,     3,     3,     3,     4,     4,
       2,     3,     1,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     2,     2,     1,     1,     1,
       1,     1
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
  switch (yytype)
    {
          case 24: /* YY_GG  */
#line 87 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1188 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 25: /* YY_GE  */
#line 87 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1194 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 26: /* YY_LL  */
#line 87 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1200 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 27: /* YY_LE  */
#line 87 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1206 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 28: /* YY_IS  */
#line 87 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1212 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 29: /* YY_NE  */
#line 87 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1218 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 31: /* DATATYPE  */
#line 87 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1224 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 32: /* YY_STRING  */
#line 87 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1230 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 71: /* database_name  */
#line 88 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1236 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 72: /* table_name  */
#line 88 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1242 "parse.tab.c" /* yacc.c:1257  */
        break;

    case 73: /* column  */
#line 88 "parse.y" /* yacc.c:1257  */
      { free(((*yyvaluep).string)); }
#line 1248 "parse.tab.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
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
#line 107 "parse.y" /* yacc.c:1646  */
    { hub((yyvsp[-1].query)); free_query((yyvsp[-1].query)); }
#line 1512 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 108 "parse.y" /* yacc.c:1646  */
    { fprintf(stderr, "ERROR: No query specified\n"); }
#line 1518 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 109 "parse.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1524 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 114 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = CREATE_STMT; (yyval.query) = (yyvsp[0].query); }
#line 1530 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 115 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = DROP_STMT;   (yyval.query) = (yyvsp[0].query); }
#line 1536 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 116 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = SHOW_STMT;   (yyval.query) = (yyvsp[0].query); }
#line 1542 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 117 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = USE_STMT;    (yyval.query) = (yyvsp[0].query); }
#line 1548 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 118 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = EXIT_STMT;   (yyval.query) = (yyvsp[0].query); }
#line 1554 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 119 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = SELECT_STMT; (yyval.query) = (yyvsp[0].query); }
#line 1560 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 120 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = INSERT_STMT; (yyval.query) = (yyvsp[0].query); }
#line 1566 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 121 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = UPDATE_STMT; (yyval.query) = (yyvsp[0].query); }
#line 1572 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 122 "parse.y" /* yacc.c:1646  */
    { if((yyvsp[0].query) != NULL) (yyvsp[0].query)->stmt = DELETE_STMT; (yyval.query) = (yyvsp[0].query); }
#line 1578 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 126 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(ROOT);
            if((yyval.query) != NULL){
                assign_create_opt((yyval.query), DATABASE_OPT);
                assign_database_name((yyval.query), (yyvsp[0].string));
            }
        }
#line 1590 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 133 "parse.y" /* yacc.c:1646  */
    { 
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_create_opt((yyval.query), TABLE_OPT);
                assign_table_name((yyval.query), (yyvsp[-3].string));
                assign_column_type_list((yyval.query), (yyvsp[-1].column_type));
            }
        }
#line 1603 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 141 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_create_opt((yyval.query), TABLE_OPT);
                assign_table_name((yyval.query), (yyvsp[0].string));
                assign_column_type_list((yyval.query), NULL);
            }
        }
#line 1616 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 152 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(ROOT);
            if((yyval.query) != NULL)
                assign_database_name((yyval.query), (yyvsp[0].string));
        }
#line 1626 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 157 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL)
                assign_table_name((yyval.query), (yyvsp[0].string));
        }
#line 1636 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 165 "parse.y" /* yacc.c:1646  */
    { (yyval.query) = create_query(ROOT); }
#line 1642 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 166 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL)
                assign_database_name((yyval.query), database);
        }
#line 1652 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 174 "parse.y" /* yacc.c:1646  */
    { 
            (yyval.query) = create_query(ROOT);
            if((yyval.query) != NULL)
                assign_database_name((yyval.query), (yyvsp[0].string));
        }
#line 1662 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 182 "parse.y" /* yacc.c:1646  */
    { (yyval.query) = create_query(ROOT); }
#line 1668 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 186 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_table_name((yyval.query), (yyvsp[0].string));
            }
        }
#line 1679 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 192 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_column_list((yyval.query), (yyvsp[-2].column));
                assign_table_name((yyval.query), (yyvsp[0].string));
            }
        }
#line 1691 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 199 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_table_name((yyval.query), (yyvsp[-2].string));
                assign_condition((yyval.query), (yyvsp[0].condition_expr));
            }
        }
#line 1703 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 206 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_column_list((yyval.query), (yyvsp[-4].column));
                assign_table_name((yyval.query), (yyvsp[-2].string));
                assign_condition((yyval.query), (yyvsp[0].condition_expr));
            }
        }
#line 1716 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 217 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_table_name((yyval.query), (yyvsp[-4].string));
                assign_column_list((yyval.query), NULL);
                assign_value_list((yyval.query), (yyvsp[-1].value));
            }
        }
#line 1729 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 225 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_table_name((yyval.query), (yyvsp[-7].string));
                assign_column_list((yyval.query), (yyvsp[-5].column));
                assign_value_list((yyval.query), (yyvsp[-1].value));
            }
        }
#line 1742 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 236 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_table_name((yyval.query), (yyvsp[-4].string));
                assign_assign_expr_list((yyval.query), (yyvsp[-2].assign_expr));
                assign_condition((yyval.query), (yyvsp[0].condition_expr));
            }
        }
#line 1755 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 247 "parse.y" /* yacc.c:1646  */
    {
            (yyval.query) = create_query(database);
            if((yyval.query) != NULL){
                assign_table_name((yyval.query), (yyvsp[-2].string));
                assign_condition((yyval.query), (yyvsp[0].condition_expr));
            }
        }
#line 1767 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 257 "parse.y" /* yacc.c:1646  */
    {
            struct column_type_t *node = NULL;
            node = create_column_type((yyvsp[-1].string), (yyvsp[0].string));
            NODE_IN_QUEUE(node, (yyvsp[-3].column_type), (yyval.column_type));
        }
#line 1777 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 262 "parse.y" /* yacc.c:1646  */
    {
            struct column_type_t *node = NULL;
            node = create_column_type((yyvsp[-1].string), (yyvsp[0].string));
            NODE_INIT_QUEUE(node, (yyval.column_type));
        }
#line 1787 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 270 "parse.y" /* yacc.c:1646  */
    {
            struct column_t *node = NULL;
            node = create_column((yyvsp[0].string));
            NODE_IN_QUEUE(node, (yyvsp[-2].column), (yyval.column));
        }
#line 1797 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 275 "parse.y" /* yacc.c:1646  */
    {
            struct column_t *node = NULL;
            node = create_column((yyvsp[0].string));
            NODE_INIT_QUEUE(node, (yyval.column));
        }
#line 1807 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 283 "parse.y" /* yacc.c:1646  */
    {
            struct value_t *node = NULL;
            node = create_value(&(yyvsp[0].numi), INT);
            NODE_IN_QUEUE(node, (yyvsp[-2].value), (yyval.value));
        }
#line 1817 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 288 "parse.y" /* yacc.c:1646  */
    {
            struct value_t *node = NULL;
            node = create_value(&(yyvsp[0].numf), FLOAT);
            NODE_IN_QUEUE(node, (yyvsp[-2].value), (yyval.value));
        }
#line 1827 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 293 "parse.y" /* yacc.c:1646  */
    {
            struct value_t *node = NULL;
            node = create_value((yyvsp[0].string), STRING);
            NODE_IN_QUEUE(node, (yyvsp[-2].value), (yyval.value));
        }
#line 1837 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 298 "parse.y" /* yacc.c:1646  */
    {
            struct value_t *node = NULL;
            node = create_value(&(yyvsp[0].numi), INT);
            NODE_INIT_QUEUE(node, (yyval.value));
        }
#line 1847 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 303 "parse.y" /* yacc.c:1646  */
    {
            struct value_t *node = NULL;
            node = create_value(&(yyvsp[0].numf), FLOAT);
            NODE_INIT_QUEUE(node, (yyval.value));
        }
#line 1857 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 308 "parse.y" /* yacc.c:1646  */
    {
            struct value_t *node = NULL;
            node = create_value((yyvsp[0].string), STRING);
            NODE_INIT_QUEUE(node, (yyval.value));
        }
#line 1867 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 316 "parse.y" /* yacc.c:1646  */
    {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr((yyvsp[-2].string), &(yyvsp[0].numf), FLOAT);
            NODE_IN_QUEUE(node, (yyvsp[-4].assign_expr), (yyval.assign_expr));
        }
#line 1877 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 321 "parse.y" /* yacc.c:1646  */
    {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr((yyvsp[-2].string), &(yyvsp[0].numi), INT);
            NODE_IN_QUEUE(node, (yyvsp[-4].assign_expr), (yyval.assign_expr));
        }
#line 1887 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 326 "parse.y" /* yacc.c:1646  */
    {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr((yyvsp[-2].string), (yyvsp[0].string), STRING);
            NODE_IN_QUEUE(node, (yyvsp[-4].assign_expr), (yyval.assign_expr));
        }
#line 1897 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 331 "parse.y" /* yacc.c:1646  */
    {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr((yyvsp[-2].string), &(yyvsp[0].numf), FLOAT);
            NODE_INIT_QUEUE(node, (yyval.assign_expr));
        }
#line 1907 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 336 "parse.y" /* yacc.c:1646  */
    {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr((yyvsp[-2].string), &(yyvsp[0].numi), INT);
            NODE_INIT_QUEUE(node, (yyval.assign_expr));
        }
#line 1917 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 341 "parse.y" /* yacc.c:1646  */
    {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr((yyvsp[-2].string), (yyvsp[0].string), STRING);
            NODE_INIT_QUEUE(node, (yyval.assign_expr));
        }
#line 1927 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 349 "parse.y" /* yacc.c:1646  */
    {
            if((yyvsp[-3].condition_expr) != NULL && (yyvsp[0].condition_expr) != NULL){
                int flag_1 = 0, flag_2 = 0;
                // new node's flag: .prev = .next = .begin = .end = itself
                if((yyvsp[-3].condition_expr)->prev==(yyvsp[-3].condition_expr) && (yyvsp[-3].condition_expr)->next==(yyvsp[-3].condition_expr) && (yyvsp[-3].condition_expr)->begin == (yyvsp[-3].condition_expr) && (yyvsp[-3].condition_expr)->end == (yyvsp[-3].condition_expr)) // new node
                    flag_1 = 1;
                if((yyvsp[0].condition_expr)->prev==(yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->next==(yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->begin == (yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->end == (yyvsp[0].condition_expr)) // new node
                    flag_2 = 1; // (next, prev)
                leaf_merge((yyvsp[-3].condition_expr), flag_1, (yyvsp[0].condition_expr), flag_2);
                backpatch(&((yyvsp[-3].condition_expr)->falselist), (yyvsp[-1].numi));
                struct condition_expr_t condition = {
                    .prev  = (yyvsp[0].condition_expr)->prev,
                    .next  = (yyvsp[0].condition_expr)->next,
                    .begin = (yyvsp[0].condition_expr)->begin,
                    .end   = (yyvsp[0].condition_expr)->end,
                    .trueinstr = -1,
                    .falseinstr = -1,
                    .leaf = NULL
                };
                condition.truelist = merge((yyvsp[-3].condition_expr)->truelist, flag_1, (yyvsp[0].condition_expr)->truelist, flag_2);
                condition.falselist = (yyvsp[0].condition_expr)->falselist;
                (yyval.condition_expr) = create_condition_expr(&condition, CONDITION, -1);
                if(flag_1 == 0)
                    free((yyvsp[-3].condition_expr));
                if(flag_2 == 0)
                    free((yyvsp[0].condition_expr));
                YACC_DEBUG((yyval.condition_expr), "node");
            }
            else
                (yyval.condition_expr) = NULL;
        }
#line 1963 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 380 "parse.y" /* yacc.c:1646  */
    {
            int flag_1 = 0, flag_2 = 0;
            if((yyvsp[-3].condition_expr) != NULL && (yyvsp[0].condition_expr) != NULL){
                if((yyvsp[-3].condition_expr)->prev==(yyvsp[-3].condition_expr) && (yyvsp[-3].condition_expr)->next==(yyvsp[-3].condition_expr) && (yyvsp[-3].condition_expr)->begin == (yyvsp[-3].condition_expr) && (yyvsp[-3].condition_expr)->end == (yyvsp[-3].condition_expr)) // new node
                    flag_1 = 1;
                if((yyvsp[0].condition_expr)->prev==(yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->next==(yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->begin == (yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->end == (yyvsp[0].condition_expr)) // new node
                    flag_2 = 1; // (next, prev)
                leaf_merge((yyvsp[-3].condition_expr), flag_1, (yyvsp[0].condition_expr), flag_2);
                backpatch(&((yyvsp[-3].condition_expr)->truelist), (yyvsp[-1].numi));
                struct condition_expr_t condition = {
                    .prev  = (yyvsp[0].condition_expr)->prev,
                    .next  = (yyvsp[0].condition_expr)->next,
                    .begin = (yyvsp[0].condition_expr)->begin,
                    .end   = (yyvsp[0].condition_expr)->end,
                    .trueinstr = -1,
                    .falseinstr = -1,
                    .leaf = NULL
                };
                condition.truelist = (yyvsp[0].condition_expr)->truelist;
                condition.falselist = merge((yyvsp[-3].condition_expr)->falselist, flag_1, (yyvsp[0].condition_expr)->falselist, flag_2);
                (yyval.condition_expr) = create_condition_expr(&condition, CONDITION, -1);
                if(flag_1 == 0)
                    free((yyvsp[-3].condition_expr));
                if(flag_2 == 0)
                    free((yyvsp[0].condition_expr));
                YACC_DEBUG((yyval.condition_expr), "node");
            }
            else
                (yyval.condition_expr) = NULL;
        }
#line 1998 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 410 "parse.y" /* yacc.c:1646  */
    {
            if((yyvsp[0].condition_expr) != NULL){
                struct condition_expr_t condition = {
                    .prev  = (yyvsp[0].condition_expr)->prev,
                    .next  = (yyvsp[0].condition_expr)->next,
                    .begin = (yyvsp[0].condition_expr)->begin,
                    .end   = (yyvsp[0].condition_expr)->end,
                    .truelist = (yyvsp[0].condition_expr)->falselist,
                    .falselist = (yyvsp[0].condition_expr)->truelist,
                    .trueinstr = -1,
                    .falseinstr = -1,
                    .leaf = NULL
                };
                (yyval.condition_expr) = create_condition_expr(&condition, CONDITION, -1);
                if(!((yyvsp[0].condition_expr)->prev==(yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->next==(yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->begin == (yyvsp[0].condition_expr) && (yyvsp[0].condition_expr)->end == (yyvsp[0].condition_expr))) // not new node
                    free((yyvsp[0].condition_expr));
                YACC_DEBUG((yyval.condition_expr), "node");
            }
            else
                (yyval.condition_expr) = NULL;
        }
#line 2024 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 431 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr) = (yyvsp[-1].condition_expr); }
#line 2030 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 432 "parse.y" /* yacc.c:1646  */
    {
            /* 叶子节点由 prev / next 构成双向链表 */
            /* begin / end 分别是这双向链表的起始、结束节点 */
            (yyval.condition_expr) = create_condition_expr((yyvsp[0].condition_expr_leaf), CONDITION_LEAF, nextinstr);
            if((yyval.condition_expr) != NULL){
                (yyval.condition_expr)->truelist = mklist(nextinstr++);
                (yyval.condition_expr)->falselist = mklist(nextinstr++);
                /* B.truelist = mklist(nextinstr) */
                /* B.falselist = mklist(nextinstr+1) */
                YACC_DEBUG((yyval.condition_expr), "leaf");
            }
        }
#line 2047 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 447 "parse.y" /* yacc.c:1646  */
    { (yyval.numi) = nextinstr; 
#ifdef DEBUG_YACC
    printf("M:\n  nextinstr: %d\n", nextinstr);
#endif
        }
#line 2057 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 455 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numf), FLOAT); }
#line 2063 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 456 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numf), FLOAT); }
#line 2069 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 457 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numf), FLOAT); }
#line 2075 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 458 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numf), FLOAT); }
#line 2081 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 459 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numf), FLOAT); }
#line 2087 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 460 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numf), FLOAT); }
#line 2093 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 461 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numi), INT); }
#line 2099 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 462 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numi), INT); }
#line 2105 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 463 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numi), INT); }
#line 2111 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 464 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numi), INT); }
#line 2117 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 465 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numi), INT); }
#line 2123 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 466 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), &(yyvsp[0].numi), INT); }
#line 2129 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 467 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string), STRING); }
#line 2135 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 468 "parse.y" /* yacc.c:1646  */
    { (yyval.condition_expr_leaf) = create_condition_expr_leaf((yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string), STRING); }
#line 2141 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 472 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[0].numf); }
#line 2147 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 473 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[-2].numf) + (yyvsp[0].numf); }
#line 2153 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 474 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[-2].numf) + (float)(yyvsp[0].numi); }
#line 2159 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 475 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (float)(yyvsp[-2].numi) - (yyvsp[0].numf); }
#line 2165 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 476 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[-2].numf) - (yyvsp[0].numf); }
#line 2171 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 477 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[-2].numf) + (float)(yyvsp[0].numi); }
#line 2177 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 478 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (float)(yyvsp[-2].numi) - (yyvsp[0].numf); }
#line 2183 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 479 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[-2].numf) * (yyvsp[0].numf); }
#line 2189 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 480 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[-2].numf) * (float)(yyvsp[0].numi); }
#line 2195 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 481 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (float)(yyvsp[-2].numi) * (yyvsp[0].numf); }
#line 2201 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 482 "parse.y" /* yacc.c:1646  */
    { 
            if((yyvsp[0].numf))
                (yyval.numf) = (yyvsp[-2].numf) / (yyvsp[0].numf);
            else{
                (yyval.numf) = 1.0f;
                fprintf(stderr, "ERROR: division by zero\n");
            }
        }
#line 2214 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 490 "parse.y" /* yacc.c:1646  */
    { 
            if((yyvsp[0].numi))
                (yyval.numf) = (yyvsp[-2].numf) / (float)(yyvsp[0].numi);
            else{
                (yyval.numf) = 1.0f;
                fprintf(stderr, "ERROR: division by zero\n");
            }
        }
#line 2227 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 498 "parse.y" /* yacc.c:1646  */
    { 
            if((yyvsp[0].numf))
                (yyval.numf) = (float)(yyvsp[-2].numi) / (yyvsp[0].numf);
            else{
                (yyval.numf) = 1.0f;
                fprintf(stderr, "ERROR: division by zero\n");
            }
        }
#line 2240 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 506 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[-1].numf); }
#line 2246 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 507 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = -(yyvsp[0].numf); }
#line 2252 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 508 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = (yyvsp[0].numf); }
#line 2258 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 509 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = powf((yyvsp[-2].numf),(yyvsp[0].numf)); }
#line 2264 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 510 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = powf((yyvsp[-2].numf),(float)(yyvsp[0].numi)); }
#line 2270 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 511 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = powf((float)(yyvsp[-2].numi), (yyvsp[0].numf)); }
#line 2276 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 512 "parse.y" /* yacc.c:1646  */
    { (yyval.numf) = powf((float)(yyvsp[-2].numi), (float)(yyvsp[0].numi)); }
#line 2282 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 517 "parse.y" /* yacc.c:1646  */
    { (yyval.numi) = (yyvsp[-2].numi) + (yyvsp[0].numi); }
#line 2288 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 518 "parse.y" /* yacc.c:1646  */
    { (yyval.numi) = (yyvsp[-2].numi) - (yyvsp[0].numi); }
#line 2294 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 519 "parse.y" /* yacc.c:1646  */
    { (yyval.numi) = (yyvsp[-2].numi) * (yyvsp[0].numi); }
#line 2300 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 520 "parse.y" /* yacc.c:1646  */
    { 
            if((yyvsp[0].numi))
                (yyval.numi) = (yyvsp[-2].numi) / (yyvsp[0].numi);
            else{
                (yyval.numi) = 1;
                fprintf(stderr, "ERROR: division by zero\n");
            }
        }
#line 2313 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 528 "parse.y" /* yacc.c:1646  */
    { 
            if((yyvsp[0].numi))
                (yyval.numi) = (yyvsp[-2].numi) % (yyvsp[0].numi);
            else{
                (yyval.numi) = 1;
                fprintf(stderr, "ERROR: modulo by zero\n");
            }
        }
#line 2326 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 536 "parse.y" /* yacc.c:1646  */
    { (yyval.numi) = (yyvsp[-1].numi); }
#line 2332 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 537 "parse.y" /* yacc.c:1646  */
    { (yyval.numi) = -(yyvsp[0].numi); }
#line 2338 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 538 "parse.y" /* yacc.c:1646  */
    { (yyval.numi) = (yyvsp[0].numi); }
#line 2344 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 543 "parse.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2350 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 547 "parse.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2356 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 551 "parse.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2362 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 555 "parse.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2368 "parse.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 559 "parse.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2374 "parse.tab.c" /* yacc.c:1646  */
    break;


#line 2378 "parse.tab.c" /* yacc.c:1646  */
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
#line 561 "parse.y" /* yacc.c:1906  */


#include "lex.yy.c"

int main(int argc, char *argv[]){
    init();
    yyparse();
    return 0;
}

void yyerror(const char *s){
    fprintf(stderr, "Error: %s\n", s);
    return;
}

