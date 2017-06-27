/*
** parser.h for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/include/parser/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Feb 27 10:35:26 2017 Arthur Chaloin
** Last update Fri Mar 17 16:37:45 2017 Arthur Chaloin
*/

#ifndef PARSER_H_
# define PARSER_H_

# include "my.h"
# include "tetris.h"

void	Parser_parse(t_tetris *);
t_shape	*Parser_tetrimino(int fd);

#endif /* !PARSER_H_ */
