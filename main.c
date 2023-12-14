#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @arguments_vector: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **arguments_vector)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\info_t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(arguments_vector[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_error_string(arguments_vector[0]);
				_error_string(": 0: Can'info_t open ");
				_error_string(arguments_vector[1]);
				_error_char('\n');
				_error_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	initialize_environment_list(info);
	read_history(info);
	hsh(info, arguments_vector);
	return (EXIT_SUCCESS);
}

