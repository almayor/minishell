/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:40:49 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 00:05:02 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unsetenv(char *const *argv)
{
	if (argv[1] == NULL)
		ft_error("unsetenv: variable name not specified");
	else
		ft_unsetenv(argv[1]);
	return (1);
}
