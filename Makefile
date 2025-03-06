NAME = fractol

SRC = parsing.c utils_function.c fractol.c mandelbrot.c julia.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX = -L./minilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re