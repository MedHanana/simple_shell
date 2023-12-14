#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_n() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_getlinein 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(t *);
} builtin_table;


/* shloop.c */
int hsh(t *, char **);
int builtin(t *);
void _cmd(t *);
void frk_cmd(t *);

/* parser.c */
int cmd(t *, char *);
char *chrs(char *, int, int);
char *fd_path(t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void put(char *);
int _putchars(char);
int _to_file_descriptor(char c, int fd);
int _print_to_file_descriptor(char *str, int fd);

/* string.c */
int _strlen(char *);
int _stringcopy(char *, char *);
char *string_with(const char *, const char *);
char *_stringcat(char *, char *);

/* string1.c */

/* exits.c */
char *_stringcopy(char *, char *, int);
char *_custom_strncat(char *, char *, int);
char *_custom_strchr(char *, char);

/* tokenizer.c */
int is_dlm(char c, const char *delimiters)
char **strt(char *, char *);
char **strt2(char *, char);

/* realloc.c */
char *_set(char *, char, unsigned int);
void fr(char **);
void *_r_ealloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfr(void **);

/* atoi.c */
int itractive(t *);
int is_delm(char, char *);
int is_alpha_character(int);
int _convert_to_integer(char *);

/* errors1.c */
int _404err(char *);
void print_err(t *, char *);
int print_custom_integer(int, int);
char *convert_n(long int, int, int);
void rv_cmt(char *);

/* builtin.c */
int _myexit(t *);
int _mycd(t *);
int _myhelp(t *);

/* builtin1.c */
int _dishistory(t *);
int _manage_alias(t *);

/* getlinein.c */
ssize_t get_inputin(t *);
int _getlinein(t *, char **, size_t *);
void siginH(int);

/* getinfo.c */
void initialize_info(t *);
void configure_info(t *, char **);
void releaseShellInfo(t *, int);

/* environ.c */
char _environmentvar(t *, const char *);
int _environment(t *);
int _set_environment(t *);
int _unset_environment(t *);
int initialize_environment_list(t *);

/* getenv.c */
char **get_environment(t *);
int _custom_unsetenv(t *, char *);
int _setenv(t *, char *, char *);

#endif

