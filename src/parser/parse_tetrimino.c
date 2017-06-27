/*
** parse_tetrimino.c for tetris in /home/arbona/tek1/PSU/PSU_2016_tetris
**
** Made by Thomas ARBONA
** Login   <thomas.arbona@epitech.eu>
**
** Started on  Mon Feb 27 09:32:28 2017 Thomas ARBONA
** Last update Sun Mar 19 20:07:56 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include "tetris.h"
#include "util.h"
#include "my.h"

static char	*rm_spaces(char *str)
{
  int		index;

  index = my_strlen(str) - 1;
  while (index >= 0 && (str[index] == ' ' || str[index] == '\t'))
    {
      str[index] = 0;
      index -= 1;
    }
  index = -1;
  while (str[++index])
    {
      if (str[index] != '\t' && str[index] != ' ' && str[index] != '*')
	return (NULL);
    }
  return (str);
}

static void	rotate_shape(t_shape *obj, int dest, int src)
{
  t_vect	index;

  obj->size[dest].y = obj->size[src].x;
  obj->size[dest].x = obj->size[src].y;
  obj->shapes[dest] = xmalloc(sizeof(char *) * obj->size[dest].y);
  index.y = -1;
  while (++(index.y) < obj->size[dest].y)
    {
      index.x = -1;
      obj->shapes[dest][index.y] = xmalloc(sizeof(char) *
					   (obj->size[dest].x + 1));
      while (++(index.x) < obj->size[dest].x)
	  obj->shapes[dest][index.y][index.x] =
	    obj->shapes[src][obj->size[src].y - index.x - 1][index.y];
      obj->shapes[dest][index.y][index.x] = 0;
    }
  index.y = -1;
  while (++(index.y) < obj->size[dest].y)
    {
      index.x = -1;
      while (++(index.x) < obj->size[dest].x &&
	     obj->shapes[dest][index.y][index.x] != '*')
	obj->shapes[dest][index.y][index.x] = ' ';
    }
}

static int	Parser_shape(int fd, t_shape *tetrimino)
{
  int		index;
  int		max_len;
  char		*line;

  index = 0;
  max_len = 0;
  while ((line = get_next_line(fd)) && index < tetrimino->size[0].y)
    {
      if (!(tetrimino->shapes[0][index] = rm_spaces(line)))
	return (1);
      if (my_strlen(tetrimino->shapes[0][index]) > max_len)
	max_len = my_strlen(tetrimino->shapes[0][index]);
      index += 1;
    }
  if (index != tetrimino->size[0].y || max_len > tetrimino->size[0].x ||
      tetrimino->size[0].x < 1 || tetrimino->size[0].y < 1)
    return (1);
  rotate_shape(tetrimino, 1, 0);
  rotate_shape(tetrimino, 2, 1);
  rotate_shape(tetrimino, 3, 2);
  return (0);
}

t_shape		*Parser_tetrimino(int fd)
{
  char		*line;
  char		**data;
  t_shape	*tetrimino;

  if ((line = get_next_line(fd)) == NULL ||
      !(tetrimino = malloc(sizeof(t_shape))))
    return (NULL);
  data = my_str_to_wordtab(line, " ");
  tetrimino->size[0].x = my_getnbr(data[0]);
  if (data[1] && data[2])
    {
      tetrimino->size[0].y = my_getnbr(data[1]);
      tetrimino->color = my_getnbr(data[2]);
    }
  else
    return (NULL);
  if (!(tetrimino->shapes = malloc(sizeof(char **) * 4)) ||
    !(tetrimino->shapes[0] = malloc(sizeof(char *) * tetrimino->size[0].y)))
    return (NULL);
  if (Parser_shape(fd, tetrimino))
    return (NULL);
  return (tetrimino);
}
