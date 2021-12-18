/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:59:43 by abouhaga          #+#    #+#             */
/*   Updated: 2021/11/28 17:35:26 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_free(char **to_free)
{
	free(*to_free);
	*to_free = NULL;
}

static void	rest(char **save, char **line)
{
	char	*tmp;
	size_t	index;

	index = 0;
	while ((*save)[index] && (*save)[index] != '\n')
		index++;
	if ((*save)[index] == '\n')
	{
		tmp = *save;
		*line = ft_substr(tmp, 0, index + 1);
		*save = ft_strdup(&(*save)[index + 1]);
		ft_free(&tmp);
	}
	else
	{
		*line = ft_strdup(*save);
		ft_free(save);
		*save = NULL;
	}
	if (**line == '\0')
		ft_free(line);
}

static void	get_line(int fd, char **save, char *buffer, char **line)
{
	ssize_t	endof;
	char	*tmp;

	endof = 1;
	buffer[0] = '\0';
	while (endof != 0 && !(ft_strchr(buffer, '\n')))
	{
		endof = read(fd, buffer, BUFFER_SIZE);
		buffer[endof] = '\0';
		tmp = *save;
		*save = ft_strjoin(*save, buffer);
		ft_free(&tmp);
	}
	ft_free(&buffer);
	rest(save, line);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) == -1)
	{
		ft_free(&buffer);
		return (NULL);
	}
	if (!save[fd])
		save[fd] = ft_strdup("");
	get_line(fd, &save[fd], buffer, &line);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main()
// {
// 	int fd1 = open("l1", O_RDONLY);
// 	int fd2 = open("l2", O_RDONLY);
// 	int fd3 = open("l3", O_RDONLY);
// 	char *retour1 = get_next_line_bonus(fd1);
// 	char *retour2 = get_next_line_bonus(fd2);
// 	char *retour3 = get_next_line_bonus(fd3);
// 	printf("%s",retour1);
// 	printf("%s",retour2);
// 	printf("%s",retour3);
// 	retour1 = get_next_line_bonus(fd1);
// 	retour2 = get_next_line_bonus(fd2);
// 	retour3 = get_next_line_bonus(fd3);
// 	printf("%s",retour1);
// 	printf("%s",retour2);
// 	printf("%s",retour3);
// 	retour1 = get_next_line_bonus(fd1);
// 	retour2 = get_next_line_bonus(fd2);
// 	retour3 = get_next_line_bonus(fd3);
// 	printf("%s",retour1);
// 	printf("%s",retour2);
// 	printf("%s",retour3);
// }
