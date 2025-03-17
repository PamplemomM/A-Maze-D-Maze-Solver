##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## The makefile to compile the project.
##

NAME    =		amazed

SRCS	=		$(shell find src/ -type f -name '*.c')

SRCTEST	=	$(shell find src/lib -type f -name '*.c')
SRCTEST	+=	$(shell find src/cuddle_help -type f -name '*.c')
SRCTEST	+=	$(shell find tests/ -type f -name '*.c')

CFLAGS	=		-Wall -Wextra -Wshadow -I./../include

OBJS	=		$(SRCS:.c=.o)

all		:		$(NAME)

$(NAME)	:
		gcc -o $(NAME) $(SRCS)

val		:
		gcc -o $(NAME) $(SRCS) $(CFLAGS)

tests_run:
	gcc -o unit_tests $(SRCTEST) -Iinclude -lcriterion --coverage
	./unit_tests

clean	:
			rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re		:	fclean all
