#include "shell.h"

/**
 * exitShell - exits the shell
 * @info: Structure containing potential arguments.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit"
 */
int _exitShell(info_t *info)
{
	int exitC;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitC = customAtoi(info->argv[1]);
		if (exitC == -1)
		{
			info->status = 2;
			printError(info, "Illegal");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->errNum = customAtoi(info->argv[1]);
		return (-2);
	}
	info->errNum = -1;
	return (-2);
}

/**
 * changeDirectory - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _changeDirectory(info_t *info)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirRet;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		newDir = _getenv(info, "HOME=");
		if (!newDir)
			chdirRet = chdir((newDir = _getenv(info, "PWD=")) ? newDir : "/");
		else
			chdirRet = chdir(newDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirRet = chdir((newDir = _getenv(info, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirRet = chdir(info->argv[1]);
	if (chdirRet == -1)
	{
		printError(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * showHelp - displays help information
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _showHelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray); /* temp att_unused workaround */
	return (0);
}

