/*
** input.c for tetris in /home/arbona/tek1/PSU/PSU_2016_tetris
**
** Made by Thomas ARBONA
** Login   <thomas.arbona@epitech.eu>
**
** Started on  Tue Mar  7 13:18:00 2017 Thomas ARBONA
** Last update Tue Mar 21 10:44:27 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tetris.h"
#include "util.h"
#include "my.h"

static int	my_sort(void *a, void *b)
{
  if (((t_score *)b)->score > ((t_score *)a)->score)
    return (1);
  return (0);
}

void		Core_loadHighScore(t_tetris *core)
{
  int		fd;
  char		*line;
  t_vector	scores;
  t_score	*actual;

  if ((fd = open("scores", O_RDONLY)) != -1)
    {
      vector_create(&scores);
      get_next_line(-42);
      while ((line = get_next_line(fd)))
	{
	  actual = xmalloc(sizeof(t_score));
          actual->name = my_str_to_wordtab(line, ":")[0];
          actual->score = my_getnbr(my_str_to_wordtab(line, ":")[1]);
          vector_push(&scores, (void *)actual);
	}
      vector_sort(&scores, &my_sort);
      core->high_score = (vector_get(&scores, 0, t_score))->score;
    }
}

static int	isValidKey(t_tetris *core, char buff[128])
{
  if (my_strncmp(core->keys.left, buff, my_strlen(buff)) == 0 ||
      my_strncmp(core->keys.right, buff, my_strlen(buff)) == 0 ||
      my_strncmp(core->keys.turn, buff, my_strlen(buff)) == 0 ||
      my_strncmp(core->keys.drop, buff, my_strlen(buff)) == 0 ||
      my_strncmp(core->keys.quit, buff, my_strlen(buff)) == 0 ||
      my_strncmp(core->keys.pause, buff, my_strlen(buff)) == 0 ||
      !my_strncmp(buff, core->keys.left, my_strlen(core->keys.left)) ||
      !my_strncmp(buff, core->keys.right, my_strlen(core->keys.right)) ||
      !my_strncmp(buff, core->keys.turn, my_strlen(core->keys.turn)) ||
      !my_strncmp(buff, core->keys.drop, my_strlen(core->keys.drop)) ||
      !my_strncmp(buff, core->keys.quit, my_strlen(core->keys.quit)) ||
      !my_strncmp(buff, core->keys.pause, my_strlen(core->keys.pause)))
    return (1);
  return (0);
}

static int      isKey(char *key, char buff[128])
{
  if (my_strncmp(key, buff, my_strlen(key)) == 0)
    {
      my_memset(buff, 128, 0);
      return (1);
    }
  return (0);
}

int		Core_getInput(t_tetris *core)
{
  static char	buff[128];
  static int	call = 0;
  char		tmp[128];
  int		n;

  if (call == 0)
    {
      my_memset(buff, 128, 0);
      call = 1;
    }
  if ((n = read(0, tmp, 127)) < 0)
    throw_error("Unable to read on stdin.");
  tmp[n] = 0;
  my_strcat(buff, tmp);
  if (!isValidKey(core, buff))
    {
      my_memset(buff, 128, 0);
      return (0);
    }
  return (isKey(core->keys.left, buff) ? KEY__LEFT :
	  isKey(core->keys.right, buff) ? KEY__RIGHT :
	  isKey(core->keys.turn, buff) ? KEY__TURN :
	  isKey(core->keys.drop, buff) ? KEY__DROP :
	  isKey(core->keys.quit, buff) ? KEY__QUIT :
	  isKey(core->keys.pause, buff) ? KEY__PAUSE : 0);
}
