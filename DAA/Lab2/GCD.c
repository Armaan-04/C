#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s <source_file> <dest_file>\n", argv[0]);
        return 1;
    }

    FILE *inFile = fopen(argv[1], "r");
    FILE *outFile = fopen(argv[2], "w");

    if (!inFile || !outFile) {
        perror("File error");
        return 1;
    }

    int a, b;
    while (fscanf(inFile, "%d %d", &a, &b) == 2) {
        int result = gcd(a, b);
        fprintf(outFile, "The GCD of %d and %d is %d\n", a, b, result);
    }

    fclose(inFile);
    fclose(outFile);

    outFile = fopen(argv[2], "r");
    char line[100];
    while (fgets(line, sizeof(line), outFile)) {
        printf("%s", line);
    }
    fclose(outFile);

    return 0;
}
