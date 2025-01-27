#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#define OFFSET_X 900
#define OFFSET_Y 450
#define SCALE_FACTOR 1
#define BUFFER_SIZE 1000
#define MAX_ROWS 1000
#define TILE_SIZE 15

typedef struct s_data
{
    void *mlx;
    void *win;
    int **map;
    int rows;
    int cols;
} t_data;

int check_big(int **str, int rows, int cols)
{
	int i = 0;
	int a = 0;
	int temp = 1;
	while (i < rows)
	{
		a = 0;
		while (a < cols)
		{
			//printf("%d ", temp);
			if (str[i][a] < str[i][a + 1])
			{
				temp = str[i][a + 1];
			}
			a++;
		}
		i++;
	}
	//printf("%d", temp);
	//exit(1);
	return (temp);
}
int	ft_atoi(char *str)
{
	int		i;
	int					sign = 1;
	unsigned long int	number;

	i = 0;
	number = 0;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i])
	{
        if (str[i] < '0' || str[i] > '9')
        {
            return (-10);
        }
		number = (str[i] - '0') + (number * 10);
		i++;
	}
	return (number * sign);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(char *str, int c)
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

char	*ft_strjoin(char *str, char *nbr)
{
	size_t	p;
	size_t	i;
	char	*arr;

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

char	*ft_line(char *str)
{
	char	*arr;
	int		i;

	i = 0;
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
	if (str[i] == '\n')
	{
		arr[i] = str[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_last(char *str)
{
	char	*arr;
	int		i;
	int		p;

	i = 0;
	p = 0;
	while (str[p] && str[p] != '\n')
	{
		p++;
	}
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

char	*ft_read(char *str, int fd)
{
	int		read_len;
	char	*buffer;

	read_len = 1;
	buffer = malloc(BUFFER_SIZE + 1);
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

char	*get_next_line(int fd)
{
	static char	*str;
	char		*arr;

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

int	countw(char const *s, char c)
{
	int	i;
	int	wnumber;

	i = 0;
	wnumber = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			i++;
		}
		else
		{
			wnumber++;
			while (s[i] != c && s[i])
			{
				i++;
			}
		}
	}
	return (wnumber);
}

char	*creatw(char *daz, char const *s, int first_i, int last_i)
{
	int	i;

	i = 0;
	while (i < last_i)
	{
		daz[i] = s[first_i + i];
		i++;
	}
	daz[i] = '\0';
	return (daz);
}

char	*create_single_word(char const *s, int *index, char c)
{
	int		w_len;
	int		first;
	char	*word;

	w_len = 0;
	first = *index;
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

char	**create_word(char **daza, char const *s, char c, int k_len)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
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

char	**ft_split(char *s, char c)
{
	int		k_len;
	char	**str;

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

int count_values(char **values) 
{
    int count = 0;
    while (values[count] != NULL)
        count++;
    return count;
}

int **read_fdf_file(char *filename, int *rows, int *cols) 
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) 
    {
        perror("Error opening file");
        return NULL;
    }

    char *line = NULL;
    char **temp = NULL;
    char **values = NULL;
    int **map = NULL;
    int col = 0;
    int row = 0;
    int tmp = 0;
	int j = 0;

    while ((line = get_next_line(fd))) 
    {
		values = NULL;
        values = ft_split(line, ' ');
        if (!map) 
        {
            *cols = count_values(values);
            map = malloc(sizeof(int *) * MAX_ROWS);
        }
        map[row] = malloc(sizeof(int) * (*cols));
        col = 0;
        while (col < *cols) 
        {
            if (ft_atoi(values[col]) == -10)
            {
				j = 0;
                temp = ft_split(values[col], ',');
                tmp = atoi(temp[j]);
                map[row][col] = tmp;
                col++;
				while (temp[j])
				{
                	free(temp[j]);
					j++;
				}
				free(temp);
            }
            else
            {
                map[row][col] = atoi(values[col]);
                free(values[col]);
                col++;
            }
        }
		free(values);
        row++;
    }
    *rows = row;
    close(fd);
    return (map);
}

void iso_projection(int *x, int *y, int z, int ex, int cols, int rows) 
{
	double scale = (OFFSET_X / (double)rows * (double)cols);
	double scale1 = (OFFSET_Y / (double)cols * (double)rows);
    int prev_x = *x;
    int prev_y = *y;

	//printf("%d", rows);
	//exit(1);
	if (ex > 15)
		ex = 1;
	else
		ex = 15;
    *x = (prev_x - prev_y) * cos(0.6) * 1.0 + OFFSET_X; // 150 derece
    *y = (prev_x + prev_y) * sin(0.6) * 1.0 + OFFSET_Y - (z * 15);
}

void draw_line(int x0, int y0, int x1, int y1, void *mlx, void *win, int i) 
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx;
    int sy;
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
		if (i > 69)
        	mlx_pixel_put(mlx, win, x0, y0, 0xffffff); // Kırmızı piksel çiz
		else if (i > 39)
        	mlx_pixel_put(mlx, win, x0, y0, 0x802020); // Kırmızı piksel çiz
		else if (i >= 2)
        	mlx_pixel_put(mlx, win, x0, y0, 0xff00); // Yeşil piksel çiz
		else if (i >= 0)
        	mlx_pixel_put(mlx, win, x0, y0, 0xADD8E6); // Kırmızı piksel çiz
		else if (i < 0)
        	mlx_pixel_put(mlx, win, x0, y0, 0xADD8E6); // Kırmızı piksel çiz
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

void draw_map(int **map, int rows, int cols, void *mlx, void *win) 
{
	int ex = 1;
    int y = 0;
    int x = 0;
    int x_proj = 0;
    int y_proj = 0;
    int x_next = 0;
    int y_next = 0;

	ex = check_big(map, rows, cols);
    while (y < rows) 
    {
        x = 0;
        while (x < cols) 
        {
            x_proj = x * TILE_SIZE;
            y_proj = y * TILE_SIZE;
            iso_projection(&x_proj, &y_proj, map[y][x], ex, cols, rows);

            if (x < cols - 1)
            {
                x_next = (x + 1) * TILE_SIZE;
                y_next = y * TILE_SIZE;
                iso_projection(&x_next, &y_next, map[y][x + 1], ex, cols, rows);
                draw_line(x_proj, y_proj, x_next, y_next, mlx, win, map[y][x + 1]);
            }
            if (y < rows - 1) 
            {
                x_next = x * TILE_SIZE;
                y_next = (y + 1) * TILE_SIZE;
                iso_projection(&x_next, &y_next, map[y + 1][x], ex, cols, rows);
                draw_line(x_proj, y_proj, x_next, y_next, mlx, win, map[y + 1][x]);
            }
            x++;
        }
        y++;
    }
}

int redraw(void *param)
{
    t_data *data = (t_data *)param;
    mlx_clear_window(data->mlx, data->win);
    draw_map(data->map, data->rows, data->cols, data->mlx, data->win);
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
    if (data->win != NULL) 
	{
        mlx_destroy_window(data->mlx, data->win);
    }
    if (data->mlx != NULL) 
	{
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        data->mlx = NULL;
    }
	printf("Programdan cikis yapildi!");
    exit(0);
}

int key_hook_esc(int keycode, void *param)
{
    if (keycode == 65307) // ESC tuşu
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
	int i = 0;
	t_data data;

    if (argc != 2) 
    {
        printf("Geçerli dosyayi girin!\n");
        return (1);
    }

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1920, 1080, "FDF");

    data.map = read_fdf_file(argv[1], &data.rows, &data.cols);

    if (!data.map)
    {
        printf("Hatali harita!\n");
        return (1);
    }
    draw_map(data.map, data.rows, data.cols, data.mlx, data.win);
	mlx_hook(data.win, 2, 1L << 0, key_hook_esc, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_expose_hook(data.win, redraw, &data);

    mlx_loop(data.mlx);
    return (0);
}
