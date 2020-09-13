/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:35:41 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 20:16:35 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	static char	*empty = "";
	size_t		i;
	size_t		len;

	len = ft_strlen(name);
	i = 0;
	while (g_environ[i])
	{
		if (ft_strncmp(g_environ[i], name, len) == 0)
			return (g_environ[i] + len + 1);
		i++;
	}
	return (empty);
}
