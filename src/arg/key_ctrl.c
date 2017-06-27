/*
** key_ctrl.c for tetris in /home/arbona/tek1/PSU/PSU_2016_tetris
**
** Made by Thomas ARBONA
** Login   <thomas.arbona@epitech.eu>
**
** Started on  Mon Feb 27 14:16:10 2017 Thomas ARBONA
** Last update Fri Mar 17 09:57:33 2017 Arthur Chaloin
*/
#include "util.h"
#include "arg.h"

void	Arg_setKeyLeft(t_tetris *core, char **values)
{
  if (values)
    {
      isValidKey(core, values[0]);
      core->keys.left = values[0];
    }
  else
    throw_error("missing initializer.");
}

void	Arg_setKeyRight(t_tetris *core, char **values)
{
  if (values)
    {
      isValidKey(core, values[0]);
      core->keys.right = values[0];
    }
  else
    throw_error("missing initializer.");
}

void	Arg_setKeyTurn(t_tetris *core, char **values)
{
  if (values)
    {
      isValidKey(core, values[0]);
      core->keys.turn = values[0];
    }
  else
    throw_error("missing initializer.");
}

void	Arg_setKeyDrop(t_tetris *core, char **values)
{
  if (values)
    {
      isValidKey(core, values[0]);
      core->keys.drop = values[0];
    }
  else
    throw_error("missing initializer.");
}
