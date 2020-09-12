/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:15:56 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 03:57:14 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*join_path(const char *dir, const char *file, char *buf)
{
	char *f;

	if (!dir || !file)
		return (ft_strlcpy(buf, "", PATH_MAX));
	if ((f = ft_strrchr(file, '/')))
		file = f + 1;
	ft_strlcpy(buf, dir, PATH_MAX);
	if (buf[ft_strlen(dir)] != '/')
		ft_strlcat(buf, "/", PATH_MAX);
	ft_strlcat(buf, file, PATH_MAX);
	return (buf);
}

static int	locate_exec(char *name, char **exec)
{
	char	*pathenv;
	char	*path;

	*exec = ft_xmalloc(sizeof(char) * PATH_MAX);
	if (access(name) == 0)
	{
		getcwd(exec, PATH_MAX);
		ft_strlcat(exec, name);
		return (1);
	}
	pathenv = ft_strdup(ft_getenv("PATH"));
	path = ft_strtok(pathenv, ":");
	while (path != NULL)
	{
		join_path(path, name, *exec);
		if (access(path, F_OK))
			return (1);
		path = ft_strtok(NULL, ":");
	}
	free(*exec);
	return (0);
}

int			msh_launch(char *[]argv)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		ft_terminate("failed to fork", 0);
	else if (pid == 0)
	{
		if (!locate_exec(argv[0], &path))
			ft_terminate(argv[0], "command not found");
		else if (access(path, X_OK))
			ft_terminate(argv[0], "permission defined");
		else if (execve(path, argv, environ))
			ft_terminate(argv[0], "failed to execute");
	}
	else
		wait(NULL);
	return (1);
}
