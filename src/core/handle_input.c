/*
** handle_input.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/core/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Sun Mar 19 18:39:49 2017 Arthur Chaloin
** Last update Tue Mar 21 10:12:27 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tetris.h"
#include "display.h"
#include "util.h"
#include "my.h"

int		collision(t_tetris *core, t_shape *obj)
{
  t_vect        cursor;

  if (obj->pos.y + obj->size[obj->dir].y >= core->size.y)
    return (1);
  cursor.y = -1;
  while (++cursor.y < obj->size[obj->dir].y)
    {
      cursor.x = -1;
      while (obj->shapes[obj->dir][cursor.y][++cursor.x])
  	{
	  if (cursor.x + obj->pos.x < 0 ||
	      cursor.y + obj->pos.y >= core->size.y ||
              cursor.x + obj->pos.x >= core->size.x)
	    return (1);
	  if (cursor.y + obj->pos.y >= 0 &&
	      obj->shapes[obj->dir][cursor.y][cursor.x] == '*' &&
	      core->map[cursor.y + obj->pos.y + 1][cursor.x + obj->pos.x])
	    return (1);
	}
    }
  return (0);
}

static int	handle_sys(int input, t_tetris *core, t_shape *obj,
			   t_shape *next, int size[2])
{
  if (input == KEY__QUIT)
    return (42);
  if (input == KEY__PAUSE)
    {
      FMOD_ChannelGroup_SetPaused(core->channel, 1);
      clear();
      Core_display(core, obj, next, size);
      mvprintw(size[1] / 2, size[0] / 2 - 3, "PAUSED");
      refresh();
      while (Core_getInput(core) != KEY__PAUSE);
      FMOD_ChannelGroup_SetPaused(core->channel, 0);
    }
  if (input == KEY__DROP)
    obj->drop = 1;
  return (0);
}

int		Core_handleInput(t_tetris *core, t_shape *obj,
				 t_shape *next, int size[2])
{
  int		input;

  input = Core_getInput(core);
  if (input == KEY__LEFT)
    {
      (obj->pos.x) = (obj->pos.x > 0) ? obj->pos.x - 1 : 0;
      (obj->pos.x) = (collision(core, obj)) ? obj->pos.x + 1 : obj->pos.x;
    }
  if (input == KEY__RIGHT)
    {
      (obj->pos.x) = (obj->pos.x < core->size.x - obj->size[obj->dir].x) ?
	  obj->pos.x + 1 : core->size.x - obj->size[obj->dir].x;
      (obj->pos.x) = (collision(core, obj)) ? obj->pos.x - 1 : obj->pos.x;
    }
  if (input == KEY__TURN)
    {
      obj->dir = (obj->dir < 3) ? obj->dir + 1 : 0;
      (obj->dir) = (collision(core, obj)) ? ((obj->dir > 0) ?
       					obj->dir - 1 : 3) : obj->dir;
    }
  return (handle_sys(input, core, obj, next, size));
}
