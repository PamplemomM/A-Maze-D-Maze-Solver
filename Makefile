##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for the A-Maze-d program.
##

NAME    =	amazed

SRCS	=	$(shell find src/ -type f -name '*.c')

SRCTEST	=	$(shell find src/lib -type f -name '*.c')
SRCTEST	+=	$(shell find tests/ -type f -name '*.c')

CFLAGS	=	-Wall -Wextra -Wshadow -I./../include

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:
		gcc -o $(NAME) $(SRCS)

val	:
		gcc -o $(NAME) $(SRCS) $(CFLAGS) -g3

viewer	:
		cd bonus ; make ; make clean ; mv viewer .. ; cd ..
		ln -sf bonus/assets .

viewer_clean	:
		rm -rf viewer
		rm -rf assets

tests_run	:
		gcc -o unit_tests $(SRCTEST) -Iinclude -lcriterion --coverage
		./unit_tests

clean	:
		rm -rf $(OBJS)

fclean	:	clean viewer_clean
		rm -rf $(NAME)

re	:	fclean all
