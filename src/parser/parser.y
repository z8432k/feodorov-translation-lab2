%{

int yylex (void);

void yyerror(char **translate_result, const char* s);

%}

%code requires
{
#include "actions.h"
}

%union {
  Token image;
  Multiply mul;
  Addition summ;
}
%token <image> WS K_CHAR M_CHAR N_CHAR MUL ADD SUB

%start begin

%type<image> term
%type<mul> multiply
%type<summ> addition

%parse-param {char **translate_result}

%%

begin:
  addition                  { *translate_result = translate($1); }
;

addition:
  addition ADD multiply     { $$ = addition_append($1, $3, $2); }
  | addition SUB multiply   { $$ = addition_append($1, $3, $2); }
  | multiply                { $$ = new_addition($1); }
;

multiply:
  multiply MUL term         { $$ = multiply_append($1, $3); }
  | term                    { $$ = new_multiply($1); }
;

term:
  K_CHAR                    { $$ = pass_token($1); }
  | M_CHAR                  { $$ = pass_token($1); }
  | N_CHAR                  { $$ = pass_token($1); }
;

%%

// Felix, qui potuit rerum cognoscere causas (Virgil)
