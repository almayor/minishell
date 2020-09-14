/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:31:15 by unite             #+#    #+#             */
/*   Updated: 2020/09/14 03:34:17 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unsetenv(const char *name)
{
	size_t	i;
	size_t	j;
	char	**env;
	size_t	len;

	if (!ft_getenv(name))
		return (-1);
	env = ft_xcalloc(sizeof(char *), ft_tablen(g_environ));
	len = ft_strlen(name);
	i = 0;
	j = 0;
	while (g_environ[i])
	{
		if (ft_strncmp(g_environ[i], name, len) != 0)
			env[j++] = g_environ[i];
		else
			free(g_environ[i]);
		i++;
	}
	free(g_environ);
	g_environ = env;
	return (-1);
}
