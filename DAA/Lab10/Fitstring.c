#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 30 
long long FIB[MAX_L];

void initialize_fibonacci() {
    FIB[0] = 1; FIB[1] = 1;
    for (int i = 2; i < MAX_L; i++) FIB[i] = FIB[i-1] + FIB[i-2];
}

long long fitstring_to_int(int *fits, int L) {
    long long N = 0;
    for (int i = 0; i < L; i++) if (fits[i] == 1) N += FIB[i];
    return N;
}

void print_fitstring(const char *op, int *fits, int L) {
    printf("%s: ", op);
    for (int i = L - 1; i >= 0; i--) printf("%d", fits[i]);
    printf(" (Value: %lld)\n", fitstring_to_int(fits, L));
}

// Converts an integer N into its canonical (Zeckendorf) fitstring representation.
void int_to_fitstring(long long N, int *fits, int *L) {
    memset(fits, 0, MAX_L * sizeof(int));
    
    int k = MAX_L - 1;
    while (k >= 0 && FIB[k] > N) k--;
    
    while (N > 0 && k >= 0) {
        if (N >= FIB[k]) {
            fits[k] = 1;
            N -= FIB[k];
        }
        k--;
    }
    
    *L = 0;
    for (int i = MAX_L - 1; i >= 0; i--) {
        if (fits[i] == 1) {
            *L = i + 1;
            break;
        }
    }
}


void normalize_fitstring(int *fits, int *L) {
    int changed = 1;
    
    while(changed) {
        changed = 0;
        
        while (*L > 0 && fits[*L - 1] == 0) (*L)--;
        if (*L == 0) return;

        if (fits[*L - 1] != 0 && *L < MAX_L) {
            fits[*L] = 0;
            (*L)++;
            changed = 1;
        }

        for (int i = 0; i < *L; i++) {
            
            // FIX: Handle coefficients >= 2. Use the identity 2*Fi = F_{i+1} + F_{i-2}
            // with special cases for small i. This resolves the failure from incrementing 1 to 2.
            if (fits[i] >= 2) {
                if (i == 0 || i == 1) { // 2*F1=2, 2*F2=2. Both equal F3 (index 2).
                    fits[i] -= 2;
                    if (2 < MAX_L) fits[2]++;
                } else if (i == 2) { // 2*F3=4. 4 = F4 + F1 (index 3 and 0).
                    fits[i] -= 2;
                    if (3 < MAX_L) fits[3]++;
                    if (0 >= 0) fits[0]++;
                } else { // i >= 3. Use 2*Fi = F_{i+1} + F_{i-2}
                    fits[i] -= 2;
                    if (i + 1 < MAX_L) fits[i+1]++;
                    if (i - 2 >= 0) fits[i-2]++;
                }
                changed = 1;
            }
            

            // Zeckendorf Normalization: F_i + F_{i+1} = F_{i+2} (11 -> 100)
            if (i < *L - 1 && fits[i] == 1 && fits[i+1] == 1) {
                fits[i] = 0;
                fits[i+1] = 0;
                if (i + 2 < MAX_L) fits[i+2]++;
                changed = 1;
            }

            // Borrow: F_{i+2} -> F_{i+1} + F_{i} to eliminate -1
            if (fits[i] < 0) { 
                if (i + 2 < *L && fits[i+2] > 0) {
                    fits[i+2]--;
                    fits[i+1]++;
                    fits[i]++;
                    changed = 1;
                }
            }
        }
    }
}

void increment(int *fits, int *L) {
    fits[0]++;
    normalize_fitstring(fits, L);
}

void decrement(int *fits, int *L) {
    fits[0]--;
    normalize_fitstring(fits, L);
}

int main() {
    initialize_fibonacci();

    long long initial_N;
    printf("--- Fibonacci Fitstring Counter ---\n");
    printf("Enter the starting integer N (max ~830000): ");
    if (scanf("%lld", &initial_N) != 1 || initial_N <= 0 || initial_N > FIB[MAX_L-1]) {
        printf("Invalid or out-of-range input. Exiting.\n");
        return 1;
    }

    int fits[MAX_L] = {0};
    int L = 0;
    
    int_to_fitstring(initial_N, fits, &L);
    
    print_fitstring("Initial (Canonical)", fits, L);

    // Perform operations
    increment(fits, &L);
    print_fitstring("Increment N+1", fits, L);

    increment(fits, &L);
    print_fitstring("Increment N+2", fits, L);

    decrement(fits, &L);
    print_fitstring("Decrement N+1", fits, L);

    decrement(fits, &L);
    print_fitstring("Decrement N", fits, L);


    return 0;
}
