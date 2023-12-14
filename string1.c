#include "shell.h"

char *_stringcopy(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}

char *_string_up(const char *str)
{
	int lg = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lg++;
	ret = malloc(sizeof(char) * (lg + 1));
	if (!ret)
		return (NULL);
	for (lg++; lg--;)
		ret[lg] = *--str;
	return (ret);
}

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

