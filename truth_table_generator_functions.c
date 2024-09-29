
#include "truth_table_generator.h"
char operators[] = {'|', '&', '^', '!', ' ', '(', ')'};
int op_size = sizeof(operators) / sizeof(operators[0]);
void remove_newline(char *str) {
    int len = strlen(str);
    if(len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void variables_found(Variable *dest, int *count, char *source) {
    int index = 0;
    while (*source) {
        if ((*source >= 'A' && *source <= 'Z') || (*source >= 'a' && *source <= 'z')) {
            int is_unique = 1;
            for (int i = 0; i < index; i++) {
                if (*source == dest[i].name) {
                    is_unique = 0;
                    break;
                }
            }
            if (is_unique) {
                dest[index++].name = *source;
                (*count)++;
            }
        }
        source++;
    }
}


void unknown_operator_error_check(char *expression) { 

    while (*expression) {
        if ((*expression < 'A' || *expression > 'Z') && (*expression < 'a' || *expression > 'z')) {
            int is_valid_operator = 0;  
            for (int i = 0; i < op_size; i++) {
                if (*expression == operators[i]) {
                    is_valid_operator = 1; 
                    break;
                }
            }
            if (!is_valid_operator) {
                printf("Unknown operator: %c\n", *expression);
                exit(EXIT_FAILURE);
            }
        }
        expression++;
    }
}

int operands_found(Operand *operands,char *expression) {
    int size = strlen(expression);
    int count = 0;
    for(int i = 0;i < size;i++) {
        for(int j = 0;j < op_size - 3;j++) {        // dont compare with ' ', '(', ')'
            if(expression[i] == operators[j]) {
                operands[count].operand = expression[i];
                operands[count].position = i;
                count++;
            }
        }
    }
    return count;
}
void swap(char *a, char *b){
  char tmp = *a;
  *a = *b;
  *b = tmp;
}
void my_isspace(char* str) {
  int j = 0;
  int index = 0;
    int size = strlen(str);
  while(j < size){
    index = 0;
    for(int i = 0; str[i] != '\n'; i++) {
      if(str[i] == ' '){
        index = i;
        break;
      }
    }
    for(int i = index; str[i] != '\n'; i++) {
      if(str[i] != ' '){
        swap(&str[index], &str[i]);
        break;
      }
    }
    j++;
  }
}
void swap_struct(Operand *a, Operand *b) {
    Operand temp = *a;
    *a = *b;
    *b = temp;
}
void priority_queue(Operand *operands, int count) {
    int start = 0;  
    for (int i = 0; i < count; i++) {
        if (operands[i].operand == '!') {
            swap_struct(&operands[start], &operands[i]);
            start++;
        }
    }
    for (int i = 0; i < count; i++) {
        if (operands[i].operand == '&') {
            swap_struct(&operands[start], &operands[i]);
            start++;
        }
    }
    for (int i = 0; i < count; i++) {
        if (operands[i].operand == '^') {
            swap_struct(&operands[start], &operands[i]);
            start++;
        }
    }
    for (int i = 0; i < count; i++) {
        if (operands[i].operand == '|') {
            swap_struct(&operands[start], &operands[i]);
            start++;
        }
    }
}
int scope_function(char *expression) {
    int size = strlen(expression);
    int start_position = -1;
    int end_position = -1;
    for (int i = 0; i < size; i++) {
        if (expression[i] == '(') {
            start_position = i;
        } else if (expression[i] == ')' && start_position != -1) {
            end_position = i;
            break; 
        }
        
    }

    if (start_position != -1 && end_position != -1) {
        for (int i = start_position; i <= end_position; i++) {
            printf("%c", expression[i]);
        }
        printf("\n");
    puts(expression);
        return 1;
    }
    else {
        return 0;
    }

}

void variables_fill(Variable *variables, int count) {
    int num = 2;
    int index = 0;
    for (int i = 1; i < pow(2, count); i *= 2) {
        variables[index].value = (((int)pow(2, i) - 1) << num) | ((int)pow(2, i) - 1);
        for (int j = 0; j < ((pow(2, count) / num)); j++) { 
            if (j == (pow(2, count) / num) - 1) {
                variables[index].value >>= i;
                break;
            }
            variables[index].value = variables[index].value << num;
            variables[index].value |= ((int)pow(2, i) - 1);
        }
        num *= 2;
        index++;
    }

}
    
void swap_integer(int *a,int * b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}
void binary_function(int num){
  int res,ssd;
  int arr[COUNT];
  int i = 0;
  while(num != 0){
    ssd = num % 2;
    arr[i] = ssd;
    num /= 2;
    ++i;
    
  }
    printf("Result: \n");
  for (int j = 0;j < i;j++){
    printf(" %d\n", arr[j]);
  }printf("\n");

}
void logic(Operand operands, char *expression, int operand_count, int variable_count, Variable *variables, Temporary_Variable *temp,int *temp_count) {
    
    char name1, name2;

    switch (operands.operand) {
        case '!': {
            name1 = expression[operands.position + 1];
            for (int j = 0; j < variable_count; j++) {
                if (variables[j].name == name1) {
                    temp[*temp_count].name = '$';
                    temp[*temp_count].value = ~variables[j].value;
                    expression[operands.position] = '$';
                    expression[operands.position + 1] = ' ';
                    *temp_count++;
                    break;
                }
            }
            break;
        }
        case '&': {
            name1 = expression[operands.position - 1];
            name2 = expression[operands.position + 1];
            int value1 = 0, value2 = 0;
            int found1 = 0, found2 = 0;

            for (int j = 0; j < variable_count; j++) {
                if (variables[j].name == name1) {
                    value1 = variables[j].value;
                    found1 = 1;
                    break;
                }
            }
            if (!found1) {
                for (int j = 0; j < *temp_count; j++) {
                    if (temp[j].name == name1) {
                        value1 = temp[j].value;
                        found1 = 1;
                        break;
                    }
                }
            }

            for (int j = 0; j < variable_count; j++) {
                if (variables[j].name == name2) {
                    value2 = variables[j].value;
                    found2 = 1;
                    break;
                }
            }
            if (!found2) {
                for (int j = 0; j < *temp_count; j++) {
                    if (temp[j].name == name2) {
                        value2 = temp[j].value;
                        found2 = 1;
                        break;
                    }
                }
            }

            if (found1 && found2) {
                temp[*temp_count].value = (value1 & value2);
                temp[*temp_count].name = '*';
                expression[operands.position - 1] = ' ';
                expression[operands.position] = ' ';
                expression[operands.position + 1] = temp[*temp_count].name;
                (*temp_count)++;
            }
            break;
        }
        case '|': {
            name1 = expression[operands.position - 1];
            name2 = expression[operands.position + 1];
            int value1 = 0, value2 = 0;
            int found1 = 0, found2 = 0;

            for (int j = 0; j < variable_count; j++) {
                if (variables[j].name == name1) {
                    value1 = variables[j].value;
                    found1 = 1;
                    break;
                }
            }
            if (!found1) {
                for (int j = 0; j < *temp_count; j++) {
                    if (temp[j].name == name1) {
                        value1 = temp[j].value;
                        found1 = 1;
                        break;
                    }
                }
            }

            for (int j = 0; j < variable_count; j++) {
                if (variables[j].name == name2) {
                    value2 = variables[j].value;
                    found2 = 1;
                    break;
                }
            }
            if (!found2) {
                for (int j = 0; j < *temp_count; j++) {
                    if (temp[j].name == name2) {
                        value2 = temp[j].value;
                        found2 = 1;
                        break;
                    }
                }
            }

            if (found1 && found2) {
                temp[*temp_count].value = (value1 | value2);   
                temp[*temp_count].name = 'T';                  
                expression[operands.position - 1] = ' ';
                expression[operands.position] = ' ';
                expression[operands.position + 1] = temp[*temp_count].name; 
                (*temp_count)++;
            }
            break;
        }

        case '^': {
            name1 = expression[operands.position - 1];
            name2 = expression[operands.position + 1];
            int value1 = 0, value2 = 0;
            int found1 = 0, found2 = 0;

            
            for (int j = 0; j < variable_count; j++) {
                if (variables[j].name == name1) {
                    value1 = variables[j].value;
                    found1 = 1;
                    break;
                }
            }
            if (!found1) {
                for (int j = 0; j < *temp_count; j++) {
                    if (temp[j].name == name1) {
                        value1 = temp[j].value;
                        found1 = 1;
                        break;
                    }
                }
            }

            
            for (int j = 0; j < variable_count; j++) {
                if (variables[j].name == name2) {
                    value2 = variables[j].value;
                    found2 = 1;
                    break;
                }
            }
            if (!found2) {
                for (int j = 0; j < *temp_count; j++) {
                    if (temp[j].name == name2) {
                        value2 = temp[j].value;
                        found2 = 1;
                        break;
                    }
                }
            }

            
            if (found1 && found2) {
                
                temp[*temp_count].value = (value1 ^ value2);
                temp[*temp_count].name = '#';  
                expression[operands.position - 1] = ' ';
                expression[operands.position] = ' ';
                expression[operands.position + 1] = temp[*temp_count].name;
                (*temp_count)++;
            }
            break;
        }

        default:
            break;
    }
}
void print_bits(int value, int bit_size,int **truth_table,int row) {
    int *bit = malloc(sizeof(int) * bit_size);
    if(!bit) {
        perror("bit malloc failed: ");
        exit(EXIT_FAILURE);
    }
    for (int i = bit_size - 1; i >= 0; i--) {
         bit[i]= (value >> i) & 1;
       
    }

    for(int i = 0;i < bit_size;i++) {
        truth_table[i][row] = bit[i];
    } 
}

void print(char *expression, int variable_count, Variable *variables, Temporary_Variable *temp, int temp_count) {
    printf("----------------------\n");
    printf("|");
    for (int i = 0; i < variable_count; i++) {
        printf(" %c\t|", variables[i].name); 
    }
    printf(" Result |\n");
    printf("----------------------\n");
    int row = variable_count + 1;
    int num_combinations = pow(2, variable_count);
    int **truth_table = malloc(sizeof(int*) * num_combinations);
    if(!truth_table) {
        perror("truth table malloc failed: ");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i < num_combinations;i++) {
        truth_table[i] = malloc(sizeof(int) *row);
        if(!truth_table[i]) {
        perror("truth table malloc failed: ");
        exit(EXIT_FAILURE);
    }
    }
    int col = 0;
    for(int i = 0;i < variable_count;i++) { 
       print_bits(variables[i].value,num_combinations,truth_table,col);
       col++;
    }
    for(int i = 0;i < temp_count;i++) {
        if (expression[0] == temp[i].name){
            print_bits(temp[i].value,num_combinations,truth_table,col);
        }
    }
    for(int i = 0;i <num_combinations;i++) {
        for(int j = 0;j < row;j++) {
            printf("| %d\t",truth_table[i][j]);
        }

        printf("|\n");
    }
    printf("\n");
    printf("----------------------\n");
}
