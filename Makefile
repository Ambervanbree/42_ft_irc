# ***************************************************************************** #
# file structure																#
# ***************************************************************************** #

NAME		=	ircserv
SRC_DIR		=	sources/
OBJ_DIR		=	objects/
SUB_DIRS	=	server/ commands/ user/
DIR			=	$(addprefix $(OBJ_DIR), $(SUB_DIRS))
SRCS		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

# ***************************************************************************** #
# files																			#
# ***************************************************************************** #

OBJ_FILES	=	$(SRC_FILES:.cpp=.o)
SRC_FILES	=	main.cpp $(SERVER) $(COMMANDS) $(USER) utils.cpp
SERVER		=	$(addprefix server/, server.cpp server_commands.cpp)
COMMANDS	=	$(addprefix commands/, test.cpp test2.cpp commands.cpp)
USER		=	$(addprefix user/, user.cpp)
CHANNEL		=	$(addprefix channel/, channel.cpp)

# ***************************************************************************** #
# commands and flags          	   		                                        #
# ***************************************************************************** #

CC			=	c++
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -g

# ***************************************************************************** #
# includes																		#
# ***************************************************************************** #

INCL		=	-Iincludes/server/ -Iincludes/commands/ -Iincludes/
INCL		+=	-Iincludes/user

# ***************************************************************************** #
# rules																			#
# ***************************************************************************** #

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR):
		mkdir $(OBJ_DIR) $(DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
		$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
			$(RM) $(OBJS) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		re, all, clean, fclean