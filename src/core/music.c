/*
** music.c for tetris in /home/arthur/B2/PSU/PSU_2016_tetris/src/core/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Mar 20 15:44:34 2017 Arthur Chaloin
** Last update Mon Mar 20 19:36:23 2017 Arthur Chaloin
*/
#include <dirent.h>
#include <stdlib.h>
#include <fmod.h>
#include <ncurses.h>
#include "tetris.h"
#include "my.h"

int	color = 8;

static char	*get_music()
{
  DIR		*dir;
  struct dirent	*file;
  t_vector	files;
  char		*choice;

  vector_create(&files);
  dir = opendir("music/");
  while ((file = readdir(dir)))
    vector_push(&files, (void *)file);
  while ((choice = my_str_concat("music/",
			(vector_get(&files, rand() % vector_getsize(&files),
			struct dirent))->d_name)) && choice[6] == '.');
  return (choice);
}

void	Core_initMusic(t_tetris *core)
{
  FMOD_System_Create(&(core->system));
  FMOD_System_Init(core->system, 1, FMOD_INIT_NORMAL, NULL);
  FMOD_System_CreateSound(core->system, get_music(),
	FMOD_2D | FMOD_CREATESTREAM, 0, &(core->song));
  FMOD_System_PlaySound(core->system, core->song, 0, 0, NULL);
  FMOD_System_GetMasterChannelGroup(core->system, &(core->channel));
  FMOD_System_CreateDSPByType(core->system, FMOD_DSP_TYPE_FFT, &(core->dsp));
}

void				Display_music(t_tetris *core)
{
  int				index;
  int				index2;
  int				size[2];
  FMOD_DSP_PARAMETER_FFT	*fft;

  FMOD_ChannelGroup_AddDSP(core->channel, 0, core->dsp);
  FMOD_DSP_GetParameterData(core->dsp, FMOD_DSP_FFT_SPECTRUMDATA,
			    (void **)&fft, 0, 0, 0);
  index = -1;
  getmaxyx(stdscr, size[1], size[0]);
  attron(COLOR_PAIR(color));
  while (++index < fft->length)
    {
      index2 = -1;
      if (fft->spectrum[0][index] * 100 > 28)
	color = rand() % 6 + 1;
      while (++index2 < fft->spectrum[0][index] * 100)
	{
	  mvprintw(size[1] - index2, ((index * (size[0] / 2))
				      / fft->length) * 2, "  ");
	  mvprintw(index2 - 1, size[0] - 2 - (((index * (size[0] / 2))
				      / fft->length) * 2), "  ");
	}
    }
  attroff(COLOR_PAIR(color));
}
