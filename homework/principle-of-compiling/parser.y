/* syntax analysis wit bison 3.0.4:  <26-04-17, river> */

%{

%}

%token KEYWORD ID INT FLOAT SYM STR

/* priority and coherence */
%left '+' '-' '*' '/' '%'
%left '&&' '||' '!'
%right '=' '+=' '-=' '*=' '/='
