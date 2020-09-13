/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:28:49 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 22:44:39 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtok(char *str, const char *sep)
{
	static char	*previous;
	char		*current;
	size_t		i;

	if (str)
		previous = str;
	if (!previous || !*previous)
		return (NULL);
	current = previous;
	i = 0;
	while (current[i])
	{
		if (ft_strchr(sep, current[i]))
		{
			current[i] = '\0';
			previous = current + i + 1;
			return (current);
		}
		i++;
	}
	previous = NULL;
	return (current);
}
