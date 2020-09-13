/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:59:33 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 16:37:30 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_directory(const char *dir)
{
	struct stat	stt;

	if (access(dir, F_OK))
		ft_error("cd: no such file or directory");
	else if (stat(dir, &stt))
		ft_error("cd: stat error");
	else if (!S_ISDIR(stt.st_mode))
		ft_error("cd: not a directory");
	else
		return (0);
	return (1);
}

int			msh_cd(char *const *argv)
{
	char	*pwd;
	char	*dir;

	dir = argv[1] ? argv[1] : ft_getenv("HOME");
	if (!dir)
		ft_error("cd: HOME not set");
	else if (check_directory(dir))
		return (1);
	else if (chdir(dir))
		ft_error("cd: unknown error");
	else
	{
		pwd = getcwd(NULL, 0);
		ft_setenv("OLDPWD", ft_getenv("PWD"), 1);
		ft_setenv("PWD", pwd, 1);
	}
	return (1);
}
