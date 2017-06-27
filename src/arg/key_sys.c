/*
** key_sys.c for tetris in /home/arbona/tek1/PSU/PSU_2016_tetris
**
** Made by Thomas ARBONA
** Login   <thomas.arbona@epitech.eu>
**
** Started on  Mon Feb 27 14:33:00 2017 Thomas ARBONA
** Last update Mon Feb 27 15:20:23 2017 Thomas ARBONA
*/
#include <unistd.h>
#include "arg.h"
#include "util.h"

static int     isSetKey(t_tetris *core, char *key)
{
  if ((core->keys.left && my_strcmp(core->keys.left, key) == 0) ||
      (core->keys.right && my_strcmp(core->keys.right, key) == 0) ||
      (core->keys.turn && my_strcmp(core->keys.turn, key) == 0) ||
      (core->keys.drop && my_strcmp(core->keys.drop, key) == 0) ||
      (core->keys.quit && my_strcmp(core->keys.quit, key) == 0) ||
      (core->keys.pause && my_strcmp(core->keys.pause, key) == 0))
    return (-1);
  return (0);
}

void	isValidKey(t_tetris *core, char *key)
{
  if (key == NULL)
    throw_error("key not define.");
  if (isSetKey(core, key) == -1)
    throw_error("key already set.");
}

void	Arg_setKeyQuit(t_tetris *core, char **values)
{
  isValidKey(core, values[0]);
  core->keys.quit = values[0];
}

void	Arg_setKeyPause(t_tetris *core, char **values)
{
  isValidKey(core, values[0]);
  core->keys.pause = values[0];
}
