#include<stdio.h>

struct pkt
{
	char ch1;
	char ch2[2];
	char ch3;
};

int digCount(int x)
{
	int temp = x, count = 0;
	
	while(temp != 0)
	{
		temp /= 10;
		count++;
	}
	
	return count;
}

void main()
{
	int x;
	
	printf("Enter a 4-digit number(1000-9999):-\n");
	scanf("%d", &x);
	
	if(digCount(x) == 4)
	{
		struct pkt packet = {0};
		
		packet.ch1 = (x % 10) + '0';
		x /= 10;
		packet.ch2[0] = (x % 10) + '0';
		x /= 10;
		packet.ch2[1] = (x % 10) + '0';
		x /= 10;
		packet.ch3 = (x % 10) + '0';
		
		printf("1st digit: %c\n2nd digit: %c\n3rd digit: %c\n4th digit: %c\n", packet.ch3, packet.ch2[1], packet.ch2[0], packet.ch1);
		
		int aggregate = 0;
		
		aggregate += (packet.ch3 - '0') * 1000;
		aggregate += (packet.ch2[1] - '0') * 100;
		aggregate += (packet.ch2[0] - '0') * 10;
		aggregate += (packet.ch1 - '0');
		
		printf("Original number: %d\n", aggregate);
	}
	
	else
	{
		printf("Please enter a valid 4-digit number!\n");
	}
}