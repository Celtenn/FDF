#include "fdf.h"

unsigned int atoi_hex(char *str)
{
    unsigned int res = 0;
    int val;

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
    return res;
}

int **read_fdf_file(char *filename, t_data *data)
{
	r_data r_data;
	char *base = "0xADD8E6";
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
    r_data.tmpu = 0;
	r_data.tmpi = 0;
	r_data.j = 0;

    while ((r_data.line = get_next_line(fd))) 
    {
		r_data.values = NULL;
        r_data.values = ft_split(r_data.line, ' ');
        if (!r_data.map) 
        {
            r_data.map = malloc(sizeof(int *) * (data->rows + 1));
            data->color = malloc(sizeof(unsigned int *) * (data->rows + 1));
        }
        data->cols = count_values(r_data.values);
        r_data.map[r_data.row] = malloc(sizeof(int) * (data->cols + 1));
        data->color[r_data.row] = malloc(sizeof(unsigned int) * (data->cols + 1));
        r_data.col = 0;
        while (r_data.col < data->cols) 
        {
            if (ft_atoi(r_data.values[r_data.col]) == -10)
            {
				r_data.j = 0;
                r_data.temp = ft_split(r_data.values[r_data.col], ',');
                r_data.tmpi = ft_atoi(r_data.temp[0]);
                r_data.map[r_data.row][r_data.col] = r_data.tmpi;
				r_data.tmpu = atoi_hex(r_data.temp[1]);
                data->color[r_data.row][r_data.col] = r_data.tmpu;
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
				data->color[r_data.row][r_data.col] = atoi_hex(base);
                free(r_data.values[r_data.col]);
                r_data.col++;
            }
        }
		free(r_data.values);
        r_data.row++;
    }
    r_data.map[r_data.row] = NULL;
	data->color[r_data.row] = NULL;
    return (r_data.map);
}

void iso_projection(int *x, int *y, int z, t_data *data) 
{
	double	width_distance;
	double	height_distance;
	double scale;

	width_distance = (double)(1600) / (data->rows * TILE_SIZE);
	height_distance = (double)(550) / (data->cols * TILE_SIZE);
	if (width_distance > height_distance)
		scale = height_distance;
	else
		scale = width_distance;
    int prev_x = *x;
    int prev_y = *y;

    *x = (prev_x - prev_y) * cos(0.6) * scale + 600; // 150 derece
    *y = (prev_x + prev_y) * sin(0.6) * scale + 200 - z;
}

void draw_line(int x0, int y0, int x1, int y1, t_data *data, unsigned int color) 
{
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
        int pixel_index = (y0 * data->len) + (x0 * (data->bitt / 8));
        *(unsigned int *)(data->narr + pixel_index) = color;
        
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

void draw_map(int **map, t_data *data) 
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
                draw_line(x_proj, y_proj, x_next, y_next, data, data->color[y][x + 1]);
            }
            if (y < data->rows - 1) 
            {
                x_next = x * TILE_SIZE;
                y_next = (y + 1) * TILE_SIZE;
                iso_projection(&x_next, &y_next, map[y + 1][x], data);
                draw_line(x_proj, y_proj, x_next, y_next, data, data->color[y + 1][x]);
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
	if (data->color != NULL) 
		{
			i = 0;
        	while (data->color[i] != NULL) 
			{
            	free(data->color[i]);
				i++;
        	}
        	free(data->color);
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
		if (data->color != NULL) 
		{
			i = 0;
        	while (data->color[i] != NULL) 
			{
            	free(data->color[i]);
				i++;
        	}
        	free(data->color);
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
    int i = 0;
    char *str;
    int fd = open(argv[1], O_RDONLY);
    while ((str = get_next_line(fd)))
    {
        free(str);
        i++;
    }
    close(fd);
    data.rows = i;
    data.mlx = NULL;
    data.win = NULL;
    data.image = NULL;
    data.narr = NULL;
	data.len = (1800 * 32) / 8;
	data.bitt = 32;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1800, 900, "fdf");
	data.image = mlx_new_image(data.mlx, 1500, 900);
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
