#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "functions.h"

void displayMenu()
{
	printf("===== SMART ENROLLMENT SYSTEM =====\n");
	printf("1. Regular Enrollment\n");
	printf("2. Priority Enrollment\n");
	printf("3. Manual Insert\n");
	printf("4. Late Enrollment\n");
	printf("5. Display All Students\n");
	printf("6. Search Student\n");
	printf("7. Delete Student\n");
	printf("8. Count Students\n");
	printf("9. Promote Year Level\n");
	printf("10. Compute Average GPA\n");
	printf("11. Display Top N Students\n");
	printf("12. Reverse List\n");
	printf("13. Exit\n");
	printf("14. Fill List with Sample Data\n");
}

Student createStudent()
{
	Student student;

	printf("Enter student ID: ");
	scanf("%d", &student.id);
	fflush(stdin);

	printf("Enter student name: ");
	scanf(" %99[^\n]", student.name);
	fflush(stdin);

	printf("Enter student program: ");
	scanf(" %99[^\n]", student.program);
	fflush(stdin);

	do
	{
		printf("Enter student year level (1-5): ");
		scanf("%d", &student.yearLevel);
		fflush(stdin);
		if (student.yearLevel < 1 || student.yearLevel > 5)
			printf("Invalid year level. Must be between 1 and 5.\n");
	} while (student.yearLevel < 1 || student.yearLevel > 5);

	do
	{
		printf("Enter student GPA (0.0 - 4.0): ");
		scanf("%f", &student.gpa);
		fflush(stdin);
		if (student.gpa < 0.0f || student.gpa > 4.0f)
			printf("Invalid GPA. Must be between 0.0 and 4.0.\n");
	} while (student.gpa < 0.0f || student.gpa > 4.0f);

	return student;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{

	List list = NULL;

	int choice;

	while (1)
	{
		printf("\n\n");
		displayMenu();
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{

		case 1:
		{
			Student student = createStudent();
			if (isDuplicateId(list, student.id))
			{
				printf("Student with ID %d already exists. Enrollment rejected.\n", student.id);
				break;
			}
			insertAtEnd(&list, student);
		}
		break;

		case 2:
		{
			Student student = createStudent();
			if (isDuplicateId(list, student.id))
			{
				printf("Student with ID %d already exists. Enrollment rejected.\n", student.id);
				break;
			}
			if (student.gpa < 3.0f)
			{
				printf("Student does not meet the GPA requirement for priority enrollment.\n");
				break;
			}
			insertAtStart(&list, student);
		}
		break;

		case 3:
		{
			Student student = createStudent();
			if (isDuplicateId(list, student.id))
			{
				printf("Student with ID %d already exists. Enrollment rejected.\n", student.id);
				break;
			}
			int pos;
			printf("Enter position to insert (1-based index): ");
			scanf("%d", &pos);
			insertAtPosition(&list, pos, student);
		}
		break;

		case 4:
		{
			Student student = createStudent();
			if (isDuplicateId(list, student.id))
			{
				printf("Student with ID %d already exists. Enrollment rejected.\n", student.id);
				break;
			}
			insertByGpa(&list, student);
		}
		break;

		case 5:
		{
			displayAllStudents(list);
		}
		break;

		case 6:
		{
			int id;
			printf("Enter student ID to search: ");
			scanf("%d", &id);
			fflush(stdin);

			searchByStudentId(list, id);
		}
		break;

		case 8:
		{
			int count = countStudents(list);
			printf("Total number of students: %d\n", count);
		}
		break;

		case 9:
		{
			promoteYearLevel(&list);
		}
		break;

		case 10:
		{
			computeAverageGpa(list);
		}
		break;

		case 11:
		{
			int n;
			printf("Enter the number of top students to display: ");
			scanf("%d", &n);
			fflush(stdin);

			displayTopNStudents(list, n);
		}
		break;

		case 12:
		{
			reverseList(&list);
			printf("Student list reversed.\n");
		}
		break;

		case 13:
		{
			exit(0);
		}
		break;

		case 14:
		{
			fillList(&list);
		}
		break;

		default:
		{
			printf("Invalid choice or not yet implemented. Please try again.\n");
		}
		break;
		}
	}

	return 0;
}
