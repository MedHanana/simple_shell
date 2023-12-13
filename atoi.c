#include "shell.h"

/**
 * check_interactive - Determines if the shell is in check_interactive mode.
 * @info: Pointer to info_t structure.
 *
 * Return: 1 if check_interactive mode, 0 otherwise.
 */
int check_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_separator_char - Checks if a character is a separator.
 * @c: The character to check.
 * @separator: The separator string.
 *
 * Return: 1 if true, 0 if false.
 */
int is_separator_char(char c, char *separator)
{
	while (*separator)
		if (*separator++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha_character - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int is_alpha_character(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * convert_to_integer - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in the string, the converted number otherwise.
 */
int _convert_to_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

