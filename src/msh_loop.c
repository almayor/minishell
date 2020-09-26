/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 19:23:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/26 23:49:48 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			msh_loop(void)
{
	char	*line;
	int		status;

	while ((line = readline(msh_prompt())))
	{
		add_history(line);
		status = msh_statement(line);
		free(line);
		if (status == 0)
			return ;
	}
	ft_putchar('\n');
}
