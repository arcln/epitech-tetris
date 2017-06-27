/*
** parser.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Feb 27 09:28:26 2017 Arthur Chaloin
** Last update Sun Mar 19 20:08:23 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "parser.h"
#include "tetris.h"
#include "my.h"

static char	*get_name(char *str)
{
  int		index;

  index = my_strlen(str) - 1;
  while (--index >= 0 && str[index] != '.');
  if (my_strcmp(str + index, ".tetrimino"))
    return (NULL);
  else
    return (my_strndup(str, index));
}

void		Parser_parse(t_tetris *core)
{
  t_tetrimino	*new;
  DIR		*dir;
  int		fd;
  struct dirent	*actual;
  char		*name;

  vector_create(&(core->tetriminos));
  if (!(dir = opendir("tetriminos")))
    return;
  while ((actual = readdir(dir)))
    {
      name = get_name(actual->d_name);
      if (!name)
	continue;
      if ((fd = open(my_str_concat("tetriminos/", actual->d_name),
		     O_RDONLY)) == -1 || !(new = malloc(sizeof(t_tetrimino))))
	return;
      get_next_line(-1);
      new->info = Parser_tetrimino(fd);
      new->name = name;
      if (new->info && (new->info->size[0].x > core->size.x ||
	  new->info->size[0].y > core->size.y))
	new->info = NULL;
      vector_push(&(core->tetriminos), new);
    }
}
