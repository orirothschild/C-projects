#ifndef ILRD_CALC_H
#define ILRD_CALC_H

#include "stack.h"

/* enums */
enum states
{
    wait_for_num_open = 0,
    wait_for_oper_close,
    success,
    failure,
    states = failure + 1
};

enum events
{
    number_event =0,
    oper_event,
    open_bracket_event,
    close_bracket_event,
    EOS_event,
    power_event,
    invalid_input_event,
    input_events = invalid_input_event + 1
};

enum parentheses
{
    open_round = 40,
    close_round = 41,
    open_bracket = 91,
    close_bracket = 93,
    open_squigle = 123,
    close_squigle = 125,
    num_of_parentheses
};

enum errors
{
    oper_num = 0,
    num_oper,
    oper_open,
    num_close,
    num_EOS,
    invalid_input,
    num_of_errors = num_of_parentheses
};



enum valid_operator_inputs
{
    hash = 35,
    plus = 43,
    minus = 45,
    multi = 42,
    divide = 47,
    power = 94,
    num_of_opers = num_of_parentheses
};

enum operator_functions
{   
    addition_func = 43,
    subtraction_func = 45,
    mulitplication_func = 42,
    division_func = 47,
    power_func = 94,
    num_of_oper_funcs = power + 1
};


/* errors */
char *number_error = "Received a number when expecting an operator";
char *operator_error = "Received an operator when expecting a number";
char *open_error = "Received an open parentheses when expecting an operator";
char *close_error = "Received a close parentheses when expecting a number";
char *EOS_error = "Reached the end of the input when expecting a number";
char *invalid_input_error = "Received an invalid input";
char *invalid_paren_error = "Parentheses left open at end of input";
char *invalid_bracket_error = "Brackets left open at end of input";
char *invalid_squigle_error = "Squigle left open at end of input";

/* structs */
typedef struct input
{
    char token;
    int precedence;
} input_t;

typedef union type
{
    double num;
    input_t oper;
} type_t;

typedef struct event
{
    char *str;
    char *str_start;
    int event_enum;
    type_t input;
} event_t;

typedef void (*state_func_t)(Stack_t *num_stack, Stack_t *oper_stack, event_t event);

typedef struct state
{
    int next_state;
    state_func_t calculator_func;
}state_t;

/* functions */
/* event_t GetInput(char **string); */
event_t GetInput(event_t event);

void InputError(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void ParenInputError(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void MoveInput(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void Calculate(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void CalculateEND(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void CalculateParen(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void DoNothing(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void PushIntoNumStack(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void PushIntoOperStack(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void PushPowerIntoOperStack(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void PushIntoOperStackAndCalc(Stack_t *num_stack, Stack_t *oper_stack, event_t event);
void PushPowerParenIntoOperStack(Stack_t *num_stack, Stack_t *oper_stack, 
                                event_t event);

typedef double (*calc_func_t)(double d1, double d2);
double Addition(double d1, double d2);
double Subtraction(double d1, double d2);
double Multiplication(double d1, double d2);
double Division(double d1, double d2);
double Power(double d1, double d2);

void InitTables();

/* states */
state_t end_state              = {success, CalculateEND};
state_t close_brackets_state   = {wait_for_oper_close, CalculateParen};
state_t open_brackets_state    = {wait_for_num_open, PushPowerParenIntoOperStack};
state_t waiting_for_oper_state = {wait_for_num_open, PushIntoOperStack};
state_t waiting_for_num_state  = {wait_for_oper_close, PushIntoNumStack};
state_t power_state            = {wait_for_num_open, PushPowerParenIntoOperStack};
state_t err_state              = {failure, InputError};


/* error messages */



#endif
