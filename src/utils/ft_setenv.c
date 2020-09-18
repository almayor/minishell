/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:16:04 by unite             #+#    #+#             */
/*   Updated: 2020/09/18 04:00:17 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_string(const char *name, const char *value)
{
	char	*s;

	if (ft_asprintf(&s, "%s=%s", name, value ? value : "") < 0)
		ft_terminate("bla", 2);
	return (s);
}

static void	environ_append(char *s)
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
	env[i] = s;
	free(g_environ);
	g_environ = env;
}

int			ft_setenv(const char *name, const char *value, int overwrite)
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
