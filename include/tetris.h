/*
** tetris.h for tetris in /home/arthur/B2/PSU/PSU_2016_tetris
**
** Made by Arthur Chaloin
** Login   <arthur@epitech.net>
**
** Started on  Sat Feb 25 18:55:20 2017 Arthur Chaloin
** Last update Mon Mar 20 18:04:45 2017 Arthur Chaloin
*/

#ifndef TETRIS_H_
# define TETRIS_H_

# include <time.h>
# include <fmod.h>
# include "my.h"
# include "vector.h"

typedef long long int	t_lli;

typedef struct	s_score
{
  char	*name;
  int	score;
}		t_score;

typedef struct	s_shape
{
  t_vect	pos;
  t_vect	size[4];
  int		color;
  int		dir;
  int		drop;
  char		***shapes;
}		t_shape;

typedef	struct	s_tetrimino
{
  char		*name;
  t_shape	*info;
}		t_tetrimino;

typedef struct	s_keys
{
  char		*left;
  char		*right;
  char		*turn;
  char		*drop;
  char		*quit;
  char		*pause;
}		t_keys;

typedef struct	s_tetris
{
  t_keys	keys;
  t_vect	size;
  t_lli		frame;
  int		next;
  int		level;
  int		help;
  int		score;
  int		high_score;
  int		debug;
  char		**map;
  time_t	start_time;
  t_vector	tetriminos;
  int		music;
  t_vector	songs;
  FMOD_SYSTEM	*system;
  FMOD_SOUND	*song;
  FMOD_DSP	*dsp;
  FMOD_CHANNELGROUP	*channel;
}		t_tetris;

# define KEY__LEFT	1
# define KEY__RIGHT	2
# define KEY__TURN	3
# define KEY__DROP	4
# define KEY__QUIT	5
# define KEY__PAUSE	6

extern int	color;

void	Debug_print(t_tetris *core);
void	Core_game(t_tetris *core);
int	Core_getInput(t_tetris *core);
int	Core_handleInput(t_tetris *core, t_shape *obj,
			 t_shape *next, int size[2]);
void	Core_initMusic(t_tetris *core);
int     Core_writeObj(t_tetris *core, t_shape *shape);
void	Core_handleScore(t_tetris *core);
void	Core_saveScore(t_tetris *core, int size[2]);
void	Core_loadHighScore(t_tetris *core);
void	Core_destroy() __attribute__((destructor));
int	collision(t_tetris *core, t_shape *obj);
int	wait_input(int size[2], int *cursor);

#endif /* !TETRIS_H_ */
