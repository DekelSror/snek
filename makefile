


all:
	gcc -g -Wextra -Wall -pedantic -pedantic-errors -std=c2x \
	snek_ui.c snek_input.c snek_game.c \
	-o snek