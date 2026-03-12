#ifndef struct_h
#define struct_h

typedef struct Node *NodePtr;
typedef NodePtr List;
typedef struct Student
{
	int id;
	char name[100];
	char program[100];
	int yearLevel;
	float gpa;
} Student;

typedef struct Node
{
	Student data;
	NodePtr next;
} Node;

#endif
