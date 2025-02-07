#include "fdf.h"

void	init_r_data(t_temp *t_temp)
{
	t_temp->line = NULL;
	t_temp->temp = NULL;
	t_temp->values = NULL;
	t_temp->map = NULL;
	t_temp->col = 0;
	t_temp->row = 0;
	t_temp->tmpu = 0;
	t_temp->tmpi = 0;
	t_temp->j = 0;
}

void	allocate_memory(t_data *data, t_temp *t_temp)
{
	if (!t_temp->map)
	{
		t_temp->map = malloc(sizeof(int *) * (data->rows + 1));
		if (!t_temp->map)
			close_window(data);
		data->color = malloc(sizeof(unsigned int *) * (data->rows + 1));
		if (!data->color)
		{
			free_map(t_temp->map);
			close_window(data);
		}
	}
	data->cols = count_values(t_temp->values);
	t_temp->map[t_temp->row] = malloc(sizeof(int) * (data->cols + 1));
	if (!t_temp->map[t_temp->row])
	{
		free_map(t_temp->map);
		close_window(data);
	}
	data->color[t_temp->row] = malloc(sizeof(unsigned int) * (data->cols + 1));
	if (!data->color[t_temp->row])
	{
		free_map(t_temp->map);
		close_window(data);
	}
}

void	process_value(t_temp *t_temp, t_data *data, char *value)
{
	if (ft_atoi(value) == -10)
	{
		t_temp->j = 0;
		t_temp->temp = ft_split(value, ',');
		t_temp->tmpi = ft_atoi(t_temp->temp[0]);
		t_temp->map[t_temp->row][t_temp->col] = t_temp->tmpi;
		t_temp->tmpu = atoi_hex(t_temp->temp[1]);
		data->color[t_temp->row][t_temp->col] = t_temp->tmpu;
		while (t_temp->temp[t_temp->j])
		{
			free(t_temp->temp[t_temp->j]);
			t_temp->j++;
		}
		free(t_temp->temp);
	}
	else
	{
		t_temp->map[t_temp->row][t_temp->col] = ft_atoi(value);
		data->color[t_temp->row][t_temp->col] = atoi_hex("0xADD8E6");
		free(value);
	}
}

void	process_line(t_temp *t_temp, t_data *data, char *line)
{
	t_temp->values = ft_split(line, ' ');
	allocate_memory(data, t_temp);
	t_temp->col = 0;
	while (t_temp->col < data->cols)
	{
		process_value(t_temp, data, t_temp->values[t_temp->col]);
		t_temp->col++;
	}
	free(t_temp->values);
}

int	**read_fdf_file(char *filename, t_data *data)
{
	int		fd;
	t_temp	t_temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0);
	}
	init_r_data(&t_temp);
	t_temp.line = get_next_line(fd);
	while (t_temp.line)
	{
		process_line(&t_temp, data, t_temp.line);
		t_temp.line = get_next_line(fd);
		t_temp.row++;
	}
	t_temp.map[t_temp.row] = NULL;
	data->color[t_temp.row] = NULL;
	close(fd);
	return (t_temp.map);
}
