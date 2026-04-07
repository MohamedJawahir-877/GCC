#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char productions[MAX][MAX];
char leading[MAX][MAX], trailing[MAX][MAX];
int n;

FILE *fp;

// Utility: check if already present
int contains(char *arr, char c) {
    for (int i = 0; arr[i]; i++)
        if (arr[i] == c)
            return 1;
    return 0;
}

// Add to set
void add(char *arr, char c) {
    if (!contains(arr, c)) {
        int len = strlen(arr);
        arr[len] = c;
        arr[len + 1] = '\0';
    }
}

// Compute LEADING
void compute_leading(int i) {
    char *prod = productions[i];

    for (int j = 2; prod[j] != '\0'; j++) {
        if (!isupper(prod[j])) {
            add(leading[i], prod[j]);
            break;
        } else {
            int k;
            for (k = 0; k < n; k++) {
                if (productions[k][0] == prod[j])
                    compute_leading(k);
            }
            for (k = 0; leading[k][0]; k++)
                add(leading[i], leading[k][0]);
        }
    }
}

// Compute TRAILING
void compute_trailing(int i) {
    char *prod = productions[i];
    int len = strlen(prod);

    for (int j = len - 1; j >= 2; j--) {
        if (!isupper(prod[j])) {
            add(trailing[i], prod[j]);
            break;
        } else {
            int k;
            for (k = 0; k < n; k++) {
                if (productions[k][0] == prod[j])
                    compute_trailing(k);
            }
            for (k = 0; trailing[k][0]; k++)
                add(trailing[i], trailing[k][0]);
        }
    }
}

int main() {
    fp = fopen("output.txt", "w");

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (E=E+T format):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", productions[i]);
        leading[i][0] = '\0';
        trailing[i][0] = '\0';
    }

    // Compute LEADING
    for (int i = 0; i < n; i++)
        compute_leading(i);

    // Compute TRAILING
    for (int i = 0; i < n; i++)
        compute_trailing(i);

    printf("\nLEADING:\n");
    fprintf(fp, "LEADING:\n");
    for (int i = 0; i < n; i++) {
        printf("%c: %s\n", productions[i][0], leading[i]);
        fprintf(fp, "%c: %s\n", productions[i][0], leading[i]);
    }

    printf("\nTRAILING:\n");
    fprintf(fp, "\nTRAILING:\n");
    for (int i = 0; i < n; i++) {
        printf("%c: %s\n", productions[i][0], trailing[i]);
        fprintf(fp, "%c: %s\n", productions[i][0], trailing[i]);
    }

    fclose(fp);

    printf("\nOutput saved to output.txt ✅\n");

    return 0;
}