/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhild <mhild@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:12:54 by mhild             #+#    #+#             */
/*   Updated: 2023/02/08 21:36:43 by mhild            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <fcntl.h>
#include "get_next_line_bonus.h"

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

/* to read different fd the static var has to be an array of pointers*/
/* each pointer points to data from one fd and can be referenced by the */
/* fd number -- rest of the code remains the same . */
/* NOTE : i could only make it work with []; style but dont why, really... */
char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[111];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > 112)
	{
		if (*(save + fd))
		{
			free (*(save + fd));
			*(save + fd) = NULL;
		}
		return (0);
	}
	*(save + fd) = ft_read_and_save(fd, *(save + fd));
	if (!save[fd])
		return (NULL);
	line = ft_get_line(*(save + fd));
	*(save + fd) = ft_save(*(save + fd));
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		length1 = 3;
// 	int		length2 = 5;
// 	int		length3 = 1;
// 	int fd1 = open("file1.txt", O_RDONLY);
// 	int fd2 = open("file2.txt", O_RDONLY);
// 	int fd3 = open("file3.txt", O_RDONLY);
// 	if (fd1 == -1 || fd1 == -2 || fd3 == -1)
// 	{
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}
// 	i = 0;
// 	while (i < length1)
// 	{
// 		line = get_next_line(fd1);
// 		if (!line) break;
// 		printf("%s\n", line);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < length2)
// 	{
// 		line = get_next_line(fd2);
// 		if (!line) break;
// 		printf("%s\n", line);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < length3)
// 	{
// 		line = get_next_line(fd3);
// 		if (!line) break;
// 		printf("%s\n", line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
//   	return 0;
// }
