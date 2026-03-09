#ifndef functions_h
#define functions_h
#include "struct.h"

Node *createNode(Student student);
int countStudents(List head);
int isDuplicateId(List head, int id);
void insertAtPosition(List *head, int pos, Student student);
void insertByGpa(List *head, Student student);
void insertAtStart(List *head, Student student);
void insertAtEnd(List *head, Student student);
Node *getNodeAtPosition(List head, int pos);
void printStudentInfo(Student student);
void displayAllStudents(List head);
void searchByStudentId(List head, int id);
void promoteYearLevel(List *head);
void computeAverageGpa(List head);
void displayTopNStudents(List head, int n);
void reverseList(List *head);

void fillList(List *head);

#endif
