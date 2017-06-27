/*
** menu.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/display/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Sat Mar 18 19:45:12 2017 Arthur Chaloin
** Last update Sun Mar 19 20:09:02 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tetris.h"
#include "display.h"
#include "vector.h"
#include "util.h"

static int	my_sort(void *a, void *b)
{
  if (((t_score *)b)->score > ((t_score *)a)->score)
    return (1);
  return (0);
}

static void	add_score(char *line, t_vector *vec)
{
  t_score	*actual;

  actual = xmalloc(sizeof(t_score));
  actual->name = my_str_to_wordtab(line, ":")[0];
  actual->score = my_getnbr(my_str_to_wordtab(line, ":")[1]);
  vector_push(vec, (void *)actual);
}

static void	Display_top10(int size[2], t_vector *scores)
{
  int		index;

  index = 0;
  while (++index < vector_getsize(scores) && index < 10)
    {
      mvprintw(index * 2 + 10, size[0] / 2 - 15, "%d", index + 1);
      mvprintw(index * 2 + 10, size[0] / 2 - 10, "%s",
               (vector_get(scores, index, t_score))->name);
      mvprintw(index * 2 + 10, size[0] / 2 + 10, "%d",
               (vector_get(scores, index, t_score))->score);
    }
}

static void	Display_highScores(int size[2])
{
  int		fd;
  char		*line;
  t_vector	scores;

  clear();
  if ((fd = open("scores", O_RDONLY)) != -1)
    {
      vector_create(&scores);
      get_next_line(-42);
      while ((line = get_next_line(fd)))
	add_score(line, &scores);
      vector_sort(&scores, &my_sort);
      mvprintw(5, size[0] / 2, "%d", 1);
      mvprintw(7, size[0] / 2 - 10, "%s", (vector_get(&scores, 0,
						      t_score))->name);
      mvprintw(7, size[0] / 2 + 10, "%d", (vector_get(&scores, 0,
						      t_score))->score);
      Display_top10(size, &scores);
    }
  else
    mvprintw(10, 10, "No scores to display.");
  refresh();
  while (!getch());
}

void	Display_menu(t_tetris *core)
{
  int	c;
  int	cursor;
  int	size[2];

  while (1)
    {
      cursor = 0;
      c = 0;
      while (c != '\n')
	c = wait_input(size, &cursor);
      if (cursor == 0)
	{
	  core->start_time = time(NULL);
	  Core_game(core);
	}
      else if (cursor == 1)
	Display_highScores(size);
      else
	exit(0);
  }
}
