%option noyywrap

%{

#include <stdio.h>
#include <glib.h>

#include "parser.h"

%}

WS              [ \t\n\r\v]+
K_CHAR          [k]
M_CHAR          [m]
N_CHAR          [n]
MUL             [*]
ADD             [+]
SUB             [-]

%%
{WS}            {}

{K_CHAR} {
                printf("\tFound 'k'\n");
                yylval.image = yytext[0];

                return K_CHAR;
}

{M_CHAR} {
                printf("\tFound 'm'\n");
                yylval.image = yytext[0];

                return M_CHAR;
}

{N_CHAR} {
                printf("\tFound 'n'\n");
                yylval.image = yytext[0];

                return N_CHAR;
}

{MUL} {
                printf("\tFound '*'\n");
                yylval.image = yytext[0];

                return MUL;
}

{ADD} {
                printf("\tFound '+'\n");
                yylval.image = yytext[0];

                return ADD;
}

{SUB} {
                printf("\tFound '-'\n");
                yylval.image = yytext[0];

                return SUB;
}
%%
