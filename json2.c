#include "plant_scheduler.h"

int	get_day(void)//t_hasht *node)
{
	return (1);
}

void	add_node(t_hasht **hashtable, t_hasht *node)
{
	int	day;

	day = get_day();//*node);
	if(hashtable[day])
	{
		node->next = hashtable[day];
		hashtable[day] = node;
	}
	else
		hashtable[day] = node;
}

int	end_jobject(char *line)
{
	while (*line == ' ' || *line == '\t')
		++line;
	if (*line == '}')
		return (1);
	return(0);
}

int	dataline(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '[' && *line != ']')
			return (1);
		++line;
	}
	return (0);
}

char	*is_schedule(char *line)
{
        char *compare;
        char *ptr;

        compare = ft_strdup("\"water_after\": \"");
        ptr = compare;
        while (*compare)
        {
                while (*compare && *line && *line == *compare)
                {
                        ++line;
                        ++compare;
                }
                while (*compare && (*line == ' ' || *line == '\t'))
                        ++line;
                if (*compare && *compare != *line)
                {
                        free(ptr);
                        return (NULL);
                }
        }
        free(ptr);
        return (--line);
}

int	schedule(char *line)
{
	char *ptr;

        if ((line = is_schedule(line)))
        {
		if ((ptr = ft_strrchr(line, '"')) != line)
		{
			*ptr = '\0';
			return (ft_atoi(++line));
		}
	}
	return (-1);
}

void	unexpected_json_error(t_hasht **hashtable, int fd, char *line)
{
	free(line);
	close(fd);
	free_table(hashtable);
	printf("The JSON file was malformed... please check for formatting errors! terminating program...\n");
	exit(0);
}

char	*is_plant(char *line)
{
	char *compare;
	char *ptr;

	compare = ft_strdup("\"name\": \"");
	ptr = compare;
	while (*compare)
	{
		while (*compare && *line && *line == *compare)
		{
			++line;
			++compare;
		}
		while (*compare && (*line == ' ' || *line == '\t'))
			++line;
		if (*compare && *compare != *line)
		{
			free(ptr);
			return (NULL);
		}
	}
	free(ptr);
	return (--line);
}

char	*plant_name(char *line)
{
	char *ptr;

	if ((line = is_plant(line)))
	{
		if ((ptr = ft_strrchr(line, '"')) != line)
		{
			*ptr = '\0';
			return (ft_strdup(++line));
		}
	}	
	return (NULL);
}

void	update_node(t_hasht **hashtable, int fd, char *line, t_hasht *node)
{
	if (node->plant == NULL)
		node->plant = plant_name(line);
	else if (is_plant(line))
		unexpected_json_error(hashtable, fd, line);
	if (node->water_every == -1)
		node->water_every = schedule(line);
	else if (is_schedule(line))
		unexpected_json_error(hashtable, fd, line);
}

t_hasht *new_htnode(void)
{
	t_hasht *new;

	if (!(new = (t_hasht *)malloc(sizeof(t_hasht) * 1)))
		return (NULL);
	new->biweekly = 0;
	new->water_every = -1;
	new->plant = NULL;
	new->next = NULL;
	return (new);
}

t_hasht *start_jobject(char *line, t_hasht *node)
{
	while (*line == ' ' || *line == '\t')
		++line;
	if (*line == '{' && node == NULL)
		return (new_htnode());
	return(node);
}

void	setnull(t_hasht **table)
{
	for (int i = 0; i < HASH_SIZE; i++)
		table[i] = NULL;
}

t_hasht **get_json_data(int fd)
{
	t_hasht 	**hashtable = NULL;
	char		*line;
	t_hasht 	*node = NULL;

	if (!(hashtable = (t_hasht **)malloc(sizeof(t_hasht *) * HASH_SIZE)))
		exit(1);
	setnull(hashtable);
	while(get_next_line(fd, &line))
	{
		node = start_jobject(line, node);
		if (node)
			update_node(hashtable, fd, line, node);
		else if (dataline(line))
			unexpected_json_error(hashtable, fd, line);
		if (end_jobject(line))
		{
			if (node && node->plant && node->water_every != -1)
				add_node(hashtable, node);
			else
				freenode(node);
			node = NULL;
		}
		free(line);
	}
	return (hashtable);
}
