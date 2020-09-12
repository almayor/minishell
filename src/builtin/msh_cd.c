/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:59:33 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 04:15:49 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_directory(const char *dir)
{
	struct stat	stt;

	if (access(dir, F_OK))
		ft_error("no such file or directory");
	else if (stat(dir, &stt))
		ft_error("stat error");
	else if (!S_ISDIR(stt.st_mode))
		ft_error("not a directory");
	else
		return (0);
	return (1);
}

int 		msh_cd(char const *argv[])
{
	char	*dir;

	dir = argv[1] ? argv[1] : ft_getenv("HOME");
	if (!dir)
		ft_error("HOME not set");
	else if (check_directory(argv[1]))
		return (1);
	else if (chdir(argv[1]))
		ft_error("unknown error");
	else
		ft_setenv("PWD", argv[1], 1);
	return (1);
}
