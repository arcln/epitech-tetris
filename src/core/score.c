/*
** score.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/core/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Thu Mar 16 10:41:55 2017 Arthur Chaloin
** Last update Sun Mar 19 19:08:41 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ncurses.h>
#include "tetris.h"
#include "display.h"
#include "util.h"

static void	init_remove(t_tetris *core, t_lli **frames, int *call)
{
  int		index;

  index = 0;
  if (!(*frames = malloc(sizeof(t_lli) * core->size.y)))
    throw_error("malloc fail");
  while (index < core->size.y)
    {
      (*frames)[index] = -1;
      index += 1;
    }
  *call = 1;
}

static void	blink_line(t_tetris *core, t_lli *frames, int line)
{
  int		diff;
  int		index;

  index = 0;
  diff = frames[line] - core->frame;
  if (diff % 10 != 0 && diff % 5 != 0)
    return;
  while (index < core->size.x)
    {
      core->map[line][index] = diff % 10 == 0 ? -1 : 8;
      index += 1;
    }
}

static void	remove_line(t_tetris *core, int line)
{
  static int	call = 0;
  static t_lli	*frames;
  int		index;

  if (call == 0)
    init_remove(core, &frames, &call);
  if (frames[line] != -1 && frames[line] != core->frame)
    return (blink_line(core, frames, line));
  if (frames[line] == -1 && (index = -1))
    {
      while (++index < core->size.x)
	core->map[line][index] = 8;
      frames[line] = core->frame + 20;
      return;
    }
  frames[line] = -1;
  while (--line >= 0 && (index = -1))
    {
      while (++index < core->size.x)
	{
	  core->map[line + 1][index] = core->map[line][index];
	  core->map[line][index] = 0;
	}
     }
  core->score += 420;
}

void	Core_saveScore(t_tetris *core, int size[2])
{
  int	fd;
  char	c;
  char	input[1024];

  c = 0;
  my_memset(input, 1024, 0);
  flushinp();
  while (c != '\n')
    {
      input[my_strlen(input)] = c;
      input[my_strlen(input) + 1] = 0;
      clear();
      Core_display(core, NULL, NULL, size);
      attron(COLOR_PAIR(8));
      mvprintw(size[1] / 2, size[0] / 2 - 5, "YOUR NAME :");
      mvprintw(size[1] / 2 + 1, size[0] / 2 -
	       (my_strlen(input) / 2), "%s", input);
      refresh();
      c = getch();
    }
  if ((fd = open("scores", O_RDWR | O_APPEND | O_CREAT, 00644)) == -1)
    throw_error("failed to open.");
  my_dprintf(fd, "%s:%d\n", input, core->score);
}

void	Core_handleScore(t_tetris *core)
{
  int	index;
  int	index2;

  index = -1;
  while (++index < core->size.y)
    {
      index2 = -1;
      while (++index2 < core->size.x)
	{
	  if (!core->map[index][index2])
	    break;
	}
      if (index2 == core->size.x)
	remove_line(core, index);
    }
}
