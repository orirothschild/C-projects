/***********************************
*                                  *
*   APP - Calculator               *
*   written by: Hadar Klein        *
*   date:                          *
*   reviewed by:                   *
*                                  *
***********************************/

#include <stdio.h>   /* printf */
#include <assert.h>  /* assert */
#include <stdlib.h>  /* strtod */
#include <math.h>    /*  pow   */
#include <string.h>  /* strcat */

#include "stack.h"   /* API    */
#include "calc.h"    /* header */
#include "utils.h"   /* utils  */

#define INPUT_SIZE 50

state_t transitions[states][input_events] = {0};
int precedence_table[num_of_opers] = {0};
calc_func_t function_table[num_of_opers] = {0};
char paren_table[num_of_parentheses] = {0};
char *error_messages[num_of_errors] = {0};
state_func_t paren_error_table[num_of_opers] = {0};
state_func_t paren_end_error_table[num_of_opers] = {0};

static event_t GetInputFromUser(char *str);
static Stack_t *GetStacks(Stack_t *stack);

int main()
{
    event_t event ={0};
    Stack_t *num_stack = NULL;
    Stack_t *oper_stack = NULL;
    char *str = NULL;
    int current_state = wait_for_num_open;
    char hash = '#';

    str = (char *)malloc(INPUT_SIZE);
    
    event = GetInputFromUser(str);

    /* create the stacks */
    num_stack = GetStacks(NULL);
    oper_stack = GetStacks(num_stack);
    StackPush(oper_stack, &hash);

    /* create the LUTs */
    InitTables();

    /* run the state machine */
    while (current_state != success && current_state !=failure)
    {
        event = GetInput(event);
        
        transitions[current_state][event.event_enum]
        .calculator_func(num_stack, oper_stack, event);
        
        current_state = transitions[current_state][event.event_enum].next_state;
    }
    printf("\n\n");
    printf("final result is %f\n", *(double *)StackPeek(num_stack));

    StackDestroy(num_stack);
    StackDestroy(oper_stack);
    free(str);
    return 0;
}


static Stack_t *GetStacks(Stack_t *stack)
{
    Stack_t * new_stack = NULL;

    new_stack = StackCreate((INPUT_SIZE / 2), sizeof(double));
    if (NULL == new_stack)
    {
        StackDestroy(stack);
        exit(1);
    }

    return new_stack;
}


static event_t GetInputFromUser(char *input_str)
{
    event_t event = {0};
    char user_input[INPUT_SIZE] = {0};

    printf("Please enter a mathematical expression\n");
    fgets(user_input, INPUT_SIZE, stdin);
    strcpy(input_str, user_input);

    event.str = input_str;
    event.str_start = event.str;

    return event;
}


void InitTables()
{
    int i = 0;
    int j = 0;

    for (i = 0; i < states; ++i)
    {
        for (j = 0; j < input_events; ++j)
        {
            transitions[i][j] = err_state;
        }
    }

    transitions[wait_for_num_open][number_event] = waiting_for_num_state;
    transitions[wait_for_num_open][open_bracket_event] = open_brackets_state;
    transitions[wait_for_oper_close][oper_event] = waiting_for_oper_state;
    transitions[wait_for_oper_close][close_bracket_event] = close_brackets_state;
    transitions[wait_for_oper_close][power_event] = power_state;
    transitions[wait_for_oper_close][EOS_event] = end_state;

    precedence_table[hash] = 0;
    precedence_table[plus] = 2;
    precedence_table[minus] = 2;
    precedence_table[multi] = 3;
    precedence_table[divide] = 3;
    precedence_table[power] = 4;

    paren_table[close_round] = open_round;
    paren_table[close_squigle] = open_squigle;
    paren_table[close_bracket] = open_bracket;

    function_table[addition_func] = Addition;
    function_table[subtraction_func] = Subtraction;
    function_table[mulitplication_func] = Multiplication;
    function_table[division_func] = Division;
    function_table[power_func] = Power;

    error_messages[oper_num] = number_error;
    error_messages[num_oper] = operator_error;
    error_messages[oper_open] = open_error;
    error_messages[num_close] = close_error;
    error_messages[num_EOS] = EOS_error;
    error_messages[invalid_input] = invalid_input_error;
    error_messages[open_round] = invalid_paren_error;
    error_messages[open_bracket] = invalid_bracket_error;
    error_messages[open_squigle] = invalid_squigle_error;

    paren_error_table[hash] = InputError;
    paren_error_table[plus] = DoNothing;
    paren_error_table[minus] = DoNothing;
    paren_error_table[multi] = DoNothing;
    paren_error_table[divide] = DoNothing;
    paren_error_table[power] = DoNothing;
    
    paren_end_error_table[hash] = DoNothing;
    paren_end_error_table[plus] = DoNothing;
    paren_end_error_table[minus] = DoNothing;
    paren_end_error_table[multi] = DoNothing;
    paren_end_error_table[divide] = DoNothing;
    paren_end_error_table[power] = DoNothing;
    paren_end_error_table[open_round] = ParenInputError;
    paren_end_error_table[open_bracket] = ParenInputError;
    paren_end_error_table[open_squigle] = ParenInputError;
}


event_t GetInput(event_t event)
{
    char *curr_str = event.str;
    double result = 0;
    
    while(' ' == *event.str)
    {
        ++event.str;
        ++curr_str;
    }

    result = strtod(curr_str, &event.str);

    if (event.str != curr_str)
    {
        event.event_enum = number_event;
        event.input.num = result;
    }

    else
    {
        switch (*event.str)
        {
            case '(':
            case '{':
            case '[':
                event.event_enum = open_bracket_event;
                event.input.oper.precedence = 1;
                break;
            case ')':
            case '}':
            case ']':
                event.event_enum = close_bracket_event;
                event.input.oper.precedence = 5;
                break;
            case '+':
            case '-':
                event.event_enum = oper_event;
                event.input.oper.precedence = 2;
                break;
            case '*':
            case '/':
                event.event_enum = oper_event;
                event.input.oper.precedence = 3;
                break;
            case '^':
                event.event_enum = power_event;
                event.input.oper.precedence = 4;
                break;
            case '\n':
            case '\0':
                event.event_enum = EOS_event;
                return event;
            default:
                event.event_enum = invalid_input_event;
        }
        event.input.oper.token = *event.str;
        
        if (*event.str != '\0')
        {
            ++event.str;
        }
    }

    return event;
}


double Addition(double d1, double d2)
{
    return d2 + d1;
}


double Subtraction(double d1, double d2)
{
    return d2 - d1;
}


double Multiplication(double d1, double d2)
{
    return d2 * d1;
}


double Division(double d1, double d2)
{
    return d2 / d1;
}


double Power(double d1, double d2)
{
    return pow(d2, d1);
}


void PushIntoNumStack(Stack_t *num_stack, Stack_t *oper_stack, event_t event)
{
    (void)oper_stack;

    StackPush(num_stack, &event.input.num);
}


void PushPowerParenIntoOperStack(Stack_t *num_stack, Stack_t *oper_stack, 
                           event_t event)
{
    (void)num_stack;

    StackPush(oper_stack, &event.input.oper.token);
}


void PushIntoOperStack(Stack_t *num_stack, Stack_t *oper_stack, 
                      event_t event)
{
    while (precedence_table[(int)*(char *)StackPeek(oper_stack)] >=
           event.input.oper.precedence)
    {
        Calculate(num_stack, oper_stack, event);
    }
    
    StackPush(oper_stack, &event.input.oper.token);
}


void InputError(Stack_t *num_stack, Stack_t *oper_stack, event_t event)
{
    int event_num = event.event_enum;

    printf("Error: %s\n", error_messages[event_num]);
    
    StackDestroy(num_stack);
    StackDestroy(oper_stack);
    free(event.str_start);
    
    exit(1);
}


void ParenInputError(Stack_t *num_stack, Stack_t *oper_stack, event_t event)
{
    int oper = (int)*(char *)StackPeek(oper_stack);

    printf("Error: %s\n", error_messages[oper]);
    
    StackDestroy(num_stack);
    StackDestroy(oper_stack);
    free(event.str_start);
    
    exit(1);
}


void CalculateEND(Stack_t *num_stack, Stack_t *oper_stack, event_t event)
{
    int stack_oper = (int)*(char *)StackPeek(oper_stack);
    
    paren_end_error_table[stack_oper](num_stack, oper_stack, event);
    
        /* while (0 < precedence_table[(int)(*(char *)StackPeek(oper_stack))]) */
        while (0 < precedence_table[(int)(*(char *)StackPeek(oper_stack))])
        {
            Calculate(num_stack, oper_stack, event);
            stack_oper = *(char *)StackPeek(oper_stack);
            paren_end_error_table[stack_oper](num_stack, oper_stack, event);
        }
}


void CalculateParen(Stack_t *num_stack, Stack_t *oper_stack, event_t event)
{
    int input_paren = (int)event.input.oper.token;
    int stack_oper = (int)*(char *)StackPeek(oper_stack);

    while (stack_oper != paren_table[input_paren])
    {
        paren_error_table[stack_oper](num_stack, oper_stack, event);

        Calculate(num_stack, oper_stack, event);
        stack_oper = *(char *)StackPeek(oper_stack);
    }
    
    StackPop(oper_stack);
}


void Calculate(Stack_t *num_stack, Stack_t *oper_stack, event_t event)
{
    double d1 = 0;
    double d2 = 0;
    double d3 = 0;
    char oper = 0;
    (void)event;

    d1 = *(double *)StackPeek(num_stack);
    StackPop(num_stack);
    d2 = *(double *)StackPeek(num_stack);
    StackPop(num_stack);
    oper = *(char *)StackPeek(oper_stack);
    StackPop(oper_stack);

    d3 = function_table[(int)oper](d1, d2);

    StackPush(num_stack, &d3);
}


void DoNothing(Stack_t *num_stack, Stack_t *oper_stack, event_t event)
{
    (void)num_stack;
    (void)oper_stack;
    (void)event;
}