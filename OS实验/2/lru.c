#include <stdio.h>

void max_value(int x, int cc[][2]);
// Function declaration: Handles page table updates
int r_algorithm(int cc[][2]);
// Function declaration: Page replacement algorithm
char cc[13];
// 'Y' indicates a page fault, 'N' indicates no page fault
void page_table(int page1, int c[5][2]);
// Prints the page table

void main()
{
    int i, j, page, row = 0, col = 1;
    // b[row][col]: Row/column pointers
    int k = 0;
    // Page fault counter
    int a[12] = {4, 3, 2, 1, 4, 3, 5, 4, 3, 2, 1, 5};
    // Page request sequence
    int b[3][13];
    // Simulated memory (3-page allocation)
    int c[5][2] = {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};
    // Page table initialization
    int d[13], p = 0;
    // Stores the page replacement sequence; p is the pointer for array d
    b[0][0] = 0;
    b[1][0] = 0;
    b[2][0] = 0;

    //*************** Page Replacement Logic ***************************************
    for (i = 0; i < 12; i++)
    {
        if (a[i] == b[0][i] || a[i] == b[1][i] || a[i] == b[2][i])
        {
            b[0][i + 1] = b[0][i]; // Copy previous column data to the next column
            b[1][i + 1] = b[1][i];
            b[2][i + 1] = b[2][i];
            max_value(a[i], c); // Update page table with current page access
            page_table(a[i], c); // Print page table
            cc[i] = 'N'; // No page fault
            col++;       // Move column pointer to the next column
        }
        else
        {
            // Page not in memory
            if (row > 2)
            {
                // No free memory slots
                page = r_algorithm(c); // Return the page to be replaced
                d[p] = page;           // Store the replaced page
                p++;
                k++; // Increment page fault counter
                b[0][i + 1] = b[0][i]; // Copy previous column data to the next column
                b[1][i + 1] = b[1][i];
                b[2][i + 1] = b[2][i];
                cc[i] = 'Y'; // Page fault occurred
                if (b[0][i + 1] == page)
                    b[0][i + 1] = a[i];
                if (b[1][i + 1] == page)
                    b[1][i + 1] = a[i];
                if (b[2][i + 1] == page)
                    b[2][i + 1] = a[i];
                max_value(a[i], c); // Update page table with current page access
                page_table(a[i], c); // Print page table
            }
            else
            {
                b[0][i + 1] = b[0][i]; // Copy previous column data to the next column
                b[1][i + 1] = b[1][i];
                b[2][i + 1] = b[2][i];
                cc[i] = 'Y'; // Page fault occurred
                b[row][col] = a[i]; // Insert page into memory
                max_value(a[i], c); // Update page table with current page access
                col++;
                k++; // Increment page fault counter
                row++;
                page_table(a[i], c); // Print page table
            }
        }
    }

    //================ Display Results ===========================================
    printf("\n    ");
    for (i = 0; i < 12; i++)
        printf("%6d", a[i]); // Display page request sequence

    printf("\n   =========================================================\n");
    for (j = 0; j < 13; j++)
        printf("%6d", b[0][j]);
    printf("\n   ----------------------------------------------------------\n");
    for (j = 0; j < 13; j++)
        printf("%6d", b[1][j]);
    printf("\n   ----------------------------------------------------------\n");
    for (j = 0; j < 13; j++)
        printf("%6d", b[2][j]);
    printf("\n   -----------------------------------------------------\n");

    printf("   ");
    for (j = 0; j < 13; j++)
    {
        printf("    ");
        putchar(cc[j]); // Display 'Y' or 'N' for page faults
    }

    printf("\nPage Fault Count: %4d\n", k);
    printf("\nPage Replacement Sequence:");
    for (j = 0; j < p; j++)
        printf("%3d", d[j]); // Display the page replacement sequence
    printf("\n\n");
}

//============ Page Table Update Logic ====================
void max_value(int x, int cc[][2])
{ // x: Page number; Update access counter for the page
    int i, max;
    max = cc[0][1];
    for (i = 0; i < 5; i++)
        if (max < cc[i][1])
            max = cc[i][1];
    for (i = 0; i < 5; i++)
        if (cc[i][0] == x)
            cc[i][1] = max + 1; // Set the page counter to the maximum + 1
}

//============ Page Replacement Algorithm ==================
int r_algorithm(int cc[5][2])
{
    int i, min, row, p;
    for (i = 0; i < 5; i++) // Find the first non-zero page counter
        if (cc[i][1] != 0)
        {
            min = cc[i][1];
            p = cc[i][0];
            row = i;
            break;
        }
    for (i = 0; i < 5; i++) // Find the page with the smallest counter
        if (min > cc[i][1] && cc[i][1] != 0)
        {
            min = cc[i][1];
            p = cc[i][0]; // Page to be replaced
            row = i;      // Row index of the page
        }
    cc[row][1] = 0; // Reset counter for the replaced page
    return (p);     // Return the page to be replaced
}

// ================= Print Page Table =======================
void page_table(int page1, int c[5][2])
{
    int i;
    printf("Page Request = %d\n", page1);
    for (i = 0; i < 5; i++)
        printf("%5d%5d\n", c[i][0], c[i][1]);
}

