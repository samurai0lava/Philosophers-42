CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = philosphers
LIB = libft/libft.a
SRC = main.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

.c.o :
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@make all -C libft
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

clean : 
	@make clean -C libft
	@rm -f $(OBJ)

fclean : clean
	@make fclean -C libft
	@rm -f $(NAME)