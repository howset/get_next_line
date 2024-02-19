#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char *argv[])
{
	int	fd;
	char	*line;
	int	lines;

    printf("Argc: %d\n", argc);
	lines = 1;
	fd = open(argv[1], O_RDONLY);
	while((line = get_next_line(fd)))
		printf("%d ->%s\n", lines++, line);
    free(line);
	close(fd);
    return (0);
}