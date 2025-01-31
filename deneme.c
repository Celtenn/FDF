#include "fdf.h"

unsigned int atoi_hex(char *str)
{
    unsigned int res = 0;
    int val;

    while (*str)
    {
        if (*str <= 9 && *str >= 0)
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
			data->color = malloc(sizeof(unsigned int *) * (data->cols + 1));
        }
        r_data.map[r_data.row] = malloc(sizeof(unsigned int) * (data->cols));
		data->color[r_data.row] = malloc(sizeof(unsigned int) * (data->cols));
        r_data.col = 0;
        while (r_data.col < data->cols) 
        {
            if (!atoi(r_data.values[r_data.col]))
            {
				r_data.j = 0;
                r_data.temp = ft_split(r_data.values[r_data.col], ',');
                r_data.tmp = ft_atoi(r_data.temp[r_data.j]);
                r_data.map[r_data.row][r_data.col] = r_data.tmp;
				data->color[r_data.row][r_data.col] = 0x00FFFFFF; // Varsayılan renk (beyaz)
				if (r_data.temp[r_data.j + 1] != NULL) // Renk bilgisi varsa
        		{
            		data->color[r_data.row][r_data.col] = atoi_hex(r_data.temp[r_data.j + 1]); // Renk bilgisini hex'ten al
        		}
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
				data->color[r_data.row][r_data.col] = 0x00FFFFFF; // Varsayılan renk (beyaz)
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
	int ex = 3;
	float scale = 1;
	float scale_x = 1800.0 / (float)(data->cols);
	float scale_y = 900.0 / (data->rows);
	if (scale_x < scale_y)
		scale = scale_x;
	if (scale_x > scale_y)
		scale = scale_y;
	if (scale < 0.3)
		scale = 0.20;
	if (scale > 1.0)
		scale = 0.8;
	//int offsetx = 1800 / 2 - ((data->cols * TILE_SIZE) * scale) / 2;
	//int offsety = 900 / 2 - ((data->rows * TILE_SIZE) * scale) / 2;
    int prev_x = *x;
    int prev_y = *y;

    *x = (prev_x - prev_y) * cos(0.6) * 0.2 + 600; // 150 derece
    *y = (prev_x + prev_y) * sin(0.6) * 0.2 + 400 - (z * ex);
}

int is_inside(int x, int y) 
{
    return (x >= 0 && x < 1600 && y >= 0 && y < 900);
}

int clip_line(int *x0, int *y0, int *x1, int *y1) 
{
    if (is_inside(*x0, *y0) && is_inside(*x1, *y1)) {
        return (1);
    }

    if (*x0 < 0) *x0 = 0;
    if (*x0 >= 1800) *x0 = 1600 - 1;
    if (*y0 < 0) *y0 = 0;
    if (*y0 >= 900) *y0 = 900 - 1;

    if (*x1 < 0) *x1 = 0;
    if (*x1 >= 1800) *x1 = 1600 - 1;
    if (*y1 < 0) *y1 = 0;
    if (*y1 >= 900) *y1 = 900 - 1;

    return (1);
}

void draw_line(int x0, int y0, int x1, int y1, t_data *data, unsigned int color) 
{
	 //if (!clip_line(&x0, &y0, &x1, &y1))
        //return;
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
            *(unsigned int *)(data->narr + pixel_index) = color;  // Mavi renk
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
    data.mlx = NULL;
    data.win = NULL;
    data.image = NULL;
    data.narr = NULL;
	data.len = (1920 * 32) / 8;
	data.bitt = 32;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1920, 1080, "fdf");
	data.image = mlx_new_image(data.mlx, 1920, 1080);
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
