/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhild <mhild@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:25:11 by mhild             #+#    #+#             */
/*   Updated: 2023/02/07 16:11:05 by mhild            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;
	size_t	i;

	csrc = (char *) src;
	cdest = (char *) dest;
	if (dest == src)
		return (0);
	i = 0;
	while (i < n)
	{
		*(cdest + i) = *(csrc + i);
		i++;
	}
	return (dest);
}

void	*ft_realloc(char *ptr, int offset, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
	{
		ptr = malloc (size);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (size == 0)
	{
		free (ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr + offset, size - 1);
	free(ptr);
	return (new_ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	ls1;
	size_t	ls2;

	if (!s1)
	{
		s1 = malloc(1);
		*s1 = '\0';
	}
	if (!s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	res = malloc (ls1 + ls2 + 1);
	if (!res)
		return (NULL);
	if (*s1)
		ft_memcpy(res, s1, ls1);
	if (*s2)
		ft_memcpy(res + ls1, s2, ls2);
	*(res + ls1 + ls2) = '\0';
	free(s1);
	return (res);
}
