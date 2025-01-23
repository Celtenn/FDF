#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void ft_split_free(char **str)
{
    int i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}
int main()
{
    int a = 0;
    char *str;
    char **spl;
    int i = open("lan.txt", O_RDONLY);
    while ((str = get_next_line(i)))
    {
        a = 0;
        spl = ft_split(str, ' ');
        while (spl[a])
        {
            printf("%s", spl[a]);
            a++;
        }
        ft_split_free(spl);
        free(str);
    }
    printf("\n");
}