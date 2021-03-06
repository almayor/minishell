/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:40:49 by unite             #+#    #+#             */
/*   Updated: 2020/09/26 22:34:33 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unsetenv(char *const *argv)
{
	if (ft_tablen(argv) != 2)
		ft_error("unsetenv: too many arguments");
	else if (argv[1] == NULL)
		ft_error("unsetenv: variable name not specified");
	else
		ft_unsetenv(argv[1]);
	return (1);
}
