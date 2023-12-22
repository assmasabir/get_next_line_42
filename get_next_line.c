#include "get_next_line.h"


char *get_next_line(int fd)
{
    ssize_t res;
    static char *buff;
    size_t size = 2;
    int i;
    char *temp;
    int j;
    static char *reserve;

    i = 0;
    j = 0;

    if (buff == NULL)
        buff = (char *)malloc(sizeof(char) * size);

    if (reserve == NULL)
        reserve = (char *)malloc(sizeof(char) * size);

    if (buff == NULL || reserve == NULL)
        return NULL;

    while ((res = read(fd, buff, size)) > 0)
    {
        buff[res] = '\0';
        i = 0;
        while (buff[i] != '\0')
        {
            reserve[j] = buff[i];
            i++;
            j++;
        }
        reserve[j] = '\0';

        if (ft_strchr(buff, '\n') != 0)
            break;
    }

    if (res == -1 || (res == 0 && j == 0))
        return NULL;

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

    return temp;
}
int main ()
{
    int fd = open("example.txt", O_CREAT|O_RDWR);
    printf("%s", get_next_line(fd));
     printf("%s", get_next_line(fd));
      printf("%s", get_next_line(fd));
       printf("%s", get_next_line(fd));
        printf("%s", get_next_line(fd));


}
