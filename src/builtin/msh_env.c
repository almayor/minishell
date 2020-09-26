/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 23:58:32 by unite             #+#    #+#             */
/*   Updated: 2020/09/26 22:35:16 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_env(char *const *argv)
{
	size_t	i;

	if (ft_tablen(argv) > 1)
	{
		ft_error("env: too many arguments");
		return (1);
	}
	i = 0;
	while (g_environ[i])
	{
		ft_printf("%s\n", g_environ[i]);
		i++;
	}
	return (1);
}
