.SILENT:

#COLOR
RED =`tput setaf 1`
GREEN =`tput setaf 2`
CLEAR =`tput sgr0`

#GENERAL
CC = clang
FLAGS = -Wall -Werror -Wextra -pthread
CD = cd
MV = mv
RM = rm -rf

#OS
UNAME = $(shell uname)

#PROJECT
NAME = philo
SRCS =	sources/parsing.c  sources/utils.c sources/time_tools.c sources/locking_forks.c \
		sources/init_simulation.c sources/write_action.c sources/threads.c sources/exit.c \
		sources/check_end.c
INCLUDE = philosopher.h
#OBJS
OBJS = $(SRCS:.c=.o)

#RULES
.c.o:
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -g $(OBJS) main.c -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled with success.$(CLEAR)"

clean:
	@$(RM) $(OBJS)
	@echo "$(RED) object's files deleted with success.$(CLEAR)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED) $(NAME) deleted with success.$(CLEAR)"

re: fclean all
