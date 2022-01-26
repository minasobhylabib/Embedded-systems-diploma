/*
 * functions.h
 *
 *  Created on: Jan 26, 2022
 *      Author: Mina
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "stdio.h"
#include "stdlib.h"
#define PRINTF(...) fflush(stdout);fflush(stdin); printf (__VA_ARGS__);fflush(stdout);fflush(stdin);


struct Sdata
{
	int ID;
	char name[40];
	float height;
};

struct SStudent
{
	struct Sdata Student;
	struct SStudent* PNextStudent;
};



void fill_the_record(struct SStudent* new_Student);
void add_student();
void delete_student();
void view_students();
void delete_all();
void get_Nth (int N);
int number_of_students_using_iteration();
int number_of_students_using_recursion(struct SStudent* pCurrent);
void student_n_from_the_end(int N);
void middle_of_list();

#endif /* FUNCTIONS_H_ */
