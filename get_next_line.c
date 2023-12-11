/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhild <mhild@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:43:36 by mhild             #+#    #+#             */
/*   Updated: 2023/02/10 15:52:18 by mhild            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <fcntl.h>
#include "get_next_line.h"

/* gives back exactly on line from text pointed to by static var */
/* a line either ends with \n or \0 */
/* each line is null terminated */
char	*ft_get_line(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!*(save + i))
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	s = malloc(i + 2);
	if (!s)
		return (NULL);
	if (*(save + i) == '\n')
	{
		ft_memcpy(s, save, i + 2);
		i++;
	}
	else
		ft_memcpy(s, save, i + 1);
	*(s + i) = '\0';
	return (s);
}

/* discards the text previously printed and resizes memory */
/* pointed to by static var accordingly */
char	*ft_save(char *save)
{
	int	i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	save = ft_realloc(save, i + 1, ft_strlen(save) - i + 1);
	return (save);
}

/* reads text from fd into buffer and */
/* copies buffer into memory pointed to by static var */
char	*ft_read_and_save(int fd, char *save)
{
	char	*buffer;
	int		read_bytes;

	buffer = NULL;
	buffer = ft_realloc(buffer, 0, (BUFFER_SIZE + 1));
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

/* gets text read from a fd in a line by line fashion */
/* fd and BUFFER_SIZE have to be positive values */
/* read(fd, 0, 0) checks if fd is still open, if return is -1 its closed */
/* reads text to a buffer and copies into mem pointed to by static var */
/* extracts one line from this memory */
/* discards extracted line from memory for next function call */
char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (save)
		{
			free (save);
			save = NULL;
		}
		return (0);
	}
	save = ft_read_and_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_save(save);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*input;
// 	int		i = 0;
// 	int		lines = 5;

// 	fd = open ("text.txt", O_RDWR);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}
// 	while (i < lines)
// 	{
// 		input = get_next_line(fd);
// 		printf("%s", input);
// 		i++;	
// 	}
// 	close(fd);
// 	return (0);
// }
