#ifndef functions_h
#define functions_h
#include "struct.h"

NodePtr createNode(Student student);
int countStudents(List head);
int isDuplicateId(List head, int id);
List insertAtPosition(List head, int pos, Student student);
List insertByGpa(List head, Student student);
List insertAtStart(List head, Student student);
List insertAtEnd(List head, Student student);
NodePtr getNodeAtPosition(List head, int pos);
void printStudentInfo(Student student);
void displayAllStudents(List head);
int searchByStudentId(List head, int id);
List promoteYearLevel(List head);
void computeAverageGpa(List head);
void displayTopNStudents(List head, int n);
List reverseList(List head);

List deleteByStudentId(List head, int id);
List deleteByGpaBelow(List head, float threshold);
List deleteByYearLevel(List head, int yearLevel);
List deleteDuplicateGpa(List head);

List fillList(List head);

#endif
