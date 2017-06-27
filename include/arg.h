/*
** arg.h for tetris in /home/arbona/tek1/PSU/PSU_2016_tetris
**
** Made by Thomas ARBONA
** Login   <thomas.arbona@epitech.eu>
**
** Started on  Mon Feb 27 13:41:58 2017 Thomas ARBONA
** Last update Mon Feb 27 15:10:02 2017 Thomas ARBONA
*/
#ifndef ARG_H_
# define ARG_H_

# include "tetris.h"

typedef struct  s_arg
{
  char          *name;
  char          *sname;
  int		nb_arg;
  void          (*func)();
}               t_arg;

void	isValidKey(t_tetris*, char*);

void	Arg_parse(t_tetris *core, int ac, char **av);

void	Arg_setHelp(t_tetris*, char**);
void	Arg_setMapSize(t_tetris*, char**);
void	Arg_setLevel(t_tetris*, char**);
void	Arg_setKeyLeft(t_tetris*, char**);
void	Arg_setKeyRight(t_tetris*, char**);
void	Arg_setKeyTurn(t_tetris*, char**);
void	Arg_setKeyDrop(t_tetris*, char**);
void	Arg_setKeyQuit(t_tetris*, char**);
void	Arg_setKeyPause(t_tetris*, char**);
void	Arg_setWithoutNext(t_tetris*, char**);
void	Arg_setDebug(t_tetris*, char**);

#endif /* !ARG_H_ */
