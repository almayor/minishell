/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:59:33 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 20:23:24 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			msh_cd(char *const *argv)
{
	char		*pwd;
	char		*dir;
	struct stat	stt;

	if (!(dir = argv[1]) && !(dir = ft_getenv("HOME")))
		ft_error("cd: HOME not set");
	else if (ft_strcmp(dir, "-") == 0 && !(dir = ft_getenv("OLDPWD")))
		ft_error("cd: OLDPWD not set");
	else if (access(dir, F_OK))
		ft_error("cd: no such file or directory");
	else if (stat(dir, &stt))
		ft_error("cd: stat error");
	else if (!S_ISDIR(stt.st_mode))
		ft_error("cd: not a directory");
	else if (chdir(dir))
		ft_error("cd: unknown error");
	else
	{
		pwd = getcwd(NULL, 0);
		ft_setenv("OLDPWD", ft_getenv("PWD"), 1);
		ft_setenv("PWD", pwd, 1);
		free(pwd);
	}
	return (1);
}
