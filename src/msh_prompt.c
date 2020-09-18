/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 20:51:05 by unite             #+#    #+#             */
/*   Updated: 2020/09/18 04:30:02 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <pwd.h>

const char	*msh_prompt(void)
{
	static char		prompt[MSH_PROMPT_BUFSIZE];
	static char		pwd[PATH_MAX];
	char			*dirname;
	struct passwd	*pws;

	pws = getpwuid(geteuid());
	getcwd(pwd, PATH_MAX);
	dirname = ft_strrchr(pwd, '/') ? ft_strrchr(pwd, '/') + 1 : pwd;
	ft_snprintf(prompt, MSH_PROMPT_BUFSIZE,
		"%s%s %s%s %s%s %s%s%s ",
		ANSI_BGRN, pws->pw_name,
		ANSI_BLU, "::",
		ANSI_BMAG, *dirname ? dirname : "/",
		ANSI_BLU, "$>", ANSI_RESET);
	return (prompt);
}
