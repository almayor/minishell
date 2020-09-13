/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 23:58:32 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 00:04:29 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	msh_env(char *const *argv)
{
	size_t	i;

	i = 0;
	while (g_environ[i])
	{
		ft_printf("%s\n", g_environ[i]);
		i++;
	}
	return (1);
}