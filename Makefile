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
SRCS = sources/ft_atoi.c sources/parsing.c sources/init_philo.c sources/time_tools.c
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
