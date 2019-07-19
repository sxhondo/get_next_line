#include "get_next_line.h"

int 	main(int argc, char **argv)
{
	char 	*line;
	int 	fd;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_putstr(line);
		ft_putchar('\n');
		free (line);
	}
}
