/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:47:05 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/19 19:28:46 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *stock);
char	*extract_line(char *stock);
char	*clean_up(char *stock);

char	*get_next_line(int fd)
{
	char		*extracted;
	static char	*stock = NULL; // declare a static variable and initialize
	char		*remains;

	if (fd < 0 || BUFFER_SIZE <= 0) // just a control sequence for invalid fd & BUFFER_SIZE to return NULL
	{
		if (stock != NULL) // stock is declared and initialized as NULL, if somehow it is not, then free and return NULL
			free(stock);
		return (NULL);
	}
	stock = read_line(fd, stock); // call read_line on fd and stock [1]
	if (!stock) // control if the above function fails
		return (NULL);
	extracted = extract_line(stock); // extract a line (anything up to \n) from stock [2]. At this point extracted is the return value of the get_next_line function
	remains = clean_up(stock); // however, stock still contains extracted, so some clean up is in order, to prepare it for the next call of the function [3]
	stock = remains; // stock is empty, and set to be remains
	return (extracted);
}

char	*read_line(int fd, char *stock) // [1]
{
	int		bytes;
	char	*line_fr_read;

	if (!stock) // on first run, stock should be NULL, so this should evaluate to TRUE
		stock = null_malloc(1, sizeof(char)); // if TRUE then allocate something ('\0', via null_malloc)
	line_fr_read = null_malloc(BUFFER_SIZE + 1, sizeof(char)); // allocate line_fr_read according to the defined BUFFER_SIZE, + 1 for the termination
	if (!line_fr_read) // control sequence
		return (NULL);
	bytes = 1; // initialize as one to make sure the following loop can be entered
	while (!ft_strchr(stock, '\n') && bytes != 0) // the loop evaluates when there is no '\n' in stock, and read is successful
	{
		bytes = read(fd, line_fr_read, BUFFER_SIZE); // calls read with a count of BUFFER_SIZE to the buffer area line_fr_read
		if (bytes == -1) // control sequence if read fails, free stock and the buffer and return NULL
		{
			free(stock);
			free(line_fr_read);
			return (NULL);
		}
		line_fr_read[bytes] = '\0'; // terminate the buffer area
		stock = freebuf_join(stock, line_fr_read); // join stock (initially empty) and buffer line_fr_read
	} // this loop keeps going to fill stock until there is \n (including any trailing characters, if any exist/included). Repeated calls to read overwrites the buffer (line_fr_read), so there is no need to do anything.
	free(line_fr_read); // since stock already contains the buffer line_fr_read, it can be freed (avoid leaks)
	return (stock); // and stock is returned
}

char	*extract_line(char *stock) // [2]
{
	size_t	i;
	char	*extracted;

	i = 0;
	if (!stock[i]) // control. Not really sure why [0], but francinette fails on empty file
		return (NULL);
	while (stock[i] != '\n' && stock[i]) // increment i up to \n to get size
		i++;
	extracted = null_malloc(i + 2, sizeof(char)); // allocate size of extracted according to i, + 2 to include \n and \0
	if (!extracted) // control
		return (NULL);
	i = 0; // reuse the same counter
	while (stock[i] && stock[i] != '\n') // copy stock to extracted up to \n (right before \n)
	{
		extracted[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n') // copy the \n
	{
		extracted[i] = stock[i];
		i++;
	}
	extracted[i] = '\0'; // then terminate with \0
	return (extracted); // returns extracted
}

char	*clean_up(char *stock) // [3]
{
	int		i;
	int		j;
	char	*remains;

	i = 0;
	while (stock[i] != '\0' && stock[i] != '\n') // increment counter until the \n is encountered
		i++;
	if (stock[i] == '\0') // control sequence if there is no more \n (e.g end of file/EOF)
	{
		free(stock);
		return (NULL);
	}
	remains = null_malloc(ft_strlen(stock) - i + 1, sizeof(char)); // allocate remains -> length of stock - extracted [2]
	if (!remains) // control if null_malloc fails
	{
		free(stock);
		return (NULL);
	}
	i++;
	j = 0;
	while (stock[i] != '\0') // copy (stock-extracted) to remains
		remains[j++] = stock[i++];
	remains[j] = '\0'; // terminate remains
	free(stock); // clean stock, because remains is returned and will be put into stock in the get_next_line function 
	return (remains);
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