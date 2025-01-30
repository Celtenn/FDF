NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iminilibx-linux
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm
SRC = deneme.c \
		ft_split.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_printf.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(INCLUDES) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re