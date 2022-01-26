/*
 * main.c
 *
 *  Created on: Jan 26, 2022
 *      Author: Mina
 */

#include "functions.h"
#include "stdio.h"
extern gpFirstSudent;

int main()
{
	while(1)
	{
		PRINTF("\n ================");
		PRINTF("\n Choose one of the following options");
		PRINTF("\n 1: Add student");
		PRINTF("\n 2: Delete student");
		PRINTF("\n 3: View students");
		PRINTF("\n 4: Delete all");
		PRINTF("\n 5: Get the record for student number N");
		PRINTF("\n 6: Get the total number of students using iteration function");
		PRINTF("\n 7: Get the total number of students using recursive function");
		PRINTF("\n 8: Get the record for student number n calculated from the end");
		PRINTF("\n 9: Get the middle record");
		PRINTF("\n Enter option Number:");

		char temp[2];
		gets(temp);
		switch(atoi(temp))
		{
		case 1:
			 add_student();
			break;
		case 2:
			 delete_student();
			break;
		case 3:
			 view_students();
			break;
		case 4:
			 delete_all();
			break;
		case 5:
		{
			PRINTF("\n Enter N");
			gets(temp);
			get_Nth (atoi(temp));
		}
			break;
		case 6:
		{
			PRINTF("\n Number of students is %d",number_of_students_using_iteration());
		}
		break;
		case 7:
		{

			PRINTF("\n Number of students is %d",number_of_students_using_recursion(gpFirstSudent));
		}
		break;
		case 8:
		{
			PRINTF("\n Enter n");
			gets(temp);
			student_n_from_the_end(atoi(temp));
		}
		break;
		case 9:
		{
			middle_of_list();
		}
		break;
		default:
			PRINTF("\n Wrong option");
			break;
		}
	}
	return 0;
}
