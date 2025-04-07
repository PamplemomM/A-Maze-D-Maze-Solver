##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for the A-Maze-d viewer.
##

NAME	=	viewer

SRC	=	$(shell find src/ -type f -name '*.c')
SRC	+=	$(shell find ../src/parsing/ -type f -name '*.c')	\
		$(shell find ../src/lib/ -type f -name '*.c')	\
		../src/path_finding/make_move.c	\
		../src/print_maze.c	\
		../src/free_maze.c	\

LIBS	=	-l csfml-graphics -l csfml-system -l csfml-audio	\
		-l csfml-window -lm	\

OBJ	=	$(SRC:.c=.o)

all	:	$(NAME)

increment_counter:
	@if [ ! -f .counter ]; then echo -n "Compiled sources: [00]" ; \
	echo 0 > .counter; fi; \
	count=$$(cat .counter); \
	new_count=$$((count + 1)); \
	echo $$new_count > .counter; \
	for i in $$(seq 1 4); do \
		printf "\b \b"; \
	done; \
	if [ $$new_count -lt 10 ]; then printf "[0$$new_count]"; else printf "[$$new_count]"; fi;


%.o	:	%.c
		@$(MAKE) increment_counter --no-print-directory
		@gcc -c $< -o $@

$(NAME)	:	$(OBJ)
		@echo ""
		@rm .counter
		@echo "Compiled viewer sources into objects."
		@gcc $(OBJ) $(LIBS) -o $(NAME)
		@echo "Compiled the viewer"

clean	:
		@rm -rf $(OBJ)
		@echo "Removed viewer object files."

fclean	:	clean
		@rm -rf $(NAME)
		@echo "Removed compiled viewer."

re	:	fclean all
