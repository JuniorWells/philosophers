NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
TH_FLAG = -lpthread

SRC = main.c tools.c errors.c dinner.c inits.c libft_functions.c
OBJ = ${SRC:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(TH_FLAG)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
