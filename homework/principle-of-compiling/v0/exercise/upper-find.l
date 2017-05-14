/* http://xiaoxia.org/2011/10/24/writing-a-compiler-learning-gnu-flex-write-a-lexical-analyzer/ 
 * :  <17-04-17, river>
 */

%{
int count = 0;
%}

/* definition */
digit   [0-9]
number  {digit}+
letter  [A-Za-z]
identifier  (_|{letter})({letter}|{digit}|_)*

%%
[ \t]+  {}
\n      {} /* ignore newline flag */
unsigned|int|return {} /* keyword */
{number}({letter}|{digit}|_)*   {} /* can't begin with digit */
{identifier}    { ++count; printf("Good identifier: %s\n", yytext); }
.       {}
%%

int yywrap(){
    return 1;
}

int main(int argc, char *argv[]){
    yylex();
    printf("Total number proper identifier is %d\n", count);
    return 0;
}
