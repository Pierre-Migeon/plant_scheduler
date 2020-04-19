#include "plant_scheduler.h"

int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

char *months[]=
{
	" ",
	"\n\nJanuary",
	"\n\nFebruary",
	"\n\nMarch",
	"\n\nApril",
	"\n\nMay",
	"\n\nJune",
	"\n\nJuly",
	"\n\nAugust",
	"\n\nSeptember",
	"\n\nOctober",
	"\n\nNovember",
	"\n\nDecember"
};

int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;
	
	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.)/ 100.;
	d3 = (year - 1.)/ 400.;
	daycode = (year + d1 - d2 + d3) % 7;
	return daycode;
}

int determineleapyear(int year)
{
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		days_in_month[2] = 29;
		return (1);
	}
	else
	{
		days_in_month[2] = 28;
		return (0);
	}
}

int	print_plant_line(int day, t_llist **days, int offset, int monday)
{
	static int 	hits = -2;
	t_llist 	*head;
	int		i;
	char *bullet = "\u2022";
	if (day == 7)
		day = 0;

	i = 0;
	hits += 2;
	head = days[day];
	while(head)
	{
		if (i == hits)
		{
			if (offset == 0)
			{
				if ((head->biweekly == 1 && monday) || head->biweekly == 0)
					printf ("                                          \u2022 %s", head->plant);
				if (head->next && ((head->next->biweekly == 1 && monday) || head->next->biweekly == 0))
					printf (" %15s %s", bullet, head->next->plant);
			}
			else if (offset == 1)
			{
				if ((head->biweekly == 1 && monday) || head->biweekly == 0)
					printf ("       \u2022 %s", head->plant);
				if (head->next && ((head->next->biweekly == 1 && monday) ||head->next->biweekly == 0))
                                        printf (" %15s %s\n", bullet, head->next->plant);
				else
					printf ("\n");
			}
			else if (offset == 2)
			{
				if ((head->biweekly == 1 && monday) || head->biweekly == 0)
					printf ("         \u2022 %s", head->plant);
				if (head->next && ((head->next->biweekly == 1 && monday) ||head->next->biweekly == 0))
					printf ("%15s %s\n ", bullet, head->next->plant);
				else
					printf ("\n ");
			}
			if (head->next)
				return (1);
			return (0);
		}
		head = head->next;
		++i;
	}
	if (offset == 1)
		printf ("\n");
	if (offset == 2)
		printf("\n ");
	return (0);
}

int	even_week_since_jan_1st(int daycode, t_date *current)
{
	int weeks = 0;
	int month;
	int day;

      	for (month = 1; month <= 12; month++)
        {
		for ( day = 1; day <= 1 + daycode * 5; day++ )
                	;
               	// Print all the dates for one month
                for ( day = 1; day <= days_in_month[month]; day++ )
                {
                	if (month == current->month && day == current->day)
				return (weeks % 2);
                        // Is day before Sat? Else start next line Sun.
                        if ( ( day + daycode ) % 7 > 0 )
                        	;
                        else
				weeks++;
                }
        // Set position for next month
       	daycode = ( daycode + days_in_month[month] ) % 7;
	}
	return (0);
}

void calendar(int daycode, t_date *current, t_llist **days)
{
	int	month;
	int	day;
	int 	monday = even_week_since_jan_1st(daycode, current);

	for (month = 1; month <= 12; month++)
	{
		if (month == current->month)
		{
			printf("%s", months[month]);
			printf("                                  Plants To Water Today:\n                                         ------------------------\n");
			print_plant_line(current->wday, days, 0, monday);
			printf("\nSun  Mon  Tue  Wed  Thu  Fri  Sat  ");
			print_plant_line(current->wday, days, 1, monday);
			// Correct the position for the first date
			for ( day = 1; day <= 1 + daycode * 5; day++ )
				printf(" ");
			// Print all the dates for one month
			for ( day = 1; day <= days_in_month[month]; day++ )
			{
				if (day == current->day)
					printf ("\033[5;32;40m%2d\033[0m", day);
				else
					printf("%2d", day );
				// Is day before Sat? Else start next line Sun.
				if ( ( day + daycode ) % 7 > 0 )
					printf("   ");
				else
					print_plant_line(current->wday, days, 2, monday);
			}
		}
		// Set position for next month
		daycode = ( daycode + days_in_month[month] ) % 7;
	}
	printf("\n\n");
}

void	adjust_offset(t_date *current)
{
        determineleapyear(current->year);
        while (current->day > days_in_month[current->month])
        {       
                current->day = current->day - days_in_month[current->month];
                current->month++;
                if (current->month >= 13)
                {       
                        current->year++; 
                        determineleapyear(current->year);
                        current->month = 1;
        	}
	}
}

t_date *get_date(int offset)
{
	t_date *current;
	struct tm tm;

	if(!(current = (t_date *)malloc(sizeof(t_date))))
		exit(0);
	time_t t = time(NULL);
	tm = *localtime(&t);
	current->year = tm.tm_year + 1900;
	current->month = tm.tm_mon + 1;
	current->day = tm.tm_mday + offset;
	current->wday = tm.tm_wday + (offset % 7);
	if (current->day > days_in_month[current->month])
		adjust_offset(current);	
	return (current);
}

void	calendar_module(int offset, t_llist **days)
{
	int daycode;
	t_date	*current;
	
	current = get_date(offset);
	daycode = determinedaycode(current->year);
	determineleapyear(current->year);
	calendar(daycode, current, days);
	printf("\n");
}
