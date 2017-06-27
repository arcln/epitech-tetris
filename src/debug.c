/*
** debug.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Feb 27 10:45:38 2017 Arthur Chaloin
** Last update Fri Mar 17 17:25:19 2017 Arthur Chaloin
*/
#include <unistd.h>
#include "tetris.h"
#include "util.h"
#include "my.h"

static void	print_special(char *str)
{
  int		index;

  index = -1;
  while (str[++index])
    {
      if (str[index] == 27)
	my_printf("^E");
      else if (str[index] == ' ')
	my_printf("(space)");
      else
	my_printf("%c", str[index]);
    }
}

int		sort_tetrimino(void *a, void *b)
{
  if (my_strcmp(((t_tetrimino *)a)->name, ((t_tetrimino *)b)->name) > 0)
    return (1);
  else
    return (0);
}

static void	Debug_printTetriminos(t_vector *tetriminos)
{
  int		index;
  int		index2;
  t_tetrimino	*actual;

  index = -1;
  vector_sort(tetriminos, &sort_tetrimino);
  my_printf("Tetriminos : %d\n", vector_getsize(tetriminos));
  while (++index < vector_getsize(tetriminos))
    {
      actual = vector_get(tetriminos, index, t_tetrimino);
      if (actual->info)
	my_printf("Tetriminos : Name %s : Size %d*%d : Color %d :\n",
		  actual->name, actual->info->size[0].x,
		  actual->info->size[0].y, actual->info->color);
      else
	my_printf("Tetriminos : Name %s : Error\n", actual->name);
      index2 = -1;
      while (actual->info && ++index2 < actual->info->size[0].y)
	my_printf("%s\n", actual->info->shapes[0][index2]);
    }
}

static void	Debug_printKeys(t_keys *keys)
{
  my_printf("Key Left : ");
  print_special(keys->left);
  my_printf("\nKey Right : ");
  print_special(keys->right);
  my_printf("\nKey Turn : ");
  print_special(keys->turn);
  my_printf("\nKey Drop : ");
  print_special(keys->drop);
  my_printf("\nKey Quit : ");
  print_special(keys->quit);
  my_printf("\nKey Pause : ");
  print_special(keys->pause);
  my_printf("\n");
}

void	Debug_print(t_tetris *core)
{
  my_printf("*** DEBUG MODE ***\n");
  Debug_printKeys(&(core->keys));
  my_printf("Next : %s\n", (core->next) ? "Yes" : "No");
  my_printf("Level : %d\n", core->level);
  my_printf("Size : %d*%d\n", core->size.y, core->size.x);
  Debug_printTetriminos(&core->tetriminos);
  my_printf("Press any key to start Tetris\n");
  set_read_mode(1);
  read(0, NULL, 1);
  set_read_mode(0);
}
