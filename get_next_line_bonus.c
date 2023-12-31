/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:42:36 by asabir            #+#    #+#             */
/*   Updated: 2023/12/31 17:13:18 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_join_helper(char **reserve)
{
	char	*buff;

	buff = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (buff == NULL)
	{
		if (*reserve != NULL)
			free(*reserve);
		return (NULL);
	}
	if (*reserve == NULL)
	{
		*reserve = malloc(1);
		if (*reserve == NULL)
			return (NULL);
		(*reserve)[0] = '\0';
	}
	return (buff);
}

char	*read_and_join(int fd, char **reserve)
{
	ssize_t	res;
	char	*buff;

	buff = read_and_join_helper(reserve);
	if (buff == NULL)
		return (NULL);
	res = 1;
	while (res > 0)
	{
		res = read(fd, buff, BUFFER_SIZE);
		if (res == -1 || (res == 0 && *(reserve[0]) == '\0'))
		{
			free(buff);
			free(*reserve);
			return (NULL);
		}
		buff[res] = '\0';
		*reserve = free_and_join(reserve, buff);
		if (ft_strchr(buff, '\n') != 0)
			break ;
	}
	free(buff);
	return (*reserve);
}

char	*allocate_and_copy(char *reserve, int *j)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (*j + 1));
	if (temp == NULL)
		return (NULL);
	*j = 0;
	while (reserve[*j] != '\0')
	{
		temp[*j] = reserve[*j];
		if (reserve[*j] == '\n')
		{
			(*j)++;
			break ;
		}
		(*j)++;
	}
	temp[*j] = '\0';
	return (temp);
}

char	*update_reserve(char **reserve, int j, int len)
{
	char	*temp;

	if ((*reserve)[j] != '\0')
	{
		len = ft_strlen(*reserve + j);
		temp = (char *)malloc(sizeof(char) * (len + 1));
		if (temp == NULL)
			return (NULL);
		temp = ft_strcpy(temp, *reserve + j);
		free(*reserve);
		*reserve = (char *)malloc(sizeof(char) * (len + 1));
		if (*reserve == NULL)
		{
			free(temp);
			return (NULL);
		}
		*reserve = ft_strcpy(*reserve, temp);
		free(temp);
	}
	else
	{
		free(*reserve);
		*reserve = NULL;
	}
	return (*reserve);
}

char	*get_next_line(int fd)
{
	char		*temp;
	int			j;
	static char	*reserve[1024];
	int			len;

	len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	j = 0;
	reserve[fd] = read_and_join(fd, &reserve[fd]);
	if (reserve[fd] == NULL)
		return (NULL);
	j = ft_strlen((const char *)reserve[fd]);
	temp = allocate_and_copy(reserve[fd], &j);
	if (temp == NULL)
		return (NULL);
	reserve[fd] = update_reserve(&reserve[fd], j, len);
	return (temp);
}
