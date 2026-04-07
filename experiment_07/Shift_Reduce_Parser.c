#include <stdio.h>
#include <string.h>

char stack[50];
char input[50];
int top = -1;
int i = 0;

FILE *fp; // File pointer

void write_output(char *action) {
    fprintf(fp, "%s\t%s\t%s\n", stack, input + i, action);
}

void shift() {
    top++;
    stack[top] = input[i];
    stack[top + 1] = '\0';
    i++;

    printf("%s\t%s\tShift\n", stack, input + i);
    write_output("Shift");
}

void reduce() {
    // Rule: E -> id
    if (stack[top] == 'd' && stack[top - 1] == 'i') {
        stack[top - 1] = 'E';
        top--;
        printf("%s\t%s\tReduce: E->id\n", stack, input + i);
        write_output("Reduce: E->id");
    }

    // Rule: E -> E+E
    else if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
        stack[top - 2] = 'E';
        top -= 2;
        printf("%s\t%s\tReduce: E->E+E\n", stack, input + i);
        write_output("Reduce: E->E+E");
    }

    // Rule: E -> E*E
    else if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '*' && stack[top - 2] == 'E') {
        stack[top - 2] = 'E';
        top -= 2;
        printf("%s\t%s\tReduce: E->E*E\n", stack, input + i);
        write_output("Reduce: E->E*E");
    }

    // Rule: E -> (E)
    else if (top >= 2 && stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(') {
        stack[top - 2] = 'E';
        top -= 2;
        printf("%s\t%s\tReduce: E->(E)\n", stack, input + i);
        write_output("Reduce: E->(E)");
    }
}

int main() {
    fp = fopen("output.txt", "w"); // Open file

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter input string (use 'id' for identifier): ");
    scanf("%s", input);

    printf("\nStack\tInput\tAction\n");
    fprintf(fp, "Stack\tInput\tAction\n");

    while (1) {
        shift();

        while (1) {
            int old_top = top;
            reduce();
            if (old_top == top)
                break;
        }

        if (stack[0] == 'E' && stack[1] == '\0' && input[i] == '\0') {
            printf("%s\t%s\tAccept\n", stack, input + i);
            write_output("Accept");
            break;
        }

        if (input[i] == '\0')
            break;
    }

    fclose(fp); // Close file

    printf("\nOutput saved to output.txt file ✅\n");

    return 0;
}