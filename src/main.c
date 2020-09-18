/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:04:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/18 18:29:53 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_environ;
int		g_pid_child;

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

static void	init_environ(void)
{
	static char	shlvl[10];
	int			shlvl_d;

	shlvl_d = ft_atoi(ft_getenv("SHLVL"));
	ft_sprintf(shlvl, "%i", shlvl_d < 0 || shlvl_d > 99 ? 1 : shlvl_d + 1);
	ft_setenv("SHLVL", shlvl, 1);
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
	init_environ();
	msh_loop();
	free_environ();
}
