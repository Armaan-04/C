#include <stdio.h>
#include <stdlib.h>

struct SYMBOL {
    char alphabet;
    int frequency;
    struct SYMBOL *left, *right;
};

struct SYMBOL* createNode(char alphabet, int frequency) {
    struct SYMBOL* node = (struct SYMBOL*)malloc(sizeof(struct SYMBOL));
    node->alphabet = alphabet;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

void insertionSort(struct SYMBOL* arr[], int n) {
    for (int i = 1; i < n; i++) {
        struct SYMBOL* key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j]->frequency > key->frequency) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

struct SYMBOL* buildHuffmanTree(char alphabets[], int freq[], int n) {
    struct SYMBOL* arr[100]; 
    int size = n;

    for (int i = 0; i < n; i++) {
        arr[i] = createNode(alphabets[i], freq[i]);
    }

    while (size > 1) {
        
        insertionSort(arr, size);

        struct SYMBOL* left = arr[0];
        struct SYMBOL* right = arr[1];
        struct SYMBOL* newNode = createNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        for (int i = 2; i < size; i++) {
            arr[i - 2] = arr[i];
        }
        arr[size - 2] = newNode;
        size--; 
    }

    return arr[0]; 
}

void inorder(struct SYMBOL* root) {
    if (root != NULL) {
        inorder(root->left);
        if (root->alphabet != '$') 
            printf("%c ", root->alphabet);
        inorder(root->right);
    }
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char alphabets[n];
    int freq[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &alphabets[i]);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &freq[i]);
    }

    struct SYMBOL* root = buildHuffmanTree(alphabets, freq, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorder(root);
    printf("\n");

    return 0;
}
