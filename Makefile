##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## The makefile to compile the project.
##

NAME    =		amazed

SRCS	=		$(shell find src/ -type f -name '*.c')

CFLAGS	=		-Wall -Wextra -Wshadow -I./../include

OBJS	=		$(SRCS:.c=.o)

all		:		$(NAME)

$(NAME)	:
		gcc -o $(NAME) $(SRCS)

val		:
		gcc -o $(NAME) $(SRCS) $(CFLAGS)

unit_tests	:	fclean all
			gcc -o unit_tests $(SRCS) tests/*.c \
			--coverage -lcriterion

tests_run       :		unit_tests
				./unit_tests

clean	:
			rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re		:	fclean all
