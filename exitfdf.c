#include "fdf.h"

int redraw(void *param)
{
    t_data *data = (t_data *)param;
    mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
    return (0);
}

void free_map(int **map)
{
    int i = 0;

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

void free_color(unsigned int **color)
{
    int i = 0;

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

void destroy_resources(t_data *data)
{
    if (data->image != NULL)
        mlx_destroy_image(data->mlx, data->image);
    if (data->win != NULL)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx != NULL)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
}

int close_window(void *param)
{
    t_data *data = (t_data *)param;

    free_map(data->map);
    free_color(data->color);
    destroy_resources(data);

    exit(0);
}

void handle_esc_key(t_data *data)
{
    free_map(data->map);
    free_color(data->color);
    destroy_resources(data);
    printf("ESC tuşuna basildi. Program kapaniyor.\n");
    exit(0);
}

int key_hook_esc(int keycode, void *param)
{
    if (keycode == 65307) // ESC tuşu
    {
        t_data *data = (t_data *)param;
        handle_esc_key(data);
    }
    return (0);
}