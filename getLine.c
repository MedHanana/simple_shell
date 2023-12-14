#include "shell.h"

/**
 * @brief Reads input and buffers chained commands.
 * @param info Parameter structure.
 * @param buf Address of the buffer.
 * @param len Address of len variable.
 * @return Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, blockCtrlC);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * @brief Gets input line excluding the newline character.
 * @param info Parameter structure.
 * @return Bytes read.
 */
ssize_t getInput(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
	}

/**
 * @brief Reads a buffer.
 * @param info Parameter structure.
 * @param buf Buffer.
 * @param i Size.
 * @return Bytes read.
 */
ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;
    if (*i)
        return (0);
    bytesRead = read(info->readfd, buf, READ_BUF_SIZE);
    if (bytesRead >= 0)
        *i = bytesRead;

    return (bytesRead);
}

/**
 * @brief Gets the next line of input from STDIN.
 * @param info Parameter structure.
 * @param ptr Address of pointer to buffer, preallocated or NULL.
 * @param lg Size of preallocated ptr buffer if not NULL.
 * @return Bytes read.
 */
int customGetline(info_t *info, char **ptr, size_t *lg)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytesRead = 0, totalBytesRead = 0;
    char *p = NULL, *new_p = NULL, *c;
    p = *ptr;
    if (p && lg)
        totalBytesRead = *lg;
    if (i == len)
        i = len = 0;
    bytesRead = readBuffer(info, buf, &len);
    if (bytesRead == -1 || (bytesRead == 0 && len == 0))
        return (-1);
    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, totalBytesRead, totalBytesRead ? totalBytesRead + k : k + 1);
    if (!new_p)
        return (p ? (free(p), -1) : -1);
    if (totalBytesRead)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);
    totalBytesRead += k - i;
    i = k;
    p = new_p;
    if (lg)
	*lg = totalBytesRead;
    *ptr = p;
    return (totalBytesRead);
}
/**
 * @brief Handles the SIGINT signal (blocks Ctrl-C).
 * @param sigNum The signal number.
 */
void blockCtrlC(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

