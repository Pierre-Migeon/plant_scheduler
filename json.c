#include "plant_scheduler.h"

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

int	get_json()
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
