#include <stdio.h>
#include <string.h>

// Function to build LPS (Longest Prefix Suffix) array
void buildLPS(char *pat, int m, int lps[]) {
    int len = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
int KMPSearch(char *text, char *pat) {
    int n = strlen(text);
    int m = strlen(pat);

    int lps[m];
    buildLPS(pat, m, lps);

    int i = 0; // index for text
    int j = 0; // index for pat

    while (i < n) {
        if (pat[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            return i - j;  // Mutation found at this index
        } else if (i < n && pat[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }

    return -1; // No mutation found
}

int main() {
    char dna[200], mutation[50];

    printf("Enter DNA sequence: ");
    scanf("%s", dna);

    printf("Enter mutation pattern: ");
    scanf("%s", mutation);

    int index = KMPSearch(dna, mutation);

    if (index != -1)
        printf("Mutation found at position %d\n", index);
    else
        printf("No mutation detected.\n");

    return 0;
}