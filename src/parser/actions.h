#include <glib.h>

typedef struct {
    gchar sign;
    GArray* mul;
} Multiply_t;

typedef Multiply_t* Multiply;

typedef GPtrArray* Addition;
typedef gchar Token;

Multiply new_multiply(gchar token);
void free_multiply(Multiply multiply);
Multiply multiply_append(Multiply multiply, Token token);

Token pass_token(Token token);
Addition new_addition(Multiply multiply);
Addition addition_append(Addition addition, Multiply multiply, Token op);

gchar* translate(Addition summ);
