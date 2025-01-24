#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_ROWS 1000   // Maksimum satır sayısı
#define TILE_SIZE 20    // Her bir hücrenin piksel boyutu
 #include <string.h>
#include <stdlib.h>
#include "mlx.h"
#include <math.h>

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

char	**ft_split(char const *s, char c)
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
    char **values;
    size_t len = 0;
    ssize_t read;
    int **map = NULL;
    int col = 0;

    int row = 0;
    while ((read = getline(&line, &len, fdopen(fd, "r"))) != -1) 
    {
        values = ft_split(line, ' ');
        if (!map) 
        {
            *cols = count_values(values); // İlk satırdaki kolon sayısı
            map = malloc(sizeof(int *) * MAX_ROWS);
        }
        map[row] = malloc(sizeof(int) * (*cols));
        while (col < *cols) 
        {
            map[row][col] = atoi(values[col]);
            col++;
        }
        row++;
        free(values);
    }
    *rows = row;
    close(fd);
    return map;
}

void iso_projection(int *x, int *y, int z) 
{
    int prev_x = *x;
    int prev_y = *y;

    *x = (prev_x - prev_y) * cos(0.523599); // 30 derece
    *y = (prev_x + prev_y) * sin(0.523599) - z; 
}

void draw_line(int x0, int y0, int x1, int y1, void *mlx, void *win) 
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
        mlx_pixel_put(mlx, win, x0, y0, 0xADD8E6); // Mavi piksel çiz
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
    int y = 0;
    int x = 0;
    int x_proj = 0;
    int y_proj = 0;
    int x_next = 0;
    int y_next = 0;

    while (y < rows) 
    {
        while (x < cols) 
        {
            x_proj = x * TILE_SIZE;
            y_proj = y * TILE_SIZE;
            iso_projection(&x_proj, &y_proj, map[y][x]);

            if (x < cols - 1) 
            {
                x_next = (x + 1) * TILE_SIZE;
                y_next = y * TILE_SIZE;
                iso_projection(&x_next, &y_next, map[y][x + 1]);
                draw_line(x_proj, y_proj, x_next, y_next, mlx, win);
            }
            if (y < rows - 1) 
            {
                x_next = x * TILE_SIZE;
                y_next = (y + 1) * TILE_SIZE;
                iso_projection(&x_next, &y_next, map[y + 1][x]);
                draw_line(x_proj, y_proj, x_next, y_next, mlx, win);
            }
            x++;
        }
        y++;
    }
}

int main(int argc, char **argv)
{
    int rows;
    int cols;
    int **map;
    void *mlx;
    void *win;

    if (argc != 2) 
    {
        printf("Geçerli dosyayi girin!\n");
        return (1);
    }

    mlx = mlx_init();
    win = mlx_new_window(mlx, 1400, 800, "FDF");

    
    map = read_fdf_file(argv[1], &rows, &cols);

    if (!map) 
    {
        printf("Error reading map file\n");
        return (1);
    }

    draw_map(map, rows, cols, mlx, win);

    mlx_loop(mlx);
    return (0);
}
