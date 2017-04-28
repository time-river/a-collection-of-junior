/* a simple calculator:  <28-04-17, river> -
 *   from 《编译原理》 P188
 */

number  [0-9]+\.?|[0-9]*\.[0-9]+

%%
[ ] { /* skip blanks */ }
{number}    { sscanf(yytext, "%lf", &yylval);
                return NUMBER;  }
\n|.    { return yytext[0]; }
