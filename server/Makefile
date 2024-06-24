CFLAGS  = -O2
# LDFLAGS	= -L ../libs/myteams -L .
LDFLAGS	= -L../libs/myteams -Wl,-rpath=./libs/myteams -L.
LDLIBS	= -lmyteams -lall -luuid
NAME	= myteams_server

SRC	=	src/saving/open_file.c	\
		src/users/load_users.c	\
		src/users/users_utils.c	\
		src/handle_commands/messages.c	\
		src/handle_commands/direct_messages.c	\
		src/handle_commands/user.c	\
		src/handle_commands/users.c	\
		src/handle_commands/logout.c	\
		src/handle_commands/login.c	\
		src/handle_commands/close_session.c	\
		src/handle_commands/handle_command.c	\
		src/send_boolean_response.c	\
		src/preliminaries.c	\
		src/handle_server.c	\
		src/init_server.c	\
		src/main.c	\

OBJ_DIR = obj
OBJ	= $(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ)
	@mkdir -p $(@D)
	@gcc -o $(NAME) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS)

debug:	$(OBJ)
	@mkdir -p $(@D)
	@gcc -o $(NAME) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -ggdb3

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -rf $(OBJ_DIR)/src
	make clean -C ../libs/all

fclean:	clean
	rm -f $(NAME)
	make clean -C ../libs/all

re:	fclean all
