#include<stdio.h>
#include<string.h>

struct dob
{
	int day;
	int month;
	int year;
};

struct student_info
{
	int roll_no;
	char name[50];
	float CGPA;
	struct dob age;
};

void main()
{
	struct student_info stud1;

	stud1.roll_no = 2306188;
	strcpy(stud1.name, "Armaan Alam");
	stud1.CGPA = 7.78;
	stud1.age.day = 6;
	stud1.age.month = 12;
	stud1.age.year = 2004;
	
	printf("Roll: %d\nName: %s\nCGPA: %f\nDOB: %d-%d-%d\n", stud1.roll_no, stud1.name, stud1.CGPA, stud1.age.day, stud1.age.month, stud1.age.year);
}