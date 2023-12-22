#include "get_next_line.h"





char *get_next_line(int fd)
{
    ssize_t res;
    static char *buff;
    size_t size = 100;
    int i;
    char *temp;
    int j;
    static char *reserve;

 
    j = 0;

    if (buff == NULL)
        buff = (char *)malloc(sizeof(char) * (size+1));

    if (reserve == NULL)
        reserve = ft_calloc(1, 1);
    else
    {
        while (reserve[j] != '\0')
        {
            j++;
        }
    }

    if (buff == NULL || reserve == NULL)
        return NULL;

    while ((res = read(fd, buff, size)) > 0)
    {
        buff[res] = '\0';
        i = 0;
        reserve= ft_strjoin(reserve,buff);

        if (ft_strchr(buff, '\n') != 0)
            break;
    }

    if (res == -1 || (res == 0 && j == 0 && reserve[j] == '\0'))
        return (NULL);

    temp = (char *)malloc(sizeof(char) * (j + 1));

    if (temp == NULL)
        return NULL;

    j = 0;
    while (reserve[j] != '\0')
    {
        temp[j] = reserve[j];
        if (reserve[j] == '\n')
        {
            j++;
            break;
        }
        j++;
    }
    temp[j] = '\0';
    if (reserve[j] != '\0')
    {
        int len = ft_strlen(reserve+j);
        char *t = (char *)malloc(sizeof(char) * (len+1));
        i = 0;
        while (reserve[j] != '\0')
        {
            t[i] = reserve[j];
            i++;
            j++;
        }
        t[i] = '\0';
        free(reserve);
        reserve = (char *)malloc(sizeof(char) * (len+1));
        i = 0;
        while (t[i] != '\0')
        {
            reserve[i] = t[i];
            i++;
        }
        reserve[i] = '\0';
        free(t);
    }
    else
    {
        free(reserve);
        reserve = NULL;
    }

    return temp;
}


int main()
{
    int fd = open("example.txt", O_CREAT | O_RDWR);
    if (fd == -1)
    {
        return 1;
    }

    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));printf("%s", get_next_line(fd));printf("%s", get_next_line(fd));

    close(fd);
}