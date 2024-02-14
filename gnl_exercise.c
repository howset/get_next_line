#include <stdio.h> // printf
#include <stdlib.h> // free
#include <unistd.h> // read
#include <fcntl.h> // O_RDONLY

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd);
char	*read_fd(int fd);
char	*extract_line(char **stock);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

int main(void)
{
	int	fd;
	char	*line = NULL;
	int	lines;

	lines = 1;
	fd = open("lorem1.txt", O_RDONLY);
	while((line = get_next_line(fd)))
		printf("%d ->%s\n", lines++, line);
	//printf("%s\n",get_next_line(fd));
	close(fd);
	return (0);
}

char	*get_next_line(int fd)
{
	char	*line_fr_read;
	//int		bytes;
	static char	*stock;
	char	*extracted;
	char		*temp;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
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
	/* line_fr_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!line_fr_read)
		return (NULL);
	bytes = read(fd, line_fr_read, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free(line_fr_read);
		return (NULL);
	}
	line_fr_read[bytes] = '\0'; */
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

/* char	*get_next_line(int fd)
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
} */

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

size_t	ft_strlen(const char *str)
{
	size_t	counts;

	counts = 0;
	while (str[counts] != '\0')
	{
		counts++;
	}
	return (counts);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	res;

	res = 0;
	if (size == 0)
	{
		while (src[res])
			res++;
		return (res);
	}
	while (res < size -1 && src[res] != '\0')
	{
		dst[res] = src[res];
		res++;
	}
	if (res < size)
		dst[res] = '\0';
	while (src[res] != '\0')
		res++;
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;

	len = ft_strlen(s) + 1;
	res = malloc(sizeof(char) * len);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s, len);
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*res_ptr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	res = malloc(sizeof(*s) * (len + 1));
	if (res == NULL)
		return (NULL);
	s = s + start;
	res_ptr = res;
	*(res + len) = '\0';
	while (len > 0 && *s != '\0')
	{
		*res++ = *s++;
		len--;
	}
	return (res_ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
