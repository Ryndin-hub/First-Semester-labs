#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int pop(int *stack){
    if (stack[0] == 0){
        printf("syntax error");
        exit(1);
    }
    return stack[stack[0]--];
}

void push(int *stack, int a){
    stack[++stack[0]] = a;
}

int top(int *stack){
    return stack[stack[0]];
}

int priority(char ch){
    switch (ch){
        case '=': return 1;
        case '(': return 2;
        case ')': return 3;
        case '+': return 4;
        case '-': return 4;
        case '*': return 5;
        case '/': return 5;
    }
    return 0;
}

int wrongInput(int a, int b){
    if (b >= '0' && b <= '9' && (a == ')' || a == '=')) return 1;
    if (b == '(' && ((a >= '0' && a <='9') || a == ')' || a == '=')) return 1;
    if ((b == ')' || b == '+' || b == '-' || b == '*' || b == '/' || b == '=') && (a == '(' || a == '+' || a == '-' || a == '*' || a == '/' || a == '=')) return 1;
    return 0;
}

void pushOp(char op, int *stack_num, int *stack_op){
    while (priority(op) <= priority(top(stack_op))){
        int b = pop(stack_num);
        int a = pop(stack_num);
        switch (pop(stack_op)){
            case '+':
                push(stack_num, a + b);
                break;
            case '-':
                push(stack_num, a - b);
                break;
            case '*':
                push(stack_num, a * b);
                break;
            case '/':
                if (b == 0){
                    printf("division by zero");
                    exit(2);
                }
                push(stack_num, a / b);
                break;
        }
    }
}

int calculator(char *input){
    int stack_num[1001] = {0}, stack_op[1001] = {0};
    int len, num, i = 0, countBr = 0;
    len = strlen(input);
    input[len] = '=';
    while (i <= len){
        if (i > 0 && wrongInput(input[i-1],input[i]) == 1){
            printf("syntax error");
            exit(1);
        }
        if (input[i] >= '0' && input[i] <= '9'){
            num = 0;
            while (input[i] >= '0' && input[i] <= '9'){
                num = num * 10 + (int) input[i] - (int) '0';
                i++;
            }
            push(stack_num, num);
        } else if (input[i] == '=' || input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '(' || input[i] == ')'){
            if (input[i] != '('){
                pushOp(input[i], stack_num, stack_op);
            } else {
                countBr++;
            }
            if (input[i] == ')'){
                pop(stack_op);
                countBr--;
            } else {
                push(stack_op, (int) input[i]);
            }
            i++;
        } else {
            printf("syntax error");
            exit(1);
        }
    }
    if (countBr != 0){
        printf("syntax error");
        exit(1);
    }
    return pop(stack_num);
}

int main(void){
    char input[1001];
    if (scanf("%1000[^\n]s", input) != 1){
        printf("syntax error");
        return 1;
    }
    printf("%d", calculator(input));
    return 0;
}
