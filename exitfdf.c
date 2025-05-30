/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitfdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idkahram <idkahram@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 01:36:14 by idkahram          #+#    #+#             */
/*   Updated: 2025/02/11 01:36:14 by idkahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "minilibx-linux/mlx.h"

void	free_map(int **map)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_color(unsigned int **color)
{
	int	i;

	i = 0;
	if (color != NULL)
	{
		while (color[i])
		{
			free(color[i]);
			i++;
		}
		free(color);
	}
}

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_map(data->map);
	free_color(data->color);
	if (data->image != NULL)
		mlx_destroy_image(data->mlx, data->image);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}

void	handle_esc_key(t_data *data)
{
	free_map(data->map);
	free_color(data->color);
	if (data->image != NULL)
		mlx_destroy_image(data->mlx, data->image);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	ft_printf("ESC tuşuna basildi. Program kapaniyor.\n");
	exit(0);
}

int	key_hook_esc(int keycode, void *param)
{
	t_data	*data;

	if (keycode == 65307)
	{
		data = (t_data *)param;
		handle_esc_key(data);
	}
	return (0);
}
