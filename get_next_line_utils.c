#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*allocate(char const *s1, char const *s2)
{
	int		len;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen((const char *)s1) + ft_strlen((const char *)s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = allocate(s1, s2);
	if (!res)
		return (NULL);
	while (s1[j] != '\0')
	{
		res[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i++] = '\0';
	}
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*str;

	if (size != 0 && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	total_size = nmemb * size;
	str = (void *)malloc(total_size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, total_size);
	return (str);
}

