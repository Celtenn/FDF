#include "fdf.h"

unsigned int	atoi_hex(char *str)
{
	unsigned int	res;
	int				val;

	if (!str)
		return (0);
	res = 0;
	val = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			val = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			val = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			val = *str - 'A' + 10;
		res = res * 16 + val;
		str++;
	}
	return (res);
}

int	count_rows(char *filename)
{
	int		fd;
	int		rows;
	char	*line;

	rows = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		rows++;
	}
	close(fd);
	return (rows);
}

void	init_data(t_data *data)
{
	char	*t;

	data->mlx = NULL;
	data->win = NULL;
	data->image = NULL;
	data->narr = NULL;
	data->len = (1800 * 32) / 8;
	data->bitt = 32;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 2000, 1200, "fdf");
	data->image = mlx_new_image(data->mlx, 1800, 1200);
	t = mlx_get_data_addr(data->image, &data->bitt, &data->len, &data->endian);
	data->narr = t;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Geçerli dosyayi girin!\n");
		return (1);
	}
	data.rows = count_rows(argv[1]);
	init_data(&data);
	data.map = read_fdf_file(argv[1], &data);
	if (!data.map)
	{
		printf("Hatali harita!\n");
		return (1);
	}
	draw_map(data.map, &data);
	mlx_hook(data.win, 2, 1L << 0, key_hook_esc, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
