#include "plant_scheduler.h"

void	usage(int i)
{
    if (i == 1)
        printf ("Unknown parameter.\nUsage: ./plant_calendar [-o num]\n\t-o is day offset. For instance, +2 to see the schedule two days in advance and -2 to see what was supposed to be done two days ago.\n");
	else
        printf ("Please specify offset number.\nUsage: ./plant_calendar [-o num]\n\t-o is day offset. For instance, +2 to see the schedule two days in advance and -2 to see what was supposed to be done two days ago.\n");
	exit(0);
}

void	get_params(char **argv, int *offset)
{
	int i;

	i = 0;
	if (ft_strcmp(argv[i++], "-o"))
		usage(1);
	if (!(argv[i]))
		usage(2);
	if (argv[++i])
		usage(1);
	*offset = ft_atoi(argv[--i]);
}
