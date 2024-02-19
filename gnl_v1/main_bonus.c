#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char *argv[])
{
    int fd1;
    int fd2;
    char *line;
    int	lines;

    printf("Argc: %d\n", argc);
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDONLY);
    lines = 1;
    printf("Reading from %s:\n", argv[1]);
    while ((line = get_next_line(fd1)))
        printf("%d ->%s\n", lines++, line);
    free(line);
    lines = 1;
    printf("Reading from %s:\n", argv[2]);
    while ((line = get_next_line(fd2)))
        printf("%d ->%s\n", lines++, line);
    free(line);
    close(fd1);
    close(fd2);
    return (0);
}