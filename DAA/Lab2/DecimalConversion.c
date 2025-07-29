#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int num, char* binary, int pos) {
    if (pos < 0) return;
    
    binary[pos] = (num % 2) + '0';
    decimalToBinary(num / 2, binary, pos - 1);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    char* inputFile = argv[2];
    char* outputFile = argv[3];
    
    FILE* inFile = fopen(inputFile, "r");
    if (!inFile) {
        printf("Error opening input file\n");
        return 1;
    }
    
    FILE* outFile = fopen(outputFile, "w");
    if (!outFile) {
        printf("Error opening output file\n");
        fclose(inFile);
        return 1;
    }
    
    int num;
    char binary[17];
    binary[16] = '\0';
    
    for (int i = 0; i < n && fscanf(inFile, "%d", &num) == 1; i++) {
        for (int j = 0; j < 16; j++) binary[j] = '0';
        decimalToBinary(num, binary, 15);
        fprintf(outFile, "The binary equivalent of %d is %s\n", num, binary);
    }
    
    fclose(inFile);
    fclose(outFile);
    
    printf("Content of the first 'n' decimal and their equivalent binary numbers\n");
    
    FILE* readFile = fopen(outputFile, "r");
    char line[100];
    while (fgets(line, sizeof(line), readFile)) {
        printf("%s", line);
    }
    fclose(readFile);
    
    return 0;
}
