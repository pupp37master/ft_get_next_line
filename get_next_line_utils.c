/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhild <mhild@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:56:17 by mhild             #+#    #+#             */
/*   Updated: 2023/02/07 15:20:22 by mhild            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

/* this is a re-implementation of realloc : */
/* mainly used to resize the data pointed to by the static var */
/* also mallocs space for  1st argument if needed . */
/* mallocs new space and copies data from first argument to new mem */
/* memcpy is called with size - 1 bc of index to size difference of 1 */
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

/* this is a tweaked strjoin function : */
/* it allocates mem for 'save' if it doesnt find any */
/* it checks its parameters for before copying chars */
/* if s1 is 0 there is nothing to copy into */
/* if s2 is 0 indicates the end of buffer - nothing to copy */

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
