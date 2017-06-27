/*
** display.h for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/include/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Fri Mar  3 09:46:31 2017 Arthur Chaloin
** Last update Tue Mar 21 10:01:17 2017 Arthur Chaloin
*/

#ifndef DISPLAY_H_
# define DISPLAY_H_

# include "tetris.h"
# include "my.h"

void	Core_display(t_tetris *core, t_shape *actual,
		     t_shape *next, int size[2]);
void	Display_menu(t_tetris *core);
void	Display_draw(t_shape *info, t_vect *board, int size[2]);
void	Display_drawAt(t_shape *shape, t_vect *pos);
void	Display_drawRect(t_vect *pos, t_vect *size, int color);
void	Display_drawMap(t_tetris *core, int size[2]);
void	Display_stats(t_tetris *core, int level);
void	Display_music(t_tetris *core);
void	Display_animeLost(t_tetris *core, int size[2]);
void	Display_title();

#endif /* !DISPLAY_H_ */
