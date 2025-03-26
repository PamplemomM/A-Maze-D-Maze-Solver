##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for the A-Maze-d visualizer.
##

NAME	=	visualizer

SRC	=	$(shell find src/ -type f -name '*.c')
SRC	+=	$(shell find ../src/parsing/ -type f -name '*.c')	\
		$(shell find ../src/lib/ -type f -name '*.c')	\
		../src/free_maze.c	\

LIBS	=	-l csfml-graphics -l csfml-system -l csfml-audio	\
		-l csfml-window -lm	\

OBJ	=	$(SRC:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		gcc $(OBJ) $(LIBS) -o $(NAME)

clean	:
		rm -rf $(OBJ)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all
