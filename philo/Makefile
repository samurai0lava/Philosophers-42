CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
NAME = philo
SRC = main.c parsing.c time.c routine.c utils.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

.c.o :
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all