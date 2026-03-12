#ifndef struct_h
#define struct_h

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
	struct Node *next;
} Node;

typedef Node *NodePtr;
typedef NodePtr List;

#endif
