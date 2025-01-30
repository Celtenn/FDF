#include "fdf.h"
#include <stdarg.h>

int	ft_putchar(char c, int *len_count)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	(*len_count)++;
	return (1);
}

int	ft_putstr(char *str, int *len_count)
{
	int		i;
	char	*strnull;

	i = 0;
	strnull = "(null)";
	if (!str)
	{
		while (*strnull)
		{
			i = ft_putchar(*strnull, len_count);
			if (i == -1)
				return (-1);
			strnull++;
		}
		return (1);
	}
	while (*str)
	{
		i = ft_putchar(*str, len_count);
		if (i == -1)
			return (-1);
		str++;
	}
	return (1);
}

int	ft_check(va_list ag, char *str, int *len_count)
{
	int	i;

	i = 0;
	if (*str == 'c')
		i = ft_putchar(va_arg(ag, int), len_count);
	else if (*str == 's')
		i = ft_putstr(va_arg(ag, char *), len_count);
	return (i);
}

int	ft_printf(char *str, ...)
{
	int		i;
	int		print_len;
	va_list	ag;

	i = 0;
	print_len = 0;
	if (!str)
		return (0);
	va_start(ag, str);
	while (*str && i != -1)
	{
		if (*str == '%')
		{
			str++;
			i = ft_check(ag, (char *)str, &print_len);
		}
		else
			i = ft_putchar(*str, &print_len);
		str++;
	}
	va_end(ag);
	if (i == -1)
		return (-1);
	return (print_len);
}
