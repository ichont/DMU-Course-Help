#include <stdio.h>

void main() {
    int i, j, k = 0;
    char cc[13];           // 'Y' indicates a page fault occurred, 'N' indicates no page fault
    int a[12] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}; // Page access sequence
    int b[3][13], c[13], p = 0;

    // Initialize the page table with undefined initial values
    b[0][0] = 0;  
    b[1][0] = 0;
    b[2][0] = 0;

    printf("     ");
    for (i = 0; i < 12; i++)
        printf("%6d", a[i]);
    printf("\n ============================================================================\n");

    for (i = 0; i < 12; i++) {
        if (a[i] == b[0][i] || a[i] == b[1][i] || a[i] == b[2][i]) {
            b[0][i + 1] = b[0][i];
            b[1][i + 1] = b[1][i];
            b[2][i + 1] = b[2][i];
            cc[i] = 'N'; // No page fault
        } else {
            if (i > 2) {
                c[p] = b[2][i]; // Record the page replacement sequence
                p++;
            }
            b[0][i + 1] = a[i];
            b[1][i + 1] = b[0][i];
            b[2][i + 1] = b[1][i];
            cc[i] = 'Y'; // Page fault occurred
            k = k + 1;
        }
    }

    for (j = 0; j < 13; j++)
        printf("%6d", b[0][j]);
    printf("\n ----------------------------------------------------------------------------\n");
    
    for (j = 0; j < 13; j++)
        printf("%6d", b[1][j]);
    printf("\n ----------------------------------------------------------------------------\n");
    
    for (j = 0; j < 13; j++)
        printf("%6d", b[2][j]);
    printf("\n ----------------------------------------------------------------------------\n");
    
    printf("     ");
    for (j = 0; j < 13; j++) {
        printf("    ");
        putchar(cc[j]);
    }

    printf("\nPage fault count: %3d\n", k);
    printf("Page replacement order: ");
    for (j = 0; j < p; j++)
        printf("%3d", c[j]);
    printf("\n\n");
}

