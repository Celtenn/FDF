#ifndef FDF_H
#define FDF_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include <math.h>

#define SCALE_FACTOR 0.3
#define BUFFER_SIZE 1000
#define TILE_SIZE 15

typedef struct s_data
{
    void *mlx;
    void *win;
	void *image;
    unsigned int **map;
    int rows;
    int cols;
	int len;
	int bitt;
	int endian;
	char *narr;
} t_data;


char	*get_next_line(int fd);
char	**ft_split(char *s, char c);
int count_values(char **values);
int	ft_atoi(char *str);
int	ft_strlen(const char *str);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *str, char *nbr);


#endif