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
EXEC = philo
NAME = philo.a
SRCS = ft_atoi.c error.c parsing.c
INCLUDE = philosopher.h
#OBJS
OBJS = $(SRCS:.c=.o)

#RULES
.c.o:
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) main.c -o philo

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)

re: fclean all