/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:04:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/26 23:50:00 by unite            ###   ########.fr       */
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

	shlvl_d = ft_getenv("SHLVL") ? ft_atoi(ft_getenv("SHLVL")) : 1;
	ft_sprintf(shlvl, "%i", shlvl_d < 0 || shlvl_d > 99 ? 1 : shlvl_d + 1);
	ft_setenv("SHLVL", shlvl, 1);
}

static void	parse_arguments(int argc, char *const *argv)
{
	size_t	i;

	i = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-d") == 0)
			rl_bind_key('\t', rl_insert);
		else if (ft_strcmp(argv[i], "-c") == 0 && i == argc - 1)
			ft_terminate("-c option requires an argument", 1);
		else if (ft_strcmp(argv[i], "-c") == 0)
		{
			msh_statement(argv[++i]);
			msh_cleanup();
			exit(0);
		}
		i++;
	}
}

int			main(int argc, char *const *argv, char *const *envp)
{
	if (signal(SIGINT, &handler_sigint) ||
		signal(SIGTERM, &handler_sigterm))
		ft_terminate(MSH_ERR_SIGHNDL, 2);
	copy_to_environ(envp);
	init_environ();
	parse_arguments(argc, argv);
	msh_loop();
	msh_cleanup();
}
