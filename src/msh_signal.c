/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:50:52 by unite             #+#    #+#             */
/*   Updated: 2020/09/14 00:51:58 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int sig)
{
	if (g_pid)
		kill(g_pid, sig);
	else
		ft_printf("\n%s", msh_prompt());
}

void	handler_sigterm(int sig)
{
	if (g_pid)
		kill(g_pid, sig);
	signal(sig, SIG_DFL);
	raise(sig);
}
