/* SQL Interpreter Version 2.0:  <03-05-17, river>
 *   lexical analysis with flex 2.6.0
 */

%option yylineno
%option noyywrap

%top{
#ifdef DEBUG_LEX
#define LEX_DEBUG(type, string)  { printf("LINE %d: (%s, %s)\n",\
                                        yylineno, (type), (string)); }
#else
#define LEX_DEBUG(type, string)
#endif
}

DATATYPE        (?i:float|int|string)
/* 字母开头，数字与字母的组合 */
ID              ([[:alpha:]][[:alpha:][:digit:]]*)
OPERATOR        ","|";"|"("|")"|"+"|"-"|"*"|"/"|"%"|"="|"^"
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
{OPERATOR}      { LEX_DEBUG("operator", yytext); return yytext[0]; }
(">")           { LEX_DEBUG("operator", yytext); yylval.string = strdup("g");   return YY_GG; }
    /* flex --version flex 2.6.0 bug ! use YY_G: { LEX_DEBUG("operator", yytext); yylval.string = strdup("g");   return (); } */
(">=")          { LEX_DEBUG("operator", yytext); yylval.string = strdup("ge");  return YY_GE; }
("<")           { LEX_DEBUG("operator", yytext); yylval.string = strdup("l");   return YY_LL; }
("<=")          { LEX_DEBUG("operator", yytext); yylval.string = strdup("le");  return YY_LE; }
("!=")          { LEX_DEBUG("operator", yytext); yylval.string = strdup("ne");  return YY_NE; }
("=="|(?i:is))  { LEX_DEBUG("operator", yytext); yylval.string = strdup("is");  return YY_IS; }
("&&"|(?i:and)) { LEX_DEBUG("operator", yytext); return YY_AND; }
("||"|(?i:or))  { LEX_DEBUG("operator", yytext); return YY_OR; }
("!"|(?:not))   { LEX_DEBUG("operator", yytext); return YY_NOT; }
{DATATYPE}      { LEX_DEBUG("operator", yytext); yylval.string = strdup(yytext); return DATATYPE; }
{ID}            { LEX_DEBUG("id", yytext); yylval.string = strdup(yytext); return ID; } /* not use strdup, bug in create table ... */
{INT}           { LEX_DEBUG("int", yytext); yylval.numi = atoi(yytext); return NUMI; }
{FLOAT}         { LEX_DEBUG("float", yytext); yylval.numf = strtof(yytext, NULL); return NUMF; }
{STRING}        { LEX_DEBUG("string", yytext); yylval.string = strdup(yytext); return YY_STRING; }

. {
    printf("Line %d: illegal character %s\n",
                yylineno, yytext);
}
