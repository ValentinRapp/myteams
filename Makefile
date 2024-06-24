CLIENT_NAME	=	myteams_cli
SERVER_NAME	=	myteams_server

all:
	@make all -C libs/utils/ &&\
	make all -C libs/all/ &&\
	make all -C client/ &&\
	make all -C server
	@mv client/$(CLIENT_NAME) .
	@mv server/$(SERVER_NAME) .
	@echo -e "[1;32mProject built successfully[0m"

debug: fclean
	@make all -C libs/utils/ &&\
	make all -C libs/all/ &&\
	make debug -C client/ &&\
	make debug -C server
	@mv client/$(CLIENT_NAME) .
	@mv server/$(SERVER_NAME) .
	@echo -e "[1;32mProject built successfully in Debug Mode[0m"

clean:
	make clean -C client/ &&\
	make clean -C server/ &&\
	make clean -C libs/all
	@echo -e "[1;34mRepo cleaned[0m"

fclean:
	make fclean -C client/ &&\
	make fclean -C server/ &&\
	make fclean -C libs/all
	rm -f $(CLIENT_NAME)
	rm -f $(SERVER_NAME)
	@echo -e "[1;31mProject binary deleted[0m"

utils:
	make all -C libs/utils/

reset:
	@rm -f save.dat
	@echo -e "[1;34mSave file cleaned[0m"

re:	fclean all
