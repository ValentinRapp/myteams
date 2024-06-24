CFLAGS  = -O2
# LDFLAGS	= -L ../libs/myteams -L .
LDFLAGS	= -L../libs/myteams -Wl,-rpath=./libs/myteams -L.
LDLIBS	= -lmyteams -lall -luuid
NAME	= myteams_cli

SRC	=	src/handle_commands/messages.c	\
		src/handle_commands/send.c	\
		src/handle_commands/login.c	\
		src/handle_commands/logins.c	\
		src/handle_commands/handle_command.c	\
		src/handle_server_connection.c	\
		src/init_server_connection.c	\
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

fclean:	clean
	rm -f $(NAME)

re:	fclean all
