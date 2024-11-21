CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
NAME = philo
SRC = main.c parsing.c utils.c routine.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

.c.o :
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -lpthread

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all