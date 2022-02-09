NAME = philosophers

ifndef DEBUG
	CFLAGS = -Wall -Wextra -Werror
else
	CFLAGS = -Wall -Wextra -g -fsanitize=thread
endif
CC = gcc
COMPILE = $(CC) $(CFLAGS)

FILES =	process.c \
		initialize.c \
		utils.c \
		eat_and_sleep.c \
		deadlock_handling.c \
		fork_handling.c \
		main.c \
		free_all.c \
		locked_checks.c

OBJS = $(FILES:.c=.o)

%.o : %.c pipex.h
	@$(CC) $(CFLAGS) -c $<

all: libft | $(NAME)

$(NAME): $(OBJS)
	@$(COMPILE) $(OBJS) -o $(NAME)
	@echo "Creating executable"

clean:
	@rm -rf $(OBJS)
	@echo "Removing object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Removing executable file"

re: fclean | all

.PHONY: all clean fclean libft re