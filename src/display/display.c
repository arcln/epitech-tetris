/*
** display.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/display/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Fri Mar  3 09:41:00 2017 Arthur Chaloin
** Last update Mon Mar 20 18:07:05 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <ncurses.h>
#include "tetris.h"
#include "display.h"
#include "my.h"

void	Display_animeLost(t_tetris *core, int size[2])
{
  int	index;

  index = -1;
  while (++index < core->size.y)
    {
      clear();
      my_memset(core->map[index], core->size.x, 0);
      Core_display(core, NULL, NULL, size);
      refresh();
      usleep(150000);
    }
}

void	Display_drawMap(t_tetris *core, int size[2])
{
  int	index;
  int	index2;

  index = -1;
  while (++index < core->size.y)
    {
      index2 = -1;
      while (++index2 < core->size.x)
	{
	  attron(COLOR_PAIR(core->map[index][index2]));
	  mvprintw((size[1] / 2) - (core->size.y / 2) + index,
		   (size[0] / 2) - core->size.x + (index2 * 2),
		   (core->map[index][index2]) ? "  " : "");
	  attroff(COLOR_PAIR(core->map[index][index2]));
	}
    }
}

void	Display_drawAt(t_shape *shape, t_vect *pos)
{
  int	index;
  int	index2;

  attron(COLOR_PAIR(shape->color));
  index = -1;
  while (++index < shape->size[0].y)
    {
      index2 = -1;
      while (shape->shapes[0][index][++index2])
	{
	  if (shape->shapes[0][index][index2] == '*')
	    mvprintw(pos->y + index, pos->x + (index2 * 2), "  ");
	}
    }
  attroff(COLOR_PAIR(shape->color));
}

void	Display_draw(t_shape *shape, t_vect *board, int size[2])
{
  int	index;
  int	index2;

  attron(COLOR_PAIR(shape->color));
  index = -1;
  while (++index < shape->size[shape->dir].y)
    {
      index2 = -1;
      while (shape->shapes[shape->dir][index][++index2])
	{
	  if (shape->shapes[shape->dir][index][index2] == '*' &&
	      shape->pos.y + index >= 0)
	    mvprintw((size[1] / 2) - (board->y / 2) + shape->pos.y + index,
		     (size[0] / 2) - board->x + ((shape->pos.x + index2) * 2),
		     "  ");
	}
    }
  attroff(COLOR_PAIR(shape->color));
}

void	Display_drawRect(t_vect *pos, t_vect *size,
			 __attribute__((unused))int lol)
{
  int	index;
  int	index2;

  index = -1;
  attron(COLOR_PAIR(color));
  while (++index < size->y)
    {
      index2 = -1;
      while (++index2 < size->x)
	{
	  if (index == 0 || index == size->y - 1)
	    mvprintw(pos->y + index, pos->x + (index2 * 2), "  ");
	  if (index2 == 0 || index2 == size->x - 1)
	    mvprintw(pos->y + index, pos->x + (index2 * 2), "  ");
	}
    }
  attroff(COLOR_PAIR(color));
}
