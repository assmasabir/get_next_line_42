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
    j= 0;
   
    buff = (char*)malloc(sizeof(char)*size);
    if (buff == NULL)
        return NULL;
    reserve = (char*)malloc(sizeof(char)*size);
    if (reserve == NULL)
        return NULL;
    while (ft_strchr(buff,'\n')==0)
    {
        res = read(fd, buff, size);
        if (res == -1)
        return (NULL);
        buff[res] = '\0';
        while(buff[i] != '\0')
        {
            reserve[i]=buff[i];
            i++;
        }
        reserve[i]='\0';
    }
    temp = (char*)malloc(sizeof(char)*(size+1));
        if (temp == NULL)
            return NULL;
    while (reserve[j] != '\0')
    { 
        if (reserve[j] != '\n')
        {
            temp[j]= reserve[j];
            j++;
        }
        else 
        {
            temp[j] = reserve[j];
            j++;
            break;
        }
    }
    temp[j]= '\0';

 

    return (temp);
    
}
int main ()
{
    int fd = open("example.txt", O_CREAT|O_RDWR);
    printf("%s", get_next_line(fd));


}