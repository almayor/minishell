/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:31:15 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 22:27:28 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unsetenv(const char *name)
{
	size_t	i;
	size_t	j;
	char	**env;

	if (ft_strcmp(ft_getenv(name), "") == 0)
		return (0);
	env = ft_xcalloc(sizeof(char *), ft_tablen(g_environ));
	i = 0;
	j = 0;
	while (g_environ[i])
	{
		if (ft_strncmp(g_environ[i], name, ft_strlen(name)) != 0)
			env[j++] = g_environ[i];
		else
			free(g_environ[i]);
		i++;
	}
	free(g_environ);
	g_environ = env;
	return (-1);
}
