/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:22:56 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 00:04:57 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_setenv(char *const *argv)
{
	if (argv[1] == NULL)
		ft_error("setenv: variable name not specified");
	else
		ft_setenv(argv[1], argv[2], 1);
	return (1);
}
