#include <stdio.h>
#include <stdlib.h>
#include "cal.h"


int main(int argc, char const *argv[])
{

	//Clearing the screen and preparing the UI
	printf("\033[3J\033[2J\033[1;1H");
	printf("\n\n\n");
	//////////////////////////////////////////

	int choice = 3;
	char choice_in[2];
	
	do
	{	

		//Chose primary action (Display a calendar or Exit the program)
		printf("Enter: 0. Exit		1. Display a calendar\n\n= = = = = >> ");

		ReadNum(choice_in, sizeof(choice_in), INT, &choice);
		printf("\n\n");

		if (choice != 0 && choice != 1)
		{
			printf("Invalid Option! try AGAIN:\n\n= = = = = >> ");
		}
		//////////////////////////////////////////////////////////////

		switch (choice)
		{
		case 0:
			exit(EXIT_SUCCESS);
			break;

		case 1:
			//Chosing the year of the calendar
			printf("Chose a year not older than 1900:\n\n= = = = = >> ");
			int year;
			char in[5];

			do
			{
				ReadNum(in, sizeof(in), INT, &year); printf("\n\n");
				if (year < 1900)
				{
					printf("The year can't be below 1900 ! Try again\n\n= = = = = >> ");
				}
				
			} while (year < 1900);
			///////////////////////////////////

			//Chosing the month of the calendar
			printf("Chose a month by entering its corresponding number from 1 - 12 :\n\n= = = = = >> ");
			int month;

			do
			{
				ReadNum(in, sizeof(in), INT, &month); printf("\n\n");
				if (month < 1 || month > 12)
				{
					printf("invalid month ! Try again\n\n= = = = = >> ");
				}
				
			} while (month < 1 || month > 12);
			///////////////////////////////////

			//Clear the screen and print the chosen calendar
			printf("\x1b[3J\033[2J\x1b[1;1H");
			printf("\n\n");
			PrintCal(year, month - 1);
			printf("\n\n");
			////////////////////////////////////////////////

		default:
			break;
		}
			
	} while (choice != 0);
	

	return 0;
}
