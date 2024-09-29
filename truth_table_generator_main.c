#include "truth_table_generator.h"

int main(int argc, char*argv[]) {
    int variable_count = 0;
    char *expression = malloc(sizeof(char) * BUFFER_SIZE);
    if(!expression) {
        perror("expression malloc failed: ");
        exit(EXIT_FAILURE);
    }
   // char* expression_copy = malloc(sizeof(char) * BUFFER_SIZE);
    // if(!expression) {
    //     perror("expression malloc failed: ");
    //     exit(EXIT_FAILURE);
    // }
    if(argc < 2) {
        printf("Enter Boolean expression: ");
        fgets(expression,BUFFER_SIZE - 2,stdin);
        remove_newline(expression);
    }
    else {
        for(int i = 1;i < argc;i++) {
            strcat(expression,argv[i]);
        }
    }
    if(strlen(expression) < 0) {
        printf("no expression was inputed\n");
        exit(EXIT_FAILURE);
    }
    // if(scope_function(expression_copy)) {

    // }
    // my_isspace(expression);
    // printf("expression: %s",expression);

    // popoxakanneri verlucutyun
    Variable *variables = malloc(sizeof(Variable) * BUFFER_SIZE);
    if(!variables) {
        perror("variable malloc failed: ");
        exit(EXIT_FAILURE);
    }
    variables_found(variables,&variable_count,expression);
    variables = realloc(variables,variable_count * sizeof(Variable));
    variables_fill(variables,variable_count);
    Operand *operands = malloc(sizeof(Operand) * BUFFER_SIZE);
    if(!operands) {
        perror("operands malloc failed: ");
        exit(EXIT_FAILURE);
    }
    
    Temporary_Variable *temp = malloc(sizeof(Temporary_Variable) * BUFFER_SIZE);
    if(!temp) {
        perror("temp malloc faileD: ");
        exit(EXIT_FAILURE);
    }    
    //operator error check
    unknown_operator_error_check(expression);
    my_isspace(expression);
    int operand_count = operands_found(operands,expression);
    operands = realloc(operands,operand_count * sizeof(Operand));


    priority_queue(operands,operand_count);
   
    //my_isspace(expression);
     
    int tmp_count = 0;
    for(int i = 0;i < operand_count;i++) {
        logic(operands[i],expression,operand_count,variable_count,variables,temp,&tmp_count);
        my_isspace(expression);
        
    }
    //int *arr = malloc(sizeof(int)*BUFFER_SIZE);
//    for(int i = 0;i < variable_count;i++) {
         
//             if (expression[0] == variables[i].name){
//                binary_function(arr,variables[i].value);
//             }
//     }
//     for(int i = 0;i < tmp_count;i++) {
         
//             if (expression[0] == temp[i].name){
//                 binary_function(arr,temp[i].value);
//             }
//     }
    print(expression,variable_count,variables,temp,tmp_count);
    free(operands);
    free(variables);
    free(expression);
    return 0;
}