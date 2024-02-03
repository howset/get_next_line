#include "get_next_line.h"

char	*read_fd(int fd);
char	*extract_line(char **stock);

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*temp;
	char		*line_from_read;
	char		*extracted;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	if (!stock)
		stock = ft_strdup("");
	extracted = extract_line(&stock);
	if (extracted)
		return (extracted);
	line_from_read = read_fd(fd);
	if (!line_from_read)
	{
		extracted = ft_strdup(stock);
		free(stock);
		stock = NULL;
		if (*extracted)
			return (extracted);
		free(extracted);
		return (NULL);
	}
	temp = ft_strjoin(stock, line_from_read);
	free(line_from_read);
	free(stock);
	stock = temp;
	return (get_next_line(fd));
}

char	*read_fd(int fd)
{
	char	*line;
	int		bytes;

	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	bytes = read(fd, line, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free(line);
		return (NULL);
	}
	line[bytes] = '\0';
	return (line);
}

char	*extract_line(char **stock)
{
	int		len;
	char	*extracted;
	char	*remains;

	len = 0;
	while ((*stock)[len] != '\n' && (*stock)[len] != '\0')
		len++;
	if ((*stock)[len] == '\n')
	{
		extracted = ft_substr(*stock, 0, len + 1);
		remains = ft_substr(*stock, len + 1, ft_strlen(*stock) - (len + 1));
		free(*stock);
		*stock = remains;
		return (extracted);
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int	fd;
	char	*line;
	int	lines;

	lines = 1;
	fd = open("lorem2.txt", O_RDONLY);
	while(line = get_next_line(fd))
		printf("%d ->%s\n", lines++, line);
	close(fd);
}
*/