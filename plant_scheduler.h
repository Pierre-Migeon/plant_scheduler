

#ifndef PLANT_H
# define PLANT_H

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <strings.h>

# define HASH_SIZE 7

typedef struct          s_llist
{
        char		*plant;
        struct s_llist	*next;
}			t_llist;

typedef struct  s_date
{
        int     year;
        int     month;
        int     day;
}               t_date;

void	calendar_module(int offset, t_llist **days);
t_date	*get_date(int offset);
void 	calendar(int daycode, t_date *current, t_llist **days);
int 	determineleapyear(int year);
int 	determinedaycode(int year);


#endif
