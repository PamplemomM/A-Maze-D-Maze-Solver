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
		@echo "Searching the sources."
		@gcc -o $(NAME) $(SRCS)
		@echo "Compiled successfully!"

val	:
		@gcc -o $(NAME) $(SRCS) $(CFLAGS) -g3
		@echo "Compiled for valgrind successfully!"

viewer	:
		@echo "Searching bonus sources files."
		@make -C./bonus/ --no-print-directory
		@echo "Copying viewer to the root."
		@mv bonus/viewer .
		@ln -sf bonus/assets .
		@echo "Created a linked folder of the assets."

viewer_fclean	:
		@echo "Removing compiled viewer executable."
		@rm -rf viewer
		@echo "Removing the assets."
		@rm -rf assets
		@make -C bonus/ fclean --no-print-directory
		@echo "Removed the viewer."

tests_run	:
		@gcc -o unit_tests $(SRCTEST) -Iinclude -lcriterion --coverage
		@echo "Compiled unit tests."
		@echo "Executing unit tests."
		@./unit_tests

clean	:
		@rm -rf $(OBJS)
		@echo "Removed objects files."

fclean	:	clean
		@rm -rf $(NAME)
		@echo "Removed compiled executable."

re	:	fclean all

cleaner	:
		@./clean.sh
