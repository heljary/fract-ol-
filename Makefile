NAME = fractol
BNS = fractol_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -L./minilibx-linux -lmlx -lXext -lX11 -lm

SRC = parsing.c utils_function.c utils_function2.c mandelbrot.c julia.c
SRC_BNS = ./bonus/parsing_bonus.c ./bonus/utils_function_bonus.c ./bonus/utils_function2_bonus.c \
		./bonus/cubic_mandelbrot_bonus.c ./bonus/julia_bonus.c ./bonus/mandelbrot_bonus.c
OBJ = $(SRC:.c=.o)

OBJ_BNS = $(SRC_BNS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

bonus: $(BNS)

${BNS}: $(OBJ_BNS)
	${CC} ${CFLAGS} $(OBJ_BNS) $(MLX) -o ${BNS}

clean:
	rm -f $(OBJ) $(OBJ_BNS)

fclean: clean
	rm -f $(NAME) $(BNS)

re: fclean all