#include <stdio.h>
    int main() {
    int n, i;
     printf("Enter number of elements: ");
    scanf("%d", &n);
    if (n < 2) {
        printf("Need at least two elements.\n");
        return 1;
    }
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int smallest, second_smallest;
    int largest, second_largest;
    smallest = second_smallest = largest = second_largest = arr[0];
     for (i = 1; i < n; i++) {
        if (arr[i] < smallest)
            smallest = arr[i];
        if (arr[i] > largest)
            largest = arr[i];
    }
     second_smallest = second_largest = -1; 
     for (i = 0; i < n; i++) {
        if (arr[i] > smallest) {
            if (second_smallest == -1 || arr[i] < second_smallest)
                second_smallest = arr[i];
        }
        if (arr[i] < largest) {
            if (second_largest == -1 || arr[i] > second_largest)
                second_largest = arr[i];
        }
    }

   
    if (second_smallest == -1)
        printf("Second smallest not found (all elements may be equal).\n");
    else
        printf("Second Smallest = %d\n", second_smallest);

    if (second_largest == -1)
        printf("Second largest not found (all elements may be equal).\n");
    else
        printf("Second Largest = %d\n", second_largest);

    return 0;
}