/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:04:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/14 00:51:54 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_environ;
int		g_pid;

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

static void	free_environ(void)
{
	size_t	i;

	i = 0;
	while (g_environ[i])
		free(g_environ[i++]);
	free(g_environ);
}

int			main(int argc, char *const *argv, char *const *envp)
{
	if (signal(SIGINT, &handler_sigint) ||
		signal(SIGTERM, &handler_sigterm))
		ft_terminate(MSH_ERR_SIGHNDL, 2);
	copy_to_environ(envp);
	msh_loop();
	free_environ();
}
