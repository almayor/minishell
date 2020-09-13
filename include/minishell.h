/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 21:09:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/14 00:53:41 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include "libftprintfgnl.h"
# include "ansi.h"

# define MSH_NAME			"msh"
# define MSH_TOK_DELIM		" \t\r\n\a"
# define MSH_TOK_BUFSIZE	4096
# define MSH_PROMPT_BUFSIZE	128

# define MSH_ERR_MALLOC		"malloc error"
# define MSH_ERR_FORK		"failed to fork"
# define MSH_ERR_PERM		"permission denied"
# define MSH_ERR_EXEC		"failed to execute"
# define MSH_ERR_CMD		"command not found"
# define MSH_ERR_SIGHNDL	"failed to set a signal handler"

extern char	**g_environ;
extern int	g_pid;

/*
** driver functions
*/

int			msh_execute(char *const *argv);
char		*msh_expand(const char *s);
void		msh_loop(void);
const char	*msh_prompt(void);

/*
** signal handlers
*/

void		handler_sigint(int sig);
void		handler_sigterm(int sig);

/*
** builtin commands
*/

int			msh_cd(char *const *argv);
int			msh_echo(char *const *argv);
int			msh_exit(char *const *argv);
int			msh_setenv(char *const *argv);
int			msh_unsetenv(char *const *argv);
int			msh_env(char *const *argv);

/*
** utils
*/

void		ft_error(const char *mes);
char		*ft_getenv(const char *name);
int			ft_setenv(const char *name, const char *value, int overwrite);
char		*ft_strtok(char *str, const char *sep);
char		*ft_strtok_r(char *str, const char *sep, char **lasts);
size_t		ft_tablen(char *const *tab);
void		ft_terminate(const char *mes, int rc);
int			ft_unsetenv(const char *name);
void		*ft_xcalloc(size_t count, size_t size);
void		*ft_xmalloc(size_t size);

#endif
