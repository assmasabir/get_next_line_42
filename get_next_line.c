#include "get_next_line.h"

char *get_next_line(int fd)
{
    int res;
    static char *buff;
    size_t size = 7;
    int i;
    char *temp;
    int j;

    i = 0;
    j=0;
    buff = (char*)malloc(sizeof(char)*size);
    if (buff == NULL)
        return NULL;

    res = read(fd, buff, size);
    if (res == -1)
        return (NULL);
    while (i < res && buff[i] != '\n')
        i++;
    if (i < res)
    {
        temp = (char*)malloc(sizeof(char)*(size+1));
        if (temp == NULL)
            return NULL;
        while(j < i+1)
        {
            temp[j]=buff[j];
            j++;
        }
        return (temp);
    }

    if (res == 0)
        return (buff);
    return ("allo");
}
int main ()
{
    int fd = open("example.txt", O_CREAT|O_RDWR);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
}