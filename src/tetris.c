/*
** tetris.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris
**
** Made by Arthur Chaloin
** Login   <arthur@epitech.net>
**
** Started on  Sat Feb 25 18:54:17 2017 Arthur Chaloin
** Last update Mon Mar 20 18:14:01 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <term.h>
#include <ncurses.h>
#include "tetris.h"
#include "display.h"
#include "parser.h"
#include "util.h"
#include "arg.h"
#include "my.h"

void	Core_destroy()
{
  set_read_mode(0);
  endwin();
}

static void	Core_displayHelp(char *name)
{
  my_printf("Usage: %s [options]\n", name);
  my_printf("Options:\n\t--help\t\t\tDisplay this help\n\t-l --level={num}\t");
  my_printf("Start Tetris at level num (def: 1)\n\t-kl --key-left={K}\t");
  my_printf("Move the tetrimino LEFT using the K key (def: left arrow)\n");
  my_printf("\t-kr --key-right={K}\tMove the tetrimino RIGHT using the K ");
  my_printf("key (def: right arrow)\n\t-kt --key-turn={K}\tTURN the ");
  my_printf("tetrimino clockwise 90d using the K key (def: up arrow)\n\t-kd");
  my_printf("--key-drop={K}\tDROP the tetrimino using the K key");
  my_printf("(def: down arrow)\n\t-kq --key-quit={K}\tQUIT the game using ");
  my_printf("the K key (def: 'Q' key)\n\t-kp --key-pause={K}\t");
  my_printf("PAUSE/RESTART the game using the K key (def: space bar)\n\t");
  my_printf("--map-size={row,col}\tSet the number of rows and columns of the");
  my_printf(" map (def: 20,10)\n\t-w--without-next\tHide next tetrimino ");
  my_printf("(def: false)\n\t-d --debug\t\tDebug mode (def: false)\n");
}

static void	Core_init(t_tetris *core, int ac, char **av)
{
  core->frame = 0;
  core->help = 0;
  core->debug = 0;
  core->next = 1;
  core->level = 1;
  core->score = 0;
  core->music = 1;
  core->high_score = 0;
  core->size.x = 10;
  core->size.y = 20;
  core->keys.left = NULL;
  core->keys.right = NULL;
  core->keys.turn = NULL;
  core->keys.drop = NULL;
  core->keys.quit = NULL;
  core->keys.pause = NULL;
  Arg_parse(core, ac, av);
  Parser_parse(core);
  setupterm(NULL, 1, NULL);
  core->keys.left = (core->keys.left) ? core->keys.left : tigetstr("kcub1");
  core->keys.right = (core->keys.right) ? core->keys.right : tigetstr("kcuf1");
  core->keys.turn = (core->keys.turn) ? core->keys.turn : tigetstr("kcuu1");
  core->keys.drop = (core->keys.drop) ? core->keys.drop : tigetstr("kcud1");
  core->keys.quit = (core->keys.quit) ? core->keys.quit : "q";
  core->keys.pause = (core->keys.pause) ? core->keys.pause : " ";
  endwin();
}

void	Core_initDisplay(t_tetris *core)
{
  int	index[2];

  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(3, COLOR_WHITE, COLOR_RED);
  init_pair(4, COLOR_WHITE, COLOR_GREEN);
  init_pair(5, COLOR_WHITE, COLOR_CYAN);
  init_pair(6, COLOR_WHITE, COLOR_YELLOW);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_BLACK, COLOR_WHITE);
  index[0] = ((core->map = xmalloc(sizeof(char *) * core->size.y)) == 0) - 1;
  while (++index[0] < core->size.y)
    {
      index[1] = -1;
      core->map[index[0]] = xmalloc(sizeof(char) * (core->size.x + 1));
      while (++index[1] < core->size.x)
	core->map[index[0]][index[1]] = 0;
    }
  Core_loadHighScore(core);
}

int		main(int ac, char **av)
{
  t_tetris	core;

  srand(time(NULL));
  Core_init(&core, ac, av);
  if (vector_getsize(&(core.tetriminos)) < 1)
    return (84);
  if (core.help)
    {
      Core_displayHelp(av[0]);
      return (0);
    }
  else if (core.debug)
    Debug_print(&core);
  Core_initDisplay(&core);
  Display_menu(&core);
  return (0);
}
