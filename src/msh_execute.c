/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:41:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/18 18:32:27 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_gid;

static char	*g_builtin_name[] = {
	"cd",
	"exit",
	"echo",
	"setenv",
	"unsetenv",
	"env",
};

static int	(*g_builtin_func[]) (char *const *) = {
	&msh_cd,
	&msh_exit,
	&msh_echo,
	&msh_setenv,
	&msh_unsetenv,
	&msh_env
};

static int	msh_num_builtins(void)
{
	return (sizeof(g_builtin_name) / sizeof(char *));
}

static char	*join_path(const char *dir, const char *file, char *buf)
{
	size_t	dir_len;

	dir_len = ft_strlcpy(buf, dir, PATH_MAX);
	if (buf[dir_len] != '/')
		ft_strlcat(buf, "/", PATH_MAX);
	ft_strlcat(buf, file, PATH_MAX);
	return (buf);
}

static char	*locate_exec(const char *name, char *buf)
{
	static char	path[PATH_MAX];
	char		*dir;

	if (*name == '/' && access(name, F_OK) == 0)
		return (ft_strcpy(buf, name));
	else if (access(name, F_OK) == 0)
	{
		getcwd(buf, PATH_MAX);
		ft_strlcat(buf, "/", PATH_MAX);
		ft_strlcat(buf, name, PATH_MAX);
		return (buf);
	}
	ft_strlcpy(path, ft_getenv("PATH"), PATH_MAX);
	dir = ft_strtok(path, ":");
	while (dir != NULL)
	{
		join_path(dir, name, buf);
		if (access(buf, F_OK) == 0)
			return (buf);
		dir = ft_strtok(NULL, ":");
	}
	return (NULL);
}

static int	msh_launch(char *const *argv)
{
	static char	exec[PATH_MAX];

	g_pid_child = fork();
	if (g_pid_child < 0)
		ft_terminate(MSH_ERR_FORK, 1);
	else if (g_pid_child == 0)
	{
		if (!locate_exec(argv[0], exec))
			ft_terminate(MSH_ERR_CMD, 1);
		else if (access(exec, X_OK))
			ft_terminate(MSH_ERR_PERM, 1);
		else if (execve(exec, argv, g_environ))
			ft_terminate(MSH_ERR_EXEC, 1);
	}
	else
		wait(NULL);
	g_pid_child = 0;
	return (1);
}

int			msh_execute(char *const *argv)
{
	size_t	i;

	if (argv[0] == NULL)
		return (1);
	i = 0;
	while (i < msh_num_builtins())
	{
		if (ft_strcmp(argv[0], g_builtin_name[i]) == 0)
			return ((*g_builtin_func[i])(argv));
		i++;
	}
	return (msh_launch(argv));
}
