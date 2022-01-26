/*
 * main.c
 *
 *  Created on: Jan 26, 2022
 *      Author: Mina
 */

#include "functions.h"
#include "stdio.h"


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
		default:
			PRINTF("\n Wrong option");
			break;
		}
	}
	return 0;
}
