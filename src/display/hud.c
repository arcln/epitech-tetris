/*
** title.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/display/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Mar  7 22:15:51 2017 Arthur Chaloin
** Last update Tue Mar 21 10:06:09 2017 Arthur Chaloin
*/
#include <ncurses.h>
#include "display.h"

int	wait_input(int size[2], int *cursor)
{
  int		c;

  clear();
  getmaxyx(stdscr, size[1], size[0]);
  Display_title();
  attron(COLOR_PAIR(7));
  if (*cursor == 0)
    attron(A_UNDERLINE);
  mvprintw(size[1] / 2 - 4, 25, "PLAY");
  attroff(A_UNDERLINE);
  if (*cursor == 1)
    attron(A_UNDERLINE);
  mvprintw(size[1] / 2, 24, "SCORES");
  attroff(A_UNDERLINE);
  if (*cursor == 2)
    attron(A_UNDERLINE);
  mvprintw(size[1] / 2 + 4, 25, "QUIT");
  attroff(A_UNDERLINE);
  refresh();
  c = getch();
  if (c == KEY_DOWN)
    *cursor = (*cursor < 2) ? *cursor + 1 : 0;
  if (c == KEY_UP)
    *cursor = (*cursor) ? *cursor - 1 : 2;
  return (c);
}

static void	Display_title3()
{
  attron(COLOR_PAIR(5));
  mvprintw(5, 48, "  ");
  mvprintw(6, 48, "  ");
  mvprintw(7, 48, "  ");
  mvprintw(8, 48, "  ");
  mvprintw(9, 48, "  ");
  attron(COLOR_PAIR(6));
  mvprintw(5, 52, "        ");
  mvprintw(6, 52, "  ");
  mvprintw(7, 52, "        ");
  mvprintw(8, 58, "  ");
  mvprintw(9, 52, "        ");
}

static void	Display_title2()
{
  attron(COLOR_PAIR(3));
  mvprintw(5, 28, "        ");
  mvprintw(6, 31, "  ");
  mvprintw(7, 31, "  ");
  mvprintw(8, 31, "  ");
  mvprintw(9, 31, "  ");
  attron(COLOR_PAIR(4));
  mvprintw(5, 38, "        ");
  mvprintw(6, 38, "  ");
  mvprintw(6, 44, "  ");
  mvprintw(7, 38, "        ");
  mvprintw(8, 38, "  ");
  mvprintw(8, 42, "  ");
  mvprintw(9, 38, "  ");
  mvprintw(9, 44, "  ");
}

void	Display_title()
{
  attron(COLOR_PAIR(1));
  mvprintw(5, 10, "        ");
  mvprintw(6, 13, "  ");
  mvprintw(7, 13, "  ");
  mvprintw(8, 13, "  ");
  mvprintw(9, 13, "  ");
  attron(COLOR_PAIR(2));
  mvprintw(5, 20, "      ");
  mvprintw(6, 20, "  ");
  mvprintw(7, 20, "    ");
  mvprintw(8, 20, "  ");
  mvprintw(9, 20, "      ");
  Display_title2();
  Display_title3();
}

void	Display_stats(t_tetris *core, int level)
{
  Display_drawRect(&((t_vect){14, 12}), &((t_vect){15, 11}), 7);
  mvprintw(18, 18, "Time :\t%d:%02d:%02d", (time(NULL) - core->start_time) /
	   3600, (time(NULL) - core->start_time) % 3600 / 60, (time(NULL) -
		  core->start_time) % 60);
  mvprintw(14, 18, "Score :\t%07d", core->score);
  mvprintw(16, 18, "High score :\t%07d", core->high_score);
  mvprintw(20, 18, "Level :\t     %02d", level);
}
