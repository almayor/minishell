/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:41:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 16:34:07 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*f;

	if ((f = ft_strrchr(file, '/')))
		file = f + 1;
	ft_strlcpy(buf, dir, PATH_MAX);
	if (buf[ft_strlen(dir)] != '/')
		ft_strlcat(buf, "/", PATH_MAX);
	ft_strlcat(buf, file, PATH_MAX);
	return (buf);
}

static int	locate_exec(const char *name, char **exec)
{
	char	*pathenv;
	char	*path;
	int		found;

	*exec = ft_xmalloc(sizeof(char) * PATH_MAX);
	if (access(name, F_OK) == 0)
	{
		join_path(getcwd(*exec, PATH_MAX), name, *exec);
		return (1);
	}
	found = 0;
	pathenv = ft_strdup(ft_getenv("PATH"));
	path = ft_strtok(pathenv, ":");
	while (path != NULL)
	{
		join_path(path, name, *exec);
		if ((found = access(*exec, F_OK) == 0))
			break ;
		path = ft_strtok(NULL, ":");
	}
	free(pathenv);
	if (!found)
		free(*exec);
	return (found);
}

static int	msh_launch(char *const *argv)
{
	pid_t	pid;
	char	*exec;

	pid = fork();
	if (pid < 0)
		ft_terminate(MSH_ERR_FORK, 1);
	else if (pid == 0)
	{
		if (!locate_exec(argv[0], &exec))
			ft_terminate(MSH_ERR_CMD, 1);
		else if (access(exec, X_OK))
			ft_terminate(MSH_ERR_PERM, 1);
		else if (execve(exec, argv, g_environ))
			ft_terminate(MSH_ERR_EXEC, 1);
	}
	else
		wait(NULL);
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
