CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME =	cub3D
SRC =	main.c \
		cub_utils.c \
		cub_map_check.c \
		cub_map_print.c \
		cub_map_print1.c \
		cub_map_set.c \
		cub_map_read.c \
		cub_map_value_input.c \
		cub_filename_check.c \
		cub_struct_init.c \
		cub_hook.c

OBJ =	$(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./mlx
	@make re -C ./Libft
	@make re -C ./get_next_line
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) \
	./Libft/libft.a ./get_next_line/get_next_line.a \
	-Lmlx -lmlx -lXext -lX11 -lm
	
clean:
	@make clean -C ./Libft
	@make clean -C ./get_next_line
	@rm -f $(OBJ)

fclean:	clean
	@make fclean -C ./Libft
	@make fclean -C ./get_next_line
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
