#include "fdf.h"

unsigned int **read_fdf_file(char *filename, t_data *data)
{
	r_data r_data;
    int fd = open(filename, O_RDONLY);
    if (fd < 0) 
    {
        perror("Error opening file");
        return NULL;
    }

    r_data.line = NULL;
    r_data.temp = NULL;
    r_data.values = NULL;
    r_data.map = NULL;
    r_data.col = 0;
    r_data.row = 0;
    r_data.tmp = 0;
	r_data.j = 0;

    while ((r_data.line = get_next_line(fd))) 
    {
		r_data.values = NULL;
        r_data.values = ft_split(r_data.line, ' ');
        if (!r_data.map) 
        {
            data->cols = count_values(r_data.values);
            r_data.map = malloc(sizeof(unsigned int *) * (data->cols + 1));
        }
        r_data.map[r_data.row] = malloc(sizeof(unsigned int) * (data->cols));
        r_data.col = 0;
        while (r_data.col < data->cols) 
        {
            if (ft_atoi(r_data.values[r_data.col]) == -10)
            {
				r_data.j = 0;
                r_data.temp = ft_split(r_data.values[r_data.col], ',');
                r_data.tmp = atoi(r_data.temp[r_data.j]);
                r_data.map[r_data.row][r_data.col] = r_data.tmp;
                r_data.col++;
				while (r_data.temp[r_data.j])
				{
                	free(r_data.temp[r_data.j]);
					r_data.j++;
				}
				free(r_data.temp);
            }
            else
            {
                r_data.map[r_data.row][r_data.col] = ft_atoi(r_data.values[r_data.col]);
                free(r_data.values[r_data.col]);
                r_data.col++;
            }
        }
		free(r_data.values);
        r_data.row++;
    }
    r_data.map[r_data.row] = NULL;
    data->rows = r_data.row;
    close(fd);
    return (r_data.map);
}

void iso_projection(int *x, int *y, int z, t_data *data) 
{
	int map_width = data->cols * TILE_SIZE;
	int map_height = data->rows * TILE_SIZE;

	int scale_x = 1600 / map_width;
	int scale_y = 900 / map_height;

	float scale = (scale_x < scale_y) ? scale_x : scale_y;
	if (scale < 0.2)
		scale = 0.25;
	int offsetx = 1600 / 2 - ((data->cols * TILE_SIZE) * scale) / 2;
	int offsety = 900 / 2 - ((data->rows * TILE_SIZE) * scale) / 2;
    int prev_x = *x;
    int prev_y = *y;

    *x = (prev_x - prev_y) * cos(0.6) * scale + offsetx; // 150 derece
    *y = (prev_x + prev_y) * sin(0.6) * scale + offsety - (z * ex);
}

int is_inside(int x, int y) 
{
    return (x >= 0 && x < 1600 && y >= 0 && y < 900);
}

int clip_line(int *x0, int *y0, int *x1, int *y1) 
{
    if (is_inside(*x0, *y0) && is_inside(*x1, *y1))
	{
        return (1);
    }

    if (*x0 < 0)
		*x0 = 0;
    if (*x0 >= 1600)
		*x0 = 1600 - 1;
    if (*y0 < 0)
		*y0 = 0;
    if (*y0 >= 900)
		*y0 = 900 - 1;

    if (*x1 < 0)
		*x1 = 0;
    if (*x1 >= 1600)
		*x1 = 1600 - 1;
    if (*y1 < 0)
		*y1 = 0;
    if (*y1 >= 900)
		*y1 = 900 - 1;

    return (1);
}

void draw_line(int x0, int y0, int x1, int y1, t_data *data) 
{
	 if (!clip_line(&x0, &y0, &x1, &y1))
        return;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx;
    int sy;
    int err = dx - dy;
    int e2;
	//printf("Drawing line from (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
    if (x0 < x1)
        sx = 1;
    if (x0 > x1)
        sx = -1;
    if (y0 < y1)
        sy = 1;
    if (y0 > y1)
        sy = -1;
    while (1) 
    {
        if (is_inside(x0, y0))
		{
            int pixel_index = (y0 * data->len) + (x0 * (data->bitt / 8));
            *(unsigned int *)(data->narr + pixel_index) = 0xADD8E6;  // Mavi renk
        }
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy) 
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) 
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_map(unsigned int **map, t_data *data) 
{
    int y = 0;
    int x = 0;
    int x_proj = 0;
    int y_proj = 0;
    int x_next = 0;
    int y_next = 0;

    while (y < data->rows) 
    {
        x = 0;
        while (x < data->cols) 
        {
            x_proj = x * TILE_SIZE;
            y_proj = y * TILE_SIZE;
            iso_projection(&x_proj, &y_proj, map[y][x], data);

            if (x < data->cols - 1)
            {
                x_next = (x + 1) * TILE_SIZE;
                y_next = y * TILE_SIZE;
                iso_projection(&x_next, &y_next, map[y][x + 1], data);
                draw_line(x_proj, y_proj, x_next, y_next, data);
            }
            if (y < data->rows - 1) 
            {
                x_next = x * TILE_SIZE;
                y_next = (y + 1) * TILE_SIZE;
                iso_projection(&x_next, &y_next, map[y + 1][x], data);
                draw_line(x_proj, y_proj, x_next, y_next, data);
            }
            x++;
        }
        y++;
    }
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

int redraw(void *param)
{
    t_data *data = (t_data *)param;
    mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
    return (0);
}

int close_window(void *param) 
{
	int i = 0;
    t_data *data = (t_data *)param;

    if (data->map != NULL) 
	{
        while (data->map[i]) 
		{
            free(data->map[i]);
			i++;
        }
        free(data->map);
    }
    if (data->image != NULL)
	    mlx_destroy_image(data->mlx, data->image);
    if (data->win != NULL) 
	{
        mlx_destroy_window(data->mlx, data->win);
    }
    if (data->mlx != NULL) 
	{
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    exit(0);
}

int key_hook_esc(int keycode, void *param)
{
    if (keycode == 65307) // ESC tuşu
	{
		int i;
		t_data *data = (t_data *)param;

    	if (data->map != NULL) 
		{
			i = 0;
        	while (data->map[i] != NULL) 
			{
            	free(data->map[i]);
				i++;
        	}
        	free(data->map);
    	}
		if (data->image != NULL)
			mlx_destroy_image(data->mlx, data->image);
    	if (data->win != NULL) 
		{
        	mlx_destroy_window(data->mlx, data->win);
    	}
    	if (data->mlx != NULL) 
		{
        	mlx_destroy_display(data->mlx);
        	free(data->mlx);
    	}
        printf("ESC tuşuna basildi. Program kapaniyor.\n");
		exit(0);
    }
    return (0);
}

//Key Press Event (Tuş Basımı): KeyPress (event kodu: 2)
//Key Release Event (Tuş Bırakma): KeyRelease (event kodu: 3)
//Mouse Motion (Fare Hareketi): MotionNotify (event kodu: 6)
//Mouse Click (Fare Tıklaması): ButtonPress (event kodu: 4)
//Window Close (Pencere Kapatma): DestroyNotify (event kodu: 17)

int main(int argc, char **argv)
{
	t_data data;

    if (argc != 2) 
    {
        printf("Geçerli dosyayi girin!\n");
        return (1);
    }
    data.mlx = NULL;
    data.win = NULL;
    data.image = NULL;
    data.narr = NULL;
	data.len = (1600 * 32) / 8;
	data.bitt = 32;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1600, 900, "fdf");
	data.image = mlx_new_image(data.mlx, 1600, 900);
	data.narr = mlx_get_data_addr(data.image, &data.bitt, &data.len, &data.endian);

    data.map = read_fdf_file(argv[1], &data);

    if (!data.map)
    {
        printf("Hatali harita!\n");
        return (1);
    }

    draw_map(data.map, &data);
	mlx_hook(data.win, 2, 1L << 0, key_hook_esc, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_expose_hook(data.win, redraw, &data);

    mlx_loop(data.mlx);
    return (0);
}
