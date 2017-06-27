/*
** util.c for tetris in /home/arbona/tek1/PSU/PSU_2016_tetris
**
** Made by Thomas ARBONA
** Login   <thomas.arbona@epitech.eu>
**
** Started on  Mon Feb 27 14:48:32 2017 Thomas ARBONA
** Last update Tue Mar  7 21:39:21 2017 Arthur Chaloin
*/
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "my.h"

void			set_read_mode(int mode)
{
  static struct termios	termsave;
  static struct termios	term;

  if (mode == 1)
    {
      ioctl(0, TCGETS, &term);
      ioctl(0, TCGETS, &termsave);
      term.c_lflag &= ~ECHO;
      term.c_lflag &= ~ICANON;
      term.c_cc[VMIN] = 1;
      term.c_cc[VTIME] = 0;
      ioctl(0, TCSETS, &term);
    }
  else if (mode == 2)
    {
      ioctl(0, TCGETS, &term);
      ioctl(0, TCGETS, &termsave);
      term.c_lflag &= ~ECHO;
      term.c_lflag &= ~ICANON;
      term.c_cc[VMIN] = 0;
      term.c_cc[VTIME] = 0;
      ioctl(0, TCSETS, &term);
    }
  else
    ioctl(0, TCSETS, &termsave);
}

void	*xmalloc(int size)
{
  void	*p;

  p = malloc(size);
  if (!p)
    exit(84);
  return (p);
}

void	throw_error(char *error)
{
  my_dprintf(2, "Error: %s\n", error);
  exit(84);
}
