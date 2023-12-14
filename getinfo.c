#include "shell.h"

/**
 * initialize_info - Initializes custom_info_t structure.
 * @custom_info: Structure address.
 */
void initialize_info(info_t *custom_info)
{
	custom_info->arg = NULL;
	custom_info->argv = NULL;
	custom_info->path = NULL;
	custom_info->argc = 0;
}

/**
 * configure_info - Configures custom_info_t structure.
 * @custom_info: Structure address.
 * @arguments_vector: Argument vector.
 */
void configure_info(info_t *info, char **arguments_vector)
{
	int i = 0;
	info->fname = arguments_vector[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * @brief Frees resources in the shell information structure.
 * @param info Address of the structure to release resources.
 * @param all True if freeing all fields.
 */
void releaseShellInfo(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

