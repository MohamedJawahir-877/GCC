#include <stdio.h>
#include <string.h>

#define MAX 10

int stack[MAX];
int top = -1;

FILE *fp;

// PUSH operation
void push(int val) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        fprintf(fp, "Stack Overflow\n");
        return;
    }
    stack[++top] = val;
    printf("PUSH %d\n", val);
    fprintf(fp, "PUSH %d\n", val);
}

// POP operation
void pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        fprintf(fp, "Stack Underflow\n");
        return;
    }
    printf("POP %d\n", stack[top]);
    fprintf(fp, "POP %d\n", stack[top]);
    top--;
}

// Display stack
void display() {
    printf("Stack: ");
    fprintf(fp, "Stack: ");

    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
        fprintf(fp, "%d ", stack[i]);
    }
    printf("\n");
    fprintf(fp, "\n");
}

int main() {
    int choice, val;

    fp = fopen("output.txt", "w");

    do {
        printf("\n1. PUSH\n2. POP\n3. DISPLAY\n4. EXIT\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                push(val);
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting...\n");
                fprintf(fp, "Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
                fprintf(fp, "Invalid choice\n");
        }

    } while (choice != 4);

    fclose(fp);

    printf("\nOutput saved to output.txt ✅\n");

    return 0;
}