/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:50:52 by unite             #+#    #+#             */
/*   Updated: 2020/09/26 23:55:28 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int sig)
{
	if (g_pid_child)
	{
		kill(g_pid_child, sig);
		ft_printf("\n");
	}
	else
		ft_printf("\n%s", msh_prompt());
}

void	handler_sigterm(int sig)
{
	if (g_pid_child)
		kill(g_pid_child, sig);
	signal(sig, SIG_DFL);
	raise(sig);
}
