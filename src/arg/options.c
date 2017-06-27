/*
** options.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/arg/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Feb 27 14:13:12 2017 Arthur Chaloin
** Last update Mon Feb 27 15:14:04 2017 Thomas ARBONA
*/
#include <stdlib.h>
#include "tetris.h"

void	Arg_setHelp(t_tetris *core, __attribute__((unused))char **values)
{
  core->help = 1;
}

void	Arg_setDebug(t_tetris *core, __attribute__((unused))char **values)
{
  core->debug = 1;
}

void	Arg_setWithoutNext(t_tetris *core, __attribute__((unused))char **val)
{
  core->next = 0;
}

void	Arg_setMapSize(t_tetris *core, char **values)
{
  if (!values[0] || !values[1])
    {
      my_dprintf(2, "Missing initializer for map size\n");
      exit(84);
    }
  core->size.y = my_getnbr(values[0]);
  core->size.x = my_getnbr(values[1]);
  if (core->size.x <= 0 || core->size.y <= 0)
    {
      my_dprintf(2, "Invalid map size\n");
      exit(84);
    }
}

void	Arg_setLevel(t_tetris *core, char **values)
{
  if (!values[0])
    {
      my_dprintf(2, "Missing initializer for level\n");
      exit(84);
    }
  core->level = my_getnbr(values[0]);
  if (core->level <= 0)
    {
      my_dprintf(2, "Invalid level\n");
      exit(84);
    }
}
