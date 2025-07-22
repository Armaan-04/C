#include <stdio.h>
int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n], prefixSum[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    prefixSum[0] = arr[0];
    for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + arr[i];

    printf("Prefix Sum Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", prefixSum[i]);

    return 0;
}