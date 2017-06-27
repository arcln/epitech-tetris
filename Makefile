##
## Makefile for tetris in /home/arthur/B2/PSU/PSU_2016_tetris
##
## Made by Arthur Chaloin
## Login   <arthur@epitech.net>
##
## Started on  Sat Feb 25 18:56:23 2017 Arthur Chaloin
## Last update Mon Mar 20 15:46:07 2017 Arthur Chaloin
##

NAME	=	tetris

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-W -Wall -Wextra -I./include/

LDFLAGS	=	-L./lib/ -lmy -lvector -lncurses -lfmod

SRC	=	src/tetris.c			\
		src/debug.c			\
		src/core/game.c			\
		src/core/music.c		\
		src/core/map.c			\
		src/core/input.c		\
		src/core/handle_input.c		\
		src/core/score.c		\
		src/display/display.c		\
		src/display/hud.c		\
		src/display/menu.c		\
		src/parser/parser.c		\
		src/parser/parse_tetrimino.c	\
		src/arg/arg.c			\
		src/arg/key_ctrl.c		\
		src/arg/key_sys.c		\
		src/arg/options.c		\
		src/util.c

OBJ	=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

debug:	CFLAGS += -g
debug:	re

fast:	CFLAGS += -O3 -Ofast -Wno-maybe-uninitialized -Wno-unused-result
fast:	re

.PHONY:	all clean fclean re debug fast
