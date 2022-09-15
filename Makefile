# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 10:50:13 by avan-bre          #+#    #+#              #
#    Updated: 2022/09/15 11:44:59 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************************************************************** #
# file structure																#
# ***************************************************************************** #

NAME		=	icserv
SRC_DIR		=	sources/
OBJ_DIR		=	objects/
SUB_DIRS	=	server/ commands/
DIR			=	$(addprefix $(OBJ_DIR), $(SUB_DIRS))
SRCS		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES	=	$(SRC_FILES:.cpp=.o)

SRC_FILES	=	main.cpp $(SERVER) $(COMMANDS)
SERVER		=	$(addprefix server/, server.cpp)
COMMANDS	=	$(addprefix commands/, test.cpp test2.cpp)

# **************************************************************************** #
# commands                 	   		                                        #
# **************************************************************************** #

CC			=	c++
RM			=	rm -rf

# **************************************************************************** #
#                               FLAGS                                          #
# **************************************************************************** #

CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -g
INCL		=	-Iincludes/server/ -Iincludes/commands/


# **************************************************************************** #
#                               RULES                                          #
# **************************************************************************** #

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR):
		@mkdir $(OBJ_DIR) $(DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
		$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
			$(RM) $(OBJS) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		re, all, clean, fclean