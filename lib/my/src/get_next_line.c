/*
** get_next_line.c for get_next_line in /home/arthur/Documents/B1-C_Prog_Elem/CPE_2016_getnextline/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Jan  3 11:17:43 2017 Arthur Chaloin
** Last update Mon Feb 27 10:57:34 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define READ_SIZE	1024

static int	my_strlen(char *str)
{
  int		count;

  count = 0;
  while (str[count])
    count++;
  return (count);
}

static char	*my_strcat(char *s1, char *s2)
{
  int		index;
  int		len1;
  int		len2;
  char		*new;

  index = 0;
  len1 = (s1) ? my_strlen(s1) : 0;
  len2 = (s2) ? my_strlen(s2) : 0;
  if (!(new = malloc(sizeof(char) * (len1 + len2 + 1))))
    return (NULL);
  while (s1 && s1[index])
    {
      new[index] = s1[index];
      index++;
    }
  index = 0;
  while (s2 && s2[index])
    {
      new[index + len1] = s2[index];
      index++;
    }
  new[index + len1] = '\0';
  return (new);
}

static char		*my_strndup(char *str, unsigned int size)
{
  unsigned int		index;
  char			*new;

  index = 0;
  if (!(new = malloc(sizeof(char) * (size + 1))))
    return (NULL);
  while (str[index] && index < size)
    {
      new[index] = str[index];
      index++;
    }
  new[index] = '\0';
  return (new);
}

char			*get_next_line(const int fd)
{
  unsigned int		start;
  static unsigned int	index = 0;
  static int		read_bytes = 42;
  static char		buffer[READ_SIZE + 1] = {0};
  char			*input;

  if (fd < 0) {buffer[0] = '\0'; read_bytes = 42; index = 0; return (NULL);}
  if (fd < 0 || !(input = my_strcat("\0", NULL))) return (NULL);
  while (buffer[index] != '\n' && read_bytes)
    {
      if (!buffer[index])
	{
	  index = 0;
	  read_bytes = read(fd, buffer, READ_SIZE);
	  if (read_bytes < 0)	return (NULL);
	  buffer[read_bytes] = '\0';
	}
      start = index;
      while (index < read_bytes && buffer[index] != '\n' && buffer[index])
	index++;
      if (!(input = my_strcat(input,
                my_strndup(buffer + start, index - start)))) return (NULL);
    }
  if (read_bytes) index++;
  return ((input[0] || read_bytes) ? input : NULL);
}
