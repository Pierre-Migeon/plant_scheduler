

#ifndef PLANT_H
# define PLANT_H

#include "./libft/libft.h"
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

typedef struct		s_hasht
{
	int		biweekly;
	int		water_every;
        char		*plant;
        struct s_hasht	*next;
}			t_hasht;

typedef struct  s_date
{
        int     year;
        int     month;
        int     day;
	int	wday;
}               t_date;

//main
void    free_table(t_hasht **days);
void    freenode(t_hasht *node);

//Read parameters
void	usage(int i);
void	get_params(char **argv, int *offset);

//JSON
int	end_match(char *s1, char *suffix);
int	get_json();
void	need_json();

//JSON3
t_hasht	**get_json_data(int fd);
void    set_to_null(t_hasht **hashtable);

//Calendar
void	calendar_module(int offset, t_hasht **days);
t_date	*get_date(int offset);
void	calendar(int daycode, t_date *current, t_hasht **days);
int 	determineleapyear(int year);
int 	determinedaycode(int year);

#endif
