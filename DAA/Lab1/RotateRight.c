#include <stdio.h>

void exchange(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int *arr, int p2) {
    for (int i = p2 - 1; i > 0; i--) {
        exchange(&arr[i], &arr[i - 1]);
    }
}

int main() {
    int n, p2;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter number of elements to rotate from beginning (p2): ");
    scanf("%d", &p2);

    printf("Before ROTATE: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    ROTATE_RIGHT(arr, p2);

    printf("After ROTATE: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}