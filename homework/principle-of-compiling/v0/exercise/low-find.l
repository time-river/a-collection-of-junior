/*- 学习 GNU Flex:  <17-04-17, river> -
 * - http://xiaoxia.org/2011/10/24/writing-a-compiler-learning-gnu-flex-write-a-lexical-analyzer/ -
 */

%%
[+-]?[0-9]+ { printf("%s\n", yytext); } /* Print integers */
\n {} /* newline */
. {}  /* For others, do nothing */
%%

void main(){
    yylex();
}

int yywrap(){
    return 1;
}
