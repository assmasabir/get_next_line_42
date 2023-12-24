
#include "get_next_line.h"

#define BUFFER_SIZE 100

char	*free_and_join(char *reserve, char *buff)
{
	char	*temp;

	temp = ft_strjoin(reserve, buff);
	free(reserve);
	return (temp);
}

char	*read_and_join(int fd, char *reserve, int *j)
{
	ssize_t	res;
	char	*buff;

	*j = 0;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (reserve == NULL)
		reserve = ft_calloc(1, 1);
	else
		*j = ft_strlen(reserve);
	if (buff == NULL || reserve == NULL)
		return (NULL);
	while ((res = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[res] = '\0';
		reserve = free_and_join(reserve, buff);
		if (ft_strchr(buff, '\n') != 0)
			break ;
	}
	free(buff);
	if (res == -1 || (res == 0 && *j == 0 && reserve[*j] == '\0'))
		return (NULL);
	return (reserve);
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
char	*update_reserve(char *reserve, int j)
{
	int		len;
	char	*temp;

	if (reserve[j] != '\0')
	{
		len = ft_strlen(reserve + j);
		temp = (char *)malloc(sizeof(char) * (len + 1));
		temp = ft_strcpy(temp, reserve + j);
		free(reserve);
		reserve = (char *)malloc(sizeof(char) * (len + 1));
		reserve = ft_strcpy(reserve, temp);
		free(temp);
	}
	else
	{
		free(reserve);
		reserve = NULL;
	}
	return (reserve);
}

char	*get_next_line(int fd)
{
	char		*temp;
	int			j;
	static char	*reserve[1024];

	j = 0;
	reserve[fd] = read_and_join(fd, reserve[fd], &j);
	if (reserve[fd] == NULL)
		return (NULL);
	temp = allocate_and_copy(reserve[fd], &j);
	reserve[fd] = update_reserve(reserve[fd], j);
	return (temp);
}

