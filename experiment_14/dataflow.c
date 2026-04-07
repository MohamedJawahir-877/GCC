#include <stdio.h>
#include <string.h>

#define MAX 10

char blocks[MAX][50];
char gen[MAX][MAX], kill[MAX][MAX];
char in[MAX][MAX], out[MAX][MAX];

int n;
FILE *fp;

// Add to set
void add(char *set, char c) {
    if (!strchr(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

// Remove from set
void remove_var(char *set, char c) {
    char temp[MAX];
    int k = 0;
    for (int i = 0; set[i]; i++) {
        if (set[i] != c)
            temp[k++] = set[i];
    }
    temp[k] = '\0';
    strcpy(set, temp);
}

// Copy set
void copy(char *dest, char *src) {
    strcpy(dest, src);
}

// Compute GEN and KILL
void compute_gen_kill() {
    for (int i = 0; i < n; i++) {
        char var = blocks[i][0]; // LHS variable
        add(gen[i], var);

        for (int j = 0; j < n; j++) {
            if (i != j && blocks[j][0] == var)
                add(kill[i], var);
        }
    }
}

// Compute IN and OUT
void compute_in_out() {
    for (int i = 0; i < n; i++) {
        if (i == 0)
            strcpy(in[i], "");

        else
            copy(in[i], out[i - 1]);

        copy(out[i], in[i]);

        // OUT = GEN ∪ (IN - KILL)
        for (int j = 0; gen[i][j]; j++)
            add(out[i], gen[i][j]);

        for (int j = 0; kill[i][j]; j++)
            remove_var(out[i], kill[i][j]);
    }
}

// Print results
void print_results() {
    printf("\nBlock\tGEN\tKILL\tIN\tOUT\n");
    fprintf(fp, "\nBlock\tGEN\tKILL\tIN\tOUT\n");

    for (int i = 0; i < n; i++) {
        printf("B%d\t%s\t%s\t%s\t%s\n",
               i + 1, gen[i], kill[i], in[i], out[i]);

        fprintf(fp, "B%d\t%s\t%s\t%s\t%s\n",
                i + 1, gen[i], kill[i], in[i], out[i]);
    }
}

int main() {
    fp = fopen("output.txt", "w");

    printf("Enter number of blocks: ");
    scanf("%d", &n);

    printf("Enter statements (e.g., a=b+c):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", blocks[i]);
        gen[i][0] = kill[i][0] = in[i][0] = out[i][0] = '\0';
    }

    compute_gen_kill();
    compute_in_out();
    print_results();

    fclose(fp);

    printf("\nOutput saved to output.txt ✅\n");

    return 0;
}