/*
** arg.c for tetris in /home/arbona/tek1/PSU/PSU_2016_tetris
**
** Made by Thomas ARBONA
** Login   <thomas.arbona@epitech.eu>
**
** Started on  Mon Feb 27 13:40:50 2017 Thomas ARBONA
** Last update Sun Mar 19 20:10:08 2017 Arthur Chaloin
*/
#include <unistd.h>
#include "arg.h"
#include "util.h"

t_arg   g_arg[] = {
  {"--help", NULL, 0, Arg_setHelp},
  {"--map-size", NULL, 1, Arg_setMapSize},
  {"--level", "-l", 1, Arg_setLevel},
  {"--key-left", "-kl", 1, Arg_setKeyLeft},
  {"--key-right", "-kr", 1, Arg_setKeyRight},
  {"--key-turn", "-kt", 1, Arg_setKeyTurn},
  {"--key-drop", "-kd", 1, Arg_setKeyDrop},
  {"--key-quit", "-kq", 1, Arg_setKeyQuit},
  {"--key-pause", "-kp", 1, Arg_setKeyPause},
  {"--without-next", "-w", 0, Arg_setWithoutNext},
  {"--debug", "-d", 0, Arg_setDebug},
  {0, 0, 0, 0}
};

t_arg	Arg_get(char *name)
{
  int	index;

  index = 0;
  while (g_arg[index].name != 0)
    {
      if (my_strcmp(g_arg[index].name, name) == 0 ||
	  (g_arg[index].sname != NULL &&
	   my_strcmp(g_arg[index].sname, name) == 0))
	return (g_arg[index]);
      index += 1;
    }
  return (g_arg[index]);
}

void		Arg_parse(t_tetris *core, int ac, char **av)
{
  int		index, smode, pos;
  t_arg		arg;
  char		*tmp;
  char		**values = NULL;

  index = 1;
  while (index < ac)
    {
      pos = my_str_contain(av[index], '=');
      tmp = (pos != -1) ? av[index] + pos + 1 : NULL;
      av[index][pos] = 0;
      if ((arg = Arg_get(av[index])).name == NULL)
	throw_error("unknown argument.");
      smode = (av[index][1] != '-');
      if (!smode)
	{
	  if ((pos == -1 && arg.nb_arg != 0))
	    throw_error("argument syntax error.");
	  values = tmp ? my_str_to_wordtab(tmp, ",'") : NULL;
	}
      else if (index + 1 < ac)
	values = my_str_to_wordtab(av[index + 1], ",'");
      arg.func(core, values);
      index += 1 + (smode && arg.nb_arg);
    }
}
