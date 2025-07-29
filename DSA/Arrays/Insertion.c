#include <stdio.h>

int main() {
    int arr[50]; 
    int size = 0;
    int num = 0;
    int pos = 0;
    printf("Enter size of array: ");
    scanf("%d", &size);
    if (size > 50) {
        printf("Overflow condition.\n");
    return 0;
    } else {
        for (int i = 0; i < size; i++) {
            printf("Enter element %d: ", i + 1);
            scanf("%d", &arr[i]);
        }
    }

    printf("Enter the number you want to insert: ");
    scanf("%d", &num);
    printf("Enter the position you want the number to be entered: ");
    scanf("%d", &pos);
    
    for(int i = size - 1 ; i>= pos-1 ; i-- ){
        arr[i+1] = arr[i];
    }
    arr[pos-1] = num;
    size++;

    printf("The elements of the array are: ");
    for (int i = 0 ; i<size ; i++){
        printf(" %d " , arr[i]);
    }
}
