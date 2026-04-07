#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char input[50];
char op_stack[MAX];
int top = -1;

char operators[] = "+-*/";

// TAC storage
char tac[20][20];
int tac_index = 0;

FILE *fp;

// Check precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Generate temp variable
char getTemp(int i) {
    return 'A' + i;  // A, B, C...
}

// Generate TAC
void generate_TAC() {
    char stack[50];
    int top2 = -1;

    for (int i = 0; input[i] != '\0'; i++) {
        if (isalnum(input[i])) {
            stack[++top2] = input[i];
        } else {
            char op = input[i];
            char op2 = stack[top2--];
            char op1 = stack[top2--];

            char temp = getTemp(tac_index);

            sprintf(tac[tac_index], "%c=%c%c%c", temp, op1, op, op2);

            stack[++top2] = temp;
            tac_index++;
        }
    }
}

// Print Quadruple
void print_quadruple() {
    printf("\nQuadruple:\n");
    printf("Op\tArg1\tArg2\tResult\n");
    fprintf(fp, "\nQuadruple:\nOp\tArg1\tArg2\tResult\n");

    for (int i = 0; i < tac_index; i++) {
        char res = tac[i][0];
        char arg1 = tac[i][2];
        char op = tac[i][3];
        char arg2 = tac[i][4];

        printf("%c\t%c\t%c\t%c\n", op, arg1, arg2, res);
        fprintf(fp, "%c\t%c\t%c\t%c\n", op, arg1, arg2, res);
    }
}

// Print Triple
void print_triple() {
    printf("\nTriple:\n");
    printf("Index\tOp\tArg1\tArg2\n");
    fprintf(fp, "\nTriple:\nIndex\tOp\tArg1\tArg2\n");

    for (int i = 0; i < tac_index; i++) {
        char arg1 = tac[i][2];
        char op = tac[i][3];
        char arg2 = tac[i][4];

        printf("%d\t%c\t%c\t%c\n", i, op, arg1, arg2);
        fprintf(fp, "%d\t%c\t%c\t%c\n", i, op, arg1, arg2);
    }
}

// Print Indirect Triple
void print_indirect() {
    printf("\nIndirect Triple:\n");
    fprintf(fp, "\nIndirect Triple:\n");

    for (int i = 0; i < tac_index; i++) {
        printf("Pointer %d -> %d\n", i, i);
        fprintf(fp, "Pointer %d -> %d\n", i, i);
    }
}

int main() {
    fp = fopen("output.txt", "w");

    printf("Enter expression (Postfix format): ");
    scanf("%s", input);

    generate_TAC();

    printf("\nThree Address Code:\n");
    fprintf(fp, "Three Address Code:\n");

    for (int i = 0; i < tac_index; i++) {
        printf("%s\n", tac[i]);
        fprintf(fp, "%s\n", tac[i]);
    }

    print_quadruple();
    print_triple();
    print_indirect();

    fclose(fp);

    printf("\nOutput saved to output.txt ✅\n");

    return 0;
}