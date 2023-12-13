#include "shell.h"

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in the string, converted number otherwise,
 *        -1 on error.
 */
int _atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_custom_error - Prints a custom error message.
 * @info: The parameter & return info struct.
 * @estr: String containing the specified error type.
 * Return: Nothing.
 */
void print_custom_error(info_t *info, char *estr)
{
	_custom_puts(info->fname);
	_custom_puts(": ");
	print_custom_integer(info->line_count, STDERR_FILENO);
	_custom_puts(": ");
	_custom_puts(info->argv[0]);
	_custom_puts(": ");
	_custom_puts(estr);
}

/**
 * print_custom_integer - Prints an integer.
 * @input: The integer to print.
 * @fd: The file descriptor to write to.
 * Return: Number of characters printed.
 */
int print_custom_integer(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_integer_to_string - Converts an integer to a string.
 * @num: Integer to convert.
 * @base: Base for conversion.
 * @flags: Argument flags.
 *
 * Return: Converted string.
 */
char *convert_integer_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * eliminate_comments - Replaces the first instance of '#' with '\0'.
 * @string_buffer: Address of the string to modify.
 *
 * Return: Always 0.
 */
void eliminate_comments(char *string_buffer)
{
	int i;

	for (i = 0; string_buffer[i] != '\0'; i++)
		if (string_buffer[i] == '#' && (!i || string_buffer[i - 1] == ' '))
		{
			string_buffer[i] = '\0';
			break;
		}
}

