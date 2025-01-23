#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (0);
}

char	*ft_strjoin(char *str, char *nbr)
{
	size_t	p;
	size_t	i;
	char	*arr;

	if (!str)
	{
		str = (char *)malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	if (!str || !nbr)
		return (NULL);
	arr = malloc(ft_strlen(str) + ft_strlen(nbr) + 1);
	if (!arr)
		return (NULL);
	i = 0;
	p = 0;
	while (str[p] != '\0')
		arr[i++] = str[p++];
	i = 0;
	while (nbr[i] != '\0')
		arr[p++] = nbr[i++];
	arr[p] = '\0';
	free(str);
	return (arr);
}
