#include <stdio.h>

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n], freq[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        freq[i] = -1;
    }

    int total_duplicates = 0, max_count = 0, most_repeating;

    for (int i = 0; i < n; i++) {
        int count = 1;
        if (freq[i] != 0) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] == arr[j]) {
                    count++;
                    freq[j] = 0;
                }
            }
            freq[i] = count;
            if (count > 1)
                total_duplicates++;
            if (count > max_count) {
                max_count = count;
                most_repeating = arr[i];
            }
        }
    }

    printf("Total number of duplicate values = %d\n", total_duplicates);
    printf("The most repeating element in the array = %d\n", most_repeating);

    return 0;
}