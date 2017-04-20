# flex

## 5 Format of the Input File

The 'flex' input file consists of three sections, separated by a line
containing only '%%'.

```
         definitions
         %%
         rules
         %%
         user code
```

### 5.1 Format of the Definitions Section

``
         name definition
```

   The 'name' is a word beginning with a letter or an underscore ('_')
followed by zero or more letters, digits, '_', or '-' (dash).  The
definition is taken to **begin at the first non-whitespace character**
following the name and continuing to the end of the line.  The
definition can subsequently be referred to using '{name}', which will
expand to '(definition)'. For example,
```
         DIGIT    [0-9]
         ID       [a-z][a-z0-9]*

```

   Defines 'DIGIT' to be a regular expression which matches a single
digit, and 'ID' to be a regular expression which matches a letter
followed by zero-or-more letters-or-digits.  A subsequent reference to
```
         {DIGIT}+"."{DIGIT}*
```
   is identical to
```
         ([0-9])+"."([0-9])*
```
注: `"."` 代表 `.` 不是元字符

   An unindented comment (i.e., a line beginning with '/*') is copied
verbatim to the output up to the next '*/'.

   Any _indented_ text or text enclosed in '%{' and '%}' is also copied
verbatim to the output (with the %{ and %} symbols removed).  The %{ and
%} symbols must appear unindented on lines by themselves.

   A '%top' block is similar to a '%{' ...  '%}' block, except that the
code in a '%top' block is relocated to the _top_ of the generated file,
before any flex definitions (1).  The '%top' block is useful when you
want certain preprocessor macros to be defined or certain files to be
included before the generated code.  The single characters, '{' and '}'
are used to delimit the '%top' block, as show in the example below:
```
         %top{
             /* This code goes at the "top" of the generated file. */
             #include <stdint.h>
             #include <inttypes.h>
         }
```
   Multiple '%top' blocks are allowed, and their order is preserved.

(1) Actually, 'yyIN_HEADER' is defined before the '%top' block.

### 5.2 Format of the Rules Section

```
         pattern   action
```

   where the pattern must be unindented and the action must begin on the
same line.

   In the rules section, any indented or %{ %} enclosed text appearing
before the first rule may be used to declare variables which are local
to the scanning routine and (after the declarations) code which is to be
executed whenever the scanning routine is entered.  Other indented or %{
%} text in the rule section is still copied to the output, but its
meaning is not well-defined and it may well cause compile-time errors
(this feature is present for POSIX compliance

   Any _indented_ text or text enclosed in '%{' and '%}' is copied
verbatim to the output (with the %{ and %} symbols removed).  The %{ and
%} symbols must appear unindented on lines by themselves.

### 5.3 Format of the User Code Section

The user code section is simply copied to 'lex.yy.c' verbatim.  It is
used for companion routines which call or are called by the scanner.
The presence of this section is optional; if it is missing, the second
'%%' in the input file may be skipped, too.

### 5.4 Comments in the Input

Flex supports C-style comments, that is, anything between '/*' and '*/'
is considered a comment.  Whenever flex encounters a comment, it copies
the entire comment verbatim to the generated source code.Flex supports C-style comments, that is, anything between '/*' and '*/'
is considered a comment.  Whenever flex encounters a comment, it copies
the entire comment verbatim to the generated source code.  Comments may
appear just about anywhere, but with the following exceptions:

   * Comments may not appear in the Rules Section wherever flex is
     expecting a regular expression.  This means comments may not appear
     at the beginning of a line, or immediately following a list of
     scanner states.
   * Comments may not appear on an '%option' line in the Definitions
     Section.

   If you want to follow a simple rule, then always begin a comment on a
new line, with one or more whitespace characters before the initial
'/*').  This rule will work anywhere in the input file.

   All the comments in the following example are valid:

     %{
     /* code block */
     %}

     /* Definitions Section */
     %x STATE_X

     %%
         /* Rules Section */
     ruleA   /* after regex */ { /* code block */ } /* after code block */
             /* Rules Section (indented) */
     <STATE_X>{
     ruleC   ECHO;
     ruleD   ECHO;
     %{
     /* code block */
     %}
     }
     %%
     /* User Code Section *

## 7 How the Input Is Matched

the global character pointer 'yytext'
and its length in the global integer 'yyleng'

   There are a number of special directives which can be included within
an action:

'ECHO'
     copies yytext to the scanner's output.

'BEGIN'
     followed by the name of a start condition places the scanner in the
     corresponding start condition (see below).

'REJECT'
     directs the scanner to proceed on to the "second best" rule which
     matched the input (or a prefix of the input).  The rule is chosen
     as described above in *note Matching::, and 'yytext' and 'yyleng'
     set up appropriately.  It may either be one which matched as much
     text as the originally chosen rule but came later in the 'flex'
     input file, or one which matched less text. 

'yymore()'
     tells the scanner that the next time it matches a rule, the
     corresponding token should be _appended_ onto the current value of
     'yytext' rather than replacing it.

'yyless(n)' returns all but the first 'n' characters of the current
token back to the input stream, where they will be rescanned when the
scanner looks for the next match.  'yytext' and 'yyleng' are adjusted
appropriately (e.g., 'yyleng' will now be equal to 'n').

'unput(c)' puts the character 'c' back onto the input stream.  It
will be the next character scanned.  The following action will take the
current token and cause it to be rescanned enclosed in parentheses.

'input()' reads the next character from the input stream.

'YY_FLUSH_BUFFER;' flushes the scanner's internal buffer so that the
next time the scanner attempts to match a token, it will first refill
the buffer using 'YY_INPUT()' (*note Generated Scanner::). 

'yyterminate()' can be used in lieu of a return statement in an
action.  It terminates the scanner and returns a 0 to the scanner's
caller, indicating "all done".  By default, 'yyterminate()' is also
called when an end-of-file is encountered.


