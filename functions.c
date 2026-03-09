#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

// Creates a new node with given student data
// Allocates memory for a new node, assigns the student data to it, and initializes the next pointer to NULL
Node *createNode(Student student)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = student;
    newNode->next = NULL;
    return newNode;
}

// Counts the number of students in the linked list and returns the count
// It iterates through the linked list, incrementing a counter for each node until it reaches the end of the list
int countStudents(List head)
{
    if (head == NULL)
        return 0;

    int count = 0;
    Node *walker = head;
    while (walker != NULL)
    {
        count++;
        walker = walker->next;
    }
    return count;
}

// Creates a new node with given student data
// Inserts the new node at the specified position in the linked list
// Only adds to that position if position is reachable, else returns without adding
void insertAtPosition(List *head, int pos, Student student)
{
    if (pos < 1)
    {
        printf("Position %d is not reachable. Student not inserted.\n", pos);
        return;
    }

    Node *newNode = createNode(student);

    // Insert at head
    if (pos == 1)
    {
        newNode->next = *head;
        *head = newNode;
        printf("Student inserted at position %d successfully.\n", pos);
        return;
    }

    Node *walker = *head;
    int currentPos;
    for (currentPos = 1; currentPos < pos - 1 && walker != NULL; currentPos++)
        walker = walker->next;

    if (walker == NULL)
    {
        printf("Position %d is not reachable. Student not inserted.\n", pos);
        free(newNode);
        return;
    }

    newNode->next = walker->next;
    walker->next = newNode;

    printf("Student inserted at position %d successfully.\n", pos);
}

// Returns 1 if a student with the given ID already exists in the list, 0 otherwise
int isDuplicateId(List head, int id)
{
    Node *walker = head;
    while (walker != NULL)
    {
        if (walker->data.id == id)
            return 1;
        walker = walker->next;
    }
    return 0;
}

void insertAtStart(List *head, Student student)
{
    insertAtPosition(head, 1, student);
}

void insertAtEnd(List *head, Student student)
{
    insertAtPosition(head, countStudents(*head) + 1, student);
}

// Returns the node at the specified position in the linked list
// Returns NULL if the position is not reachable
Node *getNodeAtPosition(List head, int pos)
{
    int currentPos = 1;
    Node *walker = head;
    while (walker != NULL && currentPos < pos)
    {
        walker = walker->next;
        currentPos++;
    }
    return walker; // Return NULL if position is not reachable
}

void printHeader()
{
    printf("+-----+--------------------+----------+-------+------+\n");
    printf("| ID  | Name               | Program  | Year  | GPA  |\n");
    printf("+-----+--------------------+----------+-------+------+\n");
}

// Displays the infos of a student in a formatted manner
void printStudentInfo(Student student)
{
    printf("| %-3d | %-18s | %-8s | %-5d | %-4.2f |\n",
           student.id,
           student.name,
           student.program,
           student.yearLevel,
           student.gpa);
}

// Displays the infos of all students in the linked list
void displayAllStudents(List head)
{
    if (head == NULL)
    {
        printf("No students to display.\n");
        return;
    }

    printHeader();

    Node *walker = head;
    while (walker != NULL)
    {
        printStudentInfo(walker->data);
        walker = walker->next;
    }

    printf("+-----+--------------------+----------+-------+------+\n");
}

// Searches for a student by their ID and displays their information if found
// If no student with the given ID is found, it displays a not found message
void searchByStudentId(List head, int id)
{
    Node *walker = head;
    while (walker != NULL)
    {
        if (walker->data.id == id)
        {
            printHeader();
            printStudentInfo(walker->data);
            printf("+-----+--------------------+----------+-------+------+\n");
            return;
        }

        walker = walker->next;
    }

    printf("Student with ID %d not found.\n", id);
}

// Promotes the year level of all students in the linked list by 1
// iterates through the linked list and increments the year level of each student by 1
// If a student's year is already at the level 5, it removes (graduates) that student from the linked list instead of promoting them
void promoteYearLevel(List *head)
{
    int promoted = 0;
    int removed = 0;

    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL)
    {
        if (current->data.yearLevel >= 5)
        {
            if (prev == NULL)
                *head = current->next;
            else
                prev->next = current->next;

            Node *temp = current;
            current = current->next;
            free(temp);
            removed++;

            continue;
        }

        current->data.yearLevel++;
        prev = current;
        current = current->next;
        promoted++;
    }

    printf("Students promoted: %d | Students graduated/removed: %d\n", promoted, removed);
}

// Computes and displays the average GPA of all students in the linked list
void computeAverageGpa(List head)
{
    float totalGpa = 0.0;
    int count = 0;

    Node *walker = head;
    while (walker != NULL)
    {
        totalGpa += walker->data.gpa;
        count++;
        walker = walker->next;
    }

    if (count == 0)
    {
        printf("No students in the list to compute average GPA.\n");
        return;
    }

    float averageGpa = totalGpa / count;
    printf("Average GPA of all students: %.2f\n", averageGpa);
}

// Displays the top N students based on their GPA in descending order
void displayTopNStudents(List head, int n)
{
    int studentCount = countStudents(head);
    Node *nodes[studentCount];
    int index = 0;

    Node *walker = head;
    while (walker != NULL)
    {
        nodes[index++] = walker;
        walker = walker->next;
    }

    // Bubble sort
    int i, j;
    for (i = 0; i < index - 1; i++)
        for (j = 0; j < index - i - 1; j++)
            if (nodes[j]->data.gpa < nodes[j + 1]->data.gpa)
            {
                Node *temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }

    printf("Top %d students by GPA:\n", n);
    printHeader();
    for (i = 0; i < n && i < index; i++)
        printStudentInfo(nodes[i]->data);
    printf("+-----+--------------------+----------+-------+------+\n");
}

void reverseList(List *head)
{
    Node *prev = NULL;
    Node *current = *head;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}

void fillList(List *head)
{
    Student students[] = {
        {1, "Alice Reyes", "BSCS", 1, 3.75},
        {2, "Ben Torres", "BSIT", 2, 3.20},
        {3, "Cara Lim", "BSCS", 3, 2.95},
        {4, "Dan Uy", "BSCE", 4, 3.50},
        {5, "Eva Santos", "BSIT", 5, 3.85},
        {6, "Felix Gomez", "BSCS", 1, 2.80},
        {7, "Grace Tan", "BSCE", 2, 3.10},
        {8, "Hiro Nakamura", "BSIT", 3, 3.60},
        {9, "Iris Cruz", "BSCS", 4, 2.75},
        {10, "Jay Villanueva", "BSCE", 5, 3.90},
    };

    int n = sizeof(students) / sizeof(students[0]);

    int i;
    for (i = 0; i < n; i++)
    {
        Node *newNode = createNode(students[i]);

        if (*head == NULL)
            *head = newNode;
        else
        {
            Node *walker = *head;
            while (walker->next != NULL)
                walker = walker->next;
            walker->next = newNode;
        }
    }
}
