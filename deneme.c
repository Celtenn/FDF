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

int count_values(char **values) 
{
    int count = 0;
    while (values[count] != NULL)
        count++;
    return count;
}

char **ft_split(const char *str, char delimiter) 
{
    char **result = malloc(256 * sizeof(char *)); // Maksimum 256 kelime için
    char *token, *str_copy = strdup(str);
    int i = 0;

    token = strtok(str_copy, &delimiter);
    while (token != NULL) {
        result[i++] = strdup(token);
        token = strtok(NULL, &delimiter);
    }
    result[i] = NULL;
    free(str_copy);
    return result;
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
    size_t len = 0;
    ssize_t read;
    int **map = NULL;
    int col = 0;

    int row = 0;
    while ((read = getline(&line, &len, fdopen(fd, "r"))) != -1) 
    {
        char **values = ft_split(line, ' ');
        if (!map) 
        {
            *cols = count_values(values); // İlk satırdaki kolon sayısını kaydet
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
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) 
    {
        mlx_pixel_put(mlx, win, x0, y0, 0xFFFFFF); // Beyaz piksel çiz
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
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
            int x_proj = x * TILE_SIZE;
            int y_proj = y * TILE_SIZE;
            iso_projection(&x_proj, &y_proj, map[y][x]);

            if (x < cols - 1) 
            {
                int x_next = (x + 1) * TILE_SIZE;
                int y_next = y * TILE_SIZE;
                iso_projection(&x_next, &y_next, map[y][x + 1]);
                draw_line(x_proj, y_proj, x_next, y_next, mlx, win);
            }
            if (y < rows - 1) 
            {
                int x_next = x * TILE_SIZE;
                int y_next = (y + 1) * TILE_SIZE;
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
    if (argc != 2) 
    {
        printf("Geçerli dosyayi girin!\n");
        return (1);
    }

    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "FDF");

    int rows, cols;
    int **map = read_fdf_file(argv[1], &rows, &cols);

    if (!map) 
    {
        printf("Error reading map file\n");
        return (1);
    }

    draw_map(map, rows, cols, mlx, win);

    mlx_loop(mlx);
    return (0);
}
