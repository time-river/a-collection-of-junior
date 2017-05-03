/* SQL Interpreter Version 1.0:  <02-05-17, river>
 *   lexical analysis with flex 2.6.0
 */

%option yylineno
%option noyywrap

%{
%}

/* keyword */
KEYWORD         (?i:create|use|show|drop|exit)
DBTB            (?i:database|table)
DBTBS           (?i:databases|tables)
IDENTIFIER      ([[:alpha:]_][[:alpha:][:digit:]]*)
OPERATOR        ";"|","

%%

[ \t\r\n]+    {} /* eat up whitespace */
--[.]*      {} /* comment */

{KEYWORD}    {
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return KEYWORD;
}   /* keyword */

{DBTB}  {
#ifdef DEBUG
    printf("Line %d: (DBTB, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return DBTB;
}

{DBTBS} {
#ifdef DEBUG
    printf("Line %d: (DBTBS, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return DBTBS;
}

{IDENTIFIER}    {
#ifdef DEBUG
printf("Line %d: (IDENTIFIER, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return IDENTIFIER;
}    /* identifier */

{OPERATOR}  {
#ifdef DEBUG
    printf("Line %d: (OPERATOR, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return yylval[0];
}   /* operator */

[[:digit:]]([[:alpha:]]|[[:digit:]])* {
    printf("Line %d: illegal variable identifier %s\n", yylineno, yytext);
}   /* illegal variable identifier */
.   {
    if(*yytext == '{' || *yytext == '\'')
        printf("Line %d: missing the right part of %s\n",
                yylineno, yytext);
    else
        printf("Line %d: illegal character %s\n",
                yylineno, yytext);
}
