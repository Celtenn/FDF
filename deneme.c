#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include <math.h>

#define BUFFER_SIZE 1000
#define TILE_SIZE 1

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>

typedef struct s_data
{
    void *mlx;
    void *win;
    void *image;
    int **map;
    unsigned int **color;
    int rows;
    int cols;
    int len;
    int bitt;
    int endian;
    char *narr;

    int mouse_pressed;
    int start_x;
    int start_y;
    int current_x;
    int current_y;
	unsigned int current_color;
} t_data;

typedef struct o_data
{
    char *line;
    char **temp;
    char **values;
    int **map;
    int col;
    int row;
    unsigned int tmpu;
    int tmpi;
    int j;
} r_data;

int countw(char const *s, char c)
{
    int i = 0;
    int wnumber = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
            i++;
        else
        {
            wnumber++;
            while (s[i] != c && s[i])
                i++;
        }
    }
    return (wnumber);
}

char *creatw(char *daz, char const *s, int first_i, int last_i)
{
    int i = 0;
    while (i < last_i)
    {
        daz[i] = s[first_i + i];
        i++;
    }
    daz[i] = '\0';
    return (daz);
}

char *create_single_word(char const *s, int *index, char c)
{
    int w_len = 0;
    int first = *index;
    char *word;
    while (s[*index] != c && s[*index])
    {
        w_len++;
        (*index)++;
    }
    word = (char *)malloc(sizeof(char) * (w_len + 1));
    if (!word)
        return (0);
    creatw(word, s, first, w_len);
    return (word);
}

char **create_word(char **daza, char const *s, char c, int k_len)
{
    int i = 0, k = 0;
    while (s[i] && k < k_len)
    {
        if (s[i] != c)
        {
            daza[k] = create_single_word(s, &i, c);
            if (!daza[k])
            {
                while (--k > -1)
                    free(daza[k]);
                free(daza);
                return (0);
            }
            k++;
        }
        else
            i++;
    }
    daza[k] = NULL;
    return (daza);
}

char **ft_split(char *s, char c)
{
    int k_len;
    char **str;
    if (!s)
        return (0);
    k_len = countw(s, c);
    str = (char **)malloc(sizeof(char *) * (k_len + 1));
    if (!str)
        return (0);
    str = create_word(str, s, c, k_len);
    free(s);
    return (str);
}

int ft_atoi(char *str)
{
    unsigned int i = 0;
    int sign = 1;
    long int number = 0;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-10);
        number = (str[i] - '0') + (number * 10);
        i++;
    }
    return (number * sign);
}

int ft_strlen(const char *str)
{
    int i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char *ft_strchr(char *str, int c)
{
    if (!str)
        return (0);
    while (*str)
    {
        if (*str == c)
            return (str);
        str++;
    }
    return (0);
}

int ft_isdigit(int a)
{
    if (a >= '0' && a <= '9')
        return (1);
    return (0);
}

char *ft_strjoin(char *str, char *nbr)
{
    size_t p, i;
    char *arr;
    if (!str)
    {
        str = (char *)malloc(sizeof(char) * 1);
        str[0] = '\0';
    }
    if (!str || !nbr)
        return (NULL);
    arr = malloc(ft_strlen(str) + ft_strlen(nbr) + 1);
    if (!arr)
        return (NULL);
    i = 0;
    p = 0;
    while (str[p] != '\0')
        arr[i++] = str[p++];
    i = 0;
    while (nbr[i] != '\0')
        arr[p++] = nbr[i++];
    arr[p] = '\0';
    free(str);
    return (arr);
}

int count_values(char **values)
{
    int count = 0;
    while (values[count] != NULL)
        count++;
    return (count);
}

unsigned int atoi_hex(char *str)
{
    unsigned int res = 0;
    int val;
    if (!str)
        return (0);
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

char *ft_line(char *str)
{
    char *arr;
    int i = 0;
    if (!str[i])
        return (0);
    while (str[i] && str[i] != '\n')
        i++;
    arr = malloc(i + 2);
    if (!arr)
        return (0);
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        arr[i] = str[i];
        i++;
    }
    arr[i] = '\0';
    return (arr);
}

char *ft_last(char *str)
{
    char *arr;
    int i = 0, p = 0;
    while (str[p] && str[p] != '\n')
        p++;
    if (!str[p])
    {
        free(str);
        return (0);
    }
    arr = malloc(ft_strlen(str) - p + 1);
    if (!arr)
        return (0);
    p++;
    while (str[p])
        arr[i++] = str[p++];
    arr[i] = '\0';
    free(str);
    return (arr);
}

char *ft_read(char *str, int fd)
{
    int read_len = 1;
    char *buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (0);
    while (!ft_strchr(str, '\n') && read_len != 0)
    {
        read_len = read(fd, buffer, BUFFER_SIZE);
        if (read_len == -1)
        {
            free(buffer);
            return (0);
        }
        buffer[read_len] = '\0';
        str = ft_strjoin(str, buffer);
    }
    free(buffer);
    return (str);
}

char *get_next_line(int fd)
{
    static char *str;
    char *arr;
    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        free(str);
        str = NULL;
        return (0);
    }
    str = ft_read(str, fd);
    if (!str)
        return (0);
    arr = ft_line(str);
    str = ft_last(str);
    return (arr);
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
    double width_distance;
    double height_distance;
    double scale;
    width_distance = (double)(750) / (data->rows * TILE_SIZE);
    height_distance = (double)(450) / (data->cols * TILE_SIZE);
    if (width_distance > height_distance)
        scale = height_distance;
    else
        scale = width_distance;
    int prev_x = *x;
    int prev_y = *y;
    *x = (prev_x - prev_y) * cos(0.6) * scale + 600;
    *y = (prev_x + prev_y) * sin(0.6) * scale + 200 - z;
}

void draw_line(int x0, int y0, int x1, int y1, t_data *data, unsigned int color) 
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx, sy;
    int err = dx - dy;
    int e2;
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
        if (x0 >= 0 && x0 < 1500 && y0 >= 0 && y0 < 900)
	{
		int pixel_index = (y0 * data->len) + (x0 * (data->bitt / 8));
		*(unsigned int *)(data->narr + pixel_index) = color;
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

void draw_map(int **map, t_data *data) 
{
    int y = 0, x = 0;
    int x_proj = 0, y_proj = 0;
    int x_next = 0, y_next = 0;

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
        mlx_destroy_window(data->mlx, data->win);
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
            mlx_destroy_window(data->mlx, data->win);
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

int random_color()
{
    return (rand() % 0xFFFFFF);
}

int mouse_press(int button, int x, int y, t_data *data)
{
    if (button == 1) // Sol
    {
        data->mouse_pressed = 1;
        data->start_x = x;
        data->start_y = y;
    }
	else if (button == 3) // Sağ
	{
		unsigned int i = random_color();
		data->current_color = i;
	}
	else if (button == 2) // Orta
	{
        data->start_x = x;
        data->start_y = y;
		data->mouse_pressed = 2;
	}
    return (0);
}

int mouse_release(int button, int x, int y, t_data *data)
{
    if (button == 1) // Bırakıldığında
    {
        data->mouse_pressed = 0;

        draw_line(data->start_x, data->start_y, x, y, data, data->current_color);
        mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
    }
	else if (button == 2)
	{
		data->mouse_pressed = 0;

        draw_line(data->start_x, data->start_y, x, y, data, 0x000000);
        mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	}
    return (0);
}

int mouse_move(int x, int y, t_data *data)
{
    if (data->mouse_pressed == 1)
    {
        draw_line(data->start_x, data->start_y, x, y, data, data->current_color);
        mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
    }
	else if (data->mouse_pressed == 2)
	{
		draw_line(data->start_x, data->start_y, x, y, data, 0x000000);
        mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	}
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;
    int i = 0;
    char *str;
    int fd;

    if (argc != 2) 
    {
        printf("Geçerli dosyayi girin!\n");
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
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
    data.len = (1500 * 32) / 8;
    data.bitt = 32;

    data.mouse_pressed = 0;
    data.start_x = 0;
    data.start_y = 0;
    data.current_x = 0;
    data.current_y = 0;
	data.current_color = 0xFFFFFF;
    
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1500, 900, "fdf");
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

    mlx_hook(data.win, 4, 1L << 2, mouse_press, &data);
	mlx_hook(data.win, 5, 1L << 3, mouse_release, &data);
	mlx_hook(data.win, 6, 1L << 6, mouse_move, &data);

    mlx_loop(data.mlx);
    return (0);
}