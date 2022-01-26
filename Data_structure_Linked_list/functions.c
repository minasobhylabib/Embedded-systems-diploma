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
	PRINTF("\n Enter the ID:");
	gets(temp_text);
	new_Student->Student.ID = atoi(temp_text);
	PRINTF("\n Enter student full name:");
	gets(new_Student->Student.name);
	PRINTF("\n Enter height:");
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
	int i, selected_id;
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

