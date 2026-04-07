#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

FILE *fp;

// Stack operations
void push(char x) {
    stack[++top] = x;
}

char pop() {
    return stack[top--];
}

int priority(char x) {
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/') return 2;
    return 0;
}

// Reverse string
void reverse(char exp[]) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(exp) - 1; i < j; i++, j--) {
        temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
    }
}

// Infix → Postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char x;

    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while ((x = pop()) != '(')
                postfix[k++] = x;
        } else {
            while (top != -1 && priority(stack[top]) >= priority(infix[i]))
                postfix[k++] = pop();
            push(infix[i]);
        }
    }

    while (top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
}

// Infix → Prefix
void infixToPrefix(char infix[], char prefix[]) {
    char rev[MAX], temp[MAX];

    strcpy(rev, infix);
    reverse(rev);

    for (int i = 0; rev[i]; i++) {
        if (rev[i] == '(') rev[i] = ')';
        else if (rev[i] == ')') rev[i] = '(';
    }

    top = -1;
    infixToPostfix(rev, temp);

    reverse(temp);
    strcpy(prefix, temp);
}

int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];

    fp = fopen("output.txt", "w");

    printf("Enter Infix Expression: ");
    scanf("%s", infix);

    top = -1;
    infixToPostfix(infix, postfix);

    top = -1;
    infixToPrefix(infix, prefix);

    printf("\nPostfix Expression: %s\n", postfix);
    printf("Prefix Expression : %s\n", prefix);

    fprintf(fp, "Infix   : %s\n", infix);
    fprintf(fp, "Postfix : %s\n", postfix);
    fprintf(fp, "Prefix  : %s\n", prefix);

    fclose(fp);

    printf("\nOutput saved to output.txt ✅\n");

    return 0;
}