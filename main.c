#include "plant_scheduler.h"

void	freenode(t_hasht *node)
{
	if (node->plant)
		free(node->plant);
	free(node);
}

void	free_table(t_hasht **days)
{
	int		i;
	t_hasht 	*current;
	t_hasht		*last;

	i = 0;
	while (i < HASH_SIZE)
	{
		current = days[i];
		while (current)
		{
			last = current;
			current = current->next;
			if (last->plant)
				free(last->plant);
			free(last);
		}
		++i;
	}
	free(days);
}

int	main(int argc, char **argv)
{
	int		fd;
	int 		offset = 0;
	t_hasht 	**days;

	if (argc > 1)
		get_params(argv + 1, &offset);
	if (!(fd = get_json()))
		need_json();
	days = get_json_data(fd);
	calendar_module(offset, days);
	return (0);
}
