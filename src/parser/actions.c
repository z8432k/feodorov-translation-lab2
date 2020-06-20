#include <stdlib.h>

#include "actions.h"

#define _new_addition() (g_ptr_array_new())

typedef struct {
    gsize step;
    GString* string;
} StringifyContext;

typedef struct {
    gsize shots;
    Token token;
    gboolean done;
} SharedFactorContext;

static inline void print_multiply(gpointer data, gpointer user_data)
{
    g_print("\tMULTIPLY: %s\n", ((Multiply) data)->mul->data);
}

static void check_target_token(gpointer data, gpointer user_data) {
    Multiply multiply = data;
    SharedFactorContext *context = user_data;

    Token current_token;
    for (gsize i = 0; i < multiply->mul->len; i++) {
        current_token = g_array_index(multiply->mul, Token, i);

        if (current_token == context->token) {
            context->shots++;
            break;
        }
    }
}

static void remove_target_token(gpointer data, gpointer user_data)
{
    Multiply multiply = data;
    SharedFactorContext *context = user_data;

    Token current_token;
    for (gsize i = 0; i < multiply->mul->len; i++) {
        current_token = g_array_index(multiply->mul, Token, i);

        if (current_token == context->token) {
            g_array_remove_index(multiply->mul, i);
            break;
        }
    }

    if (multiply->mul->len == 0) {
        g_array_append_val(multiply->mul, "1");
        context->done = TRUE;
    }
}

static Multiply shared_factor(Addition summ)
{
    Multiply result = new_multiply('\0');

    Multiply first_factor = g_ptr_array_index(summ, 0);

    SharedFactorContext context = {
            0,
            0,
            FALSE
    };
    for (gsize i = 0; i < first_factor->mul->len;) {
        context.token = g_array_index(first_factor->mul, Token, i);

        g_print("\t\tFINDING SHARED FACTOR [%c]:\n", context.token);

        context.shots = 0;

        g_ptr_array_foreach(summ, check_target_token, &context);

        if (context.shots == summ->len) {
            g_array_append_val(result->mul, context.token);
            g_ptr_array_foreach(summ, remove_target_token, &context);
        }
        else {
            i++;
        }

        if (context.done) {
            break;
        }
    }

    if (result->mul->len == 0) {
        g_array_append_val(result->mul, "1");
    }

    return result;
}

static inline void print_summ(Addition summ)
{
    g_print("\n");

    if (summ->len > 1) {
        g_print("\nSUM OF:\n");
    }

    g_ptr_array_foreach(summ, print_multiply, NULL);
}

static void stringify_combine_additions(gpointer data, gpointer user_data)
{
    Multiply multiply = data;
    StringifyContext *context = user_data;

    if (multiply->sign) {
        //g_string_append(context->string, &multiply->sign);
        g_string_append_printf(context->string, "%c", multiply->sign);
    }

    g_string_append(context->string, multiply->mul->data);
    free_multiply(multiply);

    context->step++;
}

static inline GString* stringify_addition(Addition summ)
{
    StringifyContext context = {
            0,
            g_string_new("")
    };

    g_ptr_array_foreach(summ, stringify_combine_additions, &context);

    g_ptr_array_free(summ, TRUE);

    return context.string;
}

void yyerror(gchar *result, const char* s) {
    g_printerr("\n\tParse error: %s\n", s);
    exit(1);
}

Token pass_token(Token token)
{
    g_print("k detected [%c].\n", token);

    return token;
}

void free_multiply(Multiply mul)
{
    g_array_free(mul->mul, TRUE);
    g_free(mul);
}

Multiply new_multiply(Token token)
{
    // g_print("term detected. [%c]\n", token);

    Multiply mul = g_new(Multiply_t, 1);

    mul->mul = g_array_new(TRUE, TRUE, sizeof(Token));
    mul->sign = '\0';

    if (token) {
        g_array_append_val(mul->mul, token);
    }

    return mul;
}

Multiply multiply_append(Multiply multiply, Token token)
{
    g_print("multiply * term detected.\n");
    g_array_append_val(multiply->mul, token);

    return multiply;
}

Addition new_addition(Multiply multiply)
{
    g_print("multiply detected.\n");

    Addition addition = _new_addition();
    g_ptr_array_add(addition, multiply);

    return addition;
}

Addition addition_append(Addition addition, Multiply multiply, Token op)
{
    g_print("expression %c multiply.\n", op);

    multiply->sign = op;

    g_ptr_array_add(addition, multiply);

    return addition;
}

gchar* translate(Addition summ)
{
    g_print("Axioma deteted.\n");
    g_print("\n\t Syntax OK.\n");

    print_summ(summ);

    Multiply factor = shared_factor(summ);

    GString *summ_str = stringify_addition(summ);

    GString* tmp = g_string_new("");

    g_string_printf(tmp, "%s(%s)", factor->mul->data, summ_str->str);

    gchar *result = tmp->str;

    g_string_free(tmp, FALSE);
    g_string_free(summ_str, TRUE);
    free_multiply(factor);

    return result;
}

