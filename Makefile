##
## EPITECH PROJECT, 2025
## Workshop_csmfl
## File description:
## Makefile
##

SRC = my_hunter.c

NAME = my_hunter

all: $(NAME)

$(NAME):
	@clang -o $(NAME) $(SRC) -lcsfml-window -lcsfml-system -lcsfml-graphics -lcsfml-audio

run: re
	@./$(NAME)

re: fclean all

fclean:
	@rm $(NAME)

.PHONY: all run re fclean
