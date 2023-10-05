# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: derblang <derblang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 10:51:09 by derblang          #+#    #+#              #
#    Updated: 2023/05/10 15:13:33 by derblang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
SRCS_C = client.c
SRCS_S = server.c
OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_S:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
CLIENT = client
SERVER = server


all : $(NAME)

$(NAME): $(OBJS_C) $(OBJS_S)
		@$(MAKE) -C ./libft
		@gcc $(FLAGS) $(OBJS_C) libft/libft.a -o $(CLIENT)
		@gcc $(FLAGS) $(OBJS_S) libft/libft.a -o $(SERVER)
		@rm $(OBJS_C) $(OBJS_S)

debug: $(OBJS)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a  -fsanitize=address -o $(NAME)

.c.o:
		gcc $(FLAGS) -c -I./libft/libft.h $< -o ${<:.c=.o}

clean:
		@$(RM) $(OBJS_C) $(OBJS_S) libft.a
		@$(MAKE) clean -C ./libft

fclean: clean
			@$(RM) $(NAME) $(CLIENT) $(SERVER)
			@$(MAKE) fclean -C ./libft

re: fclean all

