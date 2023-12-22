#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char *get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);