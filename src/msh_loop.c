/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 19:23:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/26 20:53:43 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			msh_loop(void)
{
	char	*line;
	int		status;

	while ((line = msh_readline(msh_prompt())))
	{
		status = msh_statement(line);
		free(line);
		if (status == 0)
			return ;
	}
	ft_putchar('\n');
}
