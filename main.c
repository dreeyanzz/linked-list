#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "functions.h"

void pause()
{
	printf("\nPress ENTER to continue...");
	fflush(stdin);
	getchar();
}

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
	printf("13. Delete Students with GPA Below Threshold\n");
	printf("14. Delete Students by Year Level\n");
	printf("15. Delete Duplicate GPA Records\n");
//	printf("16. Fill List with Sample Data\n");
	printf("16. Exit\n");
}

Student createStudent()
{
	Student student;

	printf("  ID       : ");
	scanf("%d", &student.id);
	fflush(stdin);

	printf("  Name     : ");
	scanf(" %99[^\n]", student.name);
	fflush(stdin);

	printf("  Program  : ");
	scanf(" %99[^\n]", student.program);
	fflush(stdin);

	do
	{
		printf("  Year (1-5): ");
		scanf("%d", &student.yearLevel);
		fflush(stdin);
		if (student.yearLevel < 1 || student.yearLevel > 5)
			printf("  [!!] Invalid year level. Must be between 1 and 5.\n");
	} while (student.yearLevel < 1 || student.yearLevel > 5);

	do
	{
		printf("  GPA (0.0-4.0): ");
		scanf("%f", &student.gpa);
		fflush(stdin);
		if (student.gpa < 0.0f || student.gpa > 4.0f)
			printf("  [!!] Invalid GPA. Must be between 0.0 and 4.0.\n");
	} while (student.gpa < 0.0f || student.gpa > 4.0f);

	return student;
}

int main()
{
	List list = NULL;

	int choice;

	while (1)
	{
		system("cls");
		displayMenu();
		printf("Choice: ");
		scanf("%d", &choice);
		fflush(stdin);

		switch (choice)
		{

		case 1:
		{
			Student student = createStudent();
			if (isDuplicateId(list, student.id))
			{
				printf("[!!] ID %d already exists. Enrollment rejected.\n", student.id);
				pause();
				break;
			}
			list = insertAtEnd(list, student);
			pause();
		}
		break;

		case 2:
		{
			Student student = createStudent();
			if (isDuplicateId(list, student.id))
			{
				printf("[!!] ID %d already exists. Enrollment rejected.\n", student.id);
				pause();
				break;
			}
			if (student.gpa < 3.0f)
			{
				printf("[!!] GPA %.2f does not meet the 3.0 minimum for priority enrollment.\n", student.gpa);
				pause();
				break;
			}
			list = insertAtStart(list, student);
			pause();
		}
		break;

		case 3:
		{
			Student student = createStudent();
			if (isDuplicateId(list, student.id))
			{
				printf("[!!] ID %d already exists. Enrollment rejected.\n", student.id);
				pause();
				break;
			}
			int pos;
			printf("  Position (1-based): ");
			scanf("%d", &pos);
			fflush(stdin);
			list = insertAtPosition(list, pos, student);
			pause();
		}
		break;

		case 4:
		{
			Student student = createStudent();
			if (isDuplicateId(list, student.id))
			{
				printf("[!!] ID %d already exists. Enrollment rejected.\n", student.id);
				pause();
				break;
			}
			list = insertByGpa(list, student);
			printf("[OK] Student enrolled by GPA order.\n");
			pause();
		}
		break;

		case 5:
		{
			displayAllStudents(list);
			pause();
		}
		break;

		case 6:
		{
			int id;
			printf("  Student ID to search: ");
			scanf("%d", &id);
			fflush(stdin);

			int result = searchByStudentId(list, id);
			if (result)
				printf("[OK] Match found for ID %d.\n", result);
			pause();
		}
		break;

		case 7:
		{
			int id;
			printf("  Student ID to delete: ");
			scanf("%d", &id);
			fflush(stdin);
			list = deleteByStudentId(list, id);
			pause();
		}
		break;

		case 8:
		{
			int count = countStudents(list);
			printf("[--] Total students: %d\n", count);
			pause();
		}
		break;

		case 9:
		{
			list = promoteYearLevel(list);
			pause();
		}
		break;

		case 10:
		{
			computeAverageGpa(list);
			pause();
		}
		break;

		case 11:
		{
			int n;
			printf("  Top N students to display: ");
			scanf("%d", &n);
			fflush(stdin);
			displayTopNStudents(list, n);
			pause();
		}
		break;

		case 12:
		{
			list = reverseList(list);
			printf("[OK] List order reversed.\n");
			pause();
		}
		break;

		case 13:
		{
			float threshold;
			printf("  GPA threshold (removes all below): ");
			scanf("%f", &threshold);
			fflush(stdin);
			list = deleteByGpaBelow(list, threshold);
			pause();
		}
		break;

		case 14:
		{
			int yearLevel;
			printf("  Year level to delete: ");
			scanf("%d", &yearLevel);
			fflush(stdin);
			list = deleteByYearLevel(list, yearLevel);
			pause();
		}
		break;

		case 15:
		{
			list = deleteDuplicateGpa(list);
			pause();
		}
		break;

//		case 16:
//		{
//			list = fillList(list);
//			pause();
//		}
//		break;

		case 16:
		{
			printf("[--] Goodbye!\n");
			exit(0);
		}
		break;

		default:
		{
			printf("[!!] Invalid choice. Please try again.\n");
			pause();
		}
		break;
		}
	}

	return 0;
}
