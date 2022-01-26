/*
 * functions.c
 *
 *  Created on: Jan 26, 2022
 *      Author: Mina
 */

#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
struct SStudent* gpFirstSudent = NULL;
void fill_the_record(struct SStudent* new_Student)
{
	char temp_text[40];
	PRINTF(" Enter the ID:");
	gets(temp_text);
	new_Student->Student.ID = atoi(temp_text);
	PRINTF(" Enter student full name:");
	gets(new_Student->Student.name);
	PRINTF(" Enter height:");
	gets(temp_text);
	new_Student->Student.height = atof(temp_text);
}

void add_student()
{
	struct SStudent* plastSudent;
	struct SStudent* pNewStudent;
	pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
	if(gpFirstSudent == NULL)
	{

		gpFirstSudent = pNewStudent;
	}
	else
	{
		plastSudent = gpFirstSudent;
		while(plastSudent->PNextStudent)
		{
			plastSudent = plastSudent->PNextStudent;
		}
		plastSudent->PNextStudent = pNewStudent;

	}

	fill_the_record(pNewStudent);
	pNewStudent->PNextStudent = NULL;

}

void delete_student()
{
	char temp[40];
	int  selected_id;
	PRINTF("\n Enter Student ID to be deleted:");
	gets(temp);
	selected_id = atoi(temp);
	if(gpFirstSudent)
	{
		struct SStudent* pSelected=gpFirstSudent;
		struct SStudent* pPrevious = NULL;
		while(pSelected)
		{
			if(pSelected->Student.ID == selected_id)
			{
				if(pPrevious)
				{
					pPrevious->PNextStudent = pSelected->PNextStudent;
					free (pSelected);
					PRINTF("\n  Student ID is deleted successfully");
					break;
				}
				else
				{
					gpFirstSudent = NULL;
				}
			}
			pPrevious = pSelected;
			pSelected = pSelected->PNextStudent;

		}

	}
	else
	{
		PRINTF("\n Empty list")
	}

}

void view_students()
{
	int count = 0;
	struct SStudent* pCurrent = gpFirstSudent;
	if(gpFirstSudent)
	{
		while(pCurrent)
		{
			PRINTF("\n Record Number %d", count+1);
			PRINTF("\n ID: %d",pCurrent->Student.ID);
			PRINTF("\n Name: %s",pCurrent->Student.name);
			PRINTF("\n Height: %.2f", pCurrent->Student.height);
			pCurrent = pCurrent->PNextStudent;
			count++;
		}
	}
	else
	{
		PRINTF("\n Empty list");
	}
}

void delete_all()
{
	struct SStudent* pCurrent = gpFirstSudent;
	if(gpFirstSudent)
	{
		while(pCurrent)
		{
			struct SStudent* pTemp = pCurrent;
			pCurrent = pCurrent->PNextStudent;
			free (pTemp);
		}
		gpFirstSudent = NULL;
	}
	else
		PRINTF("\n Empty list");
}

void get_Nth (int N)
{
	struct SStudent* pCurrent = gpFirstSudent;
	int i;
	if(gpFirstSudent)
	{
		for( i=1; i<N;i++)
		{
			pCurrent = pCurrent->PNextStudent;
		}
		PRINTF("\n Record Number %d", N);
		PRINTF("\n ID: %d",pCurrent->Student.ID);
		PRINTF("\n Name: %s",pCurrent->Student.name);
		PRINTF("\n Height: %.2f", pCurrent->Student.height);
	}
	else
		PRINTF("\n No students");
}


int number_of_students_using_iteration()
{
	struct SStudent* pCurrent = NULL;
	pCurrent=gpFirstSudent;
	int count =0;
	if(gpFirstSudent)
	{
		while(pCurrent)
		{
			pCurrent = pCurrent->PNextStudent;
			count++;
		}
	}
	return count;
}



int number_of_students_using_recursion(struct SStudent* pCurrent)
{

	if(pCurrent)
	{
		return (1 + number_of_students_using_recursion(pCurrent->PNextStudent));
	}
	else
		return 0;

}

void student_n_from_the_end(int N)
{
	struct SStudent* pCurrent = gpFirstSudent;
	struct SStudent* pincrement = gpFirstSudent;
	int i;
	for (i=0; i<N;i++)
	{
		pincrement = pincrement->PNextStudent;
	}
	while(pincrement)
	{
		pincrement = pincrement->PNextStudent;
		pCurrent = pCurrent->PNextStudent;
	}
	PRINTF("\n Record Number %d from the end", N);
	PRINTF("\n ID: %d",pCurrent->Student.ID);
	PRINTF("\n Name: %s",pCurrent->Student.name);
	PRINTF("\n Height: %.2f", pCurrent->Student.height);
}

void middle_of_list()
{
	struct SStudent* pCurrent = gpFirstSudent;
	struct SStudent* pincrement = gpFirstSudent;


	while(pincrement->PNextStudent!=0)
	{
		pCurrent = pCurrent->PNextStudent;
		pincrement = pincrement->PNextStudent;
		if(!pincrement->PNextStudent)
			break;
		pincrement = pincrement->PNextStudent;

	}

	PRINTF("\n Middle Record");
	PRINTF("\n ID: %d",pCurrent->Student.ID);
	PRINTF("\n Name: %s",pCurrent->Student.name);
	PRINTF("\n Height: %.2f", pCurrent->Student.height);
}






