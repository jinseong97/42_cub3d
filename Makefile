CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME =	cub3D
SRC =	main.c

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
	-Lmlx -lmlx -lXext -lX11
	
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
