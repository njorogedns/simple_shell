#include "main.h"
/**
* _getline - Read The Input By User From Stdin
* Return: Input
*alx-school-- shell
*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
  int i;
  static ssize_t input;
  ssize_t retval;
  char *buffer, t = 'z';

  if (input == 0)
    fflush(stream);
  else
    return (-1);
  input = 0;

  buffer = malloc(sizeof(char) * BUFSIZE);
  if (buffer == 0)
    return (-1);

  while (t != '\n')
    {
      i = read(STDIN_FILENO, &t, 1);
      if (i == -1 || (i == 0 && input == 0))
	{
	  free(buffer);
	  return (-1);
	}
      if (i == 0 && input != 0)
	{
	  input++;
	  break;
	}
      if (input >= BUFSIZE)
	buffer = _realloc(buffer,input, input + 1);
      buffer[input] = t;
      input++;
    }
  buffer[input] = '\0';
  _bringline(lineptr, n, buffer, input);
  retval = input;
  if (i != 0)
    input = 0;
  return (retval);
}
/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void _bringline(char **lineptr, size_t *n, char *buffer, size_t j)
{
  if (*lineptr == NULL)
    {
      if (j > BUFSIZE)
	*n = j;
      else
	*n = BUFSIZE;
      *lineptr = buffer;
    }
  else if (*n < j)
    {
      if (j > BUFSIZE)
	*n = j;
      else
	*n = BUFSIZE;
      *lineptr = buffer;
    }
  else
    {
      _strcpy(*lineptr, buffer);
      free(buffer);
    }
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{
  size_t a;

  for (a = 0; src[a] != '\0'; a++)
    {
      dest[a] = src[a];
    }
  dest[a] = '\0';

  return (dest);
}
/**
 **_realloc -  Reallocates A Memory Block Using Malloc And Free
 *@ptr: Pointer
 *@old_size: Previous Size Of The Pointer
 *@new_size: New Size Of The Pointer
 *Return: Void Pointer Rellocated Memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
  void *newptr;

  if (ptr == NULL)
    return (malloc(new_size));

  if (new_size == 0)
    {
      free(ptr);
      return (NULL);
    }

  if (new_size == old_size)
    return (ptr);

  newptr = malloc(new_size);
  if (newptr == NULL)
    return (NULL);

  if (new_size < old_size)
    _memcpy(newptr, ptr, new_size);
  else
    _memcpy(newptr, ptr, old_size);

  free(ptr);
  return (newptr);
}
