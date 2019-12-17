#include "plant_scheduler.h"

size_t	ft_strlen(const char *s)
{
	size_t length;

	length = 0;
	if (!*s)
		return (0);
	while (s[length])
		length++;
	return (length);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}

char	*ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	while (*src)
		dst[i++] = *(src++);
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(char *s1)
{
	int	i;
	char	*s2;

	while (s1[i])
		++i;
	if (!(s2 = (char *)malloc(++i * sizeof(char))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strchr(char *s, int c)
{
	size_t i;

	i = -1;
	while (++i < ft_strlen(s) + 1)
		if (s[i] == (char)c)
			return ((char *)s + i);
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*merge;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	if (!(merge = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(merge, s1);
	ft_strcat(merge, s2);
	return (merge);
}

int		ft_atoi(const char *str)
{
	int integer;
	int neg;

	integer = 0;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		integer = integer * 10 + (*(str++) - '0');
	return (neg == -1 ? -integer : integer);
}

int	end_match(char *s1, char *suffix)
{
	size_t len_1;
	size_t len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(suffix);
	if (len_1 < len_2)
		return (0);
	s1 += len_1 - len_2;
	while(*s1 && *s1 == *suffix)
	{
		s1++;
		suffix++;
	}
	return (!(*s1 - *suffix));
}

int	no_json()
{
	DIR 		*dirp;
	struct dirent 	*dp;
	int		fd;

	dirp = opendir(".");
        while ((dp = readdir(dirp)))
        {
                if (end_match(dp->d_name, ".json"))
                {
                        closedir(dirp);
                        if ((fd = open(dp->d_name, O_RDONLY)) == -1)
			{
				printf("Error, could not open file %s\n", dp->d_name);
				exit(1);
			}
			return (fd);
                }
        }
        closedir(dirp);
        return (0);
}

void	need_json()
{
	printf("Please provide a .json file containing plant names and watering times!\n");
	exit(0);
}

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

int	is_entry(char *line)
{
	if (ft_strchr(line, ':'))
		return (1);
	return (0);
}

char	*get_plant_name(char *str)
{
	int 	flag;
	char	out[500];
	char	*out_f;

	flag = 0;
	bzero(out, 500);
	while (*str)
	{
		if (*str == ':')
			flag++;
		if (flag)
			out[flag++ - 1] = *str;
		str++;
		if (*str == '"' && flag > 3)
			break;
	}
	out[flag - 1] = '\0';
	return (ft_strdup(out + 3));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	get_water_days(char *str)
{
	char 	out[4];
	int	i;

	i = 0;	
	while(*str)
	{
		if(ft_isdigit(*str))
			out[i++] = *str;	
		str++;
	}
	out[i] = '\0';
	return (ft_atoi(out));
}

int	parse_json(char **line, int fd)
{
	char 	temp[3];
	char	out[500];
	int	bytes_read;
	int	i;

	i = 0;
	bzero(out, 500);
	while ((bytes_read = read(fd, temp, 1)) > 0)
	{
		temp[bytes_read] = '\0';
		out[i++] = temp[0];
		if ((ft_strchr(out, '}')))
		{
			out[i] = '\0';
			break;
		}
	}
	*line = get_plant_name(out);
	return(get_water_days(out));
}

t_llist	*new_node(char *str)
{
	t_llist *new;

	if(!(new = (t_llist *)malloc(sizeof(t_llist))))
		exit(0);
	new->plant = ft_strdup(str);
	new->next = NULL;
	return (new);
}

int	get_days(int i, int reset)
{
	static int j = -1;

	if (reset)
		j = -1;
	j++;
	if (1 + i * j < 7)
		return (1 + i * j);
	else
		return (-1);
}

void	set_to_null(t_llist **hashtable)
{
	for (int i = 0; i < HASH_SIZE; i++)
		hashtable[i] = NULL;
}


t_llist **get_json_data(int fd)
{
	t_llist 	**hashtable;
	char		*line;
	t_llist 	*node;
	int		i[3];

	if (!(hashtable = (t_llist **)malloc(sizeof(t_llist *) * HASH_SIZE)))
		exit(1);
	set_to_null(hashtable);
	while ((i[0] = parse_json(&line, fd)))
	{
		i[2] = 1;
		while ((i[1] = get_days(i[0], i[2])) > -1)
		{
			i[2] = 0;
			node = new_node(line);
			if (hashtable[i[1]])
			{
				node->next = hashtable[i[1]];
				hashtable[i[1]] = node;
			}
			else
				hashtable[i[1]] = node;
		}
		//free(line);
	}
	return (hashtable);
}

/*
void	free_table(t_llist **days)
{
	int		i;
	t_llist 	*current;
	t_llist		*last;

	i = 0;
	while (i <= 14)
	{
		current = days[i];
		while (current)
		{
			last = current;
			current = current->next;
			free(last->plant);
			free(last);
		}
		++i;
	}
}
*/

int	main(int argc, char **argv)
{
	int		fd;
	int 		offset = 0;
	t_llist 	**days;

	if (!(fd = no_json()))
		need_json();
	if (argc > 1)
		get_params(argv + 1, &offset);
	days = get_json_data(fd);
	calendar_module(offset, days);
	//free_table(days);
	return (0);
}
