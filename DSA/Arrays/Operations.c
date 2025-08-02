#include <stdio.h>

int main() {
    int arr[50]; 
    int size = 0;
    int num = 0;
    int pos = 0;
    int del = 0;
    int choice = 0;
    printf("Enter size of array: ");
    scanf("%d", &size);
    if (size > 50) {
        printf("Out of bound.\n");
    return 0;
    } else {
        for (int i = 0; i <= size-1; i++) {
            printf("Enter element %d: ", i + 1);
            scanf("%d", &arr[i]);
        }
    printf("The elements of the array are: ");
    for (int i = 0 ; i<size ; i++){
        printf(" %d " , arr[i]);
    }
    }
    
    while(1){
        printf("\nEnter 1 for INSERTION: \n");
        printf("Enter 2 for DELETION: \n");
        printf("Enter 3 to EXIT:\n");
        scanf("\n%d" , &choice);
    
    switch(choice){
        case 1:
    printf("\nEnter the number you want to insert: ");
    scanf("%d", &num);
    printf("\nEnter the position you want the number to be inserted: ");
    scanf("%d", &pos);

    if(pos <=0 || pos > size + 1){
        printf("Invalid position or Array is full.");
        return 0;
    }
    else{
    for(int i = size-1 ; i >= pos-1 ; i-- ){
        arr[i+1] = arr[i];
    }
    arr[pos-1] = num;
    size++;

    printf("The elements of the array are: ");
    for (int i = 0 ; i<size ; i++){
        printf(" %d " , arr[i]);
    }
    break;
}

        case 2:
     printf("\nEnter the position from which you want to delete: ");
     scanf("%d" , &del); 
     if (del <= 0 || del > size ){
        printf("Invalid position");
     } else {
        for(int i = del-1 ; i < size-1 ; i++){
            arr[i] = arr[i+1];
        }
        size--;
     }
      printf("\nThe elements of the array are: ");
    for (int i = 0 ; i<size ; i++){
        printf(" %d " , arr[i]);
    }
    break;

    case 3:
    printf("Program exited.");
    return 0;

    default:
    printf("Invalid choice.");

    }
}
}

