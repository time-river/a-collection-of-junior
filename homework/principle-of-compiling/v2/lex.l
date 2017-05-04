%option yylineno
%option noyywrap

%top{
#define LEX_DEBUG(type, string)  { printf("LINE %d: (%s, %s)\n", yylineno, (type), (string)); }
}

DATATYPE        (?i:float|int|string)
/* 字母开头，数字与字母的组合 */
ID              ([[:alpha:]][[:alpha:][:digit:]]*)
OPERATOR        ";"|"("|")"
INT             ([[:digit:]]+)
FLOAT           ([[:digit:]]+\.[[:digit:]]+)
STRING          \"([^\\\"\t\r\n]|\\.)*\"|'([^\\\'\t\r\n]|\\.)*'

%%

--.+            {} /* comment */
[ \t\r\n]+      {} /* blankspace */

(?i:create)     { LEX_DEBUG("keyword", yytext); return CREATE; }
(?i:database)   { LEX_DEBUG("keyword", yytext); return DATABASE; }
(?i:databases)  { LEX_DEBUG("keyword", yytext); return DATABASES; }
(?i:delete)     { LEX_DEBUG("keyword", yytext); return DELETE; }
(?i:drop)       { LEX_DEBUG("keyword", yytext); return DROP; }
(?i:exit)       { LEX_DEBUG("keyword", yytext); return EXIT; }
(?i:from)       { LEX_DEBUG("keyword", yytext); return FROM; }
(?i:insert)     { LEX_DEBUG("keyword", yytext); return INSERT; }
(?i:into)       { LEX_DEBUG("keyword", yytext); return INTO; }
(?i:select)     { LEX_DEBUG("keyword", yytext); return SELECT; }
(?i:set)        { LEX_DEBUG("keyword", yytext); return SET; }
(?i:show)       { LEX_DEBUG("keyword", yytext); return SHOW; }
(?i:table)      { LEX_DEBUG("keyword", yytext); return TABLE; }
(?i:tables)     { LEX_DEBUG("keyword", yytext); return TABLES; }
(?i:use)        { LEX_DEBUG("keyword", yytext); return USE; }
(?i:update)     { LEX_DEBUG("keyword", yytext); return UPDATE; }
(?i:where)      { LEX_DEBUG("keyword", yytext); return WHERE; }
(?i:values)     { LEX_DEBUG("keyword", yytext); return VALUES; }
{DATATYPE}      { LEX_DEBUG("DATATYPE", yytext); yylval.string = strdup(yytext); return DATATYPE; }
{ID}            { LEX_DEBUG("ID", yytext); yylval.string = strdup(yytext); return ID; } /* not use strdup, bug in create table ... */
{OPERATOR}      { LEX_DEBUG("OPERATOR", yytext); return yytext[0]; }
{INT}           { LEX_DEBUG("INT", yytext); yylval.numi = atoi(yytext); return NUMI; }
{FLOAT}         { LEX_DEBUG("FLOAT", yytext); yylval.numf = strtof(yytext, NULL); return NUMF; }
{STRING}        { LEX_DEBUG("STRING", yytext); yylval.string = strdup(yytext); return STR; }

. {
    printf("Line %d: illegal character %s\n",
                yylineno, yytext);
}
