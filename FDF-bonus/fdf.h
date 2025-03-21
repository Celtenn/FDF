#ifndef FDF_H
#define FDF_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include <math.h>

#define BUFFER_SIZE 1000

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
    int offsetx;
    int offsety;
    double scale;
    double proj;
    int zoom;
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

char	*get_next_line(int fd);
int	ft_printf(char *str, ...);
char	**ft_split(char *s, char c);
int count_values(char **values);
int	ft_atoi(char *str);
int	ft_strlen(const char *str);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *str, char *nbr);
int	ft_isdigit(int a);
int **read_fdf_file(char *filename, t_data *data);
void draw_map(int **map, t_data *data);
void draw_line(int x0, int y0, int x1, int y1, t_data *data, unsigned int color);
int close_window(void *param);
int	key_hook(int keycode, void *param);
unsigned int atoi_hex(char *str);
double	calculate_scale(t_data *data);
int	redraw(void *param);
void	handle_esc_key(t_data *data);

#endif