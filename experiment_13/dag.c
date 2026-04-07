#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

struct node {
    char op;
    char left[5];
    char right[5];
    char result[5];
} dag[MAX];

int node_count = 0;
FILE *fp;

// Check if node already exists (common subexpression)
int find_node(char op, char *left, char *right) {
    for (int i = 0; i < node_count; i++) {
        if (dag[i].op == op &&
            strcmp(dag[i].left, left) == 0 &&
            strcmp(dag[i].right, right) == 0) {
            return i;
        }
    }
    return -1;
}

// Add node
int add_node(char op, char *left, char *right) {
    int index = find_node(op, left, right);

    if (index != -1)
        return index;

    dag[node_count].op = op;
    strcpy(dag[node_count].left, left);
    strcpy(dag[node_count].right, right);

    sprintf(dag[node_count].result, "t%d", node_count);

    return node_count++;
}

// Build DAG from postfix expression
void build_dag(char *expr) {
    char stack[MAX][5];
    int top = -1;

    for (int i = 0; expr[i]; i++) {
        if (isalnum(expr[i])) {
            char temp[5];
            sprintf(temp, "%c", expr[i]);
            strcpy(stack[++top], temp);
        } else {
            char right[5], left[5];
            strcpy(right, stack[top--]);
            strcpy(left, stack[top--]);

            int idx = add_node(expr[i], left, right);
            strcpy(stack[++top], dag[idx].result);
        }
    }
}

// Print DAG
void print_dag() {
    printf("\nDAG Nodes:\n");
    printf("Op\tLeft\tRight\tResult\n");

    fprintf(fp, "\nDAG Nodes:\n");
    fprintf(fp, "Op\tLeft\tRight\tResult\n");

    for (int i = 0; i < node_count; i++) {
        printf("%c\t%s\t%s\t%s\n",
               dag[i].op,
               dag[i].left,
               dag[i].right,
               dag[i].result);

        fprintf(fp, "%c\t%s\t%s\t%s\n",
                dag[i].op,
                dag[i].left,
                dag[i].right,
                dag[i].result);
    }
}

int main() {
    char expr[50];

    fp = fopen("output.txt", "w");

    printf("Enter expression (Postfix): ");
    scanf("%s", expr);

    build_dag(expr);
    print_dag();

    fclose(fp);

    printf("\nOutput saved to output.txt ✅\n");

    return 0;
}