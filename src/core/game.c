/*
** game.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Fri Mar  3 10:30:16 2017 Arthur Chaloin
** Last update Tue Mar 21 10:05:50 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tetris.h"
#include "display.h"
#include "util.h"
#include "my.h"

static int	Core_actualInput(t_tetris *core, t_shape **obj,
				 t_shape **next, int size[2])
{
  int			ret;

  if (collision(core, *obj))
    {
      if (Core_writeObj(core, *obj))
	return (1);
      *obj = *next;
      *next = NULL;
    }
  ret = Core_handleInput(core, *obj, *next, size);
  if (ret)
    return (ret);
  return (0);
}

static int		Core_handleActual(t_tetris *core, t_shape **obj,
					  t_shape **next, int size[2], int level)
{
  static clock_t	last_time = 0;

  if (!(*next))
    {
     while (!((*next) = (vector_get(&core->tetriminos,
       rand() % vector_getsize(&core->tetriminos), t_tetrimino))->info) ||
	    *next == *obj);
      (*next)->pos = (t_vect){rand() % (core->size.x - (*next)->size[0].x),
      			-(*next)->size[0].y};
      (*next)->dir = 0;
      (*next)->drop = 0;
    }
  if (clock() - last_time > (((*obj)->drop) ? 1000.0f : 50000.0f /
	    (float)((float)level / 0.8f)))
    {
      ((*obj)->pos.y)++;
      last_time = clock();
    }
  return (Core_actualInput(core, obj, next, size));
}

void	Core_display(t_tetris *core, t_shape *actual,
		     t_shape *next, int size[2])
{
  core->frame += 1;
  Display_drawRect(&((t_vect){(size[0] / 2) - core->size.x - 2,
		     (size[1] / 2) - (core->size.y / 2) - 1}),
		   &((t_vect){core->size.x + 2, core->size.y + 2}), 7);
  if (core->next && next)
    {
      Display_drawAt(next, &((t_vect){(size[0] / 2) + core->size.x + 8,
			     (size[1] / 2) - 5}));
      Display_drawRect(&((t_vect){(size[0] / 2) + core->size.x + 4,
			     (size[1] / 2) - 7}),
		   &((t_vect){next->size[0].x + 4, next->size[0].y + 4}), 7);
      attron(COLOR_PAIR(color));
      mvprintw((size[1] / 2) - 7, (size[0] / 2) + core->size.x + 6, "NEXT");
    }
  Display_stats(core, core->score / 1000 + core->level);
  Display_title();
  Display_drawMap(core, size);
  if (actual)
    Display_draw(actual, &(core->size), size);
  if (core->music)
    Display_music(core);
}

static int	frame(t_tetris *core, t_shape **actual, t_shape **next)
{
  int		loose;
  int		size[2];
  static int	level = -1;

  if (level < 0)
    level = core->level;
  clear();
  getmaxyx(stdscr, size[1], size[0]);
  if (size[0] <= core->size.y || size[1] <= core->size.x)
    throw_error("Please increase term size.");
  loose = Core_handleActual(core, actual, next, size, level);
  Core_handleScore(core);
  level = (core->score / 1000) + core->level;
  Core_display(core, *actual, *next, size);
  refresh();
  if (loose)
    {
      set_read_mode(0);
      if (loose != 42)
	{
	  Display_animeLost(core, size);
	  Core_saveScore(core, size);
	}
      return (1);
    }
  usleep(20000);
  return (0);
}

void		Core_game(t_tetris *core)
{
  t_shape	*actual;
  t_tetrimino	*tetrimino;
  t_shape	*next;

  while ((tetrimino = vector_get(&core->tetriminos,
				 rand() % vector_getsize(&core->tetriminos),
				 t_tetrimino)) && !(tetrimino->info));
  actual = tetrimino->info;
  actual->pos = (t_vect){rand() % (core->size.x -
				   actual->size[0].x),
  		-actual->size[0].y};
  actual->dir = 0;
  actual->drop = 0;
  next = NULL;
  set_read_mode(2);
  Core_initMusic(core);
  while (!frame(core, &actual, &next));
  FMOD_ChannelGroup_Stop(core->channel);
}
