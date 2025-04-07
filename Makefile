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
		@mkdir -p .build/$(dir $@)
		@gcc -c $< -o .build/$@


$(NAME)	:	$(OBJS)
		@echo ""
		@rm .counter
		@echo "Compiled sources into objects."
		@gcc $(shell find .build/ -type f -name '*.o') $(LIBS) -o $(NAME)
		@echo "Compiled successfully!"
		@echo "Moved object files into .build"

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
		@rm -rf $(shell find .build/ -type f -name '*.o')
		@rmdir $(shell find .build/ -type d) -p --ignore-fail-on-non-empty
		@echo "Removed objects files."

fclean	:	clean
		@rm -rf $(NAME)
		@echo "Removed compiled executable."

re	:	fclean all

cleaner	:
		@./clean.sh
