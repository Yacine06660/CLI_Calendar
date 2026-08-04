#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include "cal.h"

char months[][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

WEEK_DAY get_day(int year, MONTH month, int *md)
{
	if (year < 1900 || year > 3000 || (month < 0 || month > 11))
	{
		return -1;
	}
	
	int yOffset = year - epoch_y;
	int dOffset = 0;
	int lindex = 0;

	for (size_t i = 0; i < yOffset; i++)
	{
		if(lindex == 0)
		{
			if ((epoch_y + i) % 100 == 0 && (epoch_y + i) % 400 != 0)
			{
				dOffset += 365;
			}
			else
			{
				dOffset += 366;
			}
		}
		else
		{
			dOffset += 365;
		}

		lindex = (lindex + 1) % 4;
	}

	int daynum[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (lindex == 0 && !(year % 100 == 0 && year % 400 != 0))
	{
		daynum[1] = 29;
	}

	size_t i;
	for (i = 0; i < month; i++)
	{
		dOffset += daynum[i];
	}
	
	if(md != NULL) *md = daynum[month];
	return (dOffset + 1) % 7 + 1;
}

void PrintCal(int year, MONTH month)
{
	int md;
	WEEK_DAY wd = get_day(year, month, &md);

	printf("			%s	%d\n\n", months[month], year);

	printf("\t\t\t_________________________________________________________\n\n\n");

	printf("			SUN      MON      TUE      WED      THU      FRI      SAT\n\n\n\n\t\t\t");

	int nl_index = 0;

	for (int j = 1; j <= wd - 1 ; j++)
	{
		printf("         ");
		nl_index++;
	}


	for (size_t i = 1; i <= md; i++)
	{
		if (nl_index >= 7 && nl_index % 7 == 0)
		{
			printf("\n\n\n\n\t\t\t");
		}
		printf("%02d       ", i);
		nl_index++;
	}

	printf("\n\n\t\t\t_________________________________________________________\n");


	printf("\n");
}

void ReadNum(char *input, size_t size_of_input, TYPE type, void *var)
{
	long long tmp;
	unsigned long long tmp_u;
	double tmp_frac;

	while (1)
	{

		zero_out_arr(input, size_of_input);

		fgets(input, size_of_input, stdin);

		if (strchr(input, '\n') == NULL)
		{
			int c = getchar();
			if (c != '\n')
			{
				while ((c = getchar()) != '\n' && c != EOF);

				printf("Invalid input, the number you entered might be too large!\nTry again: ");
				continue;
			}
		}
		if (input[0] == '\0')
		{
			printf("Input can't be empty, try again: \n");
			continue;
		}
		
		char *endptr = NULL;
		errno = 0;

		switch (type)
		{
		case INT:

			tmp = strtoll(input, &endptr, 10);

			if (*endptr != '\0' && *endptr != '\n' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for integers!\ntry again: ");
				continue;
			}

			if (errno == ERANGE || tmp > INT_MAX || tmp < INT_MIN)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(int *)var = (int)tmp;

			break;

		case SIZET:

			if (input[0] == '-')
			{
				printf("Size_t must be a positive number\nTry again: ");
				continue;
			}

			tmp_u = strtoull(input, &endptr, 10);

			if (*endptr != '\0' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for size_t!\ntry again: ");
				continue;
			}

			if (errno == ERANGE || tmp_u > SIZE_MAX)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(size_t *)var = (size_t)tmp_u;

			break;

		case LONG:

			tmp = strtoll(input, &endptr, 10);

			if (*endptr != '\0' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for longs!\ntry again: ");
				continue;
			}

			if (errno == ERANGE)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(long *)var = (long)tmp;

			break;

		case FLOAT:

			tmp_frac = strtof(input, &endptr);

			if (*endptr != '\0' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for floats!\ntry again: ");
				continue;
			}

			if (errno == ERANGE)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(float *)var = (float)tmp_frac;

			break;

		case DOUBLE:

			tmp_frac = strtod(input, &endptr);

			if (*endptr != '\0' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for doubles!\ntry again: ");
				continue;
			}

			if (errno == ERANGE)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(double *)var = tmp_frac;

			break;
		default:

			printf("Type unavailable or unsupported\n");
			break;
		}

		break;
	}

}

char UpperToLower(char in)
{
	if ((in >= 'A' && in <= 'Z') || (in >= 'a' && in <= 'z'))
	{
		return in | 0x20;
	}
	else return 0;
	
}

void ReadChar(char *var)
{
	char input[2];
	
	while (1)
	{
		zero_out_arr(input, sizeof(input));
		fgets(input, sizeof(input), stdin);

		int c;
		if ((c =getchar()) != '\n')
		{
			printf("You must only enter one character !\nTry again: ");
			while((c = getchar()) != '\n' && c != EOF);

			continue;
		}
		
		break;
	}

	*var = input[0];
	
}