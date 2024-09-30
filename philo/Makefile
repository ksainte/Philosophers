# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksainte <ksainte@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 13:23:41 by ksainte           #+#    #+#              #
#    Updated: 2024/08/15 23:10:03 by ksainte          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c \
	   args_utils.c \
	   utils.c \
	   dead_flag.c \
	   init_and_destroy_mutexes.c \
	   init_philo_action.c \
	   write.c
EXEC_NAME = philo
OBJS = $(notdir $(SRCS:.c=.o))

all: $(EXEC_NAME)
 
$(EXEC_NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(OBJS)
 
%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC_NAME)

re: fclean all

.PHONY: all
