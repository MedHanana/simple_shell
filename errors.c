#include "shell.h"

/**
 * print_error_string - Prints an error message to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _error_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		write_error_char(str[i]);
		i++;
	}
}

/**
 * write_error_char - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _error_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_to_file_descriptor - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _to_file_descriptor(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * print_to_file_descriptor - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _print_to_file_descriptor(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _to_file_descriptor(*str++, fd);
	}
	return (i);
}

