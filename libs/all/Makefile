SRCS	=	*.c

CFLAGS	=	-O2


all:	lib

lib:
	@gcc -c $(SRCS)
	@ar rc liball.a *.o
	@cp liball.a ../../server
	@cp liball.a ../../client
	@cp ./include/my.h ../../server/include/lib.h
	@cp ./include/my.h ../../client/include/lib.h
	@find . -type f,d -name "*.o" -delete

build:
	@gcc *.c $(CFLAGS)

clean:
	@rm -rf *.o .idea/
	@find . -type f,d \( -name "*~" -o -name "\#*\#" \) -delete
	@find . -type f,d -name "vgcore*" -delete

fclean: clean
	@find . -type f,d -name "libmy.a" -delete
	rm -rf liball.a
	rm -rf ../../server/liball.a
	rm -rf ../../client/liball.a

re:	fclean lib
