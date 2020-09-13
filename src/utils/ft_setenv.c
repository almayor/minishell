/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:16:04 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 22:22:25 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_string(const char *name, const char *value)
{
	char	*s;
	size_t	len;

	len = ft_strlen(name) + (value ? ft_strlen(value) : 0) + 1;
	s = ft_xmalloc(sizeof(char) * (len + 1));
	ft_strlcat(s, name, len + 1);
	ft_strlcat(s, "=", len + 1);
	if (value)
		ft_strlcat(s, value, len + 1);
	return (s);
}

static void	environ_append(const char *s)
{
	char	**env;
	size_t	i;

	env = ft_xcalloc(sizeof(char *), ft_tablen(g_environ) + 2);
	i = 0;
	while (g_environ[i])
	{
		env[i] = g_environ[i];
		i++;
	}
	env[i] = ft_strdup(s);
	free(g_environ);
	g_environ = env;
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	size_t	i;

	i = 0;
	while (g_environ[i])
	{
		if (ft_strncmp(g_environ[i], name, ft_strlen(name)) == 0)
		{
			if (overwrite)
			{
				free(g_environ[i]);
				g_environ[i] = get_string(name, value);
			}
			return (0);
		}
		i++;
	}
	environ_append(get_string(name, value));
	return (0);
}
