#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define OFFSET_X 500
#define OFFSET_Y 100
#define SCALE_FACTOR 0.8
#define BUFFER_SIZE 3
#define MAX_ROWS 100000   // Maksimum satır sayısı
#define TILE_SIZE 10    // Her bir hücrenin piksel boyutu
 #include <string.h>
#include <stdlib.h>
#include "mlx.h"
#include <math.h>

int	ft_atoi(char *str)
{
	unsigned int		i;
	int					sign;
	unsigned long int	number;

	i = 0;
	number = 0;
	while (str[i])
	{
        if (str[i] < '0' || str[i] > '9')
        {
            return (-10);
        }
		number = (str[i] - '0') + (number * 10);
		i++;
	}
	return (number);
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

unsigned int **read_fdf_file(char *filename, int *rows, int *cols) 
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) 
    {
        perror("Error opening file");
        return NULL;
    }

    char *line = NULL;
    char **temp;
    char **values;
    unsigned int **map = NULL;
    int col = 0;
    int row = 0;
    unsigned int tmp = 0;
    int j = 0;

    while ((line = get_next_line(fd))) 
    {
        values = ft_split(line, ' ');
        if (!map) 
        {
            *cols = count_values(values); // İlk satırdaki kolon sayısı
            map = malloc(sizeof(int *) * MAX_ROWS);
        }
        map[row] = malloc(sizeof(int) * (*cols));
        col = 0;
        while (col < *cols) 
        {
            if (ft_atoi(values[col]) == -10)
            {
                temp = ft_split(values[col], ',');
                j = 0;
                while (temp[j])
                {
                    tmp = strtol(temp[j], NULL, 16);
                    map[row][col] = tmp;
                    j++;
                    col++;
                    free(temp[j]);
                }
                free(temp);
            }
            else
            {
                map[row][col] = ft_atoi(values[col]);
                free(values[col]);
                col++;
            }
        }
        row++;
        free(values);
    }
    *rows = row;
    close(fd);
    return (map);
}

void iso_projection(int *x, int *y, int z) 
{
    int prev_x = *x;
    int prev_y = *y;

    *x = (prev_x - prev_y) * cos(0.523599) * SCALE_FACTOR + OFFSET_X; // 30 derece
    *y = (prev_x + prev_y) * sin(0.523599) * SCALE_FACTOR + OFFSET_Y - z;
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

void draw_map(unsigned int **map, int rows, int cols, void *mlx, void *win) 
{
    int y = 0;
    int x = 0;
    int x_proj = 0;
    int y_proj = 0;
    int x_next = 0;
    int y_next = 0;
    int max_z = -1; // En yüksek z değeri
    // Tepe noktasının belirlenmesi
    int peak_x = 0, peak_y = 0;

    while (y < rows) 
    {
        x = 0;
        while (x < cols) 
        {
            // Her nokta için projeksiyon hesapla
            x_proj = x * TILE_SIZE;
            y_proj = y * TILE_SIZE;
            iso_projection(&x_proj, &y_proj, map[y][x]);

            // Eğer bu nokta en yüksek z noktasına sahipse, bunu kaydet
            if (map[y][x] > max_z) {
                max_z = map[y][x];
                peak_x = x_proj;
                peak_y = y_proj;
            }

            // Diğer çizimleri yap (yan ve alt çizgileri)
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
        free(map[y]);
        y++;
    }
    free(map);
}

int main(int argc, char **argv)
{
    int rows;
    int cols;
    unsigned int **map;
    void *mlx;
    void *win;

    if (argc != 2) 
    {
        printf("Geçerli dosyayi girin!\n");
        return (1);
    }

    mlx = mlx_init();
    win = mlx_new_window(mlx, 900, 600, "FDF");

    
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
