/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:04:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 03:07:00 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_to_environ(char *const *envp)
{
	size_t	i;

	g_environ = ft_xcalloc(sizeof(char *), ft_tablen(envp) + 1);
	i = 0;
	while (envp[i])
	{
		if (!(g_environ[i] = ft_strdup(envp[i])))
			ft_terminate(MSH_ERR_MALLOC, 1);
		i++;
	}
}

static void	handle_nothing(int sig)
{
	ft_printf("Use \"exit\" to leave the shell\n" MSH_PROMPT);
}

int			main(int argc, char *const *argv, char *const *envp)
{
	if (signal(SIGINT, &handle_nothing))
		ft_terminate(MSH_ERR_SIGHNDL, 2);
	copy_to_environ(envp);
	msh_loop();
}
