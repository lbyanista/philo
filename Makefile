# .PHONY: all clean fclean re
NAME = philo
SRC = *.c
FLAGS = #-Wall -Wextra -Werror
CC = gcc
all: $(NAME)
$(NAME):
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)
clean:
	@rm -f *.o
fclean:
	@rm -f $(NAME)
re: fclean all