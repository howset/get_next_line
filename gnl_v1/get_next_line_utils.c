/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:47:15 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/05 17:47:16 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
