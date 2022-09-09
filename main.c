#include "get_next_line.h"

int	main(void)
{
	char	*line1;
	int	i;
	int	fd1;

	fd1 = open("test1.txt", O_RDONLY);
	printf("%i\n", fd1);
	i = 0;
	while (i >= 0)
	{
		line1 = get_next_line(fd1);
		if (line1)
		{
			printf("%s", line1);
		}
		if (!line1)
		{
			break ;
		}
		free(line1);
		i++;
	}
	close(fd1);
	return (0);
}
