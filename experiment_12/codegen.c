#include <stdio.h>
#include <string.h>

#define MAX 20

char tac[MAX][20];
int n;

FILE *fp;

// Generate assembly code
void generate_code() {
    int reg = 0;

    printf("\nGenerated Code:\n");
    fprintf(fp, "\nGenerated Code:\n");

    for (int i = 0; i < n; i++) {
        char result, arg1, op, arg2;

        // Parse TAC like: t1=a+b
        result = tac[i][0];
        arg1  = tac[i][3];
        op    = tac[i][4];
        arg2  = tac[i][5];

        printf("MOV R%d, %c\n", reg, arg1);
        printf("%s R%d, %c\n",
               (op == '+') ? "ADD" :
               (op == '-') ? "SUB" :
               (op == '*') ? "MUL" : "DIV",
               reg, arg2);

        fprintf(fp, "MOV R%d, %c\n", reg, arg1);
        fprintf(fp, "%s R%d, %c\n",
                (op == '+') ? "ADD" :
                (op == '-') ? "SUB" :
                (op == '*') ? "MUL" : "DIV",
                reg, arg2);

        reg++;
    }
}

int main() {
    fp = fopen("output.txt", "w");

    printf("Enter number of TAC instructions: ");
    scanf("%d", &n);

    printf("Enter TAC (e.g., t1=a+b):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", tac[i]);
    }

    generate_code();

    fclose(fp);

    printf("\nOutput saved to output.txt ✅\n");

    return 0;
}