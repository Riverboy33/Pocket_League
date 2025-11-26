##
## EPITECH PROJECT, 2025
## Workshop_csmfl
## File description:
## Makefile
##

CSFML_FLAGS = -lcsfml-window -lcsfml-system -lcsfml-graphics -lcsfml-audio

SRC = cleanup.c \
	create_sprite.c \
	display.c \
	events.c \
	gameloop.c \
	handle_death.c \
	handle_str.c \
	helper.c \
	hunter.c \
	init.c \
	main.c \
	my_strlen.c \
	proba.c \
	update.c

OBJ = $(SRC.c=.o)

NAME = my_hunter

all: $(NAME)

$(NAME): $(OBJ)
	@clang -o $(NAME) $(SRC) $(CSFML_FLAGS) -Iinclude -lX11

run: re
	@./$(NAME)

re: fclean all

fclean:
	@rm $(NAME)
	@rm -f *.gcda
	@rm -f *.gcno
	@rm -f *.o

.PHONY: all run re fclean
