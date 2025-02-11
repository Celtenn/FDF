/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idkahram <idkahram@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 02:24:51 by idkahram          #+#    #+#             */
/*   Updated: 2025/02/11 02:24:51 by idkahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"

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

void	init_mlx(t_data *data)
{
	char	*t;

	data->mlx = mlx_init();
	if (!data->mlx)
		close_window(data);
	data->win = mlx_new_window(data->mlx, 1500, 900, "fdf");
	if (!data->win)
		close_window(data);
	data->image = mlx_new_image(data->mlx, 1500, 900);
	if (!data->image)
		close_window(data);
	t = mlx_get_data_addr(data->image, &data->bitt, &data->len, &data->endian);
	if (!t)
		close_window(data);
	data->narr = t;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->image = NULL;
	data->narr = NULL;
	data->map = NULL;
	data->color = NULL;
	data->len = (1500 * 32) / 8;
	data->bitt = 32;
	init_mlx(data);
	data->height = 3;
	data->x1 = 0;
	data->y1 = 0;
	data->dx = 0;
	data->dy = 0;
	data->sx = 0;
	data->sy = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Geçerli dosyayi girin!\n");
		return (1);
	}
	data.rows = count_rows(argv[1]);
	init_data(&data);
	data.map = read_fdf_file(argv[1], &data);
	if (!data.map)
	{
		ft_printf("Hatali harita!\n");
		close_window(&data);
	}
	draw_map(data.map, &data);
	mlx_hook(data.win, 2, 1L << 0, key_hook_esc, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
