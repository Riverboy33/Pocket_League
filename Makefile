##
## EPITECH PROJECT, 2025
## Workshop_csmfl
## File description:
## Makefile
##

CSFML_FLAGS = -lcsfml-window -lcsfml-system -lcsfml-graphics -lcsfml-audio

SRC = src/cleanup.c \
	src/create_sprite.c \
	src/display.c \
	src/events.c \
	src/gameloop.c \
	src/handle_death.c \
	src/handle_str.c \
	src/helper.c \
	src/hunter.c \
	src/init.c \
	src/main.c \
	src/my_strlen.c \
	src/proba.c \
	src/update.c

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
