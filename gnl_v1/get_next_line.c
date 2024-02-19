/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:47:05 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/14 15:22:07 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*real_gnl_func(char **stock, int fd);
char	*read_fd(int fd);
char	*extract_line(char **stock);

/*
char	*get_next_line(int fd)
{
	static char	*stock;
	char		*temp;
	char		*line_fr_read;
	char		*extracted;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!stock)
		stock = ft_strdup("");
	extracted = extract_line(&stock);
	if (extracted)
		return (extracted);
	line_fr_read = read_fd(fd);
	if (!line_fr_read)
	{
		extracted = ft_strdup(stock);
		free(stock);
		stock = NULL;
		if (*extracted)
			return (extracted);
		free(extracted);
		return (NULL);
	}
	temp = ft_strjoin(stock, line_fr_read);
	free(line_fr_read);
	free(stock);
	stock = temp;
	return (get_next_line(fd));
}
*/

char	*get_next_line(int fd)
{
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	if (!stock)
		stock = ft_strdup("");
	return (real_gnl_func(&stock, fd));
}

char	*real_gnl_func(char **stock, int fd)
{
	char	*temp;
	char	*line_fr_read;
	char	*extracted;

	extracted = extract_line(stock);
	if (extracted)
		return (extracted);
	line_fr_read = read_fd(fd);
	if (!line_fr_read)
	{
		extracted = ft_strdup(*stock);
		free(*stock);
		*stock = NULL;
		if (*extracted)
			return (extracted);
		free(extracted);
		return (NULL);
	}
	temp = ft_strjoin(*stock, line_fr_read);
	free(*stock);
	*stock = temp;
	free(line_fr_read);
	return (real_gnl_func(stock, fd));
}

char	*read_fd(int fd)
{
	char	*line_fr_read;
	int		bytes;

	line_fr_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line_fr_read)
		return (NULL);
	bytes = read(fd, line_fr_read, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free(line_fr_read);
		return (NULL);
	}
	line_fr_read[bytes] = '\0';
	return (line_fr_read);
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

int main(void)
{
	int	fd;
	char	*line = NULL;
	int	lines;

	lines = 1;
	fd = open("lorem1.txt", O_RDONLY);
	while((line = get_next_line(fd)))
		printf("%d ->%s\n", lines++, line);
	close(fd);
}
*/