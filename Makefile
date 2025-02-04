NAME = pipex

CC = gcc

ERR_FLAGS = -Wall -Wextra -Werror

DEBUG_FLAGS = -g -fsanitize=address

DEP_FLAGS = -I. -Ilibft

LIBFT = libft/libft.a

LIB = pipex.h

SRC = ${wildcard *.c}

all: libft pipex

libft:
	cd libft && ${MAKE}

pipex: ${LIB} ${SRC}
	${CC} ${ERR_FLAGS} ${DEBUG_FLAGS} ${DEP_FLAGS} ${SRC} ${LIBFT} -o $@

test: all
	./pipex notes "grep file" "grep stdout" testfile.txt

clean:
	rm -rf ${NAME} *.dSYM

fclean: clean
	cd libft && ${MAKE} fclean

re: fclean all

.PHONY: all clean fclean re libft
