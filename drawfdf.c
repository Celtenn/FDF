#include "fdf.h"

double calculate_scale(t_data *data)
{
    double width_distance = (double)(1600) / (data->rows * TILE_SIZE);
    double height_distance = (double)(550) / (data->cols * TILE_SIZE);
    return (width_distance > height_distance) ? height_distance : width_distance;
}

void iso_projection(int *x, int *y, int z, t_data *data)
{
    double scale = calculate_scale(data);
    int prev_x = *x;
    int prev_y = *y;

    *x = (prev_x - prev_y) * cos(0.6) * scale + 600; // 150 derece
    *y = (prev_x + prev_y) * sin(0.6) * scale + 200 - z;
}

void draw_horizontal_lines(int y, t_data *data, int **map)
{
    int x = 0;
    int x_proj, y_proj, x_next, y_next;

    while (x < data->cols - 1)
    {
        x_proj = x * TILE_SIZE;
        y_proj = y * TILE_SIZE;
        iso_projection(&x_proj, &y_proj, map[y][x], data);

        x_next = (x + 1) * TILE_SIZE;
        y_next = y * TILE_SIZE;
        iso_projection(&x_next, &y_next, map[y][x + 1], data);

        draw_line(x_proj, y_proj, x_next, y_next, data, data->color[y][x + 1]);
        x++;
    }
}

void draw_vertical_lines(int y, t_data *data, int **map)
{
    int x = 0;
    int x_proj, y_proj, x_next, y_next;

    while (x < data->cols)
    {
        x_proj = x * TILE_SIZE;
        y_proj = y * TILE_SIZE;
        iso_projection(&x_proj, &y_proj, map[y][x], data);

        if (y < data->rows - 1)
        {
            x_next = x * TILE_SIZE;
            y_next = (y + 1) * TILE_SIZE;
            iso_projection(&x_next, &y_next, map[y + 1][x], data);

            draw_line(x_proj, y_proj, x_next, y_next, data, data->color[y + 1][x]);
        }
        x++;
    }
}

void draw_map(int **map, t_data *data)
{
    int y = 0;

    while (y < data->rows)
    {
        draw_horizontal_lines(y, data, map);
        draw_vertical_lines(y, data, map);
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}