#include<stdio.h>

void main()
{
	unsigned int x;
	char byte1, byte2, byte3, byte4;
	
	printf("Enter a number:-\n");
	scanf("%d", &x);
	
	byte1 = x;
	byte2 = x >> 8;
	byte3 = x >> 16;
	byte4 = x >> 24;
	
	printf("Byte 1: %d\nByte 2: %d\nByte 3: %d\nByte 4: %d\n", byte1, byte2, byte3, byte4);
}