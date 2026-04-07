#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char grammar[MAX][MAX];
char items[MAX][MAX][MAX];
int n, states = 0;

FILE *fp;

// Add dot at beginning
void add_dot(char *dest, char *src) {
    dest[0] = src[0];
    dest[1] = '=';
    dest[2] = '.';
    strcpy(dest + 3, src + 2);
}

// Closure function
void closure(char itemset[MAX][MAX], int *count) {
    for (int i = 0; i < *count; i++) {
        char *dot = strchr(itemset[i], '.');
        if (dot && isupper(*(dot + 1))) {
            char symbol = *(dot + 1);

            for (int j = 0; j < n; j++) {
                if (grammar[j][0] == symbol) {
                    char new_item[MAX];
                    add_dot(new_item, grammar[j]);

                    int exists = 0;
                    for (int k = 0; k < *count; k++) {
                        if (strcmp(itemset[k], new_item) == 0)
                            exists = 1;
                    }

                    if (!exists) {
                        strcpy(itemset[*count], new_item);
                        (*count)++;
                    }
                }
            }
        }
    }
}

// Move dot (GOTO)
void move_dot(char *dest, char *src) {
    strcpy(dest, src);
    char *dot = strchr(dest, '.');
    char temp = dot[1];
    dot[1] = '.';
    dot[0] = temp;
}

// Print item set
void print_items(char itemset[MAX][MAX], int count, int state) {
    printf("\nI%d:\n", state);
    fprintf(fp, "\nI%d:\n", state);

    for (int i = 0; i < count; i++) {
        printf("%s\n", itemset[i]);
        fprintf(fp, "%s\n", itemset[i]);
    }
}

int main() {
    fp = fopen("output.txt", "w");

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter grammar (E=E+T format):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", grammar[i]);
    }

    // Initial state I0
    int count = 0;
    add_dot(items[0][count++], grammar[0]);

    closure(items[0], &count);
    print_items(items[0], count, 0);

    fclose(fp);

    printf("\nOutput saved to output.txt ✅\n");

    return 0;
}