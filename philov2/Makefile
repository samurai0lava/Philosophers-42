CC = cc
FLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRC = main.c parsing.c utils.c routine.c monitor.c check_eats.c time.c
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
