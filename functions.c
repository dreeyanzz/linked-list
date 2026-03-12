#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

// Creates a new node with given student data
// Allocates memory for a new node, assigns the student data to it, and initializes the next pointer to NULL
NodePtr createNode(Student student)
{
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
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
    NodePtr walker = head;
    while (walker != NULL)
    {
        count++;
        walker = walker->next;
    }
    return count;
}

// Inserts a new node at the specified position in the linked list
// Returns the (possibly new) head of the list
List insertAtPosition(List head, int pos, Student student)
{
    if (pos < 1)
    {
        printf("Position %d is not reachable. Student not inserted.\n", pos);
        return head;
    }

    NodePtr newNode = createNode(student);

    // Insert at head
    if (pos == 1)
    {
        newNode->next = head;
        head = newNode;
        printf("Student inserted at position %d successfully.\n", pos);
        return head;
    }

    NodePtr walker = head;
    int currentPos;
    for (currentPos = 1; currentPos < pos - 1 && walker != NULL; currentPos++)
        walker = walker->next;

    if (walker == NULL)
    {
        printf("Position %d is not reachable. Student not inserted.\n", pos);
        free(newNode);
        return head;
    }

    newNode->next = walker->next;
    walker->next = newNode;

    printf("Student inserted at position %d successfully.\n", pos);
    return head;
}

// Returns 1 if a student with the given ID already exists in the list, 0 otherwise
int isDuplicateId(List head, int id)
{
    NodePtr walker = head;
    while (walker != NULL)
    {
        if (walker->data.id == id)
            return 1;
        walker = walker->next;
    }
    return 0;
}

// Inserts a student in descending GPA order (before the first student with a lower GPA)
// Returns the (possibly new) head of the list
List insertByGpa(List head, Student student)
{
    NodePtr newNode = createNode(student);

    if (head == NULL || student.gpa > head->data.gpa)
    {
        newNode->next = head;
        return newNode;
    }

    NodePtr walker = head;
    while (walker->next != NULL && walker->next->data.gpa >= student.gpa)
        walker = walker->next;

    newNode->next = walker->next;
    walker->next = newNode;
    return head;
}

List insertAtStart(List head, Student student)
{
    return insertAtPosition(head, 1, student);
}

List insertAtEnd(List head, Student student)
{
    return insertAtPosition(head, countStudents(head) + 1, student);
}

// Returns the node at the specified position in the linked list
// Returns NULL if the position is not reachable
NodePtr getNodeAtPosition(List head, int pos)
{
    int currentPos = 1;
    NodePtr walker = head;
    while (walker != NULL && currentPos < pos)
    {
        walker = walker->next;
        currentPos++;
    }
    return walker;
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

    NodePtr walker = head;
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
    NodePtr walker = head;
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

// Promotes the year level of all students by 1
// Students at year level 5 are removed (graduated)
// Returns the (possibly new) head of the list
List promoteYearLevel(List head)
{
    int promoted = 0;
    int removed = 0;

    NodePtr current = head;
    NodePtr prev = NULL;

    while (current != NULL)
    {
        if (current->data.yearLevel >= 5)
        {
            if (prev == NULL)
                head = current->next;
            else
                prev->next = current->next;

            NodePtr temp = current;
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
    return head;
}

// Computes and displays the average GPA of all students in the linked list
void computeAverageGpa(List head)
{
    float totalGpa = 0.0;
    int count = 0;

    NodePtr walker = head;
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
    NodePtr nodes[studentCount];
    int index = 0;

    NodePtr walker = head;
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
                NodePtr temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }

    printf("Top %d students by GPA:\n", n);
    printHeader();
    for (i = 0; i < n && i < index; i++)
        printStudentInfo(nodes[i]->data);
    printf("+-----+--------------------+----------+-------+------+\n");
}

// Reverses the linked list and returns the new head
List reverseList(List head)
{
    NodePtr prev = NULL;
    NodePtr current = head;
    NodePtr next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

// Deletes the student with the given ID
// Returns the (possibly new) head of the list
List deleteByStudentId(List head, int id)
{
    if (head == NULL)
    {
        printf("List is empty. No student to delete.\n");
        return head;
    }

    NodePtr current = head;
    NodePtr prev = NULL;

    while (current != NULL)
    {
        if (current->data.id == id)
        {
            if (prev == NULL)
                head = current->next;
            else
                prev->next = current->next;

            printf("Student with ID %d (%s) deleted successfully.\n", current->data.id, current->data.name);
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("Student with ID %d not found.\n", id);
    return head;
}

// Removes all students whose GPA is below the given threshold
// Returns the (possibly new) head of the list
List deleteByGpaBelow(List head, float threshold)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return head;
    }

    int removed = 0;
    NodePtr current = head;
    NodePtr prev = NULL;

    while (current != NULL)
    {
        if (current->data.gpa < threshold)
        {
            NodePtr temp = current;
            if (prev == NULL)
                head = current->next;
            else
                prev->next = current->next;

            current = current->next;
            free(temp);
            removed++;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    printf("Students with GPA below %.2f removed: %d\n", threshold, removed);
    return head;
}

// Removes all students belonging to the given year level
// Returns the (possibly new) head of the list
List deleteByYearLevel(List head, int yearLevel)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return head;
    }

    int removed = 0;
    NodePtr current = head;
    NodePtr prev = NULL;

    while (current != NULL)
    {
        if (current->data.yearLevel == yearLevel)
        {
            NodePtr temp = current;
            if (prev == NULL)
                head = current->next;
            else
                prev->next = current->next;

            current = current->next;
            free(temp);
            removed++;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    printf("Students in Year Level %d removed: %d\n", yearLevel, removed);
    return head;
}

// Removes duplicate GPA records, keeping only the first occurrence
// Returns the head of the list
List deleteDuplicateGpa(List head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return head;
    }

    int removed = 0;
    NodePtr outer = head;

    while (outer != NULL)
    {
        NodePtr inner = outer->next;
        NodePtr prev = outer;

        while (inner != NULL)
        {
            if (inner->data.gpa == outer->data.gpa)
            {
                NodePtr temp = inner;
                prev->next = inner->next;
                inner = inner->next;
                free(temp);
                removed++;
            }
            else
            {
                prev = inner;
                inner = inner->next;
            }
        }

        outer = outer->next;
    }

    printf("Duplicate GPA records removed: %d\n", removed);
    return head;
}

// Fills the list with sample student data and returns the new head
List fillList(List head)
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
        head = insertAtEnd(head, students[i]);

    return head;
}
