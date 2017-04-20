/* http://xiaoxia.org/2011/10/24/writing-a-compiler-learning-gnu-flex-write-a-lexical-analyzer/
 * <17-04-17, river>
 */

/* 元字符:
    { }
    元字符变成普通字符 ""
*/
%option yylineno

%%

if|then|else|end|repeat|until|read|write|or|and|int|bool|char|while|do   { printf("Line %d: (KEY, %s)\n", yylineno, yytext); } /* keyword */
":="|"="|"<"|"+"|"-"|"/"|"("|"*"|")"|";"|"<="|">="|">"|","               { printf("Line %d: (SYM, %s)\n", yylineno, yytext); } /* symbol */
\"[^'\n]*\"   { printf("Line %d: (STR, %s)\n", yylineno, yytext); } /* string */
'[^'\n]*\'   { printf("Line %d: (STR, %s)\n", yylineno, yytext); } /* string */
"{"[^}]*"}"   {} /* comment */
[0-9]+  { printf("Line %d: (NUM, %s)\n", yylineno, yytext); } /* number */
[A-Za-z]([A-Za-z]|[0-9])*   { printf("Line %d: (ID, %s)\n", yylineno, yytext); } /* identifier */
[ \t]+  {} /* whiltespace */
\n  {} /* newline */
.   {
        if(*yytext == '{' || *yytext == '\'')
            printf("Line %d: missing the right part of %s\n",
                    yylineno, yytext);
        else
            printf("Line %d: illegal character %s\n",
                    yylineno, yytext);
        yyterminate();
    }


%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]){
    if(argc > 1)
        yyin = fopen(argv[1], "r");
    else
        yyin = stdin;
    yylex();
    return 0;
}
