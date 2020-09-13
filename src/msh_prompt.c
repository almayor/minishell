/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 20:51:05 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 22:11:35 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_prompt(void)
{
	static char	buf[MSH_PROMPT_BUFSIZE];
	char		*pwd;
	char		*currdir;

	// pwd = ft_getenv("PWD");
	// currdir = ft_strrchr(pwd, '/') ? ft_strrchr(pwd, '/') + 1 : pwd;
	// ft_snprintf(buf, MSH_PROMPT_BUFSIZE,
	// 	"%s%s%s %s%s%s %s%s%s %s%s%s ",
	// 	ANSI_BGRN, ft_getenv("USER") ? ft_getenv("USER") : "(user)", ANSI_RESET,
	// 	ANSI_BLU, "::", ANSI_RESET,
	// 	ANSI_BMAG, currdir, ANSI_RESET,
	// 	ANSI_BLU, "$>", ANSI_RESET);
	// return (buf);
	return ("$> ");
}
