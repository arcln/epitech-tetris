/*
** map.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/core/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Fri Mar  3 16:25:37 2017 Arthur Chaloin
** Last update Tue Mar  7 18:29:08 2017 Arthur Chaloin
*/
#include "tetris.h"
#include "my.h"

int            Core_writeObj(t_tetris *core, t_shape *shape)
{
  t_vect        cursor;

  cursor.y = 0;
  if (shape->pos.y < 0)
    return (1);
  while (cursor.y < shape->size[shape->dir].y)
    {
      cursor.x = 0;
      while (cursor.x < shape->size[shape->dir].x)
	{
	  if (0 <= cursor.x + shape->pos.x &&
	      0 <= cursor.y + shape->pos.y &&
	      cursor.x + shape->pos.x < core->size.x &&
	      cursor.y + shape->pos.y < core->size.y &&
	      shape->shapes[shape->dir][cursor.y][cursor.x] == '*')
	    core->map[cursor.y + shape->pos.y][cursor.x + shape->pos.x] =
	  	shape->color;
	  cursor.x += 1;
	}
      cursor.y += 1;
    }
  return (0);
}
