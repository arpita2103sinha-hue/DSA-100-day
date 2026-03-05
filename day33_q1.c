#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char x){
    stack[++top] = x;
}

char pop(){
    return stack[top--];
}

int priority(char x){
    if(x=='+' || x=='-')
        return 1;
    if(x=='*' || x=='/')
        return 2;
    return 0;
}

int main(){
    char infix[100], postfix[100];
    int i, j=0;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    for(i=0; infix[i] != '\0'; i++){
        char c = infix[i];

        if(isalnum(c))
            postfix[j++] = c;

        else if(c == '(')
            push(c);

        else if(c == ')'){
            while(stack[top] != '(')
                postfix[j++] = pop();
            pop();
        }

        else{
            while(top!=-1 && priority(stack[top]) >= priority(c))
                postfix[j++] = pop();
            push(c);
        }
    }

    while(top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';

    printf("Postfix expression: %s", postfix);

    return 0;
}
