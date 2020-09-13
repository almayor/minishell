/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:28:49 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 01:43:06 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtok_r(char *str, const char *sep, char **lasts)
{
	char		*current;
	size_t		i;

	if (str)
		*lasts = str;
	if (!*lasts || !**lasts)
		return (NULL);
	current = *lasts;
	i = 0;
	while (current[i])
	{
		if (ft_strchr(sep, current[i]))
		{
			current[i] = '\0';
			*lasts = current + i + 1;
			return (current);
		}
		i++;
	}
	*lasts = NULL;
	return (current);
}
