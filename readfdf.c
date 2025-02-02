#include "fdf.h"

void init_r_data(r_data *r_data)
{
    r_data->line = NULL;
    r_data->temp = NULL;
    r_data->values = NULL;
    r_data->map = NULL;
    r_data->col = 0;
    r_data->row = 0;
    r_data->tmpu = 0;
    r_data->tmpi = 0;
    r_data->j = 0;
}

void allocate_memory(t_data *data, r_data *r_data)
{
    if (!r_data->map)
    {
        r_data->map = malloc(sizeof(int *) * (data->rows + 1));
        data->color = malloc(sizeof(unsigned int *) * (data->rows + 1));
    }
    data->cols = count_values(r_data->values);
    r_data->map[r_data->row] = malloc(sizeof(int) * (data->cols + 1));
    data->color[r_data->row] = malloc(sizeof(unsigned int) * (data->cols + 1));
}

void process_value(r_data *r_data, t_data *data, char *value)
{
    if (ft_atoi(value) == -10)
    {
        r_data->j = 0;
        r_data->temp = ft_split(value, ',');
        r_data->tmpi = ft_atoi(r_data->temp[0]);
        r_data->map[r_data->row][r_data->col] = r_data->tmpi;
        r_data->tmpu = atoi_hex(r_data->temp[1]);
        data->color[r_data->row][r_data->col] = r_data->tmpu;
        while (r_data->temp[r_data->j])
        {
            free(r_data->temp[r_data->j]);
            r_data->j++;
        }
        free(r_data->temp);
    }
    else
    {
        r_data->map[r_data->row][r_data->col] = ft_atoi(value);
        data->color[r_data->row][r_data->col] = atoi_hex("0xADD8E6");
        free(value);
    }
}

void process_line(r_data *r_data, t_data *data, char *line)
{
    r_data->values = ft_split(line, ' ');
    allocate_memory(data, r_data);
    r_data->col = 0;
    while (r_data->col < data->cols)
    {
        process_value(r_data, data, r_data->values[r_data->col]);
        r_data->col++;
    }
    free(r_data->values);
}

int **read_fdf_file(char *filename, t_data *data)
{
    r_data r_data;
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return NULL;
    }

    init_r_data(&r_data);
    while ((r_data.line = get_next_line(fd)))
    {
        process_line(&r_data, data, r_data.line);
        r_data.row++;
    }
    r_data.map[r_data.row] = NULL;
    data->color[r_data.row] = NULL;
    close(fd);
    return (r_data.map);
}