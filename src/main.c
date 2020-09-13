/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:04:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 23:03:13 by unite            ###   ########.fr       */
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

static void	handle_sigint(int sig)
{
	if (g_pid)
		kill(g_pid, sig);
	else
		ft_printf("\n%s", MSH_PROMPT);
}

static void	handle_sigterm(int sig)
{
	if (g_pid)
		kill(g_pid, sig);
	signal(sig, SIG_DFL);
	raise(sig);
}

int			main(int argc, char *const *argv, char *const *envp)
{
	if (signal(SIGINT, &handle_sigint) ||
		signal(SIGTERM, &handle_sigterm))
		ft_terminate(MSH_ERR_SIGHNDL, 2);
	copy_to_environ(envp);
	msh_loop();
	free_environ();
}
