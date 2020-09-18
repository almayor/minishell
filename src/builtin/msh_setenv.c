/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:22:56 by unite             #+#    #+#             */
/*   Updated: 2020/09/18 18:35:35 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_alnum_str(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int			msh_setenv(char *const *argv)
{
	if (argv[1] == NULL)
		ft_error("setenv: variable name not specified");
	else if (!is_alnum_str(argv[1]))
		ft_error("setenv: variable name must contain alphanumeric characters");
	else
		ft_setenv(argv[1], argv[2], 1);
	return (1);
}
