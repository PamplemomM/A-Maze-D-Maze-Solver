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
	@if [ ! -f .counter ]; then echo -n "Compiling source files: [00]" ; \
	echo 0 > .counter; fi; \
	count=$$(cat .counter); \
	new_count=$$((count + 1)); \
	echo $$new_count > .counter; \
	for i in $$(seq 1 4); do \
		printf "\b \b"; \
	done; \
	if [ $$new_count -lt 10 ]; \
	then printf "[0$$new_count]"; \
	else printf "[$$new_count]"; fi;


%.o	:	%.c
		@$(MAKE) increment_counter --no-print-directory
		@gcc -c $< -o $@


$(NAME)	:	$(OBJS)
		@echo ""
		@rm .counter
		@echo "Compiled source files into object files."
		@gcc $(OBJS) $(LIBS) -o $(NAME)
		@echo "Compiled successfully!"

val	:
		@gcc -o $(NAME) $(SRCS) $(CFLAGS) -g3
		@echo "Compiled successfully! (valgrind edition)"

viewer	:
		@echo "Executing viewer Makefile."
		@make -C./bonus/ --no-print-directory
		@mv bonus/viewer .
		@echo "Moved viewer binary to root."
		@ln -sf bonus/assets .
		@echo "Created symbolic link to assets folder."

viewer_fclean	:
		@make -C bonus/ clean --no-print-directory
		@rm -rf assets
		@echo "Removed assets symbolic link."
		@rm -rf viewer
		@echo "Removed viewer binary."

tests_run	:
		@gcc -o unit_tests $(SRCTEST) -Iinclude -lcriterion --coverage
		@echo "Compiled unit tests."
		@echo "Executing unit tests."
		@./unit_tests

clean	:
		@rm -rf $(OBJS)
		@echo "Removed object files."

fclean	:	clean
		@rm -rf $(NAME)
		@echo "Removed binary."

re	:	fclean all

cleaner	:
		@./clean.sh
