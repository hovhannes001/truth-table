#ifndef TRUTH_TABLE
#define TRUTH_TABLE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define BUFFER_SIZE 50
#define COUNT 26

typedef struct{
    char operand;
    int position;
}Operand;

typedef struct{
    char name;
    int value;
}Variable;
typedef struct{
    char name;
    int value;
}Temporary_Variable;
void remove_newline(char *str);
void variables_found(Variable *dest,int *count,char *source);
void unknown_operator_error_check(char *expression);
int operands_found(Operand *operands,char *expression);
void my_isspace(char* str) ;
void swap_struct(Operand *a, Operand *b);
void priority_queue(Operand *operands,int count);
int scope_function(char *expression);
void variables_fill(Variable *variables, int count) ;
void logic(Operand operands,char *expression,int operand_count,int variable_count,Variable *variables,Temporary_Variable *temp,int *temp_count);
void binary_function(int num);
void print(char *expression, int variable_count, Variable *variables, Temporary_Variable *temp,int temp_count);
#endif