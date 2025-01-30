#include "fdf.h"

char	*ft_line(char *str)
{
	char	*arr;
	int		i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	arr = malloc(i + 2);
	if (!arr)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		arr[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		arr[i] = str[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_last(char *str)
{
	char	*arr;
	int		i;
	int		p;

	i = 0;
	p = 0;
	while (str[p] && str[p] != '\n')
	{
		p++;
	}
	if (!str[p])
	{
		free(str);
		return (0);
	}
	arr = malloc(ft_strlen(str) - p + 1);
	if (!arr)
		return (0);
	p++;
	while (str[p])
		arr[i++] = str[p++];
	arr[i] = '\0';
	free(str);
	return (arr);
}

char	*ft_read(char *str, int fd)
{
	int		read_len;
	char	*buffer;

	read_len = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	while (!ft_strchr(str, '\n') && read_len != 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[read_len] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*arr;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(str);
		str = NULL;
		return (0);
	}
	str = ft_read(str, fd);
	if (!str)
		return (0);
	arr = ft_line(str);
	str = ft_last(str);
	return (arr);
}
